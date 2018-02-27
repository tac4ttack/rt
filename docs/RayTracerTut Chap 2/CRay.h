/*! \class CRay
 *  \brief Cette classe définie l'élément de base d'un raytracer : un rayon.
 *  \author Benoît Lemaire (aka DaRkWoLf)
 *  \date   05/04/2002
 */

#ifndef __CRAY_H__
#define __CRAY_H__

#include "UtilityLib.h"

class CRay
{
	public:
		CVector3D	mVStart, mVDir;
		float		mT;	

		// constructeurs et destructeur
		CRay() {}
		virtual ~CRay() {}
};

#endif /* #ifndef __CRAY_H__ */