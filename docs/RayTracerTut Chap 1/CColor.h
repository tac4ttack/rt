/*! \class CColor
 *  \brief Cette classe represente une couleur RGB ainsi que des operateurs sur les couleurs.
 *  \author Benoît Lemaire (aka DaRkWoLf)
 *  \date   06/02/2002
 */

#ifndef __CCOLOR_H__
#define __CCOLOR_H__

class CColor
{
	public:
		float m_r, m_g, m_b;	// Les trois composantes de la couleur

		// constructeurs et destructeur
		CColor() : m_r(0), m_g(0), m_b(0) {};
		CColor(float r, float g, float b) : m_r(r), m_g(g), m_b(b) {};
		virtual ~CColor() {};

		// operateurs
		__forceinline friend CColor operator* (const CColor& c1, const CColor& c2)
		{ return CColor(c1.m_r*c2.m_r, c1.m_g*c2.m_g, c1.m_b*c2.m_b); };
		
		__forceinline friend CColor operator* (const CColor& c1, const float multiple)
		{ return CColor(c1.m_r*multiple, c1.m_g*multiple, c1.m_b*multiple); };

		__forceinline friend CColor operator+ (const CColor& c1, const CColor& c2)
		{ return CColor(c1.m_r+c2.m_r, c1.m_g+c2.m_g, c1.m_b+c2.m_b); };

		__forceinline friend void operator+= (CColor& c1, const CColor& c2)
		{ c1.m_r += c2.m_r; c1.m_g += c2.m_g; c1.m_b += c2.m_b; };

		__forceinline friend CColor operator/ (const CColor& c1, float multiple)
		{ return CColor(c1.m_r/multiple, c1.m_g/multiple, c1.m_r/multiple); }

		__forceinline friend void operator/= (CColor& c1, float multiple)
		{ c1.m_r /= multiple; c1.m_g /= multiple; c1.m_b /= multiple; }

		// main methods
		__forceinline void NormalizeColor()	{ if (m_r>1.0f) m_r = 1.0f; if (m_g>1.0f) m_g = 1.0f; if (m_b>1.0f) m_b = 1.0f; }
};

#endif /* #ifndef __CCOLOR_H__ */