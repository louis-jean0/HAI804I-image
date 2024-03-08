#include "image_ppm.h"

int main(int argc, char* argv[]) {

    char nomImgLue[250],nomImgEcrite[250];
    int sB,sH,nH,nW,nTaille;

    if(argc != 5) {
        printf("Utilisation : %s image_in.pgm image_out.pgm seuil_bas seuil_haut",argv[0]);
        exit(1);
    }

    sscanf(argv[1],"%s",nomImgLue);
    sscanf(argv[2],"%s",nomImgEcrite);
    sB = atoi(argv[3]);
    sH = atoi(argv[4]);

    OCTET *ImgIn,*ImgPreSeuillee,*ImgOut;

    lire_nb_lignes_colonnes_image_pgm(nomImgLue,&nH,&nW);
    nTaille = nH * nW;

    allocation_tableau(ImgIn,OCTET,nTaille);
    lire_image_pgm(nomImgLue,ImgIn,nTaille);
    allocation_tableau(ImgPreSeuillee,OCTET,nTaille);
    allocation_tableau(ImgOut,OCTET,nTaille);

    // Première lecture

    for(int i = 0; i < nH; i++) {
        for(int j = 0; j < nW; j++) {

            if(ImgIn[indiceImage(i,j,nW)] <= sB) {
                ImgPreSeuillee[indiceImage(i,j,nW)] = 0;
            }

            else if(ImgIn[indiceImage(i,j,nW)] >= sH) {
                ImgPreSeuillee[indiceImage(i,j,nW)] = 255;
            }

            else {
                ImgPreSeuillee[indiceImage(i,j,nW)] = ImgIn[indiceImage(i,j,nW)];
            }

        }
    }

    // Deuxième lecture

    for(int i = 1; i < nH - 1; i++) {
        for(int j = 1; j < nW - 1; j++) {

            int current_pixel = ImgPreSeuillee[indiceImage(i,j,nW)];
            int vDroite = ImgPreSeuillee[indiceImage(i+1,j,nW)];
            int vGauche = ImgPreSeuillee[indiceImage(i-1,j,nW)];
            int vBas = ImgPreSeuillee[indiceImage(i,j+1,nW)];
            int vHaut = ImgPreSeuillee[indiceImage(i,j-1,nW)];
            int vHd = ImgPreSeuillee[indiceImage(i+1,j-1,nW)];
            int vBd = ImgPreSeuillee[indiceImage(i+1,j+1,nW)];
            int vHg = ImgPreSeuillee[indiceImage(i-1,j-1,nW)];
            int vBg = ImgPreSeuillee[indiceImage(i-1,j+1,nW)];

            int deltaX = abs(vDroite - current_pixel);
            int deltaY = abs(vBas - current_pixel);

            int norme = sqrt((deltaX * deltaX)+(deltaY * deltaY));

            int pixel = ImgPreSeuillee[indiceImage(i,j,nW)];

            if(sB < pixel && sH > pixel && ((vDroite == 255) || (vGauche == 255) || (vBas == 255) || (vHaut == 255) || (vHd == 255) || (vBd == 255) || (vHg == 255) || (vBg == 255))) {
                pixel = 255;
            }
            else {
                pixel = 0;
            }

            ImgOut[indiceImage(i,j,nW)] = pixel;

        }
    }

    ecrire_image_pgm(nomImgEcrite,ImgOut,nH,nW);
    free(ImgIn);free(ImgPreSeuillee);free(ImgOut);

    return 0;

}