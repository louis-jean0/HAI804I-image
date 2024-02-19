#include <stdio.h>
#include "image_ppm.h"  

int main(int argc, char* argv[]) {

    if(argc != 4) {
        printf("Utilisation : %s image.pgm fichier_sortie.dat image_out.pgm\n",argv[0]);
        exit(1);
    }

    int T[256]; // Tableau d'occurences pour les 256 niveaux de gris
    memset(T,0,sizeof(T));

    int nH,nW,nTaille; //nH taille d'une colonne (nb de pixels sur une colonne), nW taille d'une ligne (nb de pixels sur une ligne), nTaille taille totale
    
    char nomImgLue[256];
    char nomFichierSortie[256];
    char nomImgOut[256];

    OCTET *ImgIn, *ImgOut;

    sscanf(argv[1],"%s",nomImgLue);
    sscanf(argv[2],"%s",nomFichierSortie);
    sscanf(argv[3],"%s",nomImgOut);

    lire_nb_lignes_colonnes_image_pgm(nomImgLue,&nH,&nW);

    nTaille = nH * nW;

    allocation_tableau(ImgIn,OCTET,nTaille);
    allocation_tableau(ImgOut,OCTET,nTaille);
    lire_image_pgm(nomImgLue,ImgIn,nTaille);

    for(int k = 0; k < 256; k++) {
        for(int i = 0; i < nH; i++) {
            for(int j = 0; j < nW; j++) {
                if(ImgIn[i*nW+j] == k) {
                    T[k]++;
                }
            }
        }
    }

    OCTET a0 = 255;
    OCTET a1 = 0;

    for(int i = 0; i < 256; i++) {
        if (T[i] != 0) {
            if (i < a0) {
                a0 = i; 
            }
            if (i > a1) {
                a1 = i;
            }
        }
    }

    double alpha = (double)(-255 * a0) / (double)(a1 - a0);
    float beta = (double)255/(a1 - a0);

    printf("alpha : %f, beta : %f\n", alpha,beta);

    for(int i = 0; i < nTaille; i++) {
        ImgOut[i] = alpha + beta*ImgIn[i];
    }

    FILE *out = fopen(nomFichierSortie,"wb");

    if(out == NULL) {
        perror("Erreur lors de la création du fichier");
        exit(1);
    }

    fprintf(out,"# NDG Occurrences\n");

    for(int i = 0; i < 256; i++) {
        fprintf(out,"%d %d\n",i,T[i]);
    }

    fclose(out);

    ecrire_image_pgm(nomImgOut,ImgOut,nH,nW);

    return 0;

}