/**********************************************************************************************
*
*   raylib - Advance Game template
*
*   Gameplay Screen Functions Definitions (Init, Update, Draw, Unload)
*
*   Copyright (c) 2014-2022 Ramon Santamaria (@raysan5)
*
*   This software is provided "as-is", without any express or implied warranty. In no event
*   will the authors be held liable for any damages arising from the use of this software.
*
*   Permission is granted to anyone to use this software for any purpose, including commercial
*   applications, and to alter it and redistribute it freely, subject to the following restrictions:
*
*     1. The origin of this software must not be misrepresented; you must not claim that you
*     wrote the original software. If you use this software in a product, an acknowledgment
*     in the product documentation would be appreciated but is not required.
*
*     2. Altered source versions must be plainly marked as such, and must not be misrepresented
*     as being the original software.
*
*     3. This notice may not be removed or altered from any source distribution.
*
**********************************************************************************************/

#include "raylib.h"
#include "screens.h"
#include "bruteforceterrain.h"
#include "MeshTerrain.h"

// Generate a simple triangle mesh from code
static Mesh GenMeshCustom(void)
{
    TraceLog(LOG_INFO, "Generating custom mesh...");
    Mesh mesh = { 0 };
    
    mesh.triangleCount = 1;
    mesh.vertexCount = mesh.triangleCount*3;
    mesh.vertices = (float *)MemAlloc(mesh.vertexCount*3*sizeof(float));    // 3 vertices, 3 coordinates each (x, y, z)
    //mesh.texcoords = (float *)MemAlloc(mesh.vertexCount*2*sizeof(float));   // 3 vertices, 2 coordinates each (x, y)
    mesh.colors = (unsigned char *)MemAlloc(mesh.vertexCount*4*sizeof(unsigned char));
    mesh.normals = (float *)MemAlloc(mesh.vertexCount*3*sizeof(float));     // 3 vertices, 3 coordinates each (x, y, z)
    TraceLog(LOG_INFO, "Generating custom mesh...");
    // Vertex at (0, 0, 0)
    mesh.vertices[0] = 0;
    mesh.vertices[1] = 0;
    mesh.vertices[2] = 0;
    //mesh.normals[0] = 0;
    //mesh.normals[1] = 1;
    //mesh.normals[2] = 0;
    //mesh.texcoords[0] = 0;
    //mesh.texcoords[1] = 0;
    mesh.colors[0] = 0;
    mesh.colors[1] = 255;
    mesh.colors[2] = 0;
    mesh.colors[3] = 255;

    // Vertex at (1, 0, 2)
    mesh.vertices[3] = 1;
    mesh.vertices[4] = 0;
    mesh.vertices[5] = 2;
    //mesh.normals[3] = 0;
    //mesh.normals[4] = 1;
    //mesh.normals[5] = 0;
    //mesh.texcoords[2] = 0.5f;
    //mesh.texcoords[3] = 1.0f;

    // Vertex at (2, 0, 0)
    mesh.vertices[6] = 2;
    mesh.vertices[7] = 0;
    mesh.vertices[8] = 0;
    //mesh.normals[6] = 0;
    //mesh.normals[7] = 1;
    //mesh.normals[8] = 0;
    //mesh.texcoords[4] = 1;
    //mesh.texcoords[5] =0;

    // Upload mesh data from CPU (RAM) to GPU (VRAM) memory
    UploadMesh(&mesh, false);
    TraceLog(LOG_INFO, "FINISHED generating custom mesh...");
    return mesh;
}

//----------------------------------------------------------------------------------
// Module Variables Definition (local)
//----------------------------------------------------------------------------------
static int framesCounter = 0;
static int finishScreen = 0;
terrain *sampleTerrain;
terrain *otherTerrain;
Model mdl;
Camera camera = { { 5.0f, 5.0f, 5.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f }, 45.0f, 0 };

//----------------------------------------------------------------------------------
// Gameplay Screen Functions Definition
//----------------------------------------------------------------------------------

// Gameplay Screen Initialization logic
void InitGameplayScreen(void)
{
    TraceLog(LOG_INFO, "Starting GAMEPLAY Init");
    // TODO: Initialize GAMEPLAY screen variables here!
    framesCounter = 0;
    finishScreen = 0;
    sampleTerrain = new BruteForceTerrain();
    otherTerrain = new MeshTerrain();
    mdl = LoadModelFromMesh(GenMeshCustom());
    // cam = new Camera3D;
    // cam->position.x = 5;
    // cam->position.y = 5;
    // cam->position.z = 5;
    // cam->target.x = 0; cam->target.y = 0; cam->target.z = 0;
    TraceLog(LOG_INFO, "Finalized GAMEPLAY Init");
}

// Gameplay Screen Update logic
void UpdateGameplayScreen(void)
{
    // TODO: Update GAMEPLAY screen variables here!

    // Press enter or tap to change to ENDING screen
    if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP))
    {
        finishScreen = 1;
        PlaySound(fxCoin);
    }
}

// Gameplay Screen Draw logic
void DrawGameplayScreen(void)
{
    // TODO: Draw GAMEPLAY screen here!
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), PURPLE);
    Vector2 pos = { 20, 10 };
    DrawTextEx(font, "TERRAIN", pos, font.baseSize*3.0f, 4, MAROON);
    //DrawText("PRESS ENTER or TAP to JUMP to ENDING SCREEN", 130, 220, 20, MAROON);

    UpdateCamera(&camera, CAMERA_ORBITAL);
    BeginMode3D(camera);
        DrawCube({0,0,0}, 0.3, 0.3, 0.3, BLACK);
        sampleTerrain->Render();
        otherTerrain->Render();
        //DrawModel(mdl, {0.0f,0.0f,0.0f}, 1.0f, WHITE);
    EndMode3D();
}

// Gameplay Screen Unload logic
void UnloadGameplayScreen(void)
{
    // TODO: Unload GAMEPLAY screen variables here!
}

// Gameplay Screen should finish?
int FinishGameplayScreen(void)
{
    return finishScreen;
}