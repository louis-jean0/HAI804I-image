#include "Image3D.hpp"
#include <cstring>

int main(int argc, char* argv[]) {

    if(argc != 8) {
        std::cout<<"Utilisation : "<<argv[0]<<" <nom_image_lue.img> <dimX> <dimY> <dimZ> <nom_image_ecrite.pgm> <x|y|z> <mip|aip|minip>"<<std::endl;
        exit(EXIT_FAILURE);
    }

    // On stocke le nom de l'image lue
    char image_read[256];
    sscanf(argv[1],"%s",image_read);

    // On stocke le nom de l'image écrite
    char image_write[256];
    sscanf(argv[5],"%s",image_write);

    // On stocke les dimensions nécessaires pour lire l'image
    int dimX, dimY, dimZ;
    dimX = atoi(argv[2]);
    dimY = atoi(argv[3]);
    dimZ = atoi(argv[4]);

    // On stocke l'axe selon lequel projeter
    int axis = 1; // x par défaut
    char axis_argv;
    sscanf(argv[6],"%c",&axis_argv);
    if(axis_argv == 'y') axis = 2;
    if(axis_argv == 'z') axis = 3;

    // On stocke le mode de visualisation
    int mode = 1; // MIP par défaut
    char mode_argv[10];
    sscanf(argv[7],"%s",mode_argv);
    if(strcmp(mode_argv,"aip") == 0) mode = 2;
    if(strcmp(mode_argv,"minip") == 0) mode = 3;

    // On initialise la structure l'image 3D
    Image3D image3D(dimX, dimY, dimZ);

    // On charge l'image 3D dans notre structure
    load_image(image_read, image3D);

    // On effectue la projection (qui s'occupera aussi d'écrire l'image)  
    std::vector<unsigned short> projection;
    generate_projection(image3D,projection,axis,mode,(const char*)image_write);

    return 0;

}