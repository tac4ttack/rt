#include "CPointLight.h"

CColor CPointLight::GetLightAt(CVector3D& normal, CVector3D& intersectionPoint, CMaterial* material)
{
	CVector3D	lightVector, reflectedLightVec;
	float		angle;
	CColor		finalColor;
                                  
	lightVector = intersectionPoint - GetPosition();

	lightVector.Normalize();
                                  
	angle = normal.DotProduct(-lightVector);
                                  	
	if (angle <= 0)
		finalColor = CColor(0.0f, 0.0f, 0.0f);
                                  	
	else
		finalColor = material->GetDiffuse() * GetColor() * angle;

	return finalColor;
}
