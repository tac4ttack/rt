/*! \class CTargetCamera
 *  \brief Une Target Camera (camera cible), est une camera qui poss�de une position et un point observ�.
 *  \author Beno�t Lemaire (aka DaRkWoLf)
 *  \date   06/02/2002
 */

#ifndef __CTARGETCAM_H__
#define __CTARGETCAM_H__

#include "CCamera.h"

class CTargetCamera : public CCamera
{
	private:
		CVector3D	m_lookAtPoint;	// Le point observ�
                                  
    public:
		// constructeurs et destructeur
		CTargetCamera() {}
		CTargetCamera(CVector3D& camPos, CVector3D& lookAtPoint, CVector3D& upVector);
        virtual ~CTargetCamera() {}
};

#endif /* #ifndef __CTARGETCAM_H__ */