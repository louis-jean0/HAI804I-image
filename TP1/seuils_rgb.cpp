#include <stdio.h>
#include "image_ppm.h"

int main(int argc, char* argv[]) {

    if(argc != 6) {

        printf("Utilisation : %s image.ppm S_R S_G S_B image_sortie.ppm\n",argv[0]);
        exit(1);

    }

    int nH, nW, nTaille;
    int S_R,S_G,S_B;
    char nomImageIn[256];
    char nomImageOut[256];

    sscanf(argv[1],"%s",nomImageIn);
    sscanf(argv[5],"%s",nomImageOut);
    S_R = atoi(argv[2]);
    S_G = atoi(argv[3]);
    S_B = atoi(argv[4]);

    OCTET *ImgIn,*ImgOut;

    lire_nb_lignes_colonnes_image_ppm(nomImageIn,&nH,&nW);

    nTaille = nH * nW; 

    int nTaille3 = 3 * nTaille; // On multiplie par 3 car 3 composantes (R,G,B)

    allocation_tableau(ImgIn,OCTET,nTaille3);
    allocation_tableau(ImgOut,OCTET,nTaille3);
    
    lire_image_ppm(nomImageIn,ImgIn,nTaille);

    for(int i = 0; i < nTaille3; i+=3) {

        int nR = ImgIn[i];
        int nG = ImgIn[i+1];
        int nB = ImgIn[i+2];

        if(nR < S_R) ImgOut[i] = 0; else ImgOut[i] = 255;
        if(nG < S_G) ImgOut[i+1] = 0; else ImgOut[i+1] = 255;
        if(nB < S_B) ImgOut[i+2] = 0; else ImgOut[i+2] = 255;

    }

    ecrire_image_ppm(nomImageOut,ImgOut,nH,nW);

    free(ImgIn);

    return 0;

}