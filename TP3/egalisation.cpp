#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "image_ppm.h"

int main(int argc, char* argv[]) {
    if(argc != 3) {
        printf("Utilisation : %s entree.pgm sortie.pgm\n",argv[0]);
        exit(1);
    }

    int nH, nW, nTaille;
    char nomImgEntree[256], nomImgSortie[256];
    OCTET *ImgIn, *ImgOut;

    sscanf(argv[1], "%s", nomImgEntree);
    sscanf(argv[2], "%s", nomImgSortie);

    lire_nb_lignes_colonnes_image_pgm(nomImgEntree, &nH, &nW);
    nTaille = nH * nW;

    allocation_tableau(ImgIn, OCTET, nTaille);
    lire_image_pgm(nomImgEntree, ImgIn, nTaille);
    allocation_tableau(ImgOut, OCTET, nTaille);

    int T[256] = {0};
    double F[256] = {0.0}; // Fonction de répartition

    // Calcul des occurrences
    for(int i = 0; i < nTaille; i++) {
        T[ImgIn[i]]++;
    }

    // Calcul de la fonction de répartition F(a)
    F[0] = (double)T[0] / nTaille;
    for(int i = 1; i < 256; i++) {
        F[i] = F[i-1] + (double)T[i] / nTaille;
    }

    // Calcul de T(a) pour l'égalisation de l'histogramme
    for(int i = 0; i < 256; i++) {
        T[i] = (int)(255.0 * F[i]);
    }

    // Application de T(a) à l'image
    for(int i = 0; i < nTaille; i++) {
        ImgOut[i] = T[ImgIn[i]];
    }

    ecrire_image_pgm(nomImgSortie, ImgOut, nH, nW);

    free(ImgIn);
    free(ImgOut);

    return 0;
}
