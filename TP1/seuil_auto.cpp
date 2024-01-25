#include <stdio.h>
#include "image_ppm.h"

int main(int argc, char* argv[])

{
    char cNomImgLue[250], cNomImgEcrite[250];
    int nH, nW, nTaille;
    
    if (argc != 3) 
        {
        printf("Usage: ImageIn.pgm ImageOut.pgm\n"); 
        exit(1);
        }
    
    sscanf (argv[1],"%s",cNomImgLue) ;
    sscanf (argv[2],"%s",cNomImgEcrite);

    OCTET *ImgIn, *ImgOut;
    
    lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
    nTaille = nH * nW;
    
    allocation_tableau(ImgIn, OCTET, nTaille);
    lire_image_pgm(cNomImgLue, ImgIn, nH * nW);
    allocation_tableau(ImgOut, OCTET, nTaille);

    double moyenne = 0;

    for(int i = 0; i < nH; i++) {
        for(int j = 0; j < nW; j++) {
            moyenne += ImgIn[i*nW+j];
        }
    }

    moyenne /= nTaille;
    moyenne = std::ceil(moyenne);

    printf("Moyenne : %f\n",moyenne);

    for (int i=0; i < nH; i++) {
        for (int j=0; j < nW; j++) {
        if (ImgIn[i*nW+j] < moyenne) ImgOut[i*nW+j]=0; 
        else ImgOut[i*nW+j]=255;
        }
    }

    ecrire_image_pgm(cNomImgEcrite, ImgOut,  nH, nW);
    free(ImgIn); free(ImgOut);

    }