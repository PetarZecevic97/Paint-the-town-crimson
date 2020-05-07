#pragma once
#include "Input/InputAction.h"
#include <SDL.h>


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

    struct ObstacleComponent : public Component 
    {
        vec2 m_Position{};
        
        ObstacleComponent() = default;
        ObstacleComponent(vec2 pos_) : m_Position(pos_) { };
        ObstacleComponent(float posx_, float posy_) : m_Position(posx_, posy_) { }

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
		//We need these two if we want to animate a bitch
        SDL_Rect m_src{};
		bool m_Animation{ false };
        bool m_FlipHorizontal{ false };
        bool m_FlipVertical{ false };
    };

    struct PlayerComponent : public Component
    {
        float m_speed{ 200.f };
        int m_fireballCooldown{ 500 };
        bool m_timeoutBuff{ false };
        bool m_tripleshotBuff{ false };
        bool m_multishotBuff{ false };
		int m_number_of_lives{ 3 };
    };

    struct FireballComponent : public Component
    {

    };

    struct BorderComponent : public Component
    {

    };

    struct LeftBorderComponent : public Component
    {

    };

    struct RightBorderComponent : public Component
    {

    };

    struct TopBorderComponent : public Component
    {

    };

    struct BottomBorderComponent : public Component
    {

    };

	struct HudComponent : public Component
	{

	};
	
	struct SpeedHudComponent : public Component
	{

	};

	struct RapidHudComponent : public Component
	{

	};

	struct DestroyerHudComponent : public Component
	{

	};

	struct TimelordHudComponent : public Component
	{

	};

	struct TripleHudComponent : public Component
	{

	};

	struct MultiHudComponent : public Component
	{

	};
	

	struct XComponent : public Component
	{

	};

	struct LifeDisplayComponent : public Component
	{

	};

	struct SlabComponent : public Component
	{

	};

	struct NumberComponent : public Component
	{
		int m_last_number { 3 };
	};

	struct ItemStashComponent : public Component
	{

	};

    struct ItemComponent : public Component
    {
        int m_timeCreated;
        int m_itemType;

      //  ItemComponent(int time, int item_type) : m_timeCreated(time), m_itemType(item_type) {};
        ItemComponent(int time) : m_timeCreated(time) {};
    };

    struct BuffComponent : public Component
    {
        int m_duration{ 5000 };
        int m_timeCreated;
        int m_buffType;

        BuffComponent(int time) : m_timeCreated(time) {};

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

	struct NPCComponent : public Component
	{

	};

    struct WallComponent : public Component
    {

    };
}
