/*! \class CObject
 *  \brief Cette classe est la classe de base pour toutes les primitives implementées dans le raytracer
 *  : spheres, plans, cônes ...
 *  \author Benoît Lemaire (aka DaRkWoLf)
 *  \date   06/02/2002
 */

#ifndef __COBJECT_H__
#define __COBJECT_H__

#include "CNode.h"

class CObject : public CNode
{
	protected:
		CNode		*m_Node;
                                  
	public:
		CObject() { m_Node = GetNodeInstance(); }
		virtual ~CObject() { }
                                  
		// set
		__forceinline SetNode(CNode* node) { m_Node = node; }

		// get
		__forceinline CNode* GetNode() const			{ return m_Node; }
                                  
		// [hérité de CNode]
		virtual bool IntersectsNode(const CRay& ray, CIntersectInfo *intersectInfo=NULL) = 0;
};

#endif /* #ifndef __COBJECT_H__ */