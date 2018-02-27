/*! \class CMaterial
 *  \brief Cette classe représente les materiaux ainsi que les oéprations de base sur ces derniers.
 *  \author Benoît Lemaire (aka DaRkWoLf)
 *  \date   19/04/2002
 */

#ifndef __CMATERIAL_H__
#define __CMATERIAL_H__

#include "utilitylib.h"

class CMaterial
{
	private:
		char*	mName;
		CColor	mSpecularColor;
		CColor	mDiffuseColor;
		CColor	mAmbientColor;
		CColor	mSelfIllumColor;
		float	mShininess;
		float	mShinestrength;
		float	mTransmittivity;
		float	mReflectivity;
		bool	mPermanent;

	public:
		// constructor and destructor
		CMaterial() {	mName = "EMPTY MAT"; mSpecularColor = CColor(0.0f, 0.0f, 0.0f); mDiffuseColor = CColor(0.0f, 0.0f, 0.0f); 
						mAmbientColor = CColor(0.0f, 0.0f, 0.0f); mSelfIllumColor = CColor(0.0f, 0.0f, 0.0f);
						mShininess = 0.0f; mShinestrength = 0.0f; mTransmittivity = 0.0f; mReflectivity = 0.0f; mPermanent = true;}
		CMaterial(char* name, CColor specular, CColor diffuse, CColor ambient, CColor selfillum, float transmittivity, float reflectivity, float shininess=20.0f, float shinestrength=1.0f, bool permanent=true)
			: mName(name), mSpecularColor(specular), mDiffuseColor(diffuse), mAmbientColor(ambient), mSelfIllumColor(selfillum), mShininess(shininess), 
			mShinestrength(shinestrength), mTransmittivity(transmittivity), mReflectivity(reflectivity), mPermanent(permanent) {};
		virtual ~CMaterial() { }

		// get
		__forceinline const char*	GetName() const				{ return mName; }
		__forceinline const CColor& GetDiffuse() const			{ return mDiffuseColor; }
		__forceinline const CColor& GetSpecular() const			{ return mSpecularColor; }
		__forceinline const CColor& GetAmbient() const			{ return mAmbientColor; }
		__forceinline const CColor& GetSelfIllum() const		{ return mSelfIllumColor; }
		__forceinline const float	GetShininess() const		{ return mShininess; }
		__forceinline const float	GetShinestStrength() const	{ return mShinestrength; }
		__forceinline const float	GetTransmittivity() const	{ return mTransmittivity; }
		__forceinline const float	GetReflectivity() const		{ return mReflectivity; }
		__forceinline bool			GetPermanency() const		{ return mPermanent; }

		// set
		__forceinline void SetName(char* name)							{ mName = name; }
		__forceinline void SetSpecular(const CColor& specular)			{ mSpecularColor = specular; }
		__forceinline void SetDiffuse(const CColor& diffuse)			{ mDiffuseColor = diffuse; }
		__forceinline void SetAmbient(const CColor& ambient)			{ mAmbientColor = ambient; }
		__forceinline void SetSelfIllum(const CColor& selfIllum)		{ mSelfIllumColor = selfIllum; }
		__forceinline void SetShininess(const float shininess)			{ mShininess = shininess; }
		__forceinline void SetShinesStrenght(const float sStrength)		{ mShinestrength = sStrength; }
		__forceinline void SetTransparency(const float transmittivity)	{ mTransmittivity = transmittivity; } 
		__forceinline void SetReflectivity(const float reflectivity)	{ mReflectivity = reflectivity; }
		__forceinline void SetPermanency(const bool permanent)			{ mPermanent = permanent; }

		// operators
		__forceinline friend CMaterial operator* (const CMaterial& mat, const float multiple)
		{ return CMaterial( "COMPOSITE MATERIAL",
							mat.mSpecularColor*multiple,
							mat.mDiffuseColor*multiple,
							mat.mAmbientColor*multiple,
							mat.mSelfIllumColor*multiple,
							mat.mTransmittivity*multiple,
							mat.mReflectivity*multiple,
							mat.mShininess*multiple,
							mat.mShinestrength*multiple ); }

		__forceinline friend CMaterial operator+ (const CMaterial& mat1, const CMaterial& mat2)
		{ return CMaterial( "COMPOSITE MATERIAL",
							mat1.mSpecularColor+mat2.mSpecularColor,
							mat1.mDiffuseColor+mat2.mDiffuseColor,
							mat1.mAmbientColor+mat2.mAmbientColor,
							mat1.mSelfIllumColor+mat2.mSelfIllumColor,
							mat1.mTransmittivity+mat2.mTransmittivity,
							mat1.mReflectivity+mat2.mReflectivity,
							mat1.mShininess+mat2.mShininess,
							mat1.mShinestrength+mat2.mShinestrength ); }

		__forceinline friend void operator+= (CMaterial& mat1, const CMaterial& mat2)
		{	mat1.mName = "COMPOSITE MATERIAL";
			mat1.mSpecularColor += mat2.mSpecularColor;
			mat1.mDiffuseColor += mat2.mDiffuseColor;
			mat1.mAmbientColor += mat2.mAmbientColor;
			mat1.mSelfIllumColor += mat2.mSelfIllumColor;
			mat1.mTransmittivity += mat2.mTransmittivity;
			mat1.mReflectivity += mat2.mReflectivity;
			mat1.mShininess += mat2.mShininess;
			mat1.mShinestrength += mat2.mShinestrength;
		}

		// misc functions
		__forceinline CMaterial InterpolateMaterials(const CMaterial& mat1, const CMaterial& mat2) const
		{ return CMaterial(	"COMPOSITE MATERIAL", 
							(mat1.mSpecularColor+mat2.mSpecularColor)/2.0f, 
							(mat1.mDiffuseColor+mat2.mDiffuseColor)/2.0f, 
							(mat1.mAmbientColor+mat2.mAmbientColor)/2.0f, 
							(mat1.mSelfIllumColor+mat2.mSelfIllumColor)/2.0f,
							(mat1.mTransmittivity+mat2.mTransmittivity)/2.0f,
							(mat1.mReflectivity+mat2.mReflectivity)/2.0f,
							(mat1.mShininess+mat2.mShininess)/2.0f,
							(mat1.mShinestrength+mat2.mShinestrength)/2.0f	); }
};

#endif /* #ifndef __CMATERIAL_H__ */