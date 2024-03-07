#include "image_ppm.h"

int main(int argc, char* argv[]) {

    char nomImgLue[250],nomImgEcrite[250];
    int nH,nW,nTaille;

    if(argc != 3) {
        printf("Utilisation : %s image_in_filtree.pgm image_out.pgm",argv[0]);
        exit(1);
    }

    sscanf(argv[1],"%s",nomImgLue);
    sscanf(argv[2],"%s",nomImgEcrite);

    OCTET *ImgIn,*ImgOut; // ImgIn doit être une image filtrée

    lire_nb_lignes_colonnes_image_pgm(nomImgLue,&nH,&nW);
    nTaille = nH * nW;

    allocation_tableau(ImgIn,OCTET,nTaille);
    lire_image_pgm(nomImgLue,ImgIn,nTaille);
    allocation_tableau(ImgOut,OCTET,nTaille);

    for(int i = 1; i < nH - 1; i++) {
        for(int j = 1; j < nW - 1; j++) {

            int current_pixel = ImgIn[indiceImage(i,j,nW)];
            int right_pixel = ImgIn[indiceImage(i,j+1,nW)];
            int down_pixel = ImgIn[indiceImage(i+1,j,nW)];
            int left_pixel = ImgIn[indiceImage(i,j-1,nW)];
            int up_pixel = ImgIn[indiceImage(i-1,j,nW)];

            int laplacien = 4*current_pixel - up_pixel - down_pixel - left_pixel - right_pixel; // Ici on ne met pas +128

            ImgOut[indiceImage(i,j,nW)] = laplacien;

        }
    }

    ecrire_image_pgm(nomImgEcrite,ImgOut,nH,nW);
    free(ImgIn);free(ImgOut);

    return 0;

} 