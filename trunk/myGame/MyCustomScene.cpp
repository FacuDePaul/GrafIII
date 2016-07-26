#include "MyCustomScene.h"
#include "Importer.h"
#include "Node.h"

using namespace MyGame;

engine::Node* porsche;

void MyCustomScene::OnStart() {
	porsche = new engine::Node();

	engine::Importer* importer = engine::Importer::GetInstance();
	importer->ImportScene("Porsche.obj", *porsche);

	porsche->SetScale( 100, 100, 100);
	porsche->SetPos(100, 0, 0);
}

void MyCustomScene::OnUpdate(engine::Timer * t) {

}

void MyCustomScene::Draw(engine::Renderer* r) {
	porsche->Draw(*r);
}

void MyCustomScene::OnShutdown() {
	delete porsche;
	porsche = NULL;
}

