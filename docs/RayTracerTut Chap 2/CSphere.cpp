#include "CSphere.h"

bool CSphere::IntersectsNode(const CRay& ray, CIntersectInfo *intersectInfo)
{
	float b, c;
	float delta;
	float t;
	float t1, t2;
	CVector3D intersect;
	CVector3D tmpNormal;

	CVector3D rayOrg = ray.mVStart - mCenter;	// ray in space of the sphere
                                  
	b = rayOrg.DotProduct(ray.mVDir);
	c = rayOrg.GetSquareLength() - mRadius*mRadius;
                                  
	delta = ((b*b) - c);
                                  
	if (delta<0.0f)
		return false; // pas d'intersection
                                  
	if (intersectInfo)
	{
		if (delta!=0)
		{
			delta = (float)sqrt(delta);
			t1 = (-b + delta); if (t1<0) return false;
			t2 = (-b - delta); if (t2<0) return false;
                                  
			if (t1<t2) 
				t = t1;
			else
				t = t2;
		}
                                  	
		else 
			t = (-b);

		intersect = ray.mVStart + ray.mVDir * t;

		tmpNormal = (intersect - mCenter) / mRadius;

		intersectInfo->mIntersection	= intersect;
		intersectInfo->mNormal			= tmpNormal;
		intersectInfo->mNode			= GetNode();
		intersectInfo->mMaterial		= GetMaterial();
	}
                                  
	return true;
}
