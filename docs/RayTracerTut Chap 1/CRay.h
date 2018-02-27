/*! \class CRay
 *  \brief Cette classe définie l'élément de base d'un raytracer : un rayon.
 *  \author Benoît Lemaire (aka DaRkWoLf)
 *  \date   06/02/2002
 */

#ifndef __CRAY_H__
#define __CRAY_H__

#include "UtilityLib.h"

class CRay
{
	public:
		CVector3D	m_vStart, m_vDir;
		float		m_t;	

		// constructeurs et destructeur
		CRay() {}
		virtual ~CRay() {}
};

#endif /* #ifndef __CRAY_H__ */