#pragma once
#include <raylib.h>
#include "Player.h"
#include "TileMap.h"
#include "Object.h"
#include "Bubble.h"

enum class DebugMode { OFF, SPRITES_AND_HITBOXES, ONLY_HITBOXES, SIZE };

class Scene
{
public:
    Scene();
    ~Scene();

    AppStatus Init();
    void Update();
    void Render();
    void RenderMenu(const Texture2D* image);
    void Release();
    AppStatus LoadLevel(int stage);

private:
    void CheckCollisions();
    void ClearLevel();
    void RenderObjects() const;
    void RenderObjectsDebug(const Color& col) const;
    void RenderGUI() const;

    Player *player;
    TileMap *level;
    Camera2D camera;
    Bubble* bubble;
    std::vector<Object*> objects;

    DebugMode debug;
};

