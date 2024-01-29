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

    OCTET *ImgIn,*ImgOut1,*ImgOut2;

    lire_nb_lignes_colonnes_image_pgm(nomImgLue, &nH, &nW);

    nTaille = nH * nW;

    allocation_tableau(ImgIn, OCTET, nTaille);
    lire_image_pgm(nomImgLue, ImgIn, nTaille);
    allocation_tableau(ImgOut1, OCTET, nTaille);

    for(int x = 1; x < nW - 1; x++) { // Bons indices pour respecter les problèmes sur les bords
        for(int y = 1; y < nH - 1; y++) {
            int pixel = ImgIn[indiceImage(x, y, nW)];
            int vDroite = ImgIn[indiceImage(x + 1, y, nW)];
            int vGauche = ImgIn[indiceImage(x - 1, y, nW)];
            int vBas = ImgIn[indiceImage(x, y + 1, nW)];
            int vHaut = ImgIn[indiceImage(x, y - 1, nW)];

            if(vDroite || vGauche || vHaut || vBas) {
                ImgOut1[indiceImage(x, y, nW)] = 255;
            }

            else {
                ImgOut1[indiceImage(x, y, nW)] = ImgIn[indiceImage(x, y, nW)];
            }

        }
    }

    allocation_tableau(ImgOut2, OCTET, nTaille);

    for(int x = 1; x < nW - 1; x++) { // Bons indices pour respecter les problèmes sur les bords
        for(int y = 1; y < nH - 1; y++) {
            
            int pixel = ImgOut1[indiceImage(x, y, nW)];
            int vDroite = ImgOut1[indiceImage(x + 1, y, nW)];
            int vGauche = ImgOut1[indiceImage(x - 1, y, nW)];
            int vBas = ImgOut1[indiceImage(x, y + 1, nW)];
            int vHaut = ImgOut1[indiceImage(x, y - 1, nW)];

            if(!(vDroite || vGauche || vHaut || vBas)) {
                ImgOut2[indiceImage(x, y, nW)] = 0;
            }

            else {
                ImgOut2[indiceImage(x, y, nW)] = 255;
            }

        }

    }

    ecrire_image_pgm(nomImageEcrite, ImgOut2, nH, nW);
    free(ImgIn);
    free(ImgOut1);
    free(ImgOut2);

    return 0;


}
