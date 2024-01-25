#include <stdio.h>
#include "image_ppm.h"  

int main(int argc, char* argv[]) {

    if(argc != 3) {
        printf("Utilisation : %s image.ppm fichier_sortie.dat\n",argv[0]);
        exit(1);
    }

    int T[256*3];
    memset(T,0,sizeof(T));

    int nH, nW, nTaille;

    char nomImgLue[256];
    char nomFichierSortie[256];

    OCTET *ImgIn;

    sscanf(argv[1],"%s",nomImgLue);
    sscanf(argv[2],"%s",nomFichierSortie);

    lire_nb_lignes_colonnes_image_ppm(nomImgLue,&nH,&nW);

    nTaille = nH * nW;

    int nTaille3 = 3 * nTaille;

    allocation_tableau(ImgIn,OCTET,nTaille3);
    lire_image_ppm(nomImgLue,ImgIn,nTaille);

    FILE *out = fopen(nomFichierSortie,"wb");

    if(out == NULL) {
        perror("Erreur lors de la création du fichier");
        exit(1);
    }

    for(int k = 0; k < 256; k++) {

        for(int i = 0; i < nTaille3; i+=3) {
            int nR = ImgIn[i];
            int nG = ImgIn[i+1];
            int nB = ImgIn[i+2];
            
            if(nR == k) T[3*k]++;
            if(nG == k) T[(3*k)+1]++;
            if(nB == k) T[(3*k)+2]++;
        }
    }

    fprintf(out,"Ind NR NG NB\n");

    for(int k = 0; k < 256; k++) {

        fprintf(out,"%d %d %d %d\n",k,T[3*k],T[(3*k)+1],T[(3*k)+2]);

    }

    fclose(out);
    free(ImgIn);

    return 0;

}