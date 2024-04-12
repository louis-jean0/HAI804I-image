#include "Image3D.hpp"

int main(int argc, char* argv[]) {

    if(argc != 10) {
            std::cout<<"Utilisation : "<<argv[0]<<" <nom_image_lue.img> <dimX> <dimY> <dimZ> <sizeXVoxel> <sizeYVoxel> <sizeZVoxel> <nom_maillage_ecrit.stl> <seuil>"<<std::endl;
            exit(EXIT_FAILURE);
    }

     // On stocke le nom de l'image lue
    char image_read[256];
    sscanf(argv[1],"%s",image_read);

    // On stocke le nom du maillage écrit
    char mesh_write[256];
    sscanf(argv[8],"%s",mesh_write);

    // On stocke les dimensions nécessaires pour lire l'image
    int dimX, dimY, dimZ;
    dimX = atoi(argv[2]);
    dimY = atoi(argv[3]);
    dimZ = atoi(argv[4]);

    // On stocke les dimensions d'un voxel (image anisotrope parfois donc nécessaire)
    float sizeX, sizeY, sizeZ;
    sizeX = atof(argv[5]);
    sizeY = atof(argv[6]);
    sizeZ = atof(argv[7]);

    // On stocke le seuil
    int seuil = atoi(argv[9]);

    // On initialise la structure l'image 3D
    Image3D image3D(dimX, dimY, dimZ);

    // On charge l'image 3D dans notre structure
    load_image(image_read, image3D);

    // On initialise le vecteur de sommets que l'on utilisera pour stocker les coordonnées réelles des voxels
    // Vertex est une structure de données créée dans Image3D.hpp
    std::vector<Vertex> vertices;

    // On ouvre le fichier dans lequel on va écrire
    std::ofstream stl_file;
    stl_file.open(mesh_write);
    if(!stl_file.is_open()) {
        std::cout<<"Erreur lors de la création du fichier STL pour écriture"<<std::endl;
        exit(EXIT_FAILURE);
    }

    std::vector<std::string> triangles;

    stl_file<<"solid mesh"<<std::endl;

    for(int i = 1; i < dimX - 1; ++i) { // On évite les bords
        for(int j = 1; j < dimY - 1; ++j) {
            for(int k = 1; k < dimZ - 1; ++k) {
                unsigned short current_value = image3D.get_value(i,j,k);
                if(current_value > seuil) {
                    vertices = generate_voxel_vertices(i,j,k,sizeX,sizeY,sizeZ);
                    if (image3D.get_value(i-1,j,k) < seuil) {
                        std::ostringstream triangle1;
                        std::ostringstream triangle2;
                        write_to_triangle(triangle1,vertices[0],vertices[3],vertices[7]);
                        write_to_triangle(triangle2,vertices[7],vertices[4],vertices[0]);
                        triangles.push_back(triangle1.str());
                        triangles.push_back(triangle2.str());
                    }
                    if(image3D.get_value(i+1,j,k) < seuil) {
                        std::ostringstream triangle1;
                        std::ostringstream triangle2;
                        write_to_triangle(triangle1,vertices[1],vertices[2],vertices[6]);
                        write_to_triangle(triangle2,vertices[6],vertices[5],vertices[1]);
                        triangles.push_back(triangle1.str());
                        triangles.push_back(triangle2.str());
                    }
                    if(image3D.get_value(i,j-1,k) < seuil) {
                        std::ostringstream triangle1;
                        std::ostringstream triangle2;
                        write_to_triangle(triangle1,vertices[1],vertices[5],vertices[4]);
                        write_to_triangle(triangle2,vertices[4],vertices[0],vertices[1]);
                        triangles.push_back(triangle1.str());
                        triangles.push_back(triangle2.str());
                    }
                    if(image3D.get_value(i,j+1,k) < seuil) {
                        std::ostringstream triangle1;
                        std::ostringstream triangle2;
                        write_to_triangle(triangle1,vertices[3],vertices[7],vertices[6]);
                        write_to_triangle(triangle2,vertices[6],vertices[2],vertices[3]);
                        triangles.push_back(triangle1.str());
                        triangles.push_back(triangle2.str());
                    }
                    if(image3D.get_value(i,j,k-1) < seuil) {
                        std::ostringstream triangle1;
                        std::ostringstream triangle2;
                        write_to_triangle(triangle1,vertices[1],vertices[2],vertices[3]);
                        write_to_triangle(triangle2,vertices[3],vertices[0],vertices[1]);
                        triangles.push_back(triangle1.str());
                        triangles.push_back(triangle2.str());
                    }
                    if(image3D.get_value(i,j,k+1) < seuil) {
                        std::ostringstream triangle1;
                        std::ostringstream triangle2;
                        write_to_triangle(triangle1,vertices[5],vertices[6],vertices[7]);
                        write_to_triangle(triangle2,vertices[7],vertices[4],vertices[5]);
                        triangles.push_back(triangle1.str());
                        triangles.push_back(triangle2.str());
                    }
                }   
            }
        }
    }

    for (const auto& tri : triangles) {
    stl_file<<tri;
    }

    stl_file<<"endsolid mesh"<<std::endl;
    stl_file.close();

    return 0;

}