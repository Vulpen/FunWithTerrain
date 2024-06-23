#ifndef TERRAIN_H
#define TERRAIN_H

#include "height_data.h"
#include <cstdio>

/**
 * Our abstract class of terrain defining high-level access to save and load terrain data.
 * We'll be creating multiple sub-classes that go about handling terrain in various ways, how exciting!
 */
class terrain {
    protected:
        SHEIGHT_DATA heightData;
        float heightScale = 1.0f;

    public:
        int Size;

    virtual void Render( void ) = 0;

    bool LoadHeightMap( char* filename, int size );
    bool SaveHeightMap( char* filename );
    bool UnloadHeightMap( void );

    inline void SetHeightScale (float scale);

    inline void SetHeightAtPoint(unsigned char height, int x, int z);

    inline unsigned char GetTrueHeightAtPoint(int x, int z) {
        return (heightData.data[(z * Size) + x]);
    }

    inline float GetScaledHeightAtPoint(int x, int z) {return (heightData.data[(z * Size) + x]);}

    terrain() {this->LoadHeightMap("test.txt\0", 20);}
    ~terrain() {this->UnloadHeightMap();}
};

#endif