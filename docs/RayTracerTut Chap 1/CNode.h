/*! \class CNode
 *  \brief La class node est située dessus de toutes les autres classes "objets" du raytracer.
 *  Une camera est une node, une lumiére est une node, un mesh est une node, une primitive de base est une node ...
 *  \author Benoît Lemaire (aka DaRkWoLf)
 *  \date   06/02/2002
 */

#ifndef __CNODE_H__
#define __CNODE_H__

#include "UtilityLib.h"
#include "CIntersectInfo.h"
#include "CRay.h"


class CNode
{
	protected:
		int				m_NodeType;
		char*			m_Name;
	                     	
	public:
		// constructeurs et destructeur
		CNode() { m_Name = NULL; };
		CNode(int nodeType, char *name)	{ m_NodeType=nodeType; m_Name=name; }
		virtual ~CNode() { SAFERELEASE(m_Name); }
                                  
		// raytrace related
		virtual bool IntersectsNode(const CRay& ray, CIntersectInfo *intersectInfo=NULL) = 0;
                                  
		// get
		__forceinline int			GetNodeType() const			{ return m_NodeType; }
		__forceinline const char*	GetName() const				{ return m_Name; }
        __forceinline		CNode*	GetNodeInstance() const		{ return (CNode*)this; }    
		
		// set
		__forceinline void	SetNodeType(int nodeType)	{ m_NodeType = nodeType; }
		__forceinline void	SetName(char* name)			{ m_Name = name; }
};

#endif /* #ifndef __CNODE_H__ */