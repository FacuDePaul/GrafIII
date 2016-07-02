#include "MyGame.h"
#include "animation.h"
#include "Scene.h"
#include "Importer.h"
#include "MyCustomScene.h"
#include <iostream>

using namespace MyGame;
float mSpeed = 0.1f;


engine::Node* bsp;

bool Game::Init(engine::Renderer& r){
	mainCamera = r.c;
	mainCamera->SetPosition(0, 0, -200);
	CreateScene("Scene1");
	engine::Scene* scene1 = GetScene("Scene1");

	MyCustomScene* mcs = new MyCustomScene("MyCustomSceneYAY");
	AddScene(mcs);

	engine::Importer* importer = engine::Importer::GetInstance();

	//importer->ImportScene(*scene1, "scene1.xml");
	/*
	plane = new engine::Mesh(r, true);
	importer->ImportMesh(*plane, "Porsche.obj");
	mesh = new engine::Cube(r);
	*/
	r.SetBackgroundColor(0, 0, 0);

	wolf = new engine::Node();
	if (importer->ImportScene("./tiny/tiny.x", *wolf)){
		wolf->SetAnimation("");
		wolf->SetPos(0.0f, 0.0f, 100.0f);
		wolf->SetScale(1.0f, 1.0f, 1.0f);
	}
	else{
		delete wolf;
		wolf = NULL;
	}

	bsp = new engine::Node();
	importer->ImportScene("bspscene.3ds", *bsp);

	AddToBSPTree(*bsp, true, true);

	return true;
}


void Game::Frame(engine::Renderer& r, engine::DirectInput& dInput, engine::Timer& timer){

	engine::Game::Frame(r, dInput, timer);

	if(dInput.keyDown(engine::Input::KEY_UP) || dInput.keyDown(engine::Input::KEY_W)){
		mainCamera->MoveForward(mSpeed * timer.timeBetweenFrames());
	}

	if(dInput.keyDown(engine::Input::KEY_DOWN) || dInput.keyDown(engine::Input::KEY_S)){
		mainCamera->MoveForward(-mSpeed * timer.timeBetweenFrames());
	}

	if(dInput.keyDown(engine::Input::KEY_LEFT) || dInput.keyDown(engine::Input::KEY_A)){
		mainCamera->MoveRight(-mSpeed * timer.timeBetweenFrames());
	}

	if(dInput.keyDown(engine::Input::KEY_RIGHT) || dInput.keyDown(engine::Input::KEY_D)){
		mainCamera->MoveRight(mSpeed * timer.timeBetweenFrames());
	}

	if (dInput.mouseDown(engine::Input::MB_1)){
		mainCamera->Yaw(dInput.mouseRelPosX() * mSpeed / 200 * timer.timeBetweenFrames());
		//mainCamera->Pitch(dInput.mouseRelPosY() * mSpeed / 200 * timer.timeBetweenFrames());
	}

	

	if(dInput.keyDown(engine::Input::KEY_SPACE)){
		mainCamera->MoveUp(mSpeed * timer.timeBetweenFrames());
	}

	if(dInput.keyDown(engine::Input::KEY_LCONTROL)){
		mainCamera->MoveUp(-mSpeed * timer.timeBetweenFrames());
	}

	if(dInput.keyDown(engine::Input::KEY_E)){
		mainCamera->Roll(-mSpeed / 100 * timer.timeBetweenFrames());
	}

	if(dInput.keyDown(engine::Input::KEY_Q)){
		mainCamera->Roll(mSpeed / 100 * timer.timeBetweenFrames());
	}

	if (dInput.keyDown(engine::Input::KEY_ESCAPE))
		setGame(false);
	
	

	if (wolf != NULL)
	{
		wolf->Update(timer);
		wolf->Draw(r);
	}
		
}


void Game::DeInit(){
	if (mesh){
		delete mesh;
		mesh = NULL;
	}

	if (wolf){
		delete wolf;
		wolf = NULL;
	}
}
