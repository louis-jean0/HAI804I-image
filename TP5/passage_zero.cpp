#include "image_ppm.h"
#include <cmath>

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

    for(int i = 1; i < nH - 1; i++) {
        for(int j = 1; j < nW - 1; j++) {

            int current_pixel = ImgIn[indiceImage(i,j,nW)];
            int right_pixel = ImgIn[indiceImage(i+1,j,nW)];
            int down_pixel = ImgIn[indiceImage(i,j+1,nW)];

            int deltaX = abs(right_pixel - current_pixel);
            int deltaY = abs(down_pixel - current_pixel);

            int norme = sqrt((deltaX * deltaX)+(deltaY * deltaY));

            float phase = atan((float)deltaY/(float)deltaX);

        }
    }

    ecrire_image_pgm(nomImgEcrite,ImgOut,nH,nW);
    free(ImgIn);free(ImgOut);

    return 0;

} 