// ----------------------------------------------------------------------------
// Filename        : image_ppm.c
// Description     :
// Created On      : Tue Mar 31 13:26:36 2005
// ----------------------------------------------------------------------------

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#define allocation_tableau(nom, type, nombre) \
if( (nom = (type*) calloc (nombre, sizeof(type) ) ) == NULL ) \
{\
 printf("\n Allocation dynamique impossible pour un pointeur-tableau \n");\
 exit(1);\
}

typedef unsigned char OCTET;

/*===========================================================================*/
void ignorer_commentaires(FILE * f)
{
  unsigned char c;
  while((c=fgetc(f)) == '#')
    while((c=fgetc(f)) != '\n');
  fseek(f, -sizeof(unsigned char), SEEK_CUR);
}
/*===========================================================================*/


/*===========================================================================*/
void ecrire_image_ppm(char  nom_image[], OCTET *pt_image, int nb_lignes, int nb_colonnes)
{
   FILE *f_image;
   int taille_image = 3*nb_colonnes * nb_lignes;

   if( (f_image = fopen(nom_image, "wb")) == NULL)
      {
	 printf("\nPas d'acces en ecriture sur l'image %s \n", nom_image);
	 exit(EXIT_FAILURE);
      }
   else
      {
	 fprintf(f_image,"P6\r") ;                               /*ecriture entete*/
	 fprintf(f_image,"%d %d\r255\r", nb_colonnes, nb_lignes) ;

	 if( (fwrite((OCTET*)pt_image, sizeof(OCTET), taille_image, f_image))
	     != (size_t)(taille_image))
	    {
	       printf("\nErreur d'ecriture de l'image %s \n", nom_image);
	       exit(EXIT_FAILURE);
	    }
	 fclose(f_image);
      }
}
/*===========================================================================*/

/*===========================================================================*/		
void lire_nb_lignes_colonnes_image_ppm(char nom_image[], int *nb_lignes, int *nb_colonnes)
{
   FILE *f_image;
   int max_grey_val;

   /* cf : l'entete d'une image .ppm : P6                   */
   /*				       nb_colonnes nb_lignes */
   /*    			       max_grey_val          */


   if( (f_image = fopen(nom_image, "rb")) == NULL)
      {
	 printf("\nPas d'acces en lecture sur l'image %s \n", nom_image);
	 exit(EXIT_FAILURE);
      }
   else
      {
	 fscanf(f_image, "P6 ");
	 ignorer_commentaires(f_image);
	 fscanf(f_image, "%d %d %d%*c", nb_colonnes, nb_lignes, &max_grey_val);
	 fclose(f_image);
      }
}
/*===========================================================================*/
/*===========================================================================*/
void lire_image_ppm(char  nom_image[], OCTET *pt_image, int taille_image)
{
   FILE *f_image;
   int  nb_colonnes, nb_lignes, max_grey_val;
   taille_image=3*taille_image;

   if( (f_image = fopen(nom_image, "rb")) == NULL)
      {
	 printf("\nPas d'acces en lecture sur l'image %s \n", nom_image);
	 exit(EXIT_FAILURE);
      }
   else
      {
	fscanf(f_image, "P6 ");
	ignorer_commentaires(f_image);
	fscanf(f_image, "%d %d %d%*c",
	       &nb_colonnes, &nb_lignes, &max_grey_val); /*lecture entete*/

	 if( (fread((OCTET*)pt_image, sizeof(OCTET), taille_image, f_image))
	     !=  (size_t)(taille_image))
	    {
	       printf("\nErreur de lecture de l'image %s \n", nom_image);
	       exit(EXIT_FAILURE);
	    }
	 fclose(f_image);
      }
}

/*===========================================================================*/
/*===========================================================================*/

void planR(OCTET *pt_image, OCTET *src, int taille_image){
   int i;
   for (i=0; i<taille_image; i++){
      pt_image[i]=src[3*i];
      }
   }
   
/*===========================================================================*/
/*===========================================================================*/

void planG(OCTET *pt_image, OCTET *src, int taille_image){
   int i;
   for (i=0; i<taille_image; i++){
      pt_image[i]=src[3*i+1];
      }
   }   

/*===========================================================================*/
/*===========================================================================*/

void planB(OCTET *pt_image, OCTET *src, int taille_image){
   int i;
   for (i=0; i<taille_image; i++){
      pt_image[i]=src[3*i+2];
      }
   }
   
/*===========================================================================*/   
/*===========================================================================*/

void ecrire_image_pgm(char  nom_image[], OCTET *pt_image, int nb_lignes, int nb_colonnes)
{
   FILE *f_image;
   int taille_image = nb_colonnes * nb_lignes;

   if( (f_image = fopen(nom_image, "wb")) == NULL)
      {
	 printf("\nPas d'acces en ecriture sur l'image %s \n", nom_image);
	 exit(EXIT_FAILURE);
      }
   else
      {
	 fprintf(f_image,"P5\r") ;                               /*ecriture entete*/
	 fprintf(f_image,"%d %d\r255\r", nb_colonnes, nb_lignes) ;

	 if( (fwrite((OCTET*)pt_image, sizeof(OCTET), taille_image, f_image))
	     != (size_t) taille_image)
	    {
	       printf("\nErreur de lecture de l'image %s \n", nom_image);
	       exit(EXIT_FAILURE);
	    }
	 fclose(f_image);
      }
}
/*===========================================================================*/

void lire_nb_lignes_colonnes_image_pgm(char nom_image[], int *nb_lignes, int *nb_colonnes)
{
   FILE *f_image;
   int max_grey_val;

   /* cf : l'entete d'une image .pgm : P5                    */
   /*				       nb_colonnes nb_lignes */
   /*    			       max_grey_val          */


   if( (f_image = fopen(nom_image, "rb")) == NULL)
      {
	 printf("\nPas d'acces en lecture sur l'image %s \n", nom_image);
	 exit(EXIT_FAILURE);
      }
   else
      {
	 fscanf(f_image, "P5 ");
	 ignorer_commentaires(f_image);
	 fscanf(f_image, "%d %d %d%*c", nb_colonnes, nb_lignes, &max_grey_val);
	 fclose(f_image);
      }
}
/*===========================================================================*/
/*===========================================================================*/
void lire_image_pgm(char  nom_image[], OCTET *pt_image, int taille_image)
{
   FILE *f_image;
   int  nb_colonnes, nb_lignes, max_grey_val;

   if( (f_image = fopen(nom_image, "rb")) == NULL)
      {
	 printf("\nPas d'acces en lecture sur l'image %s \n", nom_image);
	 exit(EXIT_FAILURE);
      }
   else
      {
	fscanf(f_image, "P5 ");
	ignorer_commentaires(f_image);
	fscanf(f_image, "%d %d %d%*c",
	       &nb_colonnes, &nb_lignes, &max_grey_val); /*lecture entete*/

	 if( (fread((OCTET*)pt_image, sizeof(OCTET), taille_image, f_image))
	     !=  (size_t) taille_image)
	    {
	       printf("\nErreur de lecture de l'image %s \n", nom_image);
	       exit(EXIT_FAILURE);
	    }
	 fclose(f_image);
      }
}
/*===========================================================================*/
int indiceImage(int x, int y, int width) {
   if (x >= width) {
      printf("x trop grand/n");
   }
   return y * width + x;
}
/*===========================================================================*/

/*===========================================================================*/
int indiceImageCouleur(int x, int y, int width, int c) {

   return (3 * ((y * width) + x)) + c;

}
/*===========================================================================*/

/*===========================================================================*/
void erosion_binaire(OCTET *ImgIn, OCTET *ImgOut, int nH, int nW) {
   for(int i = 0; i < nH * nW; i++) { // Premier traitement afin d'avoir des valeurs sur les bords (mêmes valeurs que l'image d'entrée)
      ImgOut[i] = ImgIn[i];
   } 

   for(int x = 1; x < nW - 1; x++) { // Bons indices pour respecter les problèmes sur les bords
        for(int y = 1; y < nH - 1; y++) {
            int vDroite = ImgIn[indiceImage(x + 1, y, nW)];
            int vGauche = ImgIn[indiceImage(x - 1, y, nW)];
            int vBas = ImgIn[indiceImage(x, y + 1, nW)];
            int vHaut = ImgIn[indiceImage(x, y - 1, nW)];

            if(vDroite || vGauche || vHaut || vBas) {
               ImgOut[indiceImage(x, y, nW)] = 255;
            }

            else {
               ImgOut[indiceImage(x, y, nW)] = 0;
            }
         }
   }
}
/*===========================================================================*/

/*===========================================================================*/
void dilatation_binaire(OCTET *ImgIn, OCTET *ImgOut, int nH, int nW) {
   for(int i = 0; i < nH * nW; i++) { // Premier traitement afin d'avoir des valeurs sur les bords (mêmes valeurs que l'image d'entrée)
      ImgOut[i] = ImgIn[i];
   }

   for(int x = 1; x < nW - 1; x++) { // Bons indices pour respecter les problèmes sur les bords
      for(int y = 1; y < nH - 1; y++) {
         int vDroite = ImgIn[indiceImage(x + 1, y, nW)];
         int vGauche = ImgIn[indiceImage(x - 1, y, nW)];
         int vBas = ImgIn[indiceImage(x, y + 1, nW)];
         int vHaut = ImgIn[indiceImage(x, y - 1, nW)];

         if((vDroite == 0 || vGauche == 0 || vHaut == 0 || vBas == 0)) {
            ImgOut[indiceImage(x, y, nW)] = 0;
         }

         else {
            ImgOut[indiceImage(x, y, nW)]  = 255;
         }
      }
   }
}
/*===========================================================================*/

/*===========================================================================*/
void fermeture_binaire(OCTET *ImgIn, OCTET *ImgOut, int nH, int nW) {
   OCTET* ImgIntermediaire;
   allocation_tableau(ImgIntermediaire,OCTET,nH*nW);
   dilatation_binaire(ImgIn,ImgIntermediaire,nH,nW);
   erosion_binaire(ImgIntermediaire,ImgOut,nH,nW);
}
/*===========================================================================*/

/*===========================================================================*/
void ouverture_binaire(OCTET *ImgIn, OCTET *ImgOut, int nH, int nW) {
   OCTET* ImgIntermediaire;
   allocation_tableau(ImgIntermediaire,OCTET,nH*nW);
   erosion_binaire(ImgIn,ImgIntermediaire,nH,nW);
   dilatation_binaire(ImgIntermediaire,ImgOut,nH,nW);
}
/*===========================================================================*/

/*===========================================================================*/
void erosion_ndg(OCTET *ImgIn, OCTET *ImgOut, int nH, int nW) {
   for(int i = 0; i < nH * nW; i++) { // Premier traitement afin d'avoir des valeurs sur les bords (mêmes valeurs que l'image d'entrée)
      ImgOut[i] = ImgIn[i];
   } 

   for(int x = 1; x < nW - 1; x++) { // Bons indices pour respecter les problèmes sur les bords
        for(int y = 1; y < nH - 1; y++) {
            int vDroite = ImgIn[indiceImage(x + 1, y, nW)];
            int vGauche = ImgIn[indiceImage(x - 1, y, nW)];
            int vBas = ImgIn[indiceImage(x, y + 1, nW)];
            int vHaut = ImgIn[indiceImage(x, y - 1, nW)];

            int max1 = std::min(vDroite,vGauche);
            int max2 = std::min(vBas,vHaut);
            int value = std::min(max1,max2);

            ImgOut[indiceImage(x,y,nW)] = value;
      }
   }  
}
/*===========================================================================*/

/*===========================================================================*/
void dilatation_ndg(OCTET *ImgIn, OCTET *ImgOut, int nH, int nW) {
   for(int i = 0; i < nH * nW; i++) { // Premier traitement afin d'avoir des valeurs sur les bords (mêmes valeurs que l'image d'entrée)
      ImgOut[i] = ImgIn[i];
   } 

   for(int x = 1; x < nW - 1; x++) { // Bons indices pour respecter les problèmes sur les bords
        for(int y = 1; y < nH - 1; y++) {
            int vDroite = ImgIn[indiceImage(x + 1, y, nW)];
            int vGauche = ImgIn[indiceImage(x - 1, y, nW)];
            int vBas = ImgIn[indiceImage(x, y + 1, nW)];
            int vHaut = ImgIn[indiceImage(x, y - 1, nW)];

            int max1 = std::max(vDroite,vGauche);
            int max2 = std::max(vBas,vHaut);
            int value = std::max(max1,max2);

            ImgOut[indiceImage(x,y,nW)] = value;
      }
   }  
}
/*===========================================================================*/

/*===========================================================================*/
void fermeture_ndg(OCTET *ImgIn, OCTET *ImgOut, int nH, int nW) {
   OCTET* ImgIntermediaire;
   allocation_tableau(ImgIntermediaire,OCTET,nH*nW);
   dilatation_ndg(ImgIn,ImgIntermediaire,nH,nW);
   erosion_ndg(ImgIntermediaire,ImgOut,nH,nW);
}
/*===========================================================================*/

/*===========================================================================*/
void ouverture_ndg(OCTET *ImgIn, OCTET *ImgOut, int nH, int nW) {
   OCTET* ImgIntermediaire;
   allocation_tableau(ImgIntermediaire,OCTET,nH*nW);
   erosion_ndg(ImgIn,ImgIntermediaire,nH,nW);
   dilatation_ndg(ImgIntermediaire,ImgOut,nH,nW);
}
/*===========================================================================*/

/*===========================================================================*/
void erosion_couleur(OCTET *ImgIn, OCTET *ImgOut, int nH, int nW) {
    // Copie des valeurs sur les bords
    int nTaille3 = nH * nW * 3;
    for(int i = 0; i < nTaille3; i++) {
        ImgOut[i] = ImgIn[i];
    }

    for(int x = 1; x < nW - 1; x++) {
        for(int y = 1; y < nH - 1; y++) {
            for(int c = 0; c < 3; c++) { // Boucle sur chaque canal de couleur
                int vDroite = ImgIn[indiceImageCouleur(x + 1, y, nW, c)];
                int vGauche = ImgIn[indiceImageCouleur(x - 1, y, nW, c)];
                int vBas = ImgIn[indiceImageCouleur(x, y + 1, nW, c)];
                int vHaut = ImgIn[indiceImageCouleur(x, y - 1, nW, c)];

                int min1 = std::min(vDroite, vGauche);
                int min2 = std::min(vBas, vHaut);
                int value = std::min(min1, min2);

                ImgOut[indiceImageCouleur(x, y, nW, c)] = value;
            }
        }
    }
}
/*===========================================================================*/

/*===========================================================================*/
void dilatation_couleur(OCTET *ImgIn, OCTET *ImgOut, int nH, int nW) {
    // Copie des valeurs sur les bords
    int nTaille3 = nH * nW * 3;
    for(int i = 0; i < nTaille3; i++) {
        ImgOut[i] = ImgIn[i];
    }

    for(int x = 1; x < nW - 1; x++) {
        for(int y = 1; y < nH - 1; y++) {
            for(int c = 0; c < 3; c++) { // Boucle sur chaque canal de couleur
                int vDroite = ImgIn[indiceImageCouleur(x + 1, y, nW, c)];
                int vGauche = ImgIn[indiceImageCouleur(x - 1, y, nW, c)];
                int vBas = ImgIn[indiceImageCouleur(x, y + 1, nW, c)];
                int vHaut = ImgIn[indiceImageCouleur(x, y - 1, nW, c)];

                int max1 = std::max(vDroite, vGauche);
                int max2 = std::max(vBas, vHaut);
                int value = std::max(max1, max2);

                ImgOut[indiceImageCouleur(x, y, nW, c)] = value;
            }
        }
    }
}
/*===========================================================================*/

/*===========================================================================*/
void fermeture_couleur(OCTET *ImgIn, OCTET *ImgOut, int nH, int nW) {
   OCTET* ImgIntermediaire;
   allocation_tableau(ImgIntermediaire,OCTET,nH*nW*3);
   dilatation_couleur(ImgIn,ImgIntermediaire,nH,nW);
   erosion_couleur(ImgIntermediaire,ImgOut,nH,nW);
}
/*===========================================================================*/

/*===========================================================================*/
void ouverture_couleur(OCTET *ImgIn, OCTET *ImgOut, int nH, int nW) {
   OCTET* ImgIntermediaire;
   allocation_tableau(ImgIntermediaire,OCTET,nH*nW*3);
   erosion_couleur(ImgIn,ImgIntermediaire,nH,nW);
   dilatation_couleur(ImgIntermediaire,ImgOut,nH,nW);
}
/*===========================================================================*/

/*===========================================================================*/
double distance_euclidienne_ppm(OCTET pixel1[3], OCTET pixel2[3]) {
   return sqrt(pow(pixel2[0] - pixel1[0],2) +
               pow(pixel2[1] - pixel1[1],2) +
               pow(pixel2[2] - pixel1[2],2));
}
/*===========================================================================*/

/*===========================================================================*/
void RGBtoYCbCr(OCTET* ImgIn, OCTET* ImgY, OCTET* ImgCb, OCTET* ImgCr, int nTaille) {
   OCTET *ImgR, *ImgG, *ImgB;

   allocation_tableau(ImgR,OCTET,nTaille);
   allocation_tableau(ImgG,OCTET,nTaille);
   allocation_tableau(ImgB,OCTET,nTaille);

   planR(ImgR,ImgIn,nTaille);
   planG(ImgG,ImgIn,nTaille);
   planB(ImgB,ImgIn,nTaille);

   for(int i = 0; i < nTaille; i++) {
      ImgY[i] = 0.299*ImgR[i] + 0.587*ImgG[i] + 0.114*ImgB[i];
      ImgCb[i] = -0.1687*ImgR[i] - 0.3313*ImgG[i] + 0.5*ImgB[i] + 128;
      ImgCr[i] = 0.5*ImgR[i] - 0.4187*ImgG[i] - 0.0813*ImgB[i] + 128;
   }
}
/*===========================================================================*/

/*===========================================================================*/
void reconstruire_ppm(OCTET* ImgR, OCTET* ImgG, OCTET* ImgB, OCTET* ImgOut, int nTaille) {
   for(int i = 0; i < nTaille; i++) {
         ImgOut[3*i] = ImgR[i];
         ImgOut[3*i+1] = ImgG[i];
         ImgOut[3*i+2] = ImgB[i];
      }
}
/*===========================================================================*/