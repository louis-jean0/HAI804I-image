#include <stdio.h>
#include "image_ppm.h"

int main(int argc, char* argv[]) {

    if(argc != 5) {
        printf("Utilisation : %s image.pgm ligne_ou_colonne indice fichier_sortie.dat\n",argv[0]);
        exit(1);
    }

    int nH, nW, nTaille;
    int indice = atoi(argv[3]);
    char nomImgLue[256];
    char l_ou_col[10];
    char nomFichierSortie[256];

    OCTET *ImgIn;

    sscanf(argv[1],"%s",nomImgLue);
    sscanf(argv[2],"%s",l_ou_col);
    sscanf(argv[4],"%s",nomFichierSortie);

    lire_nb_lignes_colonnes_image_pgm(nomImgLue,&nH,&nW);

    nTaille = nH * nW;

    allocation_tableau(ImgIn,OCTET,nTaille);

    lire_image_pgm(nomImgLue,ImgIn,nTaille);

    FILE *out = fopen(nomFichierSortie,"wb");

    if(strcmp(l_ou_col,"ligne")) {

        for(int j = 0; j < nW; j++) {
            fprintf(out,"%d %d\n",j,ImgIn[j*nW+indice]);
        }

    }

    else if(strcmp(l_ou_col,"colonne")) {

        for(int i = 0; i < nH; i++) {
            fprintf(out,"%d %d\n",i,ImgIn[indice*nW+i]);
        }

    }   

    return 0;

}