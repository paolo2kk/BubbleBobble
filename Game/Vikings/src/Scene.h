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
<<<<<<< Updated upstream

private:
    AppStatus LoadLevel(int stage);

    Player *player;
    TileMap *level;
    Camera2D camera;
=======
    AppStatus LoadLevel(int stage);
    void BubbleSpawner();
    int stage = 1;
private:
    void CheckCollisions();
    void ClearLevel();
    void UpdateBubbles();
    void RenderObjects();
    void RenderObjectsDebug(const Color& col) const;
    void RenderGUI() const;
    float eTimeSpawnX;
    float eTimeSpawnY;
    Player *player;
    TileMap *level;
    Camera2D camera;
    std::vector<Object*> objects;
    std::vector<Bubble*> bubbles;
>>>>>>> Stashed changes

    DebugMode debug;
};

