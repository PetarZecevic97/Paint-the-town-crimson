#pragma once
#include "Input/InputAction.h"


using ComponentTypeID = std::size_t;

namespace Engine
{
    class Entity;
    struct Texture;

    struct Component
    {
        Entity* m_Owner{};
        ComponentTypeID m_TypeId{ 0 };
        bool m_Active{ false };
        virtual ~Component() = default;

    private:
        inline static ComponentTypeID m_MaxComponentTypeId = 0;

    public:
        template <typename T>
        static ComponentTypeID GetComponentTypeID()
        {
            static_assert (std::is_base_of<Component, T>::value, "");
            static ComponentTypeID typeID = Component::m_MaxComponentTypeId++;
            return typeID;
        }
    };

    struct TransformComponent : public Component
    {
        vec2 m_Position{};
        vec2 m_Size{};
        float m_Rotation{};

        TransformComponent() = default;
        TransformComponent(vec2 pos) : m_Position(pos) { };
        TransformComponent(vec2 pos, vec2 size) : m_Position(pos), m_Size(size) { };
        TransformComponent(float posx, float posy) : m_Position(posx, posy) { };
        TransformComponent(float posx, float posy, float sizex, float sizey) : m_Position(posx, posy), m_Size(sizex, sizey) { };
    };

    struct MoverComponent : public Component
    {
        vec2 m_TranslationSpeed{};
        float m_RotationSpeed{};

        MoverComponent() = default;
        MoverComponent(float x, float y) : m_TranslationSpeed(x, y) { };
        MoverComponent(float x, float y, float r) : m_TranslationSpeed(x, y), m_RotationSpeed(r) { };
    };

    enum class ECollisionShape
    {
        AABox,
        Circle,
    };

    struct CollisionComponent : public Component
    {
        vec2 m_Size{}; // only using first element for circle
        ECollisionShape m_Shape{ ECollisionShape::Circle };
        std::set<Entity*> m_CollidedWith{};

        CollisionComponent() = default;
        CollisionComponent(float radius) : m_Size(radius) {}
        CollisionComponent(float x, float y) : m_Size(x, y), m_Shape(ECollisionShape::AABox) {}
    };

    struct SpriteComponent : public Component
    {
        Texture* m_Image{};
        bool m_FlipHorizontal{ false };
        bool m_FlipVertical{ false };
    };

    struct PlayerComponent : public Component
    {

    };

    struct HealthComponent : public Component
    {
        int m_CurrentHealth;
        int m_MaxHealth;
    };

    struct CameraComponent : public Component
    {
        Entity* m_ReferenceEntity{};
        float m_PanSpeed{};

        CameraComponent() = default;
        CameraComponent(float speed) : m_PanSpeed(speed) {};
    };

    struct InputComponent : public Component
    {
        std::vector<InputAction> inputActions;
    };
}
