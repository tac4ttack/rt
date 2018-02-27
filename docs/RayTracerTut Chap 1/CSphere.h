/*! \class CSphere
 *  \brief Cette classe définie la primitive de base "Sphere" du Raytracer.
 *  \author Benoît Lemaire (aka DaRkWoLf)
 *  \date   06/02/2002
 */

#ifndef __CSPHERE_H__
#define __CSPHERE_H__

#include "CObject.h"

class CSphere : public CObject
{
	private:
		CVector3D	m_Center; // Le centre de la sphére
		float		m_Radius; // Le rayon de la sphére

	public:
		// constructeurs et destructeur 
		CSphere() {}
		CSphere(CVector3D center, float radius) : m_Center(center), m_Radius(radius) {}
		virtual ~CSphere() {}

		// [hérité de CObject]
		bool IntersectsNode(const CRay& ray, CIntersectInfo *intersectInfo=NULL) ; 
};

#endif /* #ifndef __CSPHERE_H__ */