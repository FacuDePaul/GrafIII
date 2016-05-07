#pragma once
#include "myEngine_API.h"
#include <d3d9.h>
#include <d3dx9.h>
#include <vector>
#include <map>
#include "Entity.h"

namespace engine{

	class Mesh;
	class Renderer;
	class Animation;
	class Timer;
	class Bone;

	class MYENGINE_API Node : public Entity{

	private:
		D3DXVECTOR3 m_Pos;
		D3DXVECTOR3 m_Sc;
		
		
		std::vector<Mesh*> m_vMeshes;

		void SetBB();
		void GetBBCenter(D3DXVECTOR3* vertices);
		void UpdateTransformation(D3DXMATRIX transformation);

	public:
		Node();
		~Node();

		void Draw(Renderer&);
		void NodeDraw(Renderer&);

		D3DXMATRIX local;
		D3DXMATRIX world;
		D3DXMATRIX defaultMatrix;

		D3DXVECTOR3 m_BoundMin;
		D3DXVECTOR3 m_BoundMax;
		D3DXVECTOR3 m_bbCenter;

		std::vector<Node*> m_vChilds;

		void ReceiveAssimpData(D3DXMATRIX*);
		void AddChild(Node* child);
		void AddMesh(Mesh* child);
		Node* GetChild(int index);
		Node* GetChild(std::string name);
		int GetChildsCount();

		//Skeletal Animation
	private:
		std::map<std::string, Animation*> animations;
		int animationFrame;
		Animation* currentAnimation;

	public:
		Bone* bone;
		void PlayAnim(std::string);
		void PauseAnim(std::string);
		void StopAnim(std::string);
		void ResetAnim(std::string);
		void AddAnimation(Animation*);
		void SetAnimation(std::string);
		void SetAnimation(Animation*);
		Animation* GetAnim(std::string);
		void Update(Timer&) override;
		bool isPlaying();
	};

}