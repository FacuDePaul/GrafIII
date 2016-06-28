#pragma once
#include "myEngine_API.h"
#include <vector>
#include <string>
#include <d3dx9.h>


namespace engine {
	class Node;
	class Renderer;
	
	class NodeBSP {
	public:
		NodeBSP(D3DXPLANE plane, D3DXVECTOR3 point);
		virtual ~NodeBSP();

		NodeBSP* m_pFrontNode;
		NodeBSP* m_pBackNode;

		D3DXPLANE m_Plane;
		D3DXVECTOR3 m_PlanePoint;

		std::vector<Node*> m_vBackObjects;
		std::vector<Node*> m_vFrontObjects;

		enum Position
		{
			BACK, FRONT, INSIDE
		};
		Position GetPosition(D3DXVECTOR3 BoundingBox[]);
		Position GetPosition(D3DXVECTOR3 Position);

		friend class Node;
		void AddNode(NodeBSP*);
		void Draw(Renderer* pRenderer, D3DXVECTOR3 CameraPos);
		void AddChild(Node*);
		std::string Name;
	};
}

