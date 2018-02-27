/*! \class CPointLight
 *  \brief Cette classe d�fnie une omni light, c'est � dire une lampe
 *  repr�sent�e par un point qui �met de la lumi�re uniform�ment dans toutes les directions.
 *  \author Beno�t Lemaire (aka DaRkWoLf)
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

		// [h�rit� de CLight]
		CColor GetLightAt(CVector3D& normal, CVector3D& intersectionPoint, CMaterial* material);
};

#endif /* #ifndef __CPOINTLIGHT_H__ */