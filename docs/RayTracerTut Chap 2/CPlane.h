/*! \class CPlane
 *  \brief Cette classe definie la primitive PLAN.
 *  \author Benoît Lemaire (aka DaRkWoLf)
 *  \date   05/04/2002
 */

#ifndef __CPLANE_H__
#define __CPLANE_H__

#include "CObject.h"

class CPlane : public CObject
{
	private:
		CVector3D	mNormal;
		CVector3D	mPointPlane;
                                  		
	public:
		CPlane() {}
		CPlane(const CVector3D& pointplane, const CVector3D& normal);
		CPlane(const CVector3D& point1, const CVector3D& point2, const CVector3D& point3);
		virtual ~CPlane() {}

		// [CNode inherited]
		bool IntersectsNode(const CRay& ray, CIntersectInfo *intersectInfo=NULL);
};

#endif /* #ifndef __CPLANE_H__ */