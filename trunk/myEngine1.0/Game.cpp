#include "Game.h"
#include "Scene.h"
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


void Game::AddScene(Scene* newScene){

	if (newScene == NULL)
		return;

	if (newScene->GetName() == ""){
		newScene->SetName("NewScene-" + (m_mapa.size() + 1));
	}

	m_mapa[newScene->GetName()] = newScene;
}