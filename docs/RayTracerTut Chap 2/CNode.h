/*! \class CNode
 *  \brief La class node est située dessus de toutes les autres classes "objets" du raytracer.
 *  Une camera est une node, une lumiére est une node, un mesh est une node, une primitive de base est une node ...
 *  \author Benoît Lemaire (aka DaRkWoLf)
 *  \date   05/04/2002
 */

#ifndef __CNODE_H__
#define __CNODE_H__

#include "UtilityLib.h"
#include "CIntersectInfo.h"
#include "CRay.h"
#include "RayTracerTypes.h"

class CNode
{
	protected:
		int				mNodeType;
		char*			mName;
	                     	
	public:
		// constructeurs et destructeur
		CNode() { mName = NULL; };
		CNode(int nodeType, char *name)	{ mNodeType=nodeType; mName=name; }
		virtual ~CNode() { SAFERELEASE(mName); }
                                  
		// raytrace related
		virtual bool IntersectsNode(const CRay& ray, CIntersectInfo *intersectInfo=NULL) = 0;
                                  
		// get
		__forceinline int			GetNodeType() const			{ return mNodeType; }
		__forceinline const char*	GetName() const				{ return mName; }
        __forceinline		CNode*	GetNodeInstance() const		{ return (CNode*)this; }    
		
		// set
		__forceinline void	SetNodeType(int nodeType)	{ mNodeType = nodeType; }
		__forceinline void	SetName(char* name)			{ mName = name; }
};

#endif /* #ifndef __CNODE_H__ */