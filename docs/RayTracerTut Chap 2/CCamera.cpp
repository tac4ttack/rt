#include "CCamera.h"

CCamera::CCamera(CVector3D& vCamPos, CVector3D& vUpVector, int type) : CNode(CAMERA, "CAMERA")
{
	mCamPos			= vCamPos;
	mUpVec				= vUpVector;
	mViewplaneDist		= 1.0f;
	mViewplaneHeight	= 0.35f;
	mViewplaneWidth	= 0.5f;
	
}

CVector3D CCamera::CalcDirVec(float x, float y, int xRes, int yRes)
{
	float xIndent, yIndent;
                                  
	xIndent = mViewplaneWidth / (float)xRes;
	yIndent = mViewplaneHeight /  (float)yRes;
                                  
	return (mViewPlaneUpLeft + mRightVec*xIndent*x - mUpVec*yIndent*y) -  GetPosition();
}

                             
