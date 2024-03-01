#include "image_ppm.h"

int main(int argc, char* argv[]) {

    char nomImgLue[250],nomImgEcrite[250];
    int seuil,nH,nW,nTaille;

    if(argc != 4) {
        printf("Utilisation : %s image_in.pgm image_out.pgm seuil",argv[0]);
        exit(1);
    }

    sscanf(argv[1],"%s",nomImgLue);
    sscanf(argv[2],"%s",nomImgEcrite);
    sscanf(argv[3],"%d",&seuil);

    OCTET *ImgIn,*ImgOut;

    lire_nb_lignes_colonnes_image_pgm(nomImgLue,&nH,&nW);
    nTaille = nH * nW;

    allocation_tableau(ImgIn,OCTET,nTaille);
    lire_image_pgm(nomImgLue,ImgIn,nTaille);
    allocation_tableau(ImgOut,OCTET,nTaille);

    for(int i = 1; i < nH - 1; i++) {
        for(int j = 1; j < nW - 1; j++) {

            if(ImgIn[indiceImage(i,j,nW)] < seuil) {
                ImgOut[indiceImage(i,j,nW)] = 0;
            }

            else {
                ImgOut[indiceImage(i,j,nW)] = 255;
            }

        }
    }

    ecrire_image_pgm(nomImgEcrite,ImgOut,nH,nW);
    free(ImgIn);free(ImgOut);

    return 0;

}