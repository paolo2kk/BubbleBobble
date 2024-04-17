#pragma once

#include "raylib.h"
#include "Globals.h"
#include <unordered_map>
#include <string>

enum class Resource {
    IMG_MENU,
    IMG_TUTORIAL,
    IMG_INTRO,
    IMG_GAME_OVER,
    IMG_PLAYER_2,
    IMG_SCORE,
    IMG_MENU2,
    IMG_MENU3,
    IMG_MENU4,
    IMG_INSCOIN,
    IMG_PLAYER_1,
    IMG_PLAYER, 
    IMG_TILES,
    IMG_TILES2,
    IMG_ITEMS,
    IMG_BONUS,
    IMG_BUBBLES,
    IMG_STAGE1,
    IMG_STAGE2,
};

class ResourceManager {
public:
    //Singleton instance retrieval
    static ResourceManager& Instance()
    {
        static ResourceManager instance; //Guaranteed to be initialized only once
        return instance;
    }

    //Load and unload texture
    AppStatus LoadTexture(Resource id, const std::string& file_path);
    AppStatus LoadAudio(Resource id, const std::string& file_path);
    void ReleaseTexture(Resource id);

    //Get texture by key
    const Texture2D* GetTexture(Resource id) const;

    //Release resources
    void Release();

    //Ensure Singleton cannot be copied or assigned
    ResourceManager(const ResourceManager&) = delete;
    ResourceManager& operator=(const ResourceManager&) = delete;

private:
    //Private constructor to prevent instantiation
    ResourceManager();
    //Destructor
    ~ResourceManager();

    //Dictionary to store loaded textures
    std::unordered_map<Resource, Texture2D> textures;
    std::unordered_map<Resource, Sound> sounds;

};