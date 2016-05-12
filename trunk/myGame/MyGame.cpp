#include "MyGame.h"
#include "animation.h"
#include "Scene.h"
#include "Importer.h"
#include "MyCustomScene.h"
#include <iostream>

using namespace MyGame;
float mSpeed = 0.1f;


bool Game::Init(engine::Renderer& r){
	mainCamera = r.c;
	mainCamera->SetPosition(&D3DXVECTOR3(0, 0, -200));
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

	car = new engine::Node();
	if (importer->ImportScene("./Tiny.x", *car)){
		car->SetPos(0.0f, 0.0f, 100.0f);
		car->SetScale(1.0f, 1.0f, 1.0f);
	}
	else{
		delete car;
		car = NULL;
	}

	return true;
}


void Game::Frame(engine::Renderer& r, engine::DirectInput& dInput, engine::Timer& timer){

	// Camera Update 

	if(dInput.keyDown(engine::Input::KEY_UP) || dInput.keyDown(engine::Input::KEY_W)){
		mainCamera->MoveForward(mSpeed * timer.timeBetweenFrames());
	}

	if(dInput.keyDown(engine::Input::KEY_DOWN) || dInput.keyDown(engine::Input::KEY_S)){
		mainCamera->MoveForward(-mSpeed * timer.timeBetweenFrames());
	}

	if(dInput.keyDown(engine::Input::KEY_LEFT) || dInput.keyDown(engine::Input::KEY_A)){
		mainCamera->Strafe(-mSpeed * timer.timeBetweenFrames());
	}

	if(dInput.keyDown(engine::Input::KEY_RIGHT) || dInput.keyDown(engine::Input::KEY_D)){
		mainCamera->Strafe(mSpeed * timer.timeBetweenFrames());
	}

	if (dInput.mouseDown(engine::Input::MB_1)){
		mainCamera->Yaw(dInput.mouseRelPosX() * mSpeed / 200 * timer.timeBetweenFrames());
		mainCamera->Pitch(dInput.mouseRelPosY() * mSpeed / 200 * timer.timeBetweenFrames());
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
	
	car->Update(timer);
	car->PlayAnim("");

	if (car != NULL)
		car->Draw(r);
}


void Game::DeInit(){
	if (mesh){
		delete mesh;
		mesh = NULL;
	}

	if (pig){
		delete pig;
		pig = NULL;
	}

	if (car){
		delete car;
		car = NULL;
	}
}
