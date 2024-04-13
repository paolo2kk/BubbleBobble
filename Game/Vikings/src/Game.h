#pragma once
#include "Globals.h"
#include "Scene.h"

enum class GameState { MAIN_MENU, PLAYING, TRANSITIONING, INSERT_COIN, PLAYER_1 };

class Game
{
public:
    Game();
    ~Game();

    AppStatus Initialise(float scale);
    AppStatus Update();
    void Render();
    void Cleanup();

private:
    AppStatus BeginPlay();
    //void FinishPlay();

    AppStatus LoadResources();
    void UnloadResources();

    GameState state;
    Scene *scene;
    const Texture2D *img_menu;
    const Texture2D *img_insert_coin;
    const Texture2D *img_player_1;
    const Texture2D* img_stage1;
    const Texture2D* img_stage2;
    int timeValue = 0;
    float timer = 0;
    float totalTime = 2.5f;
    float timeElapsed = 0.0f;

    //To work with original game units and then scale the result
    RenderTexture2D target;
    Rectangle src, dst;
};