/*! \class CScene
 *  \brief Cette classe contient toutes les informations sur une scéne.
 *  Elle contient les éléments de la scéne (caméras, lumiéres, objets ...)
 *  \author Benoît Lemaire (aka DaRkWoLf)
 *  \date   05/04/2002
 */

#ifndef __CSCENE_H__
#define __CSCENE_H__

#include "CCamera.h"
#include "CObject.h"
#include "CNode.h"
#include "assert.h"
#include "CLight.h"
#include <vector>

using namespace std;

class CScene
{
	private:
		int						mNumNodes;
		vector<CNode*>			mNodes;
		vector<CCamera*>		mCameras;
		vector<CLight*>			mLights;
		vector<CMaterial*>		mMaterials;
		CCamera					*mActiveCamera;
                                  
	public:
		// constructeurs et destructeurs
		CScene() : mNumNodes(0), mActiveCamera(NULL) {}
		virtual ~CScene() 
		{ }

		// get
		__forceinline int			GetNumNodes() const { return mNumNodes; }
		__forceinline CNode*		GetNode(const unsigned int i) const { assert(i<mNodes.size()); return mNodes[i]; }
		__forceinline CLight*		GetLight(const unsigned int i) const { assert(i<mLights.size()); return mLights[i]; }
		__forceinline int			GetNumLights() const { return mLights.size(); }
		__forceinline CCamera*		GetActiveCamera() const { return mActiveCamera; }
		__forceinline CMaterial*	GetMaterial(const unsigned int i) const { assert(i<mMaterials.size()); return mMaterials[i]; }

		// set
		__forceinline void		SetActiveCamera(const unsigned int i) { assert(i<mCameras.size()); mActiveCamera = mCameras[i]; }
		__forceinline void		SetActiveCamera(CCamera* cam) { assert(cam); mActiveCamera = cam; }

		// methodes
		__forceinline	bool	AddObject(CObject* object) { assert( object ); AddNode(object); return true; }
		__forceinline	bool	AddCamera(CCamera* camera) { assert( camera ); mCameras.push_back(camera); AddNode(camera); SetActiveCamera(camera); return true; }
		__forceinline	bool	AddNode(CNode* node) { assert( node ); mNodes.push_back(node); mNumNodes++; return true; }
		__forceinline	bool	AddLight(CLight* light) { assert( light ); mLights.push_back(light); AddNode(light); return true; }
		__forceinline	bool	AddMaterial(CMaterial* material) { assert(material); mMaterials.push_back(material); return true; }
};

#endif /* #ifndef __CSCENE_H__ */