#include <stdio.h>
#include "image_ppm.h"
#include <stdlib.h>

int main(int argc, char* argv[]) {

    if (argc != 4) {
        printf("Usage: %s image_in.pgm image_truth.pgm nb_seuils\n", argv[0]);
        return 1;
    }

    char cNomImgLue[250], cNomImgVerite[250];
    int nH, nW, nTaille, nb_seuils;

    sscanf(argv[1], "%s", cNomImgLue);
    sscanf(argv[2], "%s", cNomImgVerite);
    nb_seuils = atoi(argv[3]);

    OCTET *ImgIn, *ImgVerite;

    lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
    nTaille = nH * nW;

    allocation_tableau(ImgIn, OCTET, nTaille);
    allocation_tableau(ImgVerite, OCTET, nTaille);

    lire_image_pgm(cNomImgLue, ImgIn, nTaille);
    lire_image_pgm(cNomImgVerite, ImgVerite, nTaille);

    FILE *fichierROC = fopen("roc_data.dat", "w");
    if(fichierROC == NULL) {
        perror("Erreur lors de l'ouverture du fichier roc_data.dat");
        exit(EXIT_FAILURE);
    }
    fprintf(fichierROC, "# Seuil TPR FPR\n");

    for (int seuil = 0; seuil < 256; seuil += 256 / nb_seuils) {
        int TP = 0, FP = 0, TN = 0, FN = 0;

        for (int i = 0; i < nTaille; i++) {
            int pixelSeuille = (ImgIn[i] > seuil) ? 255 : 0;
            int pixelVerite = ImgVerite[i];

            if (pixelVerite == 255 && pixelSeuille == 255) TP++;
            else if (pixelVerite == 255 && pixelSeuille == 0) FN++;
            else if (pixelVerite == 0 && pixelSeuille == 255) FP++;
            else if (pixelVerite == 0 && pixelSeuille == 0) TN++;
        }

        // À ce stade, vous avez TP, FP, TN et FN pour le seuil actuel
        // Vous pouvez maintenant calculer la sensibilité et la spécificité et les imprimer
        float TPR = (TP + FN) > 0 ? (float)TP / (TP + FN) : 0; // Sensibilité, Taux de vrai positif
        float FPR = (FP + TN) > 0 ? (float)FP / (FP + TN) : 0; // 1 - Spécificité, Taux de faux positif

        printf("Seuil: %d, TPR: %f, FPR: %f, TP: %d, FP: %d, TN: %d, FN: %d\n", seuil, TPR, FPR, TP, FP, TN, FN);

        fprintf(fichierROC, "%d %f %f\n", seuil, TPR, FPR);
    }

    fclose(fichierROC);

    free(ImgIn);
    free(ImgVerite);

    return 0;
}
