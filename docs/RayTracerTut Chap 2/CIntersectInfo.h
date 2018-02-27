/*! \class CIntersectInfo
 *  \brief Cette classe contient des informations sur une intersection
 *  \author Benoît Lemaire (aka DaRkWoLf)
 *  \date   05/04/2002
 */

#ifndef __CINTERSECTINFO_H__
#define __CINTERSECTINFO_H__

#include "UtilityLib.h"
#include "stdlib.h"

// forward declarations
class CScene;
class CNode;
class CMaterial;
                                  
// information sur l'intersection
class CIntersectInfo
{
	public:
		CVector3D		mIntersection;	// Position de l'intersection	
		CVector3D		mNormal;		// Normale au point d'intersection
		CNode			*mNode;			// Node touchée par l'intersection
		CMaterial		*mMaterial;		// Material au point d'intersection

		// constructeurs et destructeur
		CIntersectInfo() : mNode(NULL) {}
		virtual ~CIntersectInfo() {}
};

#endif /* #ifndef __CINTERSECTINFO_H__ */