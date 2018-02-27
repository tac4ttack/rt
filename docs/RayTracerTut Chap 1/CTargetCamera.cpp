#include "CTargetCamera.h"

CTargetCamera::CTargetCamera(CVector3D& camPos, CVector3D& lookAtPoint, CVector3D& upVector) : CCamera( camPos, upVector )
{
	m_lookAtPoint = lookAtPoint;
                                  
	// Nous calculons le vecteur directeur de la camera
	m_vecDir = (m_lookAtPoint - camPos);
	m_vecDir.Normalize();
                                  
	// Maintenant nous calculons le vecteur droite (en utilisant le produit en croix)
	m_rightVec = (m_upVec * m_vecDir);
                    
	// De meme pour le "vrai" vecteur haut.
	m_upVec = (m_vecDir * m_rightVec);
                                  
	// Maintenant nous avons toutes les informations pour détérminer la position 
	// en haut à gauche du viewplane.
	m_viewPlaneUpLeft = camPos + ((m_vecDir*m_viewplaneDist)+(m_upVec*(m_viewplaneHeight/2.0f)))-(m_rightVec*(m_viewplaneWidth/2.0f));
}
