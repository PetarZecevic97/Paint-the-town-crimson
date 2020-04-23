#pragma once


struct SDL_Texture;

namespace Engine {

    class Renderer;

    struct Texture
    {
        SDL_Texture* m_Texture{};

        bool LoadTexture(Renderer* renderer_, std::string path_);
        Texture() = default;
        Texture(Renderer* renderer_, std::string path_);
        ~Texture();
    };
}
