/*! \class CIntersectInfo
 *  \brief Cette classe contient des informations sur une intersection
 *  \author Benoît Lemaire (aka DaRkWoLf)
 *  \date   06/02/2002
 */

#ifndef __CINTERSECTINFO_H__
#define __CINTERSECTINFO_H__

#include "UtilityLib.h"
#include "stdlib.h"

// forward declarations
class CScene;
class CNode;
                                  
// information sur l'intersection
class CIntersectInfo
{
	public:
		CVector3D		m_Intersection; // Position de l'intersection	
		CNode			*m_Node;		// Node touchée par l'intersection

		// constructeurs et destructeur
		CIntersectInfo() : m_Node(NULL) {}
		virtual ~CIntersectInfo() {}
};

#endif /* #ifndef __CINTERSECTINFO_H__ */