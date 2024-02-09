#include <stdio.h>
#include "image_ppm.h"
#include <stdlib.h>

int main(int argc, char* argv[]) {

    if (argc != 4) {
        printf("Usage: %s image_in.ppm image_seuillee.pgm image_out.ppm\n", argv[0]);
        return 1;
    }

    char nomImgIn[256], nomImgSeuillee[256], nomImgOut[256];
    int nH, nW, nTaille;

    sscanf(argv[1], "%s", nomImgIn);
    sscanf(argv[2], "%s", nomImgSeuillee);
    sscanf(argv[3], "%s", nomImgOut);

    OCTET *ImgIn, *ImgSeuillee, *ImgOut;

    lire_nb_lignes_colonnes_image_ppm(nomImgIn,&nH,&nW);

    nTaille = nH * nW;
    int nTaille3 = nTaille * 3;

    allocation_tableau(ImgIn,OCTET,nTaille3);
    allocation_tableau(ImgSeuillee,OCTET,nTaille);
    allocation_tableau(ImgOut,OCTET,nTaille3);

    lire_image_ppm(nomImgIn,ImgIn,nTaille);
    lire_image_pgm(nomImgSeuillee,ImgSeuillee,nTaille);

    // Copie de l'image de base pour gérer les bords
    for(int i = 0; i < nTaille3; i++) {
      ImgOut[i] = ImgIn[i];
    }

    for(int j = 1; j < nH - 1; j++) {
        for(int i = 1; i < nW - 1; i++) {
            if(ImgSeuillee[indiceImage(i,j,nW)] == 0) {
                for (int c = 0; c < 3; c++) {
                    int sum = 0;
                    for (int dj = -1; dj <= 1; dj++) {
                        for (int di = -1; di <= 1; di++) {
                            sum += ImgIn[indiceImageCouleur(i + di, j + dj, nW, c)];
                        }
                    }
                    ImgOut[indiceImageCouleur(i, j, nW, c)] = sum / 9;
                }
            }
        }
    }
    ecrire_image_ppm(nomImgOut, ImgOut, nH, nW);
    free(ImgIn);
    free(ImgSeuillee);
    free(ImgOut);
}
