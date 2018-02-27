/*! \class CScene
 *  \brief Cette classe contient toutes les informations sur une scéne.
 *  Elle contient les éléments de la scéne (caméras, lumiéres, objets ...)
 *  \author Benoît Lemaire (aka DaRkWoLf)
 *  \date   06/02/2002
 */

#ifndef __CSCENE_H__
#define __CSCENE_H__

#include "CCamera.h"
#include "CObject.h"
#include "CNode.h"
#include "assert.h"
#include <vector>

using namespace std;

class CScene
{
	private:
		int						m_NumNodes;
		vector<CNode*>			m_Nodes;
		vector<CCamera*>		m_Cameras;
		CCamera					*m_ActiveCamera;
                                  
	public:
		// constructeurs et destructeurs
		CScene() : m_NumNodes(0), m_ActiveCamera(NULL) {}
		virtual ~CScene() 
		{ }

		// get
		__forceinline int			GetNumNodes() const { return m_NumNodes; }
		__forceinline CNode*		GetNode(const unsigned int i) const { assert(i<m_Nodes.size()); return m_Nodes[i]; }
		__forceinline CCamera*		GetActiveCamera() const { return m_ActiveCamera; }

		// set
		__forceinline void		SetActiveCamera(const unsigned int i) { assert(i<m_Cameras.size()); m_ActiveCamera = m_Cameras[i]; }
		__forceinline void		SetActiveCamera(CCamera* cam) { assert(cam); m_ActiveCamera = cam; }

		// methodes
		__forceinline	bool	AddObject(CObject* object) { assert( object ); AddNode(object); return true; }
		__forceinline	bool	AddCamera(CCamera* camera) { assert( camera ); m_Cameras.push_back(camera); AddNode(camera); SetActiveCamera(camera); return true; }
		__forceinline	bool	AddNode(CNode* node) { assert( node ); m_Nodes.push_back(node); m_NumNodes++; return true; }
};

#endif /* #ifndef __CSCENE_H__ */