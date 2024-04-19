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
AppStatus ResourceManager::LoadMusic(Resource id, const std::string& file_path) {
    Music music = LoadMusicStream(file_path.c_str());
    if (!music.ctxData) {
        LOG("Failed to load music ", file_path);
        return AppStatus::ERROR;
    }
    musicResources[id] = music;
    return AppStatus::OK;
}
AppStatus ResourceManager::LoadSoundEffect(Resource id, const std::string& file_path) {
    Sound sound = LoadSound(file_path.c_str());
    if (!sound.frameCount) {
        LOG("Failed to load sound effect ", file_path);
        return AppStatus::ERROR;
    }
    soundEffects[id] = sound;
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
void ResourceManager::UnloadMusic(Resource id) {
    if (musicResources.find(id) != musicResources.end()) {
        UnloadMusicStream(musicResources[id]);
        musicResources.erase(id);
    }
}
void ResourceManager::PlaySoundEffect(Resource id) {
    auto it = soundEffects.find(id);
    if (it != soundEffects.end()) {
        PlaySound(it->second);
    }
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
const Music* ResourceManager::GetMusic(Resource id) const {
    auto it = musicResources.find(id);
    if (it != musicResources.end()) {
        return &(it->second);
    }
    return nullptr;
}

void ResourceManager::Release()
{
    for (auto& pair : textures)
    {
        UnloadTexture(pair.second);
    }
    textures.clear();
}