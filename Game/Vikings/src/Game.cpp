#include "Game.h"
#include "Globals.h"
#include "ResourceManager.h"
#include <stdio.h>

Game::Game()
{

    scene = nullptr;
    state = GameState::MAIN_MENU;
    img_menu = nullptr;
    img_insert_coin = nullptr;
    img_player_1 = nullptr;
    img_stage1 = nullptr;
    img_stage2 = nullptr;

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
}
AppStatus Game::Initialise(float scale)
{
    float w, h;
    w = WINDOW_WIDTH * scale;
    h = WINDOW_HEIGHT * scale;

    //Initialise window
    InitWindow((int)w, (int)h, "Vikings");

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
        case GameState::MAIN_MENU:

            if (IsKeyPressed(KEY_ESCAPE)) return AppStatus::QUIT;
            if (IsKeyPressed(KEY_SPACE))
            {
                state = GameState::INSERT_COIN;
            }
            break;

        case GameState::INSERT_COIN:

            if (IsKeyPressed(KEY_ESCAPE)) return AppStatus::QUIT;
            if (IsKeyPressed(KEY_SPACE))
            {
                state = GameState::PLAYER_1;
            }
            break;

        case GameState::PLAYER_1:

            if (IsKeyPressed(KEY_ESCAPE)) return AppStatus::QUIT;
            if (IsKeyPressed(KEY_SPACE))
            {
                if (BeginPlay() != AppStatus::OK) return AppStatus::ERROR;
                state = GameState::PLAYING;
            }
            break;

        case GameState::PLAYING:  
            if (IsKeyPressed(KEY_ESCAPE))
            {
                //FinishPlay();
                state = GameState::MAIN_MENU;
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
        case GameState::MAIN_MENU:
            scene->RenderMenu(img_menu);
            break;

        case GameState::INSERT_COIN:
            DrawTexture(*img_insert_coin, 0, 0, WHITE);
            break;

        case GameState::PLAYER_1:
            DrawTexture(*img_player_1, 0, 0, WHITE);
            break;

        case GameState::PLAYING:
            scene->Render();
            break;
        case GameState::TRANSITIONING:
            float progress = timeElapsed / totalTime;
            float yPos_stage2 = 224.0f * -progress; 
            if (timeElapsed < totalTime) {
                DrawTexture(*img_stage1, 0, yPos_stage2, WHITE);
                DrawTexture(*img_stage2, 0, yPos_stage2 + 224, WHITE);

                timeElapsed += GetFrameTime();

            }
            else {
                timeElapsed = 0;
                state = GameState::PLAYING;
                scene->LoadLevel(2);
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
void Game::UnloadResources()
{
    ResourceManager& data = ResourceManager::Instance();
    data.ReleaseTexture(Resource::IMG_MENU);
    data.ReleaseTexture(Resource::IMG_INSCOIN);
    data.ReleaseTexture(Resource::IMG_PLAYER_1);


    UnloadRenderTexture(target);
}