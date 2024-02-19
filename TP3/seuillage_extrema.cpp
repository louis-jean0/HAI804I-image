#include <stdio.h>
#include "image_ppm.h"  

int seuil(int valeur, int smin, int smax) {
    if (valeur < smin) return smin;
    else if (valeur > smax) return smax;
    else return valeur;
}

void appliquerSeuil(OCTET* img, int nTaille, int smin, int smax) {
    for(int i = 0; i < nTaille; i++) {
        img[i] = seuil(img[i], smin, smax);
    }
}

int main(int argc, char* argv[]) {
    if(argc != 3) {
        printf("Utilisation : %s image.ppm image_out.ppm\n", argv[0]);
        exit(1);
    }

    int nH, nW, nTaille;
    char nomImgLue[256];
    char nomImgOut[256];

    OCTET *ImgIn, *ImgR, *ImgG, *ImgB;

    sscanf(argv[1], "%s", nomImgLue);
    sscanf(argv[2], "%s", nomImgOut);

    lire_nb_lignes_colonnes_image_ppm(nomImgLue, &nH, &nW);
    nTaille = nH * nW;

    allocation_tableau(ImgIn, OCTET, 3 * nTaille);
    allocation_tableau(ImgR, OCTET, nTaille);
    allocation_tableau(ImgG, OCTET, nTaille);
    allocation_tableau(ImgB, OCTET, nTaille);

    lire_image_ppm(nomImgLue, ImgIn, nTaille);
    planR(ImgR,ImgIn,nTaille);
    planG(ImgG,ImgIn,nTaille);
    planB(ImgB,ImgIn,nTaille);

    // Seuils à définir selon l'analyse de l'histogramme
    int sminR = 10;
    int smaxR = 240;
    int sminG = 10;
    int smaxG = 240;
    int sminB = 20;
    int smaxB = 240;

    appliquerSeuil(ImgR, nTaille, sminR, smaxR);
    appliquerSeuil(ImgG, nTaille, sminG, smaxG);
    appliquerSeuil(ImgB, nTaille, sminB, smaxB);

    for (int i = 0; i < nTaille; i++) {
        ImgIn[3*i] = ImgR[i];
        ImgIn[3*i+1] = ImgG[i];
        ImgIn[3*i+2] = ImgB[i];
    }

    ecrire_image_ppm(nomImgOut, ImgIn, nH, nW);

    free(ImgR);
    free(ImgG);
    free(ImgB);
    free(ImgIn);

    return 0;
}
