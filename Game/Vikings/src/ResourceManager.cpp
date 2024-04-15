#include "ResourceManager.h"


ResourceManager::ResourceManager()
{
}
ResourceManager::~ResourceManager()
{
    Release();
}

//Load a texture from a file and associate it with the key id
AppStatus ResourceManager::LoadTexture(Resource id, const std::string& file_path)
{
    //Load the texture
    Texture2D texture = ::LoadTexture(file_path.c_str());
    if (texture.id == 0)
    {
        //Error loading texture
        LOG("Failed to load texture ", file_path);
        return AppStatus::ERROR;
    }
    
    //Insert the loaded texture into the map with the specified key
    textures[id] = texture;
    return AppStatus::OK;
}

AppStatus ResourceManager::LoadMusic(Resource id, const std::string& file_path) {
    Music* musicStream = new Music(LoadMusicStream(file_path.c_str()));

    // Assuming 'frameCount' might be a valid check to see if any data is loaded
    if (musicStream->frameCount == 0) {
        LOG("Failed to load music ", file_path);
        delete musicStream;
        return AppStatus::ERROR;
    }
    music[id].reset(musicStream);  // Using unique_ptr to manage the Music object
    return AppStatus::OK;
}


AppStatus ResourceManager::LoadAudio(Resource id, const std::string& file_path)
{
    //Load the sound1
    Sound sound = ::LoadSound(file_path.c_str());
    if (sound.frameCount == 0)
    {
        //Error loading sound
        LOG("Failed to load sound ", file_path);
        return AppStatus::ERROR;
    }

    //Insert the loaded sound into the map with the specified key
    sounds[id] = sound;
    return AppStatus::OK;
}

//Release the texture associated with the key id
void ResourceManager::ReleaseTexture(Resource id)
{
    //Find the texture associated with the key
    auto it = textures.find(id);

    //If found, unload the texture and remove it from the map
    if (it != textures.end())
    {
        UnloadTexture(it->second);
        textures.erase(it);
    }
}

//Realase the Music 
void ResourceManager::ReleaseMusic(Resource id) {
    auto it = music.find(id);
    if (it != music.end()) {
        UnloadMusicStream(*(it->second));  // Unload the Music stream before erasing
        music.erase(it);
    }
}

//Get Music by key
const Music* ResourceManager::GetMusic(Resource id) const {
    auto it = music.find(id);
    if (it != music.end()) {
        return it->second.get();  // Use .get() to return the raw pointer managed by unique_ptr
    }
    return nullptr;
}

//Get a texture by key
const Texture2D* ResourceManager::GetTexture(Resource id) const
{
    //Find the texture associated with the key and return it
    auto it = textures.find(id);
    if (it != textures.end())   return &(it->second);

    //Return nullptr if key is not found
    return nullptr;
}

void ResourceManager::Release()
{
    for (auto& pair : textures)
    {
        UnloadTexture(pair.second);
    }
    textures.clear();

    for (auto& pair : music) {
        UnloadMusicStream(*(pair.second));
    }
    music.clear();
}