#include "Image3D.hpp"

int main(int argc, char* argv[]) {

    if(argc != 5) {
        std::cout<<"Utilisation : "<<argv[0]<<" <nom_image_lue.img> <dimX> <dimY> <dimZ>"<<std::endl;
        exit(EXIT_FAILURE);
    }

    // On stocke le nom de l'image lue
    char image_read[256];
    sscanf(argv[1],"%s",image_read);

    // On stocke les dimensions nécessaires pour lire l'image
    int dimX, dimY, dimZ;
    dimX = atoi(argv[2]);
    dimY = atoi(argv[3]);
    dimZ = atoi(argv[4]);

    // On initialise la structure l'image 3D
    Image3D image3D(dimX, dimY, dimZ);

    // On charge l'image 3D dans notre structure
    load_image(image_read, image3D);

    // On demande de choisir un voxel pour ensuite afficher sa valeur
    int i, j, k;
    std::cout<<"Entrez les coordonnées du voxel (i j k) : ";
    std::cin>>i>>j>>k;
    std::cout<<"Intensité du voxel ["<<i<<","<<j<<","<<k<<"] : "<<image3D.get_value(i,j,k)<<std::endl;

    // On affiche la valeur minimale et maximale des voxels de l'image
    unsigned short min, max;
    find_min_max(image3D,min,max);
    std::cout<<"Valeur minimale : "<<min<<std::endl;
    std::cout<<"Valeur maximale : "<<max<<std::endl;

    return 0;

}