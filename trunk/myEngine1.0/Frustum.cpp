#include "Frustum.h"
#include "Renderer.h"
using namespace engine;

Frustum::Frustum(Renderer* r){
	_r = r;
}

Frustum::~Frustum(){

}

void Frustum::ConstructFrustum(){

	D3DXMATRIX matrix;
	D3DXMATRIX viewMatrix;
	D3DXMATRIX projectionMatrix;
	_r->d3d_dev->GetTransform(D3DTS_VIEW, &viewMatrix);
	_r->d3d_dev->GetTransform(D3DTS_PROJECTION, &projectionMatrix);

	// Combino las matrices
	D3DXMatrixMultiply(&matrix, &viewMatrix, &projectionMatrix);
	// left plane
	m_planes[0].a = matrix._14 + matrix._11;
	m_planes[0].b = matrix._24 + matrix._21;
	m_planes[0].c = matrix._34 + matrix._31;
	m_planes[0].d = matrix._44 + matrix._41;
	
	// right plane
	m_planes[1].a = matrix._14 - matrix._11;
	m_planes[1].b = matrix._24 - matrix._21;
	m_planes[1].c = matrix._34 - matrix._31;
	m_planes[1].d = matrix._44 - matrix._41;
	
	// bottom plane
	m_planes[2].a = matrix._14 + matrix._12;
	m_planes[2].b = matrix._24 + matrix._22;
	m_planes[2].c = matrix._34 + matrix._32;
	m_planes[2].d = matrix._44 + matrix._42;

	// top plane
	m_planes[3].a = matrix._14 - matrix._12;
	m_planes[3].b = matrix._24 - matrix._22;
	m_planes[3].c = matrix._34 - matrix._32;
	m_planes[3].d = matrix._44 - matrix._42;

	// near plane
	m_planes[4].a = matrix._13;
	m_planes[4].b = matrix._23;
	m_planes[4].c = matrix._33;
	m_planes[4].d = matrix._43;

	// far plane
	m_planes[5].a = matrix._14 - matrix._13;
	m_planes[5].b = matrix._24 - matrix._23;
	m_planes[5].c = matrix._34 - matrix._33;
	m_planes[5].d = matrix._44 - matrix._43;

	// normalize planes
	for (unsigned int i = 0; i<6; i++){
		D3DXPlaneNormalize(&m_planes[i], &m_planes[i]);
	}
}



bool Frustum::CheckCube(D3DXVECTOR3* pVertex){
	for (int i = 0; i < 6; i++){
		if (D3DXPlaneDotCoord(&m_planes[i], &pVertex[0]) >= 0.0f)continue;
		if (D3DXPlaneDotCoord(&m_planes[i], &pVertex[1]) >= 0.0f)continue;
		if (D3DXPlaneDotCoord(&m_planes[i], &pVertex[2]) >= 0.0f)continue;
		if (D3DXPlaneDotCoord(&m_planes[i], &pVertex[3]) >= 0.0f)continue;
		if (D3DXPlaneDotCoord(&m_planes[i], &pVertex[4]) >= 0.0f)continue;
		if (D3DXPlaneDotCoord(&m_planes[i], &pVertex[5]) >= 0.0f)continue;
		if (D3DXPlaneDotCoord(&m_planes[i], &pVertex[6]) >= 0.0f)continue;
		if (D3DXPlaneDotCoord(&m_planes[i], &pVertex[7]) >= 0.0f)continue;
		return false;
	}
	return true;
}
