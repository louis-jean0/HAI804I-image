#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>
#include <numeric>
#include <fstream>
#include <string>
#include <sstream>

struct Image3D {
    std::vector<unsigned short> data; // Stockage des voxels
    int dimX, dimY, dimZ; // Stockage des dimensions

    // Constructeur
    Image3D(int x, int y, int z) : dimX(x), dimY(y), dimZ(z) {
        // Il y a dimX * dimY * dimZ voxels dans l'image
        data.resize(dimX * dimY * dimZ);
    }

    // Méthode pour récupérer l'index d'un voxel
    int get_index(int i, int j, int k) const {
        return k * dimX * dimY + j * dimX + i; // Adapté pour le balayage de l'annexe C
        // k * dimX * dimY pour se déplacer de coupe en coupe
        // j * dimX pour se déplacer de ligne en ligne à l'intérieur d'une coupe
        // i pour se déplacer de colonne en colonne à l'intérieur d'une ligne
    }

    // Méthode pour récupérer la valeur d'un voxel
    unsigned short get_value(int i, int j, int k) const {
        return data[get_index(i,j,k)];
    }

    // Méthode pour définir la valeur d'un voxel
    void set_value(int i, int j, int k, unsigned short value) {
        data[get_index(i,j,k)] = value;
    }
};

// Fonction pour charger une image
void load_image(char* image_read, Image3D &image3D) {
    FILE* file = fopen(image_read, "r");
    if (!file) {
        std::cout<<"Erreur lors de l'ouverture de l'image"<<std::endl;
        exit(EXIT_FAILURE);
    }
    // On lit de k en i pour respecter le balayage
    for(int k = 0; k < image3D.dimZ; ++k) {
        for(int j = 0; j < image3D.dimY; ++j) {
            for(int i = 0; i < image3D.dimX; ++i) {
                unsigned char bytes[2]; // Ici, les voxels sont stockés sur 2 octets
                if(fread(&bytes, sizeof(unsigned char), 2, file) != 2) { // Il faut indiquer à fread que l'on veut lire 2 octets
                    std::cout<<"Erreur lors de la lecture de l'image"<<std::endl;
                    exit(EXIT_FAILURE);
                }
                unsigned short current_voxel_read = 256 * bytes[0] + bytes[1]; // Comme dans l'exemple de la slide 35 du cours (format Big Endian), si on fait 256 * bytes[1] + bytes[0] alors on trouve 58368 (erreur mentionnée au tableau)
                image3D.set_value(i,j,k,current_voxel_read);
            }
        }
    }
}

struct Vertex {
    float x,y,z;
};

// Fonction pour générer les sommets d'un voxel
std::vector<Vertex> generate_voxel_vertices(int i, int j, int k, float sizeX, float sizeY, float sizeZ) {
    std::vector<Vertex> vertices(8);
    vertices[0] = { (i - 0.5f) * sizeX, (j - 0.5f) * sizeY, (k - 0.5f) * sizeZ };
    vertices[1] = { (i + 0.5f) * sizeX, (j - 0.5f) * sizeY, (k - 0.5f) * sizeZ };
    vertices[2] = { (i + 0.5f) * sizeX, (j + 0.5f) * sizeY, (k - 0.5f) * sizeZ };
    vertices[3] = { (i - 0.5f) * sizeX, (j + 0.5f) * sizeY, (k - 0.5f) * sizeZ };
    vertices[4] = { (i - 0.5f) * sizeX, (j - 0.5f) * sizeY, (k + 0.5f) * sizeZ };
    vertices[5] = { (i + 0.5f) * sizeX, (j - 0.5f) * sizeY, (k + 0.5f) * sizeZ };
    vertices[6] = { (i + 0.5f) * sizeX, (j + 0.5f) * sizeY, (k + 0.5f) * sizeZ };
    vertices[7] = { (i - 0.5f) * sizeX, (j + 0.5f) * sizeY, (k + 0.5f) * sizeZ };
    return vertices;
}

