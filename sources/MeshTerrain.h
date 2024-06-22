#ifndef MESH_TERRAIN_H
#define MESH_TERRAIN_H
#define TERRAIN_WIDTH 20    // TODO : Define these in a separate config probably
#define TERRAIN_MAX 9
#include "terrain.h"
#include "raylib.h"

class MeshTerrain : public terrain {
    public:
    MeshTerrain();
    void Render() override;

    private:
    Mesh terrainMesh;
    Model terrainModel;
    Mesh GenerateTerrainMesh();
    float LinearConversion(float val, float oldMax, float newMax);
};

#endif