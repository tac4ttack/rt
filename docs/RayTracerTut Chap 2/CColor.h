/*! \class CColor
 *  \brief Cette classe represente une couleur RGB ainsi que des operateurs sur les couleurs.
 *  \author Benoît Lemaire (aka DaRkWoLf)
 *  \date   05/04/2002
 */

#ifndef __CCOLOR_H__
#define __CCOLOR_H__

class CColor
{
	public:
		float mR, mG, mB;	// Les trois composantes de la couleur

		// constructeurs et destructeur
		CColor() : mR(0), mG(0), mB(0) {};
		CColor(float r, float g, float b) : mR(r), mG(g), mB(b) {};
		virtual ~CColor() {};

		// operateurs
		__forceinline friend CColor operator* (const CColor& c1, const CColor& c2)
		{ return CColor(c1.mR*c2.mR, c1.mG*c2.mG, c1.mB*c2.mB); };
		
		__forceinline friend CColor operator* (const CColor& c1, const float multiple)
		{ return CColor(c1.mR*multiple, c1.mG*multiple, c1.mB*multiple); };

		__forceinline friend CColor operator+ (const CColor& c1, const CColor& c2)
		{ return CColor(c1.mR+c2.mR, c1.mG+c2.mG, c1.mB+c2.mB); };

		__forceinline friend void operator+= (CColor& c1, const CColor& c2)
		{ c1.mR += c2.mR; c1.mG += c2.mG; c1.mB += c2.mB; };

		__forceinline friend CColor operator/ (const CColor& c1, float multiple)
		{ return CColor(c1.mR/multiple, c1.mG/multiple, c1.mB/multiple); }

		__forceinline friend void operator/= (CColor& c1, float multiple)
		{ c1.mR /= multiple; c1.mG /= multiple; c1.mB /= multiple; }

		// main methods
		__forceinline void NormalizeColor()	{ if (mR>1.0f) mR = 1.0f; if (mG>1.0f) mG = 1.0f; if (mB>1.0f) mB = 1.0f; }
};

#endif /* #ifndef __CCOLOR_H__ */