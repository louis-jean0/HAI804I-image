#include <stdio.h>
#include <stdlib.h>
#include "image_ppm.h"

void flouImage(OCTET *ImgIn, OCTET *ImgOut, int nH, int nW) {
    for (int i = 0; i < nH; i++) {
        for (int j = 0; j < nW; j++) {
            int somme = 0;
            int count = 0;

            for (int ki = -1; ki <= 1; ki++) {
                for (int kj = -1; kj <= 1; kj++) {
                    int ni = i + ki;
                    int nj = j + kj;

                    if (ni >= 0 && ni < nH && nj >= 0 && nj < nW) {
                        somme += ImgIn[ni * nW + nj];
                        count++;
                    }
                }
            }

            ImgOut[i * nW + j] = somme / count;
        }
    }
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("Usage: %s entree.pgm sortie.pgm\n", argv[0]);
        exit(1);
    }

    char *nomImgEntree = argv[1], *nomImgSortie = argv[2];
    int nH, nW, nTaille;
    OCTET *ImgIn, *ImgOut;

    lire_nb_lignes_colonnes_image_pgm(nomImgEntree, &nH, &nW);
    nTaille = nH * nW;

    allocation_tableau(ImgIn, OCTET, nTaille);
    lire_image_pgm(nomImgEntree, ImgIn, nTaille);
    allocation_tableau(ImgOut, OCTET, nTaille);

    flouImage(ImgIn, ImgOut, nH, nW);

    ecrire_image_pgm(nomImgSortie, ImgOut, nH, nW);

    free(ImgIn);
    free(ImgOut);

    return 0;
}
