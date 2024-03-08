#include "image_ppm.h"
#include <iostream>

int main(int argc, char* argv[]) {

    char nomImgLue[250],nomImgEcrite[250];
    int nH,nW,nTaille;

    if(argc != 3) {
        printf("Utilisation : %s image_in.pgm image_out.pgm",argv[0]);
        exit(1);
    }

    sscanf(argv[1],"%s",nomImgLue);
    sscanf(argv[2],"%s",nomImgEcrite);

    OCTET *ImgIn,*ImgOut;

    lire_nb_lignes_colonnes_image_pgm(nomImgLue,&nH,&nW);
    nTaille = nH * nW;

    allocation_tableau(ImgIn,OCTET,nTaille);
    lire_image_pgm(nomImgLue,ImgIn,nTaille);
    allocation_tableau(ImgOut,OCTET,nTaille);

    double somme[4] = {0,0,0,0};
    double count[4] = {0,0,0,0};
    double moyenne[4] = {0,0,0,0};
    double somme_carres_ecart[4] = {0,0,0,0};
    double variance[4] = {0,0,0,0};
    double ecart_type[4] = {0,0,0,0};

    for(int i = 0; i < nH; i++) {
        for(int j = 0; j < nW; j++) {
            int bloc = (i >= nH / 2) * 2 + (j >= nW / 2);
            int current_pixel = ImgIn[indiceImage(i,j,nW)];
            count[bloc]++;
            somme[bloc] += current_pixel;
        }
    }

    for(int i = 0; i < 4; i++) {
        moyenne[i] = somme[i]/count[i];
    }

    for(int i = 0; i < nH; i++) {
        for(int j = 0; j < nW; j++) {
            int bloc = (i >= nH / 2) * 2 + (j >= nW / 2);
            int current_pixel = ImgIn[indiceImage(i,j,nW)];
            double ecart = current_pixel - moyenne[bloc];
            somme_carres_ecart[bloc] += ecart * ecart;
        }
    }

    for(int i = 0; i < 4; i++) {
        variance[i] = somme_carres_ecart[i] / count[i];
        ecart_type[i] = sqrt(variance[i]);
        std::cout<<"Bloc "<<i<<" : moyenne = "<<moyenne[i]<<", variance = "<<variance[i]<<", écart-type = "<<ecart_type[i]<<std::endl;
    }

    for(int i = 0; i < nH; i++) {
        for(int j = 0; j < nW; j++) {
            int bloc = (i >= nH / 2) * 2 + (j >= nW / 2);
            int index_in = indiceImage(i,j,nW);
            ImgOut[index_in] = moyenne[bloc];
        }
    }

    ecrire_image_pgm(nomImgEcrite,ImgOut,nH,nW);
    free(ImgIn);free(ImgOut);

    return 0;

} 