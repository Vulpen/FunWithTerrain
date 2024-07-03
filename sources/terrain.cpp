#include "terrain.h"
#include "raylib.h"
#include "fstream"

// inline unsigned char terrain::GetTrueHeightAtPoint(int x, int z) {
//     return (heightData.data[(z * Size) + x]);
// }

// inline float terrain::GetScaledHeightAtPoint(int x, int z) {return (heightData.data[(z * Size) + x]);}

void terrain::SetHeightScale (float scale) {
    heightScale = scale;
}

inline void terrain::SetHeightAtPoint(unsigned char height, int x, int z) {
    heightData.data[(z * Size) + x] = height;
}

//bool terrain::LoadHeightMap( char* filename, int size ) {
//    //printf("Loading HeightMap");
//    TraceLog(LOG_INFO, "Loading HeightMap %i", size);
//
//    FILE *file = fopen(filename, "r");
//    //FILE *file;
//
//    if (file == NULL) {
//        TraceLog(LOG_INFO, "Could not open file %s\n", filename);
//        perror("screm");
//        return false;
//    }
//
//    TraceLog(LOG_INFO, "1");
//    if(heightData.data)
//        UnloadHeightMap();
//
//    TraceLog(LOG_INFO, "2");
//    heightData.data = new unsigned char [size * size];
//
//    if (heightData.data == NULL) {
//        //printf("Could not allocate memory for%s\n", filename);
//        TraceLog(LOG_INFO, "Could not allocate height map data.");
//        return false;
//    }
//
//    TraceLog(LOG_INFO, "3");
//    fread(heightData.data, sizeof(unsigned char), size*size, file);
//    TraceLog(LOG_INFO, "4");
//    fclose(file);
//
//    heightData.size = size;
//    Size = size;
//
//    //printf("Successfully loaded: %s\n", filename);
//    TraceLog(LOG_INFO, "Successfully loaded: %s\n", filename);
//    return true;
//}

bool terrain::LoadHeightMap(char *filename, int size) {
    TraceLog(LOG_INFO, "Loading HeightMap %i", size);

    std::ifstream inFile(filename);

    if (!inFile) {
        TraceLog(LOG_ERROR, "Could not open file %s\n", filename);
        perror("screm");
        return false;
    }

    if(heightData.data)
        UnloadHeightMap();

    heightData.data = new unsigned int [size * size];

    for (int x = 0; x < size; x++) {
        for (int y = 0; y < size; y++) {
            int number;
            inFile >> number;
            TraceLog(LOG_DEBUG, "Loading %u from file");
            heightData.data[y * size + x] = number;
        }
    }

    heightData.size = size;
    Size = size;

    //printf("Successfully loaded: %s\n", filename);
    TraceLog(LOG_INFO, "Successfully loaded: %s\n", filename);

    inFile.close();
    if( !inFile ) {
        TraceLog(LOG_ERROR, "Could not close file %s\n", filename);
        perror("screm");
        return false;
    }

    return true;
}

bool terrain::UnloadHeightMap( void ) {
    if(heightData.data) {
        delete[] heightData.data;
        heightData.size = 0;
        printf("Successfully unloaded heightmap\n");
    }

    return true;
}