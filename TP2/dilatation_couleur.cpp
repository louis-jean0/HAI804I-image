#include <stdio.h>
#include "image_ppm.h"

int main(int argc, char* argv[]) {

    char nomImgLue[256],nomImageEcrite[256];

    sscanf(argv[1],"%s",nomImgLue);
    sscanf(argv[2],"%s",nomImageEcrite);

    int nH,nW,nTaille,nTaille3;

    if(argc != 3) {

        printf("Usage : %s image_in.ppm image_out.ppm",argv[0]);

    }

    OCTET *ImgIn,*ImgOut;

    lire_nb_lignes_colonnes_image_ppm(nomImgLue, &nH, &nW);

    nTaille = nH * nW;
    nTaille3 = nTaille * 3;

    allocation_tableau(ImgIn, OCTET, nTaille3);
    lire_image_ppm(nomImgLue, ImgIn, nTaille);
    allocation_tableau(ImgOut, OCTET, nTaille3);

    dilatation_couleur(ImgIn, ImgOut, nH, nW);

    ecrire_image_ppm(nomImageEcrite, ImgOut, nH, nW);
    free(ImgIn);
    free(ImgOut);

    return 0;

}