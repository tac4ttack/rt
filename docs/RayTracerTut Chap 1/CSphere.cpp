#include "CSphere.h"

bool CSphere::IntersectsNode(const CRay& ray, CIntersectInfo *intersectInfo)
{
	float b, c;;
	float delta;
	float t;
	float t1, t2;
	CVector3D intersect;
	CVector3D tmpNormal;

	CVector3D rayOrg = ray.m_vStart - m_Center;	// ray in space of the sphere
                                  
	b = rayOrg.DotProduct(ray.m_vDir);
	c = rayOrg.GetSquareLength() - m_Radius*m_Radius;
                                  
	delta = ((b*b) - c);
                                  
	if (delta<0.0f)
		return false; // pas d'intersection
                                  
	if (intersectInfo)
	{
		if (delta!=0)
		{
			delta = (float)sqrt(delta);
			t1 = (-b + delta); 
			t2 = (-b - delta); 
                                  
			if (t1<t2) 
				t = t1;
			else
				t = t2;
		}
                                  	
		else 
			t = (-b);

		intersect = ray.m_vStart + ray.m_vDir * t;

		intersectInfo->m_Intersection	= intersect;
		intersectInfo->m_Node			= GetNode();
	}
                                  
	return true;
}
