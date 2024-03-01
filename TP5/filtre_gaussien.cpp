#include "image_ppm.h"

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
        ImgOut[i] = ImgIn[i];
    }

    for(int i = 1; i < nH - 1; i++) {
        for(int j = 1; j < nW - 1; j++) {
        
            int current_pixel = ImgIn[indiceImage(i,j,nW)];
            int vDroite = ImgIn[indiceImage(i+1,j,nW)];
            int vGauche = ImgIn[indiceImage(i-1,j,nW)];
            int vBas = ImgIn[indiceImage(i,j+1,nW)];
            int vHaut = ImgIn[indiceImage(i,j-1,nW)];
            int vHd = ImgIn[indiceImage(i+1,j-1,nW)];
            int vBd = ImgIn[indiceImage(i+1,j+1,nW)];
            int vHg = ImgIn[indiceImage(i-1,j-1,nW)];
            int vBg = ImgIn[indiceImage(i-1,j+1,nW)];

            int gauss = 4*(vDroite + vGauche + vBas + vHaut) + 8*current_pixel + vHd + vBd + vHg + vBg;

            ImgOut[indiceImage(i,j,nW)] = floor(gauss/28);

        }
    }

    ecrire_image_pgm(nomImgEcrite,ImgOut,nH,nW);
    free(ImgIn);free(ImgOut);

    return 0;

}