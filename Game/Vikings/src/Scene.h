#pragma once
#include <raylib.h>
#include "Player.h"
#include "TileMap.h"
#include "Object.h"
#include "BubbleFromPlayer.h"
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
    void Release();
    AppStatus LoadLevel(int stage);
    int stage = 1;
    void PlayerBubbleSpawn();
    int Score() const;
private:
    void BubbleSpawner();
    void CheckCollisions();
    void ClearLevel();
    void UpdateBubbles();
    void RenderObjects();
    void RenderObjectsDebug(const Color& col) const;

    Player *player;
    TileMap *level;
    Camera2D camera;
    float eBubblingTime;
    float eTimeSpawnX;
    float eTimeSpawnY;
    std::vector<Object*> objects;
    std::vector<Bubble*> bubbles;
    std::vector<BubbleFromPlayer*> bubblesPlayer;

    DebugMode debug;
};

