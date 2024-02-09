#include <stdio.h>
#include "image_ppm.h"
#include <stdlib.h>

int main(int argc, char* argv[]) {

    if (argc != 3) {
        printf("Usage: %s image_in.ppm image_out.ppm\n", argv[0]);
        return 1;
    }

    char cNomImgLue[250], cNomImgEcrite[250];
    int nH, nW, nTaille;

    sscanf(argv[1], "%s", cNomImgLue);
    sscanf(argv[2], "%s", cNomImgEcrite);

    OCTET *ImgIn, *ImgOut;

    lire_nb_lignes_colonnes_image_ppm(cNomImgLue, &nH, &nW);
    nTaille = nH * nW;
    int nTaille3 = nTaille * 3;

    allocation_tableau(ImgIn, OCTET, nTaille3);
    lire_image_ppm(cNomImgLue, ImgIn, nTaille);
    allocation_tableau(ImgOut, OCTET, nTaille3);

    for(int i = 0; i < nTaille3; i++) {
      ImgOut[i] = ImgIn[i];
    }

    for (int j = 1; j < nH - 1; j++) {
        for (int i = 1; i < nW - 1; i++) {
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

    ecrire_image_ppm(cNomImgEcrite, ImgOut, nH, nW);
    free(ImgIn);
    free(ImgOut);

    return 0;
}
