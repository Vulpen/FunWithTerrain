#include "MeshTerrain.h"

MeshTerrain::MeshTerrain() {
    // Generate Mesh stuff here i guess?
    
    LoadHeightMap("heightgen.txt\0", TERRAIN_WIDTH);

    TraceLog(LOG_INFO, "Generating terrain mesh...");
    terrainMesh = GenerateTerrainMesh();
    TraceLog(LOG_INFO, "Uploading and generating terrain model...");
    UploadMesh(&terrainMesh, false);
    terrainModel = LoadModelFromMesh(terrainMesh);
    TraceLog(LOG_INFO, "FINISHED uploading terrain model.");
}

void MeshTerrain::Render() {
    //terrainModel = LoadModelFromMesh(terrainMesh);
    DrawModel(terrainModel, {0.0f,0.0f,0.0f}, 1.0f, WHITE);
}

Mesh MeshTerrain::GenerateTerrainMesh() {
    Mesh mesh = {0};
    int size = TERRAIN_WIDTH;
    Size = TERRAIN_WIDTH;
    // Winding order matters without the normals array!
    mesh.triangleCount = (size - 1) * (size - 1) * 2;
    //mesh.triangleCount = (size * size) - 1;
    mesh.vertexCount = mesh.triangleCount * 3;
    mesh.vertices = (float *)MemAlloc(mesh.vertexCount*3*sizeof(float));    // 3 vertices, 3 coordinates each (x, y, z)
    //mesh.texcoords = (float *)MemAlloc(mesh.vertexCount*2*sizeof(float));   // 3 vertices, 2 coordinates each (x, y)
    mesh.colors = (unsigned char *)MemAlloc(mesh.vertexCount*4*sizeof(unsigned char));
    mesh.normals = (float *)MemAlloc(mesh.vertexCount*3*sizeof(float));     // 3 vertices, 3 coordinates each (x, y, z)

    for (int z = 0; z < size - 1; z++) {
        for (int x = 0; x <  size - 1; x++) {
            int ind = (z * (size-1)) + x;
            TraceLog(LOG_INFO, "Index: %d", ind);
            // vectors[ind].x = x;
            // vectors[ind].y = GetScaledHeightAtPoint(x,z) - 48;
            // vectors[ind].z = z;
            // //printf("%i ", GetScaledHeightAtPoint(x,z+1) - 48);
            // vectors[ind+1].x = x;
            // vectors[ind+1].y = GetScaledHeightAtPoint(x,z+1) - 48;
            // vectors[ind+1].z = z+1;


            int vertexInd = ind * 18;
            int colorInd = ind * 24;
            int vertHeight = GetScaledHeightAtPoint(x,z) - 48;
            int vertColor = LinearConversion(vertHeight, TERRAIN_MAX, 255);
            mesh.vertices[vertexInd] = x;
            mesh.vertices[vertexInd+1] = vertHeight;
            mesh.vertices[vertexInd+2] = z;
            mesh.colors[colorInd] = vertColor;
            mesh.colors[colorInd + 1] = vertColor;
            mesh.colors[colorInd + 2] = vertColor;
            mesh.colors[colorInd + 3] = 255;

            vertHeight = GetScaledHeightAtPoint(x,z+1) - 48;
            vertColor = LinearConversion(vertHeight, TERRAIN_MAX, 255);
            mesh.vertices[vertexInd+3] = x;
            mesh.vertices[vertexInd+4] = vertHeight;
            mesh.vertices[vertexInd+5] = z+1;
            mesh.colors[colorInd + 4] = vertColor;
            mesh.colors[colorInd + 5] = vertColor;
            mesh.colors[colorInd + 6] = vertColor;
            mesh.colors[colorInd + 7] = 255;

            vertHeight = GetScaledHeightAtPoint(x+1,z) - 48;
            vertColor = LinearConversion(vertHeight, TERRAIN_MAX, 255);
            mesh.vertices[vertexInd+6] = x+1;
            mesh.vertices[vertexInd+7] = vertHeight;
            mesh.vertices[vertexInd+8] = z;
            mesh.colors[colorInd + 8] = vertColor;
            mesh.colors[colorInd + 9] = vertColor;
            mesh.colors[colorInd + 10] = vertColor;
            mesh.colors[colorInd + 11] = 255;

            vertHeight = GetScaledHeightAtPoint(x+1,z+1) - 48;
            vertColor = LinearConversion(vertHeight, TERRAIN_MAX, 255);            
            mesh.vertices[vertexInd + 9] = x + 1;
            mesh.vertices[vertexInd + 10] = vertHeight;
            mesh.vertices[vertexInd + 11] = z + 1;
            mesh.colors[colorInd + 12] = vertColor;
            mesh.colors[colorInd + 13] = vertColor;
            mesh.colors[colorInd + 14] = vertColor;
            mesh.colors[colorInd + 15] = 255;

            vertHeight = GetScaledHeightAtPoint(x+1,z) - 48;
            vertColor = LinearConversion(vertHeight, TERRAIN_MAX, 255);
            mesh.vertices[vertexInd + 12] = x+1;
            mesh.vertices[vertexInd + 13] = vertHeight;
            mesh.vertices[vertexInd + 14] = z;
            mesh.colors[colorInd + 16] = vertColor;
            mesh.colors[colorInd + 17] = vertColor;
            mesh.colors[colorInd + 18] = vertColor;
            mesh.colors[colorInd + 19] = 255;

            vertHeight = GetScaledHeightAtPoint(x,z+1) - 48;
            vertColor = LinearConversion(vertHeight, TERRAIN_MAX, 255);
            mesh.vertices[vertexInd + 15] = x;
            mesh.vertices[vertexInd + 16] = vertHeight;
            mesh.vertices[vertexInd + 17] = z+1;
            mesh.colors[colorInd + 20] = vertColor;
            mesh.colors[colorInd + 21] = vertColor;
            mesh.colors[colorInd + 22] = vertColor;
            mesh.colors[colorInd + 23] = 255;
        }
    }
    return mesh;
}

float MeshTerrain::LinearConversion(float val, float oldMax, float newMax) {
    return (val / oldMax) * newMax;
}