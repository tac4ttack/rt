/*! \class CSphere
 *  \brief Cette classe d�finie la primitive de base "Sphere" du Raytracer.
 *  \author Beno�t Lemaire (aka DaRkWoLf)
 *  \date   05/04/2002
 */

#ifndef __CSPHERE_H__
#define __CSPHERE_H__

#include "CObject.h"

class CSphere : public CObject
{
	private:
		CVector3D	mCenter; // Le centre de la sph�re
		float		mRadius; // Le rayon de la sph�re

	public:
		// constructeurs et destructeur 
		CSphere() {}
		CSphere(CVector3D center, float radius) : mCenter(center), mRadius(radius) {}
		virtual ~CSphere() {}

		// [h�rit� de CObject]
		bool IntersectsNode(const CRay& ray, CIntersectInfo *intersectInfo=NULL) ; 
};

#endif /* #ifndef __CSPHERE_H__ */