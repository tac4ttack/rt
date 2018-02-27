/*! \class CLight
 *  \brief Classe de base lumiére
 *  \author Benoît Lemaire (aka DaRkWoLf)
 *  \date   19/04/2002
 */

#ifndef __CLIGHT_H__
#define __CLIGHT_H__

#include "UtilityLib.h"
#include "CMaterial.h"
#include "CNode.h"
#include "CRay.h"

class CLight : public CNode
{
	protected:	
		float		mDiffuseColor;
		float		mSpecularColor;
		CVector3D	mPosition;
		CColor		mColor;
		int			mLightType;

	public:
		// constructeurs et destructeur
		CLight() {};
		CLight(CVector3D position, float diffuseColor, float specularColor, CColor color, int type) : CNode(LIGHT, "LIGHT")
		{ mPosition = position; mDiffuseColor = diffuseColor; mSpecularColor = specularColor; mColor = color; mLightType = type;  }
		virtual ~CLight() {};

		// get
		__forceinline const CVector3D&	GetPosition() const { return mPosition; }
		__forceinline const CColor&		GetColor() const	{ return mColor; }
		__forceinline int				GetType() const		{ return mLightType; }

		// [hérité de CNode]
		bool IntersectsNode(const CRay& ray, CIntersectInfo *intersectInfo=NULL) { return false; }

		// La méthode virtuel pure d'éclairage.
		virtual CColor GetLightAt(CVector3D& normal, CVector3D& intersectionPoint, CMaterial* material) = 0;
};

#endif /* #ifndef __CLIGHT_H__ */