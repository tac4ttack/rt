/*! \class CPointLight
 *  \brief Cette classe défnie une omni light, c'est à dire une lampe
 *  représentée par un point qui émet de la lumiére uniformément dans toutes les directions.
 *  \author Benoît Lemaire (aka DaRkWoLf)
 *  \date   19/04/2002
 */

#ifndef __CPOINTLIGHT_H__
#define __CPOINTLIGHT_H__

#include "CLight.h"

class CPointLight : public CLight
{	
	public:
		// constructeurs et destructeur
		CPointLight() {};
		CPointLight(const CVector3D& position, float diffuseColor, float specularColor, const CColor& color) 
		: CLight(position, diffuseColor, specularColor, color, OMNILIGHT) { }
		virtual ~CPointLight() {};

		// [hérité de CLight]
		CColor GetLightAt(CVector3D& normal, CVector3D& intersectionPoint, CMaterial* material);
};

#endif /* #ifndef __CPOINTLIGHT_H__ */