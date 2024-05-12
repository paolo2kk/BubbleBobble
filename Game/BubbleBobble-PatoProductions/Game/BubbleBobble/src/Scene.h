#pragma once
#include <raylib.h>
#include "Player.h"
#include "TileMap.h"
#include "Object.h"
#include "BubbleFromPlayer.h"
#include "Bubble.h"
#include "Enemy.h"
#include "EnemyManager.h"
#include "ShotManager.h"
#include "ParticleManager.h"
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
    void RandomItemSpawn();
    int stage = 1;
    int AllObjects;
    void PlayerBubbleSpawn();
    int Score() const;
    void ResetScore() const;
    bool returnMenu = false;
    bool passStage = false;
private:
    void BubbleSpawner();
    void CheckCollisions();
    void BubbleDespawn();
    void ClearLevel();
    void UpdateBubbles();
    void RenderObjects();
    void RenderObjectsDebug(const Color& col) const;

    Player *player;
    TileMap *level;
    Enemy* enemy;
    Camera2D camera;
    float eBubblingTime;
    float eTimeSpawnX;
    float eTimeSpawnY;
    std::vector<Object*> objects;
    std::vector<Bubble*> bubbles;
    EnemyManager* enemies;
    ShotManager* shots;
    ParticleManager* particles;

    std::vector<BubbleFromPlayer*> bubblesPlayer;

    DebugMode debug;
};

