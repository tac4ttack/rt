/*! \class CObject
 *  \brief Cette classe est la classe de base pour toutes les primitives implementées dans le raytracer
 *  : spheres, plans, cônes ...
 *  \author Benoît Lemaire (aka DaRkWoLf)
 *  \date   05/04/2002
 */

#ifndef __COBJECT_H__
#define __COBJECT_H__

#include "CNode.h"
#include "CMaterial.h"

class CObject : public CNode
{
	protected:
		CNode		*mNode;
		CMaterial   *mMaterial;
                                  
	public:
		CObject() { mNode = GetNodeInstance(); }
		virtual ~CObject() { }
                                  
		// set
		__forceinline SetNode(CNode* node) { mNode = node; }
		__forceinline SetMaterial(CMaterial* material)  { mMaterial = material; }

		// get
		__forceinline CMaterial* GetMaterial() const	{ return mMaterial; }
		__forceinline CNode* GetNode() const			{ return mNode; }
                                  
		// [hérité de CNode]
		virtual bool IntersectsNode(const CRay& ray, CIntersectInfo *intersectInfo=NULL) = 0;
};

#endif /* #ifndef __COBJECT_H__ */