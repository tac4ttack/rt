#include "CTargetCamera.h"

CTargetCamera::CTargetCamera(CVector3D& camPos, CVector3D& lookAtPoint, CVector3D& upVector) : CCamera( camPos, upVector, TARGETCAMERA )
{
	mLookAtPoint = lookAtPoint;
                                  
	// Nous calculons le vecteur directeur de la camera
	mVecDir = (mLookAtPoint - camPos);
	mVecDir.Normalize();
                                  
	// Maintenant nous calculons le vecteur droite (en utilisant le produit en croix)
	mRightVec = (mUpVec * mVecDir);
                    
	// De meme pour le "vrai" vecteur haut.
	mUpVec = (mVecDir * mRightVec);
                                  
	// Maintenant nous avons toutes les informations pour détérminer la position 
	// en haut à gauche du viewplane.
	mViewPlaneUpLeft = camPos + ((mVecDir*mViewplaneDist)+(mUpVec*(mViewplaneHeight/2.0f)))-(mRightVec*(mViewplaneWidth/2.0f));
}
