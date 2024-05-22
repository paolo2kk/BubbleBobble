#pragma once
#include "Globals.h"
#include "Scene.h"
#include "Text.h"

enum class GameState { MAIN_MENU, PLAYING, TRANSITIONING, INSERT_COIN, PLAYER_1, TUTORIAL, INTRO, PLAYER_2_AND_1, GAME_OVER, START};

class Game
{
public:
    Game();
    ~Game();

    AppStatus Initialise(float scale);
    AppStatus Update();
    void Render();
    void Cleanup();

    void RenderUI();
    void RenderLives();
    bool pastTime(float time);
    const int GetCredit();
    void incCredit();
    void decCredit();
    void RenderCredit();
    void FadeTransition();

private:
    AppStatus BeginPlay();
    //void FinishPlay();

    AppStatus LoadResources();
    void UnloadResources();

    int TittleOffset;
    int stageCounter;
    int credit;
    float frameCounter;
    float alpha;
    bool fadeCondition;
    int transCounter;
    int HighScore;

    GameState state;
    Scene *scene;
    const Texture2D *img_player_1;
    const Texture2D* img_stage1;
    const Texture2D* img_stage2;
    const Texture2D* img_intro;
    const Texture2D* img_player_2;
    const Texture2D* img_game_over;
    const Texture2D* img_tutorial;
    const Texture2D* img_menu;
    const Texture2D* img_insert_coin;
    const Texture2D* img_ScoreHeader;
    const Texture2D* img_upc_citm;
    const Texture2D* img_pato_productions;
    const Texture2D* img_explanation;
    const Texture2D* img_life_bob;
    const Texture2D* img_life_bub;
    int timeValue = 0;
    float timer = 0;
    float totalTime = 1.5f;
    float timeElapsed = 0.0f;

    //To work with original game units and then scale the result
    RenderTexture2D target;
    Rectangle src, dst;
    Text* text_;
};