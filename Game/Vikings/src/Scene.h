#pragma once
#include <raylib.h>
#include "Player.h"
#include "TileMap.h"

enum class DebugMode { OFF, SPRITES_AND_HITBOXES, ONLY_HITBOXES, SIZE };

class Scene
{
public:
    Scene();
    ~Scene();

    AppStatus Init();
    void Update();
    void Render();
    void Release();


private:
    AppStatus LoadLevel(int stage);
    AppStatus LoadMenu(int stage);

    Player *player;
    TileMap *level;
    UI* menu;
    Camera2D camera;

    DebugMode debug;
};

