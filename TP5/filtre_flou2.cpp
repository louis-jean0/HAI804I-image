#include <stdio.h>
#include "image_ppm.h"

int main(int argc, char* argv[]) {
  
  char cNomImgLue[250], cNomImgEcrite[250];
  int nH, nW, nTaille;
  
  if (argc != 3) 
     {
       printf("Utilisation : %s image_lue.pgm image_ecrite.pgm\n",argv[0]); 
       exit (1) ;
     }

  sscanf (argv[1],"%s",cNomImgLue);
  sscanf (argv[2],"%s",cNomImgEcrite);

  OCTET *ImgIn, *ImgOut;
   
  lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
  nTaille = nH * nW;
  
  allocation_tableau(ImgIn, OCTET, nTaille);
  lire_image_pgm(cNomImgLue, ImgIn, nH * nW);
  allocation_tableau(ImgOut, OCTET, nTaille);

  for(int i = 0; i < nTaille; i++) {
    ImgOut[i] = ImgIn[i];
  }

  for (int i=1; i < nH-1; i++) {
    for (int j=1; j < nW-1; j++) {
      int somme = ImgIn[indiceImage(i-1,j-1,nW)]+ImgIn[indiceImage(i-1,j,nW)]+ImgIn[indiceImage(i-1,j+1,nW)]
      +ImgIn[indiceImage(i,j-1,nW)]+ImgIn[indiceImage(i,j,nW)]+ImgIn[indiceImage(i,j+1,nW)]
      +ImgIn[indiceImage(i+1,j-1,nW)]+ImgIn[indiceImage(i+1,j,nW)]+ImgIn[indiceImage(i+1,j+1,nW)];

      ImgOut[indiceImage(i,j,nW)]=somme/9;
    }
  }

  ecrire_image_pgm(cNomImgEcrite, ImgOut,  nH, nW);
  free(ImgIn);free(ImgOut);
  
  return 0;
  
}