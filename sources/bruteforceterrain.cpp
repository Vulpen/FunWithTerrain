#include "bruteforceterrain.h"
#include "raylib.h"

void BruteForceTerrain::Render( void ) {
    DrawText("Rendering Terrain", 150,150,20,BLUE);

    // int vectSize = (Size-1) * (Size-1);
    // Vector3 *vectors = new Vector3[vectSize * 2];

    // for(int i = 0; i < Size * Size; i++) {
    //     printf("%c ", heightData.data[i]);
    // }
    // printf("\n");

    // TODO: Each Z is a strip unfortunately

    // for ( int i = 0; i < vectSize; i++) {
    //     int x = i % Size;
    //     int z = i / Size;

    //     int ind = i * 2;
    //     vectors[ind].x = x;
    //     vectors[ind].y = GetScaledHeightAtPoint(x,z) - 48;
    //     vectors[ind].z = z;
    //     //printf("%i ", GetScaledHeightAtPoint(x,z+1) - 48);
    //     vectors[ind+1].x = x;
    //     vectors[ind+1].y = GetScaledHeightAtPoint(x,z+1) - 48;
    //     vectors[ind+1].z = z+1;
    // }

    // DrawTriangleStrip3D(vectors, (vectSize * 2), MAROON);

    int vectSize = (Size-1);
    Vector3 *vectors = new Vector3[vectSize * 2];

    for (int z = 0; z < Size - 1; z++) {
        for (int x = 0; x < Size - 1; x++) {
            int ind = x * 2;
            vectors[ind].x = x;
            vectors[ind].y = GetScaledHeightAtPoint(x,z) - 48;
            vectors[ind].z = z;
            //printf("%i ", GetScaledHeightAtPoint(x,z+1) - 48);
            vectors[ind+1].x = x;
            vectors[ind+1].y = GetScaledHeightAtPoint(x,z+1) - 48;
            vectors[ind+1].z = z+1;
        }
        DrawTriangleStrip3D(vectors, (vectSize * 2), MAROON);
    }
}