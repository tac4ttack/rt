#include "RaytracerChap2.h"

/* [ Coeur du raytracer. L'algo du raytracing se trouve dans cette fonction, dont le rôle est de calculer ] */
/* [ la couleur finale du pixel courant, en lui passant le rayon primaire émis.                           ] */
CColor RayTrace(const CScene& scene, const CRay& ray, unsigned int depth)	
{
	CColor			finalColor(0.0f, 0.0f, 0.0f);	// La couleur finale (noire au debut ... couleur de fond)
	float			distance = 999999.9f;			// La distance parcourue par le rayon avant de toucher la node
	float			tmpDistance;					// Une distance temporaire
	CNode			*currentNode;					// La node en cours de traitement
	CNode			*closestNode=NULL;				// La node qui sera la plus proche
	CIntersectInfo	interInfo;						// Les informations sur l'intersection
	CIntersectInfo	closestInterInfo;				// Les informations sur l'intersection de la node la plus proche
	
	
	// Eclairage
	bool			lightBlocked;		// Booleen qui nous permet de dire si le rayon de lumiére est bloqué sur son chemin ou non
	CVector3D		lightVec;			// Le vecteur allant de la source lumineuse vers le point d'intersection
	float			lightToObjDist;		// La distance entre la source lumineuse et le point d'intersection
	float			lightToInterDist;	// La distance entre la source lumineuse et le point d'intersection de la node courante
	CRay			lightRay;			// Le rayon lumineux
	CIntersectInfo	lightInterInfo;		// Les informations sur l'intersection du rayon lumineux et d'une node
	

	// On parcoure toutes les nodes de notre scene (cameras, objets ...)
	for (int i=0; i<scene.GetNumNodes(); i++)
	{
		currentNode = scene.GetNode(i);

		if (currentNode->IntersectsNode(ray, &interInfo))
		{
			// On à pas besoin de comparer la longueur en elle meme (qui est la racine carré de la somme des carrés des coeeficients)
			// En evitant la racine carré on obtient la meme comparaison, mais en une opération de moins (sqrt est trés gourmand).
			tmpDistance = (interInfo.mIntersection - ray.mVStart).GetSquareLength();

			if (tmpDistance < distance)
			{
				distance = tmpDistance;
				closestNode = currentNode;
				closestInterInfo = interInfo;
			}	
		}
	}

	if (closestNode)
	{
		// On parcoure toute les sources lumineuses
		for (int i=0; i<scene.GetNumLights(); i++)
		{
			lightBlocked = false;
                                  			
			// Calc the vec (normalized) going from the light to the intersection point
			lightVec = closestInterInfo.mIntersection - scene.GetLight(i)->GetPosition();
			lightToObjDist = lightVec.GetMagnitude();
			lightVec.Normalize();
                                  
			lightRay.mVStart = scene.GetLight(i)->GetPosition();
			lightRay.mVDir = lightVec;
                                  
			// We go through all the objects to see if one
			// of them block the light coming to the dest object 
			for (int j=0; j<scene.GetNumNodes(); j++)
			{
				currentNode = scene.GetNode(j);
				
				// put away the case of the object itself
				if (currentNode != closestInterInfo.mNode)
					if (currentNode->IntersectsNode(lightRay, &lightInterInfo)) 
					{
						lightToInterDist = (lightInterInfo.mIntersection - scene.GetLight(i)->GetPosition()).GetMagnitude();
						if (lightToInterDist < lightToObjDist)
							lightBlocked = true;
					}
			}

			if (!lightBlocked)
				finalColor += scene.GetLight(i)->GetLightAt(closestInterInfo.mNormal, closestInterInfo.mIntersection, closestInterInfo.mMaterial);		
		}

		// Clean non permanent material
		if (closestInterInfo.mMaterial->GetPermanency() == false)
			delete (closestInterInfo.mMaterial); closestInterInfo.mMaterial = NULL;
	}
	

	finalColor.NormalizeColor();
	return finalColor;
}

/* [ Fonction de rendu. Parcoure tous les pixels de l'image, crée le rayon correpondant et lance le raytracing ] */
/* [ avec ce rayon. Enregistre le rendu final dans un fichier image.                                           ] */
int Render(const CScene& scene, unsigned int width, unsigned height, const char* outputfilename)
{
	CRay			currentRay;			// Le rayon primaire émis courant (de l'oeil, à travers un pixel, vers la scéne).
	CVector3D		vDir;				// Le vecteur directeur (unitaire) du rayon.
	FILE*			mOutputFileRAW;	// Le fichier image destination (format RAW : rvbrvbrvbrvb....).
	CColor			tmpColor;			// La couleur finale du pixel courant.
	unsigned char	tmpR, tmpG, tmpB;	// Les trois composantes de la couleur (Rouge Vert Bleu).

	// On cree le fichier destination
	mOutputFileRAW		= fopen(outputfilename, "wb");

	// On parcoure tous les pixels de l'image finale
	for (int y=0; y<height; y++)
		for (int x=0; x<width; x++)
		{
			// [---Creation du rayon à emetrre---]
			// L'origine du rayon est la position de la camera
			currentRay.mVStart = scene.GetActiveCamera()->GetPosition();

			// On calcule le veteur directeur grâce à une méthode de la classe CCamera
			vDir = scene.GetActiveCamera()->CalcDirVec(x, y, width, height);	
			vDir.Normalize();
			currentRay.mVDir = vDir;

			// On trace le rayon, et on recupére la couleur finale du pixel
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
            tmpR = (unsigned char)(tmpColor.mR*255);
			tmpG = (unsigned char)(tmpColor.mG*255);	
			tmpB = (unsigned char)(tmpColor.mB*255);
                                  
			// Et on ecrit finalement la couleur de ce pixel dans le fichier
			fwrite(&tmpR, sizeof(unsigned char), 1, mOutputFileRAW);
			fwrite(&tmpG, sizeof(unsigned char), 1, mOutputFileRAW);
			fwrite(&tmpB, sizeof(unsigned char), 1, mOutputFileRAW);
		}

	fclose(mOutputFileRAW);

	return true;
}


	