void write_to_triangle(std::ostringstream &triangle, Vertex v1, Vertex v2, Vertex v3) {
    triangle<<"facet normal 0 0 0"<<std::endl;
    triangle<<"outer loop"<<std::endl;
    triangle<<"vertex "<<v1.x<<" "<<v1.y<<" "<<v1.z<<std::endl;
    triangle<<"vertex "<<v2.x<<" "<<v2.y<<" "<<v2.z<<std::endl;
    triangle<<"vertex "<<v3.x<<" "<<v3.y<<" "<<v3.z<<std::endl;
    triangle<<"endloop"<<std::endl;
    triangle<<"endfacet"<<std::endl;
}

// Fonction pour trouver la valeur minimale et maximale des voxels d'une image 3D
void find_min_max(Image3D &image3D, unsigned short &min, unsigned short &max) {
    min = std::numeric_limits<unsigned short>::max();
    max = std::numeric_limits<unsigned short>::min();
    for(int i = 0; i < image3D.dimX; ++i) {
        for(int j = 0; j < image3D.dimY; ++j) {
            for(int k = 0; k < image3D.dimZ; ++k) {
                unsigned short current_voxel = image3D.get_value(i,j,k);
                if(current_voxel < min) min = current_voxel;
                if(current_voxel > max) max = current_voxel;
            }
        }
    }
}

// Fonction pour écrire une image au format pgm (reprise des TPs avec M. Puech et adaptée pour traiter avec des unsigned short)
void ecrire_image_pgm(const char nom_image[], std::vector<unsigned short>& pt_image, int nb_lignes, int nb_colonnes) {
   FILE *f_image;
   int taille_image = nb_colonnes * nb_lignes;
   std::vector<unsigned char> buffer(taille_image); // Buffer pour stocker les données converties

   // Conversion
   unsigned short max_val = *std::max_element(pt_image.begin(), pt_image.end());
   for(int i = 0; i < taille_image; ++i) {
       // Normalisation
       buffer[i] = static_cast<unsigned char>(255.0 * pt_image[i] / max_val);
   }

   if((f_image = fopen(nom_image, "wb")) == NULL) {
      printf("\nPas d'acces en ecriture sur l'image %s \n", nom_image);
      exit(EXIT_FAILURE);
   } else {
      fprintf(f_image, "P5\n%d %d\n255\n", nb_colonnes, nb_lignes);
      fwrite(buffer.data(), sizeof(unsigned char), taille_image, f_image);
      fclose(f_image);
   }
}

// Fonction pour générer la projection choisie et écrire l'image correspondante
void generate_projection(Image3D &image3D, std::vector<unsigned short> &projection, int axis, int mode, const char* image_write) {
    int width, height, depth;
    switch(axis) {
        case 1: // Axe x
            width = image3D.dimY;
            height = image3D.dimZ;
            depth = image3D.dimX;
            break;
        case 2: // Axe y
            width = image3D.dimX;
            height = image3D.dimZ;
            depth = image3D.dimY;
            break;
        case 3: // Axe z
            width = image3D.dimX;
            height = image3D.dimY;
            depth = image3D.dimZ;
            break;
        default:
            std::cout<<"Axe invalide"<<std::endl;
            exit(EXIT_FAILURE);
            return;
    }

    projection.resize(width * height, (mode == 3) ? std::numeric_limits<unsigned short>::max() : 0); // Initialiser pour MIP/AIP avec 0, pour MINIP avec max

    for(int x = 0; x < width; ++x) {
        for(int y = 0; y < height; ++y) {
            std::vector<unsigned short> values(depth); // Stocke les valeurs le long de l'axe de profondeur
            for(int d = 0; d < depth; ++d) {
                int i, j, k;
                switch(axis) {
                    case 1: i = d; j = x; k = y; break; // Axe x
                    case 2: i = x; j = d; k = y; break; // Axe y
                    case 3: i = x; j = y; k = d; break; // Axe z
                }
                values[d] = image3D.get_value(i, j, k);
            }
            unsigned short projected_voxel;
            if(mode == 1) { // MIP
                projected_voxel = *std::max_element(values.begin(), values.end());
            } else if(mode == 2) { // AIP
                unsigned long sum = std::accumulate(values.begin(), values.end(), 0UL); // Trick pour calculer la somme
                projected_voxel = (unsigned short)(sum / values.size());
            } else if(mode == 3) { // MINIP
                projected_voxel = *std::min_element(values.begin(), values.end());
            }
            projection[y * width + x] = projected_voxel;
        }
    }
    ecrire_image_pgm(image_write, projection, height, width);
}