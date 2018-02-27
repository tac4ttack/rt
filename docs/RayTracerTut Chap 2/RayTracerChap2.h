/*! \brief Ce projet constitue le second code source de la serie d'articles
 *  "D�veloppement d'un raytracer". 
 *  \author Beno�t Lemaire (aka DaRkWoLf)
 *  \date   19/04/2002
 */

#include "UtilityLib.h"
#include "CTargetCamera.h"
#include "CSphere.h"
#include "CPlane.h"
#include "CScene.h"
#include "CMaterial.h"
#include "CPointLight.h"

// Prototypes de nos fonctions
CColor RayTrace(const CScene& scene, const CRay& ray, unsigned int depth);
int Render(const CScene& scene, unsigned int width, unsigned height, const char* outputfilename);