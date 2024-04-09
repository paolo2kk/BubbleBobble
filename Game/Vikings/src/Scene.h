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

    Player *player;
    TileMap *level;
    Camera2D camera;

    DebugMode debug;
};

