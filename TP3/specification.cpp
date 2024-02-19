#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "image_ppm.h"

void calculerFR(OCTET* img, int nTaille, double F[256]) {
    int histogram[256] = {0};
    for(int i = 0; i < nTaille; i++) {
        histogram[img[i]]++;
    }
    F[0] = histogram[0] / (double)nTaille;
    for(int i = 1; i < 256; i++) {
        F[i] = F[i-1] + (double)histogram[i] / nTaille;
    }
}

int main(int argc, char* argv[]) {
    if(argc != 4) {
        printf("Usage: %s imageB.pgm imageR.pgm sortieB_specifiee.pgm\n", argv[0]);
        exit(1);
    }

    int nH, nW, nTaille, nH_R, nW_R, nTaille_R;
    char *nomImgB = argv[1], *nomImgR = argv[2], *nomImgSortie = argv[3];
    OCTET *ImgB, *ImgB_egalisee, *ImgR, *ImgB_specifiee;

    // Lecture de l'image B
    lire_nb_lignes_colonnes_image_pgm(nomImgB, &nH, &nW);
    nTaille = nH * nW;
    allocation_tableau(ImgB, OCTET, nTaille);
    lire_image_pgm(nomImgB, ImgB, nTaille);

    // Calcul de l'histogramme de B
int histogramB[256] = {0};
for(int i = 0; i < nTaille; i++) {
    histogramB[ImgB[i]]++;
}

// Calcul de la fonction de répartition FB pour B
double F_B[256];
F_B[0] = (double)histogramB[0] / nTaille;
for(int i = 1; i < 256; i++) {
    F_B[i] = F_B[i - 1] + (double)histogramB[i] / nTaille;
}

// Allocation de l'image B égalisée
allocation_tableau(ImgB_egalisee, OCTET, nTaille);

// Égalisation de l'histogramme de B
for(int i = 0; i < nTaille; i++) {
    ImgB_egalisee[i] = (int)(255 * F_B[ImgB[i]]);
}


    // Lecture de l'image R
    lire_nb_lignes_colonnes_image_pgm(nomImgR, &nH_R, &nW_R);
    nTaille_R = nH_R * nW_R;
    allocation_tableau(ImgR, OCTET, nTaille_R);
    lire_image_pgm(nomImgR, ImgR, nTaille_R);

    // Calcul des fonctions de répartition FR et FB
    double F_R[256];
    calculerFR(ImgR, nTaille_R, F_R);
    calculerFR(ImgB_egalisee, nTaille, F_B); // Assumer que ImgB_egalisee est déjà calculé

    // Création de la table de correspondances
    int correspondance[256];
    for(int i = 0; i < 256; i++) {
        double minDiff = fabs(F_B[i] - F_R[0]);
        correspondance[i] = 0;
        for(int j = 1; j < 256; j++) {
            double diff = fabs(F_B[i] - F_R[j]);
            if(diff < minDiff) {
                minDiff = diff;
                correspondance[i] = j;
            }
        }
    }

    // Application de la table de correspondance à B égalisée pour spécifier l'histogramme
    allocation_tableau(ImgB_specifiee, OCTET, nTaille);
    for(int i = 0; i < nTaille; i++) {
        ImgB_specifiee[i] = correspondance[ImgB_egalisee[i]];
    }

    ecrire_image_pgm(nomImgSortie, ImgB_specifiee, nH, nW);

    free(ImgB);
    free(ImgB_egalisee);
    free(ImgR);
    free(ImgB_specifiee);

    return 0;
}
