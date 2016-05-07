#pragma once
#include "myEngine_API.h"
#include <d3dx10math.h>


namespace engine{
	class Renderer;
	class MYENGINE_API Frustum{
	public:
		Frustum(Renderer*);
		~Frustum();

		void ConstructFrustum(float, D3DXMATRIX, D3DXMATRIX);

		bool CheckCube(float, float, float, float);
		bool CheckSphere(float, float, float, float);

	private:
		Renderer* _r;
		D3DXPLANE m_planes[6];
	};

}
