#include "Game.h"
#include "Globals.h"
#include "ResourceManager.h"
#include <stdio.h>

Game::Game()
{

    scene = nullptr;
    state = GameState::START;
    img_menu = nullptr;
    img_insert_coin = nullptr;
    img_intro = nullptr;
    img_explanation = nullptr;
    img_upc_citm = nullptr;
    img_pato_productions = nullptr;
    img_player_2 = nullptr;
    img_game_over = nullptr;
    img_tutorial = nullptr;
    img_player_1 = nullptr;
    img_intro = nullptr;
    img_ScoreHeader = nullptr;
    img_stage1 = nullptr;
    img_stage2 = nullptr;


    alpha = 1;
    fadeCondition = true;
    transCounter = 0;
    
    credit = 0;
    shouldGetTime = true;
    time = GetTime();


    target = {};
    src = {};
    dst = {};

    
}
Game::~Game()
{
    if (scene != nullptr)
    {
        scene->Release();
        delete scene;
        scene = nullptr;
    }
    UnloadImage(customIcon);

}
AppStatus Game::Initialise(float scale)
{
    float w, h;
    w = WINDOW_WIDTH * scale;
    h = WINDOW_HEIGHT * scale;

    //Initialise window
    InitWindow((int)w, (int)h, "Bubble Bobble");
    SetWindowIcon(customIcon);
    //Render texture initialisation, used to hold the rendering result so we can easily resize it
    target = LoadRenderTexture(WINDOW_WIDTH, WINDOW_HEIGHT);
    if (target.id == 0)
    {
        LOG("Failed to create render texture");
        return AppStatus::ERROR;
    }
    SetTextureFilter(target.texture, TEXTURE_FILTER_POINT);
    src = { 0, 0, WINDOW_WIDTH, -WINDOW_HEIGHT };
    dst = { 0, 0, w, h };

    //Load resources
    if (LoadResources() != AppStatus::OK)
    {
        LOG("Failed to load resources");
        return AppStatus::ERROR;
    }

    //Set the target frame rate for the application
    SetTargetFPS(60);
    //Disable the escape key to quit functionality
    SetExitKey(0);

    return AppStatus::OK;
}
AppStatus Game::LoadResources()
{
    ResourceManager& data = ResourceManager::Instance();
    
    if (data.LoadTexture(Resource::IMG_MENU, "images/TitleSpriteSeett.png") != AppStatus::OK)
    {
        return AppStatus::ERROR;
    }
    img_menu = data.GetTexture(Resource::IMG_MENU);

    if (data.LoadTexture(Resource::IMG_INSCOIN, "images/InsertCoin.png") != AppStatus::OK)
    {
        return AppStatus::ERROR;
    }
    img_insert_coin = data.GetTexture(Resource::IMG_INSCOIN);


    if (data.LoadTexture(Resource::IMG_PLAYER_1, "images/Push player 1.png") != AppStatus::OK)
    {
        return AppStatus::ERROR;
    }
    img_player_1 = data.GetTexture(Resource::IMG_PLAYER_1);

    if (data.LoadTexture(Resource::IMG_PLAYER_2, "images/Push player 2 and 1.png") != AppStatus::OK)
    {
        return AppStatus::ERROR;
    }
    img_player_2 = data.GetTexture(Resource::IMG_PLAYER_2);

    if (data.LoadTexture(Resource::IMG_SCORE, "images/Onlyscore.png") != AppStatus::OK)
    {
        return AppStatus::ERROR;
    }
    img_ScoreHeader = data.GetTexture(Resource::IMG_SCORE);

    if (data.LoadTexture(Resource::IMG_TUTORIAL, "images/Tutorial For Naw.png") != AppStatus::OK)
    {
        return AppStatus::ERROR;
    }
    img_tutorial = data.GetTexture(Resource::IMG_TUTORIAL);

    if (data.LoadTexture(Resource::IMG_INTRO, "images/Cinematic.png") != AppStatus::OK)
    {
        return AppStatus::ERROR;
    }
    img_intro = data.GetTexture(Resource::IMG_INTRO);

    if (data.LoadTexture(Resource::IMG_EXPL, "images/Explanation.png") != AppStatus::OK)
    {
        return AppStatus::ERROR;
    }
    img_explanation = data.GetTexture(Resource::IMG_EXPL);

    if (data.LoadTexture(Resource::IMG_UPC_CITM, "images/UPC_CITM.png") != AppStatus::OK)
    {
        return AppStatus::ERROR;
    }
    img_upc_citm = data.GetTexture(Resource::IMG_UPC_CITM);

    if (data.LoadTexture(Resource::IMG_PATO, "images/Pato Productions.png") != AppStatus::OK)
    {
        return AppStatus::ERROR;
    }
    img_pato_productions = data.GetTexture(Resource::IMG_PATO);

    if (data.LoadTexture(Resource::IMG_GAME_OVER, "images/Game over.png") != AppStatus::OK)
    {
        return AppStatus::ERROR;
    }
    img_game_over = data.GetTexture(Resource::IMG_GAME_OVER);

    if (data.LoadTexture(Resource::IMG_STAGE1, "images/uno.png") != AppStatus::OK)
    {
        return AppStatus::ERROR;
    }
    img_stage1 = data.GetTexture(Resource::IMG_STAGE1);
    
    if (data.LoadTexture(Resource::IMG_STAGE2, "images/dos.png") != AppStatus::OK)
    {
        return AppStatus::ERROR;
    }
    img_stage2 = data.GetTexture(Resource::IMG_STAGE2);


    return AppStatus::OK;
}
const int Game::GetCredit()
{
    return credit;
}
void Game::RenderCredit()
{
    if (GetCredit() < 99999)
    {
        DrawText(TextFormat("%d", GetCredit()), 225, 214, 8, WHITE);
    }
}
void Game::incCredit()
{
    credit++;
    RenderCredit();
}
int Game::CheckTimePassed()
{
    if (shouldGetTime == true)
    {
        time = GetTime();
        shouldGetTime = false;
    }

    return GetTime() - time;
}
void Game::RenderScore()
{
    DrawTexture(*img_ScoreHeader, 0, 0, WHITE);
    DrawText(TextFormat("%d", scene->Score()), 38, 8, 8, WHITE);
    DrawText(TextFormat("%d", scene->Score()), 38, 8, 8, WHITE);
}
AppStatus Game::BeginPlay()
{
    scene = new Scene();
    if (scene == nullptr)
    {
        LOG("Failed to allocate memory for Scene");
        return AppStatus::ERROR;
    }
    if (scene->Init() != AppStatus::OK)
    {
        LOG("Failed to initialise Scene");
        return AppStatus::ERROR;
    }

    return AppStatus::OK;
}
//void Game::FinishPlay()
//{
//    scene->Release();
//    delete scene;
//    scene = nullptr;
//}
AppStatus Game::Update()
{
    //Check if user attempts to close the window, either by clicking the close button or by pressing Alt+F4
    if(WindowShouldClose()) return AppStatus::QUIT;

    switch (state)
    {
        case GameState::START:
            if (transCounter == 6)
            {
                shouldGetTime = true;
                state = GameState::MAIN_MENU;
            }
            break;

        case GameState::MAIN_MENU:
            if (IsKeyPressed(KEY_ESCAPE)) return AppStatus::QUIT;
            if ((CheckTimePassed() > 5) && (GetCredit() == 0))
            {
                state = GameState::INSERT_COIN;
                shouldGetTime = true;
            }
            if (IsKeyPressed(KEY_ENTER))
            {
                incCredit();
                state = GameState::PLAYER_1;
            }
            break;

        case GameState::INSERT_COIN:

            if (IsKeyPressed(KEY_ESCAPE)) return AppStatus::QUIT;
            if (CheckTimePassed() > 3)
            {
                state = GameState::TUTORIAL;
                shouldGetTime = true;
            }
            if (IsKeyPressed(KEY_ENTER))
            {
                incCredit();
                state = GameState::PLAYER_1;
            }
            break;

        case GameState::TUTORIAL:
            if (IsKeyPressed(KEY_ESCAPE)) return AppStatus::QUIT;
            if (IsKeyPressed(KEY_ENTER))
            {
                incCredit();
                state = GameState::PLAYER_1;
            }
            break;

        case GameState::PLAYER_1:

            if (IsKeyPressed(KEY_ESCAPE)) return AppStatus::QUIT;
            if (IsKeyPressed(KEY_SPACE))
            {

                state = GameState::INTRO;
            }
            if (IsKeyPressed(KEY_ENTER))
            {
                incCredit();
                state = GameState::PLAYER_2_AND_1;
            }
            break;

        case GameState::PLAYER_2_AND_1:

            if (IsKeyPressed(KEY_ESCAPE)) return AppStatus::QUIT;
            if (IsKeyPressed(KEY_SPACE))
            {

                state = GameState::INTRO;
            }
            if (IsKeyPressed(KEY_ENTER))
            {
                incCredit();
            }
            break;

        case GameState::INTRO:

            if (IsKeyPressed(KEY_ESCAPE)) return AppStatus::QUIT;
            if (CheckTimePassed() > 7)
            {
                if (BeginPlay() != AppStatus::OK) return AppStatus::ERROR;
                state = GameState::PLAYING;
                shouldGetTime = true;
            }
            break;
        case GameState::GAME_OVER:
            if (CheckTimePassed() > 3)
            {
                state = GameState::MAIN_MENU;
                shouldGetTime = true;
            }
            break;

        case GameState::PLAYING:  
            if (IsKeyPressed(KEY_ESCAPE))
            {
                //FinishPlay();
                state = GameState::GAME_OVER;
            }
            else if (IsKeyPressed(KEY_Q)) {
                state = GameState::TRANSITIONING;
            }
            else
            {
                //Game logic
                scene->Update();
            }
            break;
        case GameState::TRANSITIONING:
            
            break;
            
    }
    return AppStatus::OK;
}
void Game::Render()
{
    //Draw everything in the render texture, note this will not be rendered on screen, yet
    BeginTextureMode(target);
    ClearBackground(BLACK);
    
    switch (state)
    {
        case GameState::START:
            if ((transCounter == 0)||(transCounter==1))
            {
                DrawTexture(*img_explanation, 0, 0, WHITE);
                FadeTransition();

            }
            else if ((transCounter == 2) || (transCounter == 3))
            {
                DrawTexture(*img_upc_citm, 0, 0, WHITE);
                FadeTransition();

            }
            else if ((transCounter == 4) || (transCounter == 5))
            {
                DrawTexture(*img_pato_productions, 0, 0, WHITE);
                FadeTransition();

            }

        break;
        case GameState::MAIN_MENU:
            DrawTexture(*img_menu, 0, 0, WHITE);
            RenderCredit();
            RenderScore();
            break;

        case GameState::INSERT_COIN:
            DrawTexture(*img_insert_coin, 0, 0, WHITE);
            RenderCredit();
            RenderScore();
            break;

        case GameState::TUTORIAL:
            DrawTexture(*img_tutorial, 0, 0, WHITE);
            RenderScore();
            break;

        case GameState::INTRO:
            DrawTexture(*img_intro, 0, 0, WHITE);
            break;

        case GameState::PLAYER_1:
            DrawTexture(*img_player_1, 0, 0, WHITE);
            RenderCredit();
            RenderScore();
            break;

        case GameState::PLAYER_2_AND_1:
            DrawTexture(*img_player_2, 0, 0, WHITE);
            RenderCredit();
            RenderScore();
            break;

        case GameState::GAME_OVER:
            DrawTexture(*img_game_over, 0, 0, WHITE);
            RenderCredit();
            RenderScore();
            break;

        case GameState::PLAYING:
            scene->Render();
            RenderScore();
            break;
        case GameState::TRANSITIONING:
            float progress = timeElapsed / totalTime;
            float yPos_stage2 = 224.0f * -progress; 
            if (timeElapsed < totalTime) {
                DrawTexture(*img_stage1, 0, yPos_stage2, WHITE);
                DrawTexture(*img_stage2, 0, yPos_stage2 + 224, WHITE);
                RenderScore();

                timeElapsed += GetFrameTime();

            }
            else {
                timeElapsed = 0;
                state = GameState::PLAYING;
                scene->LoadLevel(2);
                RenderScore();
            }
          
            break;
    }
    
    EndTextureMode();

    //Draw render texture to screen, properly scaled
    BeginDrawing();
    DrawTexturePro(target.texture, src, dst, { 0, 0 }, 0.0f, WHITE);
    EndDrawing();
}
void Game::Cleanup()
{
    UnloadResources();
    CloseWindow();
}
void Game::FadeTransition()
{
    if ( fadeCondition == true )
    {
        DrawRectangle(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, Fade(BLACK, alpha));
        alpha -= 0.02;
    }
    else if (fadeCondition == false)
    {
        DrawRectangle(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, Fade(BLACK, alpha));
        alpha += 0.02;
    }

    if (alpha > 1)
    {
        alpha = 1;
        fadeCondition = 1;
        transCounter++;
    }
    if (alpha < 0)
    {
        alpha = 0.0;
        WaitTime(2);
        fadeCondition = false;
        transCounter++;
    }
}

void Game::UnloadResources()
{
    ResourceManager& data = ResourceManager::Instance();
    data.ReleaseTexture(Resource::IMG_MENU);
    data.ReleaseTexture(Resource::IMG_INSCOIN);
    data.ReleaseTexture(Resource::IMG_PLAYER_1);
    data.ReleaseTexture(Resource::IMG_GAME_OVER);
    data.ReleaseTexture(Resource::IMG_INTRO);
    data.ReleaseTexture(Resource::IMG_PLAYER_2);
    data.ReleaseTexture(Resource::IMG_TUTORIAL);
    data.ReleaseTexture(Resource::IMG_SCORE);



    UnloadRenderTexture(target);
}