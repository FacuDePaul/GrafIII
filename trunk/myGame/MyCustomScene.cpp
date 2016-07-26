#include "MyCustomScene.h"
#include "Importer.h"
#include "Node.h"

using namespace MyGame;

engine::Node* porsche;

void MyCustomScene::OnStart() {
	porsche = new engine::Node();

	engine::Importer* importer = engine::Importer::GetInstance();
	importer->ImportScene("Porsche.obj", *porsche);

	porsche->SetScale( 20, 20, 20);
}

void MyCustomScene::OnUpdate(engine::Timer * t) {

}

void MyCustomScene::OnShutdown() {
	
}

void MyCustomScene::Draw(engine::Renderer* r) {
	porsche->Draw(*r);
}