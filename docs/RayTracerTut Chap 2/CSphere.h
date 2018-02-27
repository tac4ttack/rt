/*! \class CSphere
 *  \brief Cette classe définie la primitive de base "Sphere" du Raytracer.
 *  \author Benoît Lemaire (aka DaRkWoLf)
 *  \date   05/04/2002
 */

#ifndef __CSPHERE_H__
#define __CSPHERE_H__

#include "CObject.h"

class CSphere : public CObject
{
	private:
		CVector3D	mCenter; // Le centre de la sphére
		float		mRadius; // Le rayon de la sphére

	public:
		// constructeurs et destructeur 
		CSphere() {}
		CSphere(CVector3D center, float radius) : mCenter(center), mRadius(radius) {}
		virtual ~CSphere() {}

		// [hérité de CObject]
		bool IntersectsNode(const CRay& ray, CIntersectInfo *intersectInfo=NULL) ; 
};

#endif /* #ifndef __CSPHERE_H__ */