#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "image_ppm.h"

int main(int argc, char* argv[]) {
    if(argc != 3) {
        printf("Utilisation : %s image.pgm fichier_sortie.dat\n",argv[0]);
        exit(1);
    }

    int T[256]; // Tableau d'occurrences pour les 256 niveaux de gris
    memset(T,0,sizeof(T));

    int nH,nW,nTaille; // nH, nW, et nTaille définis comme avant
    
    char nomImgLue[256];
    char nomFichierSortie[256];

    OCTET *ImgIn;

    sscanf(argv[1],"%s",nomImgLue);
    sscanf(argv[2],"%s",nomFichierSortie);

    lire_nb_lignes_colonnes_image_pgm(nomImgLue,&nH,&nW);
    nTaille = nH * nW;

    allocation_tableau(ImgIn,OCTET,nTaille);
    lire_image_pgm(nomImgLue,ImgIn,nTaille);

    // Calcul des occurrences comme avant
    for(int k = 0; k < 256; k++) {
        for(int i = 0; i < nH; i++) {
            for(int j = 0; j < nW; j++) {
                if(ImgIn[i*nW+j] == k) {
                    T[k]++;
                }
            }
        }
    }

    FILE *out = fopen(nomFichierSortie,"wb");
    if(out == NULL) {
        perror("Erreur lors de la création du fichier");
        exit(1);
    }

    fprintf(out,"# NDG Probabilites\n");
    // Calcul et écriture de la ddp
    for(int i = 0; i < 256; i++) {
        double prob = (double)T[i] / (double)nTaille;
        fprintf(out,"%d %.6f\n",i,prob);
    }

    fclose(out);

    return 0;
}
