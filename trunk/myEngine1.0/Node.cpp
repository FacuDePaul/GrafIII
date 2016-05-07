#include "Node.h"
#include "Mesh.h"
#include "Renderer.h"

#include "timer\Timer.h"
#include "animation.h"

#include <iostream>
using namespace engine;


Node::Node() : bone(NULL), currentAnimation(NULL), animationFrame(-1)
{
	D3DXMatrixIdentity(&world);
	D3DXMatrixIdentity(&defaultMatrix);
	D3DXMatrixIdentity(&local);
}

Node::~Node(){
	for (int i = 0; i < m_vChilds.size(); i++) {
		delete m_vChilds[i];
		m_vChilds[i] = NULL;
	}

	for (int i = 0; i < m_vMeshes.size(); i++) {
		delete m_vMeshes[i];
		m_vMeshes[i] = NULL;
	}
}



void Node::ReceiveAssimpData(D3DXMATRIX* mx){
	defaultMatrix = *mx;
}


void Node::Draw(Renderer& r){
	D3DXMatrixIdentity(&world);
	r.SetMatrix(World, &world);
	UpdateTransformation(world);
	NodeDraw(r);
}


void Node::UpdateTransformation(D3DXMATRIX parentWorld){
	D3DXMATRIX translation;
	D3DXMATRIX scalation;
	D3DXMATRIX rotx;
	D3DXMATRIX roty;
	D3DXMATRIX rotz;

	D3DXMatrixIdentity(&local);

	// translation
	D3DXMatrixTranslation(&translation, m_position.x + pivot.x, m_position.y + pivot.y, m_position.z + pivot.z);
	D3DXMatrixMultiply(&local, &translation, &local);


	//	rotation
	D3DXMatrixRotationX(&rotx, _RotX);
	D3DXMatrixRotationY(&roty, _RotY);
	D3DXMatrixRotationZ(&rotz, _RotZ);

	D3DXMatrixMultiply(&local, &rotx, &local);
	D3DXMatrixMultiply(&local, &roty, &local);
	D3DXMatrixMultiply(&local, &rotz, &local);

	
	// scalation
	D3DXMatrixScaling(&scalation, _ScaleX, _ScaleY, _ScaleZ);
	D3DXMatrixMultiply(&local, &scalation, &local);

	if (!isPlaying()) {
		D3DXMatrixMultiply(&local, &local, &defaultMatrix);
	} else {
		D3DXMATRIX frame = currentAnimation->GetMatrix(animationFrame);
		D3DXMatrixMultiply(&local, &local, &frame);
	}


	D3DXMatrixMultiply(&world, &local, &parentWorld);

	if (bone != NULL) {
		// TO-DO.
	}

	if (m_vChilds.size() > 0){
		for (int i = 0; i <m_vChilds.size(); i++){
			m_vChilds[i]->UpdateTransformation(world);
		}
	}

	SetBB();
}


void Node::NodeDraw(Renderer& r){
	if (r.m_frustum->CheckCube(m_bbCenter.x, m_bbCenter.y, m_bbCenter.z, D3DXVec3Length(&(m_bbCenter - m_BoundMax)))){
		//std::cout << GetName() <<"   " << D3DXVec3Length(&(m_bbCenter - m_BoundMax)) << std::endl;
		// Chech Center & bounds max
		if (m_vChilds.size() > 0){
			for (int i = 0; i < m_vChilds.size(); i++){
				m_vChilds[i]->NodeDraw(r);
			}
		}

		if (m_vMeshes.size() > 0){
			for (int i = 0; i < m_vMeshes.size(); i++){
				r.SetMatrix(World, &world);
				m_vMeshes[i]->Draw();
			}
		}
	}
	else{
		//std::cout << D3DXVec3Length(&(m_bbCenter - m_BoundMax)) << std::endl;
		// Never enters here!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		std::cout << GetName() + " is not drawn." << std::endl;
	}
}

void Node::AddChild(Node* child){
	m_vChilds.push_back(child);
}

void Node::AddMesh(Mesh* child){
	m_vMeshes.push_back(child);
}


