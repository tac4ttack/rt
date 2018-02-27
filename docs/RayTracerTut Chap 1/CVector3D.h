/*! \class CVector3D
 *  \brief Cette classe contient une representation d'un vecteur 3D (x, y, z), ainsi que des opérations sur les vecteurs.
 *  \author Benoît Lemaire (aka DaRkWoLf)
 *  \date   06/02/2002
 */

#ifndef __CVECTOR3D_H__
#define __CVECTOR3D_H__

#include "math.h"
#include "stdio.h"

class CVector3D
{
	public:
		float x, y, z;

		// constructeurs et destructeur
		CVector3D() : x(0.0f), y(0.0f), z(0.0f) {}
		CVector3D(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
		virtual ~CVector3D() {}

		// operateurs
		__forceinline friend CVector3D operator+ (const CVector3D& v1, const CVector3D& v2) // addition
		{ return CVector3D(v1.x+v2.x, v1.y+v2.y, v1.z+v2.z); }

		__forceinline friend void operator+= (CVector3D& v1, const CVector3D& v2) // addition
		{ v1.x += v2.x; v1.y += v2.y; v1.z += v2.z; }

		__forceinline friend CVector3D operator- (const CVector3D& v1, const CVector3D& v2) // soustraction
		{ return CVector3D(v1.x-v2.x, v1.y-v2.y, v1.z-v2.z); }

		__forceinline friend CVector3D operator* (const CVector3D& v1, const CVector3D& v2) // produit en croix
		{ return CVector3D(	( v1.y * v2.z ) - ( v1.z * v2.y ), ( v1.z * v2.x ) - ( v1.x * v2.z ), ( v1.x * v2.y ) - ( v1.y * v2.x )	); }; 
		
		__forceinline friend CVector3D operator* (const CVector3D& v1, const float multiple) // scaling
		{ return CVector3D(v1.x*multiple, v1.y*multiple, v1.z*multiple); }

		__forceinline friend CVector3D operator/ (const CVector3D& v1, const float multiple) // scaling
		{ return CVector3D(v1.x/multiple, v1.y/multiple, v1.z/multiple); }

		__forceinline friend void operator/= (CVector3D& v1, float multiple) // scaling
		{ v1.x /= multiple; v1.y /= multiple; v1.z /= multiple; }

		__forceinline friend CVector3D operator- (const CVector3D& v) // opposé
		{ return CVector3D(-v.x, -v.y, -v.z); }

		// methodes
		__forceinline float DotProduct(const CVector3D& v) { return (x*v.x + y*v.y + z*v.z); }
		__forceinline float GetMagnitude()	const { return (float)sqrt(x*x+y*y+z*z); }
        __forceinline void Normalize() { float mag = GetMagnitude(); x /= mag; y /= mag; z /= mag; }
		__forceinline float GetSquareLength() const { return (x*x+y*y+z*z); }
		__forceinline CVector3D	Reflect(const CVector3D& n) { float fac=2.0f*(n.x*x+n.y*y+n.z*z); return CVector3D(fac*n.x-x,fac*n.y-y,fac*n.z-z); }
};


#endif /* #ifndef __CVECTOR3D_H__ */