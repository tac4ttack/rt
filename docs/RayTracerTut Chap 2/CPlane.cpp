#include "CPlane.h"
                                  
CPlane::CPlane(const CVector3D& pointplane, const CVector3D& normal)
{
	mNormal = normal;
	mNormal.Normalize();
		
	mPointPlane = pointplane;
}
                                  
                                  
bool CPlane::IntersectsNode(const CRay& ray, CIntersectInfo *intersectInfo)
{
	float t;
	float dv;

	dv = mNormal.DotProduct(ray.mVDir);

	if (dv == 0)
		return false;

	t = ( ( -(mNormal.DotProduct(ray.mVStart-mPointPlane))) / dv );
    
	if (t<0)
		return false;

	if (intersectInfo)
	{
		intersectInfo->mIntersection	= ray.mVStart + ray.mVDir * t;

		if (dv < 0)
			intersectInfo->mNormal			= mNormal;

		else
			intersectInfo->mNormal			= -mNormal; 

		intersectInfo->mNode			= GetNode();
		intersectInfo->mMaterial		= GetMaterial();
	}
                                  	
	return true;
}

                                  
