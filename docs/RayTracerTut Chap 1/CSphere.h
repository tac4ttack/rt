/*! \class CSphere
 *  \brief Cette classe d�finie la primitive de base "Sphere" du Raytracer.
 *  \author Beno�t Lemaire (aka DaRkWoLf)
 *  \date   06/02/2002
 */

#ifndef __CSPHERE_H__
#define __CSPHERE_H__

#include "CObject.h"

class CSphere : public CObject
{
	private:
		CVector3D	m_Center; // Le centre de la sph�re
		float		m_Radius; // Le rayon de la sph�re

	public:
		// constructeurs et destructeur 
		CSphere() {}
		CSphere(CVector3D center, float radius) : m_Center(center), m_Radius(radius) {}
		virtual ~CSphere() {}

		// [h�rit� de CObject]
		bool IntersectsNode(const CRay& ray, CIntersectInfo *intersectInfo=NULL) ; 
};

#endif /* #ifndef __CSPHERE_H__ */