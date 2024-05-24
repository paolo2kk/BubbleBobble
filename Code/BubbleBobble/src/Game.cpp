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
    img_life_bub = nullptr;
    img_life_bob = nullptr;

    HighScore = 0;
    alpha = 1;
    TittleOffset= 0;
    fadeCondition = true;
    transCounter = 0;
    frameCounter = 0;
    credit = 0;
    playtime = 0;
    text_ = new Text();

    stageCounter = 1;

    target = {};
    src = {};
    dst = {};

    IntroBob = new Entity();
    IntroBub = new Entity();
}
Game::~Game()
{
    if (scene != nullptr)
    {
        scene->Release();
        delete scene;
        scene = nullptr;
    }
    CloseAudioDevice();
}
AppStatus Game::Initialise(float scale)
{
    InitAudioDevice();

    float w, h;
    w = WINDOW_WIDTH * scale;
    h = WINDOW_HEIGHT * scale;


    //Initialise window
    InitWindow((int)w, (int)h, "Bubble Bobble");
    //Render texture initialisation, used to hold the rendering result so we can easily resize it
    if (ResourceManager::Instance().LoadMusic(Resource::MUSIC_INTRO, "music/Music/Intro.ogg") != AppStatus::OK) {
        // Handle error, perhaps by logging or attempting a graceful shutdown.
        return AppStatus::ERROR;
    }

    if (ResourceManager::Instance().LoadMusic(Resource::MUSIC_BACKGROUND, "music/Music/Main_Theme_Music.ogg") != AppStatus::OK) {
        // Handle error
        return AppStatus::ERROR;
    }

    if (ResourceManager::Instance().LoadSoundEffect(Resource::MUSIC_TITLE, "music/SFX/Intro_SFX.wav") != AppStatus::OK) {
        // Handle error
        return AppStatus::ERROR;
    }

    if (ResourceManager::Instance().LoadMusic(Resource::MUSIC_FALSE_ENDING, "music/Music/False_Ending.ogg") != AppStatus::OK) {
        // Handle error
        return AppStatus::ERROR;
    }

    if (ResourceManager::Instance().LoadMusic(Resource::MUSIC_GAME_OVER, "music/Music/Game_Over_music.ogg") != AppStatus::OK) {
        // Handle error
        return AppStatus::ERROR;
    }

    if (ResourceManager::Instance().LoadMusic(Resource::MUSIC_MAIN_THEME_HURRY, "music/Music/Main_Theme_Hurry_Music.ogg") != AppStatus::OK) {
        // Handle error
        return AppStatus::ERROR;
    }

    if (ResourceManager::Instance().LoadMusic(Resource::MUSIC_REAL_ENDING, "music/Music/Real_ending_Music.ogg") != AppStatus::OK) {
        // Handle error
        return AppStatus::ERROR;
    }

    if (ResourceManager::Instance().LoadMusic(Resource::MUSIC_SUPER_DRUNK, "music/Music/Super_Drunk_Music.ogg") != AppStatus::OK) {
        // Handle error
        return AppStatus::ERROR;
    }

    if (ResourceManager::Instance().LoadSoundEffect(Resource::SFX_JUMP, "music/SFX/Jump_SFX.wav") != AppStatus::OK) {
        // Handle error
        return AppStatus::ERROR;
    }

    if (ResourceManager::Instance().LoadSoundEffect(Resource::SFX_PICKUP, "music/SFX/Eat_Fruit_SFX.wav") != AppStatus::OK) {
        // Handle error
        return AppStatus::ERROR;
    }

    if (ResourceManager::Instance().LoadSoundEffect(Resource::SFX_BUBBLE, "music/SFX/Bubble_SFX.wav") != AppStatus::OK) {
        // Handle error
        return AppStatus::ERROR;
    }

    if (ResourceManager::Instance().LoadSoundEffect(Resource::SFX_BOSS_ATTAK, "music/SFX/Boss atack.wav") != AppStatus::OK) {
        // Handle error
        return AppStatus::ERROR;
    }

    if (ResourceManager::Instance().LoadSoundEffect(Resource::SFX_BUBBLE_POP, "music/SFX/Bubble_pop_SFX.wav") != AppStatus::OK) {
        // Handle error
        return AppStatus::ERROR;
    }

    if (ResourceManager::Instance().LoadSoundEffect(Resource::SFX_DEATH, "music/SFX/Death_SFX.wav") != AppStatus::OK) {
        // Handle error
        return AppStatus::ERROR;
    }

    if (ResourceManager::Instance().LoadSoundEffect(Resource::SFX_ELECTRIC_HIT, "music/SFX/Electric_Hit_SFX.wav") != AppStatus::OK) {
        // Handle error
        return AppStatus::ERROR;
    }

    if (ResourceManager::Instance().LoadSoundEffect(Resource::SFX_INSERT_COIN, "music/SFX/Coin_Insert_SFX.wav") != AppStatus::OK) {
        // Handle error
        return AppStatus::ERROR;
    }


    PlayMusicStream(*ResourceManager::Instance().GetMusic(Resource::MUSIC_BACKGROUND));
    PlayMusicStream(*ResourceManager::Instance().GetMusic(Resource::MUSIC_INTRO));
    PlayMusicStream(*ResourceManager::Instance().GetMusic(Resource::MUSIC_MAIN_THEME_HURRY));



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

    if (data.LoadTexture(Resource::IMG_LIFE_BOB, "images/1.png") != AppStatus::OK)
    {
        return AppStatus::ERROR;
    }
    img_life_bob = data.GetTexture(Resource::IMG_LIFE_BOB);

    if (data.LoadTexture(Resource::IMG_LIFE_BUB, "images/2.png") != AppStatus::OK)
    {
        return AppStatus::ERROR;
    }
    img_life_bub = data.GetTexture(Resource::IMG_LIFE_BUB);

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


    if (data.LoadTexture(Resource::IMG_CINEMATIC_LETTERS, "images/Cinematic_Leters.png") != AppStatus::OK)
    {
        return AppStatus::ERROR;
    }
    img_cinematic_letters = data.GetTexture(Resource::IMG_CINEMATIC_LETTERS);

    text_->Initialise(Resource::IMG_TEXT, "images/NUMBERS.png", '0', 8);

    if (data.LoadTexture(Resource::IMG_ITEMS, "images/Objects.png") != AppStatus::OK)
    {
        return AppStatus::ERROR;
    }

    InitBubBobIntro();
    return AppStatus::OK;
}
const int Game::GetCredit()
{
    return credit;
}
void Game::RenderCredit()
{
    if (GetCredit() < 999)
    {
        text_->Draw(225, 215, TextFormat("%d",credit), WHITE);
    }
}
void Game::incCredit()
{
    credit++;
    RenderCredit();
    ResourceManager::Instance().PlaySoundEffect(Resource::SFX_INSERT_COIN);
}
void Game::decCredit()
{
    credit--;
}
bool Game::pastTime(float time)
{
    frameCounter++;
    if (frameCounter / 60 == time)
    {
        frameCounter = 0;
        return true;
    }
    return false;
}
void Game::RenderUI()
{
    DrawTexture(*img_ScoreHeader, 0, -1, WHITE);
    text_->Draw(35, 8, TextFormat("%d", scene->Score()), WHITE);

    if (scene->Score() >= HighScore)
    {
        HighScore = scene->Score();
    }
    text_->Draw(122, 8, TextFormat("%d", HighScore), WHITE);


}
void Game::RenderLives()
{
    if (scene != nullptr)
{

    if (scene->player->lives == 3)
    {
        DrawTexture(*img_life_bub, 0, WINDOW_HEIGHT - 8, WHITE);
        DrawTexture(*img_life_bub, 8, WINDOW_HEIGHT - 8, WHITE);
        DrawTexture(*img_life_bub, 16, WINDOW_HEIGHT - 8, WHITE);
    }
    else if (scene->player->lives == 2)
    {
        DrawTexture(*img_life_bub, 0, WINDOW_HEIGHT - 8, WHITE);
        DrawTexture(*img_life_bub, 16, WINDOW_HEIGHT - 8, WHITE);
    }
    else if (scene->player->lives == 1)
    {
        DrawTexture(*img_life_bub, 0, WINDOW_HEIGHT-8, WHITE);
    }

}
}
AppStatus Game::BeginPlay()
{
    if (scene != nullptr)
    {
        scene->Release();
        delete scene;
        scene = nullptr;
    }

    // Create new scene
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
void Game::InitBubBobIntro()
{
    Point p(60, 150);
    IntroBub->Set(p, p, 32, 32, 32, 32);
    IntroBub->InitializeAnimations();
    IntroBub->SetAnimationE((int)Animations::BUB_LEVEL_TRANSITION_FASE_2);

    Point d(160, 150);
    IntroBob->Set(d, d, 32, 32, 32, 32);
    IntroBob->InitializeAnimations();
    IntroBob->SetAnimationE((int)Animations::BOB_LEVEL_TRANSITION_FASE_2);

}
AppStatus Game::Update()
{
    //Check if user attempts to close the window, either by clicking the close button or by pressing Alt+F4
    if(WindowShouldClose()) return AppStatus::QUIT;

    switch (state)
    {
        case GameState::START:
            if (transCounter == 6)
            {
              
                state = GameState::MAIN_MENU;
            }
            if (IsKeyPressed(KEY_ONE))
            {
                state = GameState::INTRO;
            }
            break;

        case GameState::MAIN_MENU:
            if (IsKeyPressed(KEY_ESCAPE)) return AppStatus::QUIT;
            if (pastTime(5) && (GetCredit() == 0))
            {
                state = GameState::INSERT_COIN;
            }
            if (IsKeyPressed(KEY_ENTER))
            {
                incCredit();
                state = GameState::PLAYER_1;
            }
            if (IsKeyPressed(KEY_SPACE))
            {
                state = GameState::INTRO;
            }
            if (IsKeyPressed(KEY_ONE))
            {
                state = GameState::PLAYING;
            }
            break;

        case GameState::INSERT_COIN:
            if (IsKeyPressed(KEY_ESCAPE)) return AppStatus::QUIT;
            if (pastTime(3))
            {
                state = GameState::TUTORIAL;
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

            if (pastTime(.1))//should be 8.4
            {

                if (BeginPlay() != AppStatus::OK) return AppStatus::ERROR;
                state = GameState::PLAYING;
            }
            break;
        case GameState::GAME_OVER:
            if (pastTime(3))
            {
                state = GameState::MAIN_MENU;
            }
            break;

        case GameState::PLAYING:  
            if (IsKeyPressed(KEY_ESCAPE))
            {
                //FinishPlay();
                state = GameState::GAME_OVER;
                decCredit();
            }
            else if (scene->passStage == true) {

                stageCounter++;
                if (stageCounter >= 3)
                {
                    stageCounter = 1;
                    state = GameState::MAIN_MENU;
                    decCredit();
                    break;
                }
                state = GameState::TRANSITIONING;
                scene->passStage = false;
            }
            else
            {
                //Game logic
                scene->Update();
            }
            if (scene->returnMenu == true)
            {
                state = GameState::MAIN_MENU;

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
            if (transCounter == 6)
            {
                ResourceManager::Instance().PlaySoundEffect(Resource::MUSIC_TITLE);
                transCounter++;
            }

            DrawTexture(*img_menu, TittleOffset, 0, WHITE);
            if ((int)frameCounter % 3 == 0)
            {
                if (TittleOffset == -WINDOW_WIDTH * 3)
                {
                    TittleOffset = 0;
                }
                else
                {
                    TittleOffset -= WINDOW_WIDTH;
                }
            }


            RenderCredit();
            RenderUI();
            scene->ResetScore();
            break;

        case GameState::INSERT_COIN:

            DrawTexture(*img_insert_coin, 0, 0, WHITE);
            RenderCredit();
            RenderUI();
            break;

        case GameState::TUTORIAL:
            DrawTexture(*img_tutorial, 0, 0, WHITE);
            RenderUI();
            break;

        case GameState::INTRO:
            UpdateMusicStream(*ResourceManager::Instance().GetMusic(Resource::MUSIC_INTRO));
            DrawTexture(*img_intro, 0, 0, WHITE);
            if (((int)frameCounter / 60) % 2 == 0)
            {
                alpha += 0.01;
                DrawRectangle(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, Fade(BLACK, alpha));
            }
            else
            {
                alpha -= 0.01;
                DrawRectangle(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, Fade(BLACK, alpha));
            }
            DrawTexture(*img_cinematic_letters, 0, 0, WHITE);
            IntroBub->Spriteset();
            IntroBob->Spriteset();

            break;

        case GameState::PLAYER_1:

            DrawTexture(*img_player_1, 0, 0, WHITE);
            RenderCredit();
            RenderUI();
            alpha = 0;
            break;

        case GameState::PLAYER_2_AND_1:
            DrawTexture(*img_player_2, 0, 0, WHITE);
            RenderCredit();
            RenderUI();
            alpha = 0;
            break;

        case GameState::GAME_OVER:
            DrawTexture(*img_game_over, 0, 0, WHITE);
            RenderCredit();
            RenderUI();
            break;

        case GameState::PLAYING:
            if ((playtime/60) <= 30)
            {
                UpdateMusicStream(*ResourceManager::Instance().GetMusic(Resource::MUSIC_BACKGROUND));
                playtime++;
            }
            else
            {
                UpdateMusicStream(*ResourceManager::Instance().GetMusic(Resource::MUSIC_MAIN_THEME_HURRY));
                playtime++;
            }
            RenderUI();
            scene->Render();
            RenderLives();

            break;
        case GameState::TRANSITIONING:
            UpdateMusicStream(*ResourceManager::Instance().GetMusic(Resource::MUSIC_BACKGROUND));
            float progress = timeElapsed / totalTime;
            float yPos_stage2 = 224.0f * -progress; 
            playtime = 0;
            if (timeElapsed < totalTime) {

                DrawTexture(*img_stage1, 0, yPos_stage2, WHITE);
                DrawTexture(*img_stage2, 0, yPos_stage2 + 224, WHITE);
                RenderUI();
                RenderLives();
                timeElapsed += GetFrameTime();

            }
            else {
                RenderUI();
                timeElapsed = 0;
                state = GameState::PLAYING;
                scene->LoadLevel(2);
                RenderLives();
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
        WaitTime(3);
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
    
    data.UnloadMusic(Resource::MUSIC_BACKGROUND);
    data.UnloadMusic(Resource::SFX_INSERT_COIN);
    data.UnloadMusic(Resource::SFX_JUMP);
    data.UnloadMusic(Resource::SFX_BUBBLE);
    data.UnloadMusic(Resource::SFX_PICKUP);

    UnloadRenderTexture(target);
}