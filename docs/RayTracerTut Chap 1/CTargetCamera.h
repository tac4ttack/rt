/*! \class CTargetCamera
 *  \brief Une Target Camera (camera cible), est une camera qui posséde une position et un point observé.
 *  \author Benoît Lemaire (aka DaRkWoLf)
 *  \date   06/02/2002
 */

#ifndef __CTARGETCAM_H__
#define __CTARGETCAM_H__

#include "CCamera.h"

class CTargetCamera : public CCamera
{
	private:
		CVector3D	m_lookAtPoint;	// Le point observé
                                  
    public:
		// constructeurs et destructeur
		CTargetCamera() {}
		CTargetCamera(CVector3D& camPos, CVector3D& lookAtPoint, CVector3D& upVector);
        virtual ~CTargetCamera() {}
};

#endif /* #ifndef __CTARGETCAM_H__ */