#include "RayTracerChap1.h"
#include <assert.h>

int Render(const CScene& scene, unsigned int width, unsigned height, const char* outputfilename);
CColor RayTrace(const CScene& scene, const CRay& ray, unsigned int depth);

int main()
{
	// Notre sc�ne
	CScene			myScene;

	// Notre cam�re
	CTargetCamera*	myCamera=NULL;						
	CVector3D		myCameraPos(0.0f, 0.0f, -3.0f);		// Position de la camera
	CVector3D		myCameraLookAt(0.0f, 0.0f, 10.0f);	// Position du point regard�
	CVector3D		myCameraUpVec(0.0f, 1.0f, 0.0f);	// Vecteur haut de la cam�ra

	// Une sph�re
	CSphere*		mySphere=NULL;
	CVector3D		mySpherePos(0.0f, 0.0f, 10.0f);		// Position de la sph�re
	float			mySphereRadius = 2.0f;				// Rayon de la sph�re

	myCamera	= new CTargetCamera(myCameraPos, myCameraLookAt, myCameraUpVec); assert (myCamera != NULL);
	mySphere	= new CSphere(mySpherePos, mySphereRadius); assert (mySphere != NULL);

	// On ajoute la cam�ra et la sph�re � notre sc�ne
	myScene.AddCamera(myCamera);
	myScene.AddObject(mySphere);

	// On lance le rendu
	Render(myScene, 640, 480, "renders//Chapitre1.raw");

	// On lib�re la m�moire avant de quitter
	SAFERELEASE(myCamera);
	SAFERELEASE(mySphere);

	return 0;
}

/* [ Coeur du raytracer. L'algo du raytracing se trouve dans cette fonction, dont le r�le est de calculer ] */
/* [ la couleur finale du pixel courant, en lui passant le rayon primaire �mis.                           ] */
CColor RayTrace(const CScene& scene, const CRay& ray, unsigned int depth)	
{
	CNode *currentNode;

	// On parcoure toutes les nodes de notre scene (cameras, objets ...)
	for (int i=0; i<scene.GetNumNodes(); i++)
	{
		currentNode = scene.GetNode(i);

		// Si le rayon rentre en contact avec la node, on renvoie la couleur BLANC	
		if (currentNode->IntersectsNode(ray))
			 return CColor(1.0f, 1.0f, 1.0f);
	}

	// Si il n'y a pas d'intersection, on renvoie tout simplement NOIR (couleur de fond).
	return CColor(0.0f, 0.0f, 0.0f);
}

/* [ Fonction de rendu. Parcoure tous les pixels de l'image, cr�e le rayon correpondant et lance le raytracing ] */
/* [ avec ce rayon. Enregistre le rendu final dans un fichier image.                                           ] */
int Render(const CScene& scene, unsigned int width, unsigned height, const char* outputfilename)
{
	CRay			currentRay;			// Le rayon primaire �mis courant (de l'oeil, � travers un pixel, vers la sc�ne).
	CVector3D		vDir;				// Le vecteur directeur (unitaire) du rayon.
	FILE*			m_OutputFileRAW;	// Le fichier image destination (format RAW : rvbrvbrvbrvb....).
	CColor			tmpColor;			// La couleur finale du pixel courant.
	unsigned char	tmpR, tmpG, tmpB;	// Les trois composantes de la couleur (Rouge Vert Bleu).

	// On cree le fichier destination
	m_OutputFileRAW		= fopen(outputfilename, "wb");

	// On parcoure tous les pixels de l'image finale
	for (int y=0; y<height; y++)
		for (int x=0; x<width; x++)
		{
			// [---Creation du rayon � emetrre---]
			// L'origine du rayon est la position de la camera
			currentRay.m_vStart = scene.GetActiveCamera()->GetPosition();

			// On calcule le veteur directeur gr�ce � une m�thode de la classe CCamera
			vDir = scene.GetActiveCamera()->CalcDirVec(x, y, width, height);	
			vDir.Normalize();
			currentRay.m_vDir = vDir;

			// On trace le rayon, et on recup�re la couleur finale du pixel
			tmpColor = RayTrace( scene, currentRay, 0 );

			// Affichage de notre "barre de progression" ;)
			if (x==0 && y==0.25f*height)
				printf("25 percent completed !\n");

			if (x==0 && y==0.5f*height)
				printf("50 percent completed !\n");

			if (x==0 && y==0.75f*height)
				printf("75 percent completed !\n");

			if (x==0 && y==height-1)
				printf("100 percent completed !\n");

			// On decompose la couleur dans les trois couleurs de base (Rouge Vert Bleu).
            tmpR = (unsigned char)(tmpColor.m_r*255);
			tmpG = (unsigned char)(tmpColor.m_g*255);	
			tmpB = (unsigned char)(tmpColor.m_b*255);
                                  
			// Et on ecrit finalement la couleur de ce pixel dans le fichier
			fwrite(&tmpR, sizeof(unsigned char), 1, m_OutputFileRAW);
			fwrite(&tmpG, sizeof(unsigned char), 1, m_OutputFileRAW);
			fwrite(&tmpB, sizeof(unsigned char), 1, m_OutputFileRAW);
		}

	fclose(m_OutputFileRAW);

	return true;
}


	
