/*! \class CCamera
 *  \brief Classe de base Camera.
 *  \author Benoît Lemaire (aka DaRkWoLf)
 *  \date   05/04/2002
 */

#ifndef __CCAMERA_H__
#define __CCAMERA_H__

#include "CNode.h"
#include "UtilityLib.h"

class CCamera : public CNode
{
	protected:
		float mViewplaneDist;												// Distance du viexplane par rapport à la position de la cam.
        float mViewplaneWidth, mViewplaneHeight;							// Largeur/Hauteur du viewplane.
        CVector3D mCamPos, mVecDir, mUpVec, mRightVec, mViewPlaneUpLeft;	// Position de la camera, direction, vecteur haut, vecteur droite, position haut gauche du viewplane.
                                  		
    public:
        CCamera() {}
		CCamera(CVector3D& vCamPos, CVector3D& vUpVector, int type);
        virtual ~CCamera() {}
		
		CVector3D CalcDirVec(float x, float y, int xRes, int yRes);

		// get
		__forceinline const CVector3D& GetPosition() { return mCamPos; }

		// node raytrace related
		/** Une camera est une Node, elle posséde donc également une classe d'intersection.
		Cependant on se contenter de retourner faux. Mais grâce à cette approche, il est également
		possible d'afficher une camera, par exemple en dessinant une sphere bleue pour les cameras ;) */
		bool IntersectsNode(const CRay& ray, CIntersectInfo *intersectInfo=NULL) { return false; };
};


#endif /* #ifndef __CCAMERA_H__ */