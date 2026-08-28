#include <iostream>
#include <cmath>
#include <string>

#include "raylib.h"

#include "Window_Properities.hpp"
#include "Song.hpp"
#include "Section.hpp"


Camera2D camera;
Camera2D UI;


Song song("lights-down", "normal");
int gridSize = 50;
int coloums = 4;
int rows;


bool isSongPlayed = false;

// void sectionalGrid() { 
//     for (auto &section : song.sections) {
//         if (song.curBeat % section.sectionBeat == 0) {
//             // std::cout << std::to_string(song.curBeat) << std::endl;
                
//         }
        
//     }
// }

void Start() {
    InitWindow(Window_Properities::WIDTH, Window_Properities::HEIGHT, "FNFCharter");
    SetTargetFPS(60);
    InitAudioDevice();
    song.loadSongAudio();
    song.loadFromJson();
    
    // ---------------- Grid Initialization ----------------------
    for (auto &section : song.sections) {
        rows += section.sectionBeat * song.stepPerBeat;
        
    }

    // grid = Grid(coloums, rows, gridSize);

    camera = { 0 };
    camera.target = (Vector2){ 0.0f, 0.0f };
    camera.offset = (Vector2){0, 0};
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    UI = { 0 };
    UI.target = (Vector2){ 0.0f, 0.0f };
    UI.offset = (Vector2){0, 0};
    UI.rotation = 0.0f;
    UI.zoom = 1.0f;
    

}

void Update(float deltaTime) {
    // grid.createGrid();
    // sectionalGrid();
    // song.sections.at(0).drawSection();
    song.manageSections();

   if (IsKeyPressed(KEY_SPACE)) {
        isSongPlayed = !isSongPlayed;

        if (isSongPlayed) {
            song.playSong();
        } else {
            song.stopSong();
        }
    }

    if (isSongPlayed) {
        camera.offset.y -= song.scrollSpeed * 3;
        song.calculateBeatsAndSteps(deltaTime);

    } 
    


    UpdateMusicStream(song.Voices);
    UpdateMusicStream(song.Inst);
    // camera.offset.y -= 0.5;
}

void UpdateUI(float deltaTime) {
    // std::cout <<  std::to_string(song.curBeat) << std::endl;
    DrawText(("Beats : " + std::to_string(song.curBeat)).c_str(), 250, 10, 20, WHITE);
    DrawText(("Steps : " + std::to_string(song.curStep)).c_str(), 250, 35, 20, WHITE);
    
}

int main(void) {
    
    Start();    

    while (!WindowShouldClose()) {
        BeginDrawing();
            ClearBackground(BLACK); 
            // for normal Objects
            BeginMode2D(camera);
                Update(GetFrameTime());
            EndMode2D();

            // UI objects
            BeginMode2D(UI);
                UpdateUI(GetFrameTime());
            EndMode2D();


        EndDrawing();
    }

    CloseAudioDevice();
    CloseWindow();

    return 0;
}


