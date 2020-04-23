

namespace Engine
{
    class Renderer;
    struct Texture;

    class TextureManager
    {
    public:
        bool CreateTexture(Renderer* renderer_, std::string name_, std::string path_);
        Texture* GetTexture(std::string name_);

        TextureManager() = default;
    private:
        std::unordered_map<std::string, std::unique_ptr<Texture>> m_Textures{};

        TextureManager(const TextureManager& other) = delete;
        TextureManager& operator=(TextureManager& other) = delete;
    };
}