Node* Node::GetChild(int index){
	if (m_vChilds.empty())
		return this;

	index = index > m_vChilds.size() ? m_vChilds.size() - 1 : index;
	index = index < 0 ? 0 : index;
	return m_vChilds[index];
}



Node* Node::GetChild(std::string name){
	if (m_vChilds.empty())
		return this;

	for (short i = 0; i < m_vChilds.size(); i++){
		if (m_vChilds[i]->GetName() == name)
			return m_vChilds[i];
	}

	return this;
}



int Node::GetChildsCount(){
	if (m_vChilds.empty())
		return -1;
	return m_vChilds.size();
}


void Node::SetBB(){
	if (!m_vMeshes.empty()){
		D3DXVECTOR3 v_vertices[8];
		GetBBCenter(m_vMeshes[0]->m_pBB);
		for (int i = 0; i < 8; i++)
			D3DXVec3TransformCoord(&v_vertices[0], &m_vMeshes[0]->m_pBB[i], &world);

		m_BoundMax = v_vertices[0];

		for (int i = 1; i < 8; i++){
			// X
			if (v_vertices[i].x > m_BoundMax.x)
				m_BoundMax.x = v_vertices[i].x;

			// Y
			if (v_vertices[i].y > m_BoundMax.y)
				m_BoundMax.y = v_vertices[i].y;

			// Z
			if (v_vertices[i].z > m_BoundMax.z)
				m_BoundMax.z = v_vertices[i].z;
		}
	}
	else if (!m_vChilds.empty()){

		for (int i = 0; i < m_vChilds.size(); i++){
			D3DXVECTOR3 vChildMax = m_vChilds[i]->m_BoundMax;

			if (vChildMax.x > m_BoundMax.x)
				m_BoundMax.x = vChildMax.x;

			if (vChildMax.y > m_BoundMax.y)
				m_BoundMax.y = vChildMax.y;

			if (vChildMax.z > m_BoundMax.z)
				m_BoundMax.z = vChildMax.z;
		}
	}
}



void Node::GetBBCenter(D3DXVECTOR3* vertices){
	for (int i = 0; i < 8; i++){
		m_bbCenter += vertices[i];
	}

	m_bbCenter /= 8;
}

void Node::Update(Timer& t) {
	if (currentAnimation != NULL) {
		currentAnimation->Update(t.timeBetweenFrames());
	}
}

void Node::AddAnimation(Animation* animation) {
	if (!animations.count(animation->GetName())) {
		animations[animation->GetName()] = animation;
	}
}

void Node::SetAnimation(std::string anim) {
	if (animations.count(anim)) {
		Animation* animation = animations[anim];
		SetAnimation(animation);
	}
}

void Node::SetAnimation(Animation* anim) {
	if (currentAnimation != NULL)
		currentAnimation->Stop();
	currentAnimation = anim;
	animationFrame = currentAnimation->GetFrameIndex(this->GetName());
	for (int i = 0; i < GetChildsCount(); i++) {
		m_vChilds[i]->SetAnimation(anim);
	}
}

bool Node::isPlaying() {
	if (currentAnimation != NULL)
		if (currentAnimation->GetState() == Animation::State::PLAY)
			if (animationFrame != -1)
				return true;

	return false;
}

Animation* Node::GetAnim(std::string anim) {
	if (animations.count(anim)) {
		return animations[anim];
	}

	return NULL;
}

void Node::PlayAnim(std::string name) {
	if (animations.count(name)) {
		if (currentAnimation != animations[name])
			SetAnimation(name);
		else currentAnimation->Play();
	}
}

void Node::PauseAnim(std::string name){
	if (animations.count(name)) {
		if (currentAnimation != animations[name])
			SetAnimation(name);
		else currentAnimation->Pause();
	}
}

void Node::StopAnim(std::string name){
	if (animations.count(name)) {
		if (currentAnimation != animations[name])
			SetAnimation(name);
		else currentAnimation->Stop();
	}
}
void Node::ResetAnim(std::string name){
	if (animations.count(name)) {
		if (currentAnimation != animations[name])
			SetAnimation(name);
		else currentAnimation->Reset();
	}
}