#include "NodeBSP.h"
#include "Renderer.h"
#include "Node.h"

using namespace engine;

NodeBSP::NodeBSP(D3DXPLANE plane, D3DXVECTOR3 point) :m_Plane(plane), m_PlanePoint(point), m_pFrontNode(NULL), m_pBackNode(NULL)
{

}

NodeBSP::~NodeBSP() {
	if (m_pFrontNode) {
		delete m_pFrontNode;
		m_pFrontNode = NULL;
	}
	if (m_pBackNode) {
		delete m_pBackNode;
		m_pBackNode = NULL;
	}
}

void NodeBSP::AddNode(NodeBSP* pNode) {
	if (pNode)
	{
		if (GetPointPos(pNode->m_PlanePoint) == BACK)
			if (m_pBackNode == NULL)
				m_pBackNode = pNode;
			else
				m_pBackNode->AddNode(pNode);
		else
			if (m_pFrontNode == NULL)
				m_pFrontNode = pNode;
			else
				m_pFrontNode->AddNode(pNode);
	}
}

void NodeBSP::AddChild(Node * pNode) {
	if (pNode)
	{
		NodeBSP::Position pos = GetBoxPos(pNode->m_vBB);
		if (pos == BACK)
			if (!m_pBackNode)
				m_vBackObjects.push_back(pNode);
			else
				m_pBackNode->AddChild(pNode);
		else if (pos == FRONT)
			if (!m_pFrontNode)
				m_vFrontObjects.push_back(pNode);
			else
				m_pFrontNode->AddChild(pNode);
		else if (pos == OVERLAP)
			if (!m_pFrontNode)
				m_vFrontObjects.push_back(pNode);
			else
				m_pFrontNode->AddChild(pNode);
			if (!m_pBackNode)
				m_vBackObjects.push_back(pNode);
			else
				m_pBackNode->AddChild(pNode);
	}
}

void NodeBSP::Draw(Renderer& r, D3DXVECTOR3 vCameraPos) {
	Position pos = GetPointPos(vCameraPos);
	if (pos == BACK)
		if (!m_pBackNode)
			for (int i = 0; i < m_vBackObjects.size(); i++)
				m_vBackObjects[i]->DrawMeshes(r);
		else
			m_pBackNode->Draw(r, vCameraPos);
	else if (pos == FRONT)
		if (!m_pFrontNode)
			for (int i = 0; i < m_vFrontObjects.size(); i++)
				m_vFrontObjects[i]->DrawMeshes(r);
		else
			m_pFrontNode->Draw(r, vCameraPos);
}

NodeBSP::Position NodeBSP::GetPointPos(D3DXVECTOR3& point) {
	float distance = D3DXPlaneDotCoord(&m_Plane, &point);
	if (distance >= 0)
		return FRONT;
	else
		return BACK;
}

NodeBSP::Position NodeBSP::GetBoxPos(D3DXVECTOR3 Box[]) {
	Position pos = GetPointPos(Box[0]);
	for (int i = 1; i < 8; i++)
		if (pos != GetPointPos(Box[i]))
			return OVERLAP;
	return pos;
}