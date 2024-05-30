#pragma once
#include <raylib.h>
#include "Player.h"
#include "Player2.h"
#include "TileMap.h"
#include "Object.h"
#include "BubbleFromPlayer.h"
#include "Bubble.h"
#include "Enemy.h"
#include "EnemyManager.h"
#include "ShotManager.h"
#include "Bottle.h"
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
    int AllObjects;
    void PlayerBubbleSpawn();
    int Score() const;
    int Score2() const;
    void ResetScore() const;
    bool returnMenu = false;
    bool passStage = false;
    int stage = 1;

    Player* player;
    Player2* player2;
    bool P2in;
    bool P1in;
    bool nextSceneTrigger = false;
private:
    void BubbleSpawner();
    void CheckCollisions();
    void BubbleDespawn();
    void ClearLevel();
    void UpdateBubbles();
    void RenderObjects();
    void RenderObjectsDebug(const Color& col) const;

    int numEnemies = 0;
    float eTimeTrans = 0;
    TileMap *level;
    Enemy* enemy;
    Camera2D camera;
    float eBubblingTime;
    float eTimeSpawnX;
    float eTimeSpawnY;
    float eTimeBottle = 0;
    std::vector<Object*> objects;
    std::vector<Object*> thunds;

    std::vector<Projectile*> projectiles;

    std::vector<Bubble*> bubbles;
    EnemyManager* enemies;
    ShotManager* shots;
    ParticleManager* particles;

    std::vector<BubbleFromPlayer*> bubblesPlayer;
    std::vector<BubbleFromPlayer*> bubblesPlayer2;

    DebugMode debug;
};

