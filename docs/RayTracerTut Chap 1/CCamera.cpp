#include "CCamera.h"

CCamera::CCamera(CVector3D& vCamPos, CVector3D& vUpVector)
{
	m_camPos			= vCamPos;
	m_upVec				= vUpVector;
	m_viewplaneDist		= 1.0f;
	m_viewplaneHeight	= 0.35f;
	m_viewplaneWidth	= 0.5f;
	
}

CVector3D CCamera::CalcDirVec(float x, float y, int xRes, int yRes)
{
	float xIndent, yIndent;
                                  
	xIndent = m_viewplaneWidth / (float)xRes;
	yIndent = m_viewplaneHeight /  (float)yRes;
                                  
	return (m_viewPlaneUpLeft + m_rightVec*xIndent*x - m_upVec*yIndent*y) -  GetPosition();
}

                             
