#include "image_ppm.h"
#include <iostream>
#include <cmath>
#include <tgmath.h>

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

    for(int i = 0; i < nTaille; i++) {
        std::cout<<(int)ImgIn[i]<<std::endl;
    }

    for(int i = 1; i < nH - 1; i++) {
        for(int j = 1; j < nW - 1; j++) {

            int current_pixel = ImgIn[indiceImage(i,j,nW)];
            int right_pixel = ImgIn[indiceImage(i,j+1,nW)];
            int down_pixel = ImgIn[indiceImage(i+1,j,nW)];
            int left_pixel = ImgIn[indiceImage(i,j-1,nW)];
            int up_pixel = ImgIn[indiceImage(i-1,j,nW)];
            int diag_bas_droite_pixel = ImgIn[indiceImage(i+1,j+1,nW)];
            int diag_haut_droite_pixel = ImgIn[indiceImage(i-1,j+1,nW)];

            int deltaX = abs(right_pixel - current_pixel);
            int deltaY = abs(down_pixel - current_pixel);

            int norme = sqrt((deltaX * deltaX)+(deltaY * deltaY));

            float phase = atan2((float)deltaY,(float)deltaX);

            int pixel_out = 0;

            if(phase >= -M_PI/8 && phase < M_PI/8) {
                // Horizontal (droite)
                if(current_pixel * right_pixel < 0) {pixel_out = 255;}
            }
            else if(phase >= M_PI/8 && phase < 3*M_PI/8) {
                // Diagonale bas droite
                if(current_pixel * diag_bas_droite_pixel < 0) {pixel_out = 255;}
            }
            else if((phase >= 3*M_PI/8 && phase <= M_PI/2) || (phase < -3*M_PI/8 && phase >= -M_PI/2)) {
                // Bas
                if(current_pixel * down_pixel < 0) {pixel_out = 255;}
            }
            else if(phase >= -3*M_PI/8 && phase < -M_PI/8) {
                // Diagonale haut droite
                if(current_pixel * diag_haut_droite_pixel < 0) {pixel_out = 255;}
            }
            else if(current_pixel * up_pixel < 0) {
                // Haut
                pixel_out = 255;
            }
            //std::cout<<pixel_out<<std::endl;
            ImgOut[indiceImage(i,j,nW)] = pixel_out;
        }
    }

    ecrire_image_pgm(nomImgEcrite,ImgOut,nH,nW);
    free(ImgIn);free(ImgOut);

    return 0;

} 