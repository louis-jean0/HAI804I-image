#include "image_ppm.h"
#include <iostream>
#include <cmath>

void division_recursive(OCTET *ImgIn, OCTET *ImgOut, int x_debut_bloc, int x_fin_bloc, int y_debut_bloc, int y_fin_bloc, int seuil, int nW) {
    int largeur_bloc = x_fin_bloc - x_debut_bloc;
    int hauteur_bloc = y_fin_bloc - y_debut_bloc;
    
    double moyenne = moyenne_bloc(ImgIn, x_debut_bloc, x_fin_bloc, y_debut_bloc, y_fin_bloc, nW);
    double variance = variance_bloc(ImgIn, moyenne, x_debut_bloc, x_fin_bloc, y_debut_bloc, y_fin_bloc, nW);
    double ecart_type = sqrt(variance);
    //std::cout<<"Ecart-type du bloc : "<<ecart_type<<std::endl;
    //std::cout<<"Taille du bloc : "<<hauteur_bloc*largeur_bloc<<std::endl;    
    if (ecart_type <= seuil || largeur_bloc <= 2 || hauteur_bloc <= 2) {
        for(int i = y_debut_bloc; i < y_fin_bloc; i++) {
            for(int j = x_debut_bloc; j < x_fin_bloc; j++) {
                ImgOut[indiceImage(i,j,nW)] = moyenne;
            }
        }
    } else {
        int x_milieu = x_debut_bloc + largeur_bloc / 2;
        int y_milieu = y_debut_bloc + hauteur_bloc / 2;
        
        division_recursive(ImgIn, ImgOut, x_debut_bloc, x_milieu, y_debut_bloc, y_milieu, seuil, nW);
        division_recursive(ImgIn, ImgOut, x_milieu, x_fin_bloc, y_debut_bloc, y_milieu, seuil, nW);
        division_recursive(ImgIn, ImgOut, x_debut_bloc, x_milieu, y_milieu, y_fin_bloc, seuil, nW);
        division_recursive(ImgIn, ImgOut, x_milieu, x_fin_bloc, y_milieu, y_fin_bloc, seuil, nW);
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

    lire_nb_lignes_colonnes_image_pgm(nomImgLue,&nH,&nW);
    nTaille = nH * nW;

    allocation_tableau(ImgIn,OCTET,nTaille);
    lire_image_pgm(nomImgLue,ImgIn,nTaille);
    allocation_tableau(ImgOut,OCTET,nTaille);

    double variance = variance_pgm(ImgIn,nH,nW);
    double ecart_type = sqrt(variance);
    std::cout<<"Ecart-type de l'image globale : "<<ecart_type<<std::endl;

    division_recursive(ImgIn,ImgOut,0,nW,0,nH,seuil,nW);

    ecrire_image_pgm(nomImgEcrite,ImgOut,nH,nW);
    free(ImgIn);free(ImgOut);

    return 0;

} 