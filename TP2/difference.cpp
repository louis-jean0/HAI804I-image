#include <cstdio>
#include <stdio.h>
#include "image_ppm.h"

int main(int argc, char* argv[]) {

    char nomImgLue1[256],nomImgLue2[256],nomImageEcrite[256];

    sscanf(argv[1],"%s",nomImgLue1);
    sscanf(argv[2],"%s",nomImgLue2);
    sscanf(argv[3],"%s",nomImageEcrite);

    int nH,nW,nTaille;

    if(argc != 4) {

        printf("Usage : %s image_in1.pgm image_in2.pgm image_out.pgm",argv[0]);

    }

    OCTET *ImgIn1,*ImgIn2,*ImgOut;

    lire_nb_lignes_colonnes_image_pgm(nomImgLue1, &nH, &nW);

    nTaille = nH * nW;

    allocation_tableau(ImgIn1, OCTET, nTaille);
    allocation_tableau(ImgIn2, OCTET, nTaille);
    lire_image_pgm(nomImgLue1, ImgIn1, nTaille);
    lire_image_pgm(nomImgLue2, ImgIn2, nTaille);
    allocation_tableau(ImgOut, OCTET, nTaille);

    for(int x = 0; x < nH; x++) {
        for(int y = 0; y < nW; y++) {
            
            int pixelNormal = ImgIn1[indiceImage(x, y, nW)];
            int pixelDilate = ImgIn2[indiceImage(x, y, nW)];

            if(pixelNormal == 255 && pixelDilate == 255) {

                ImgOut[indiceImage(x, y, nW)] = 255;

            }

            else if(pixelNormal == 0 && pixelDilate == 0) {
               
                ImgOut[indiceImage(x, y, nW)] = 255;
            
            }

            else {

                ImgOut[indiceImage(x, y, nW)] = 0;

            }

        }
    }

    ecrire_image_pgm(nomImageEcrite, ImgOut, nH, nW);
    free(ImgIn1);
    free(ImgIn2);
    free(ImgOut);

    return 0;

}