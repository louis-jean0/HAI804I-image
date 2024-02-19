#include "image_ppm.h"
#include <iostream>

int main(int argc, char* argv[]) {

    if(argc != 5) {
        printf("Utilisation : %s image_R.pgm image_G.pgm image_B.pgm image_out.ppm\n",argv[0]);
        exit(1);
    }

    char nomImageR[256], nomImageG[256], nomImageB[256], nomImageOut[256];

    int nH, nW, nTaille, nTaille3;

    sscanf(argv[1],"%s",nomImageR);
    sscanf(argv[2],"%s",nomImageG);
    sscanf(argv[3],"%s",nomImageB);
    sscanf(argv[4],"%s",nomImageOut);

    lire_nb_lignes_colonnes_image_pgm(nomImageR,&nH,&nW);

    nTaille = nH * nW;
    nTaille3 = 3 * nTaille;

    OCTET *ImgR, *ImgG, *ImgB, *ImgOut;

    allocation_tableau(ImgR,OCTET,nTaille);
    allocation_tableau(ImgG,OCTET,nTaille);
    allocation_tableau(ImgB,OCTET,nTaille);
    allocation_tableau(ImgOut,OCTET,nTaille3);

    lire_image_pgm(nomImageR,ImgR,nTaille);
    lire_image_pgm(nomImageG,ImgG,nTaille);
    lire_image_pgm(nomImageB,ImgB,nTaille);

    reconstruire_ppm(ImgR, ImgG, ImgB, ImgOut, nTaille);

    ecrire_image_ppm(nomImageOut,ImgOut,nH,nW);

    free(ImgR);
    free(ImgG);
    free(ImgB);
    free(ImgOut);

    return 0;

}