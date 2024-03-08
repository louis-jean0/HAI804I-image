#include "image_ppm.h"
#include <iostream>

void division_recursive_couleur(OCTET *ImgIn, OCTET *ImgOut, int x_debut_bloc, int x_fin_bloc, int y_debut_bloc, int y_fin_bloc, double seuil, int nW) {
    int largeur_bloc = x_fin_bloc - x_debut_bloc;
    int hauteur_bloc = y_fin_bloc - y_debut_bloc;
    
    double moyenneR, moyenneG, moyenneB;
    moyenne_bloc_couleur(ImgIn, x_debut_bloc, x_fin_bloc, y_debut_bloc, y_fin_bloc, nW, moyenneR, moyenneG, moyenneB);
    
    double varianceR, varianceG, varianceB;
    variance_bloc_couleur(ImgIn, x_debut_bloc, x_fin_bloc, y_debut_bloc, y_fin_bloc, nW, moyenneR, moyenneG, moyenneB, varianceR, varianceG, varianceB);
    
    double varianceMoyenne = (varianceR + varianceG + varianceB) / 3.0;
    double ecart_type = sqrt(varianceMoyenne);
    
    if (ecart_type <= seuil || largeur_bloc <= 8 || hauteur_bloc <= 8) {
        for(int i = y_debut_bloc; i < y_fin_bloc; i++) {
            for(int j = x_debut_bloc; j < x_fin_bloc; j++) {
                int indiceR = indiceImageCouleur('R', j, i, nW);
                int indiceG = indiceImageCouleur('G', j, i, nW);
                int indiceB = indiceImageCouleur('B', j, i, nW);
                ImgOut[indiceR] = moyenneR;
                ImgOut[indiceG] = moyenneG;
                ImgOut[indiceB] = moyenneB;
            }
        }
    } else {
        int x_milieu = x_debut_bloc + largeur_bloc / 2;
        int y_milieu = y_debut_bloc + hauteur_bloc / 2;
        
        division_recursive_couleur(ImgIn, ImgOut, x_debut_bloc, x_milieu, y_debut_bloc, y_milieu, seuil, nW);
        division_recursive_couleur(ImgIn, ImgOut, x_milieu, x_fin_bloc, y_debut_bloc, y_milieu, seuil, nW);
        division_recursive_couleur(ImgIn, ImgOut, x_debut_bloc, x_milieu, y_milieu, y_fin_bloc, seuil, nW);
        division_recursive_couleur(ImgIn, ImgOut, x_milieu, x_fin_bloc, y_milieu, y_fin_bloc, seuil, nW);
    }
}

int main(int argc, char* argv[]) {

    char nomImgLue[250],nomImgEcrite[250];
    int nH,nW,nTaille;

    if(argc != 4) {
        printf("Utilisation : %s image_in.pgm image_out.pgm seuil",argv[0]);
        exit(1);
    }

    sscanf(argv[1],"%s",nomImgLue);
    sscanf(argv[2],"%s",nomImgEcrite);
    int seuil = atoi(argv[3]);

    OCTET *ImgIn,*ImgOut;

    lire_nb_lignes_colonnes_image_ppm(nomImgLue,&nH,&nW);
    nTaille = nH * nW;
    int nTaille3 = 3 * nTaille;

    allocation_tableau(ImgIn,OCTET,nTaille3);
    lire_image_ppm(nomImgLue,ImgIn,nTaille);
    allocation_tableau(ImgOut,OCTET,nTaille3);

    division_recursive_couleur(ImgIn,ImgOut,0,nW,0,nH,seuil,nW);

    ecrire_image_ppm(nomImgEcrite,ImgOut,nH,nW);
    free(ImgIn);free(ImgOut);

    return 0;

} 