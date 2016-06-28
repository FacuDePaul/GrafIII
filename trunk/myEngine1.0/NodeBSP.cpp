#include "NodeBSP.h"
#include "Renderer.h"
#include "Node.h"

void NodeBSP::AddNode(NodeBSP* pNode) {
	if (pNode == NULL) return;

	NodeBSP::Position pos = GetPosition(pNode->m_PlanePoint);

	if (pos == BACK) {
		if (m_pBackNode == NULL) {
			m_pBackNode = pNode;
		}
		else {
			m_pBackNode->AddNode(pNode);
		}
	}
	else {
		if (m_pFrontNode == NULL) {
			m_pFrontNode = pNode;
		}
		else {
			m_pFrontNode->AddNode(pNode);
		}
	}
}
//----------------------------------------------------------------------
void NodeBSP::AddChild(Node * node) {
	if (node == NULL) return;

	NodeBSP::Position pos = GetPosition(node->m_vBB);

	if (pos == BACK){
		if (m_pBackNode == NULL) {
			m_vBackObjects.push_back(node);
		}
		else {
			m_pBackNode->AddChild(node);
		}
	}
	else if (pos == FRONT) {
		if (m_pFrontNode == NULL) {
			m_vFrontObjects.push_back(node);
		}
		else {
			m_pFrontNode->AddChild(node);
		}
	}
	else if (pos == INSIDE) {
		if (m_pFrontNode == NULL) {
			m_vFrontObjects.push_back(node);
		}
		else {
			m_pFrontNode->AddChild(node);
		}
		if (m_pBackNode == NULL) {
			m_vBackObjects.push_back(node);
		}
		else {
			m_pBackNode->AddChild(node);
		}
	}
}
//---------------------------------------------------------------------------------------
void NodeBSP::Draw(Renderer* pRenderer, D3DXVECTOR3 vCameraPos) {
	NodeBSP::Position pos = GetPosition(vCameraPos);
	if (pos == BACK) {
		if (m_pBackNode == NULL) {
			for (int i = 0; i < m_vBackObjects.size(); i++) {
				m_vBackObjects[i]->DrawMeshes(pRenderer);
			}
		}
		else {
			m_pBackNode->Draw(pRenderer, vCameraPos);
		}
	}
	else if (pos == FRONT) {
		if (m_pFrontNode == NULL) {
			for (int i = 0; i < m_vFrontObjects.size(); i++) {
				m_vFrontObjects[i]->DrawMeshes(pRenderer);
			}
		}
		else {
			m_pFrontNode->Draw(pRenderer, vCameraPos);
		}
	}
}
//---------------------------------------------------------------------------------------
NodeBSP::Position NodeBSP::GetPosition(D3DXVECTOR3 pos) {
	float distance = D3DXPlaneDotCoord(&m_Plane, &pos);
	if (distance > 0) {
		return FRONT;
	}
	else if (distance == 0) {
		return INSIDE;
	}
	else {
		return BACK;
	}
}
//---------------------------------------------------------------------------------------
NodeBSP::Position NodeBSP::GetPosition(D3DXVECTOR3 BoundingBox[]) {
	Position aux;
	aux = GetPosition(BoundingBox[0]);
	for (int i = 1; i < 8; i++) {
		// 2 points en posiciones distintas... Inside!
		if (aux != GetPosition(BoundingBox[i])) {
			return INSIDE;
		}
	}
	return aux;
}
//----------------------------------------------------------------------
NodeBSP::NodeBSP(D3DXPLANE plane, D3DXVECTOR3 point) {
	m_Plane = plane;
	m_PlanePoint = point;
	m_pBackNode = NULL;
	m_pFrontNode = NULL;
}
//----------------------------------------------------------------------
NodeBSP::~NodeBSP() {
	if (m_pFrontNode) {
		delete m_pFrontNode;
	}
	if (m_pBackNode) {
		delete m_pBackNode;
	}
}