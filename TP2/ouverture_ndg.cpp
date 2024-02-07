#include <stdio.h>
#include "image_ppm.h"

int main(int argc, char* argv[]) {

    char nomImgLue[256],nomImageEcrite[256];

    sscanf(argv[1],"%s",nomImgLue);
    sscanf(argv[2],"%s",nomImageEcrite);

    int nH,nW,nTaille;

    if(argc != 3) {

        printf("Usage : %s image_in.pgm image_out.pgm",argv[0]);

    }

    OCTET *ImgIn,*ImgOut;

    lire_nb_lignes_colonnes_image_pgm(nomImgLue, &nH, &nW);

    nTaille = nH * nW;

    allocation_tableau(ImgIn, OCTET, nTaille);
    lire_image_pgm(nomImgLue, ImgIn, nTaille);
    allocation_tableau(ImgOut, OCTET, nTaille);

    ouverture_ndg(ImgIn,ImgOut,nH,nW);

    ecrire_image_pgm(nomImageEcrite, ImgOut, nH, nW);
    free(ImgIn);
    free(ImgOut);

    return 0;


}
