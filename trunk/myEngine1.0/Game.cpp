#include "Game.h"
#include "Scene.h"
#include "Node.h"
#include "NodeBSP.h"
#include "Renderer.h"
#include "Camera.h"
using namespace engine;

Game::~Game(){
	for (m_mIterator = m_mapa.begin(); m_mIterator != m_mapa.end(); m_mIterator++) {
		delete m_mIterator->second;
	}
}


void Game::DrawScenes(Renderer* m_pRender, Timer* timer){
	m_mIterator = m_mapa.begin();
	do{
		m_mIterator->second->Update(timer);
		m_mIterator->second->Draw(m_pRender);
		m_mIterator++;
	} while (m_mIterator != m_mapa.end());
}


void Game::CreateScene(std::string str){
	Scene * escena = new Scene(str);
	//m_mapa[str] = escena;
	AddScene(escena);
}


Scene* Game::GetScene(std::string str){
	for (m_mIterator = m_mapa.begin(); m_mIterator != m_mapa.end(); m_mIterator++)
	{
		if (m_mIterator->first == str)
			return m_mIterator->second;
	}
	return NULL;
}


void Game::OnSceneInit(){
	m_mIterator = m_mapa.begin();
	do {
		m_mIterator->second->OnStart();
		m_mIterator++;
	} while (m_mIterator != m_mapa.end());
}


void Game::OnSceneUpdate(Timer* t){
	m_mIterator = m_mapa.begin();
	do {
		m_mIterator->second->OnUpdate(t);
		m_mIterator++;
	} while (m_mIterator != m_mapa.end());
}


void Game::OnSceneShutdown(){
	m_mIterator = m_mapa.begin();
	do {
		m_mIterator->second->OnShutdown();
		m_mIterator++;
	} while (m_mIterator != m_mapa.end());
}

void Game::Frame(engine::Renderer& r, engine::DirectInput&, engine::Timer&) {
	if (BSP != NULL) {

		for (int i = 0; i < ParentNodes.size(); i++) {
			ParentNodes[i]->Draw(r);
		}

		BSP->Draw(&r, r.c->m_Position);
	}
}

void Game::AddScene(Scene* newScene){

	if (newScene == NULL)
		return;

	if (newScene->GetName() == ""){
		newScene->SetName("NewScene-" + (m_mapa.size() + 1));
	}

	m_mapa[newScene->GetName()] = newScene;
}

void Game::AddNodeToBSP(Node* node) {
	if (node->isPlane)
		AddBSPPlane(node);

	NodesToBSP.push_back(node);
	for (int i = 0; i < node->m_vChilds.size(); i++) {
		AddNodeToBSP(node->m_vChilds[i]);
	}
}

//----------------------------------------------------
void Game::AddBSPPlane(Node* pNode) {
	D3DXPLANE plane = pNode->GetPlane();
	D3DXVECTOR3 point(pNode->world._41, pNode->world._42, pNode->world._43);
	NodeBSP* bspnode = new NodeBSP(plane, point);
	BSPNodes.push_back(bspnode);
	bspnode->Name = pNode->GetName();
}
//----------------------------------------------------
void Game::RegisterInBSPtree(Node* node, bool isBSP) {
	D3DXMATRIX identity;
	D3DXMatrixIdentity(&identity);
	node->UpdateTransformation(identity);
	if (!isBSP)
		ParentNodes.push_back(node);
	else {
		AddNodeToBSP(node);
	}
}
//----------------------------------------------------
void Game::ArrangeBSPTree() {
	if (NodesToBSP.size() != 0) {
		BSP = BSPNodes[0];
		for (int i = 1; i < BSPNodes.size(); i++) {
			if (BSPNodes[i] != NULL)
				BSP->AddNode(BSPNodes[i]);
		}
		for (int i = 0; i < NodesToBSP.size(); i++) {
			if (NodesToBSP[i]->m_vMeshes.size())
				BSP->AddChild(NodesToBSP[i]);
		}
	}

	BSPNodes.clear();
	NodesToBSP.clear();
}
