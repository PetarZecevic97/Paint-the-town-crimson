#include "precomp.h"
#include "InputManager.h"

#include "ECS/EntityManager.h"

namespace Engine
{
    bool KeyDown(KeyboardButton _iKey)
    {
        short iState = GetAsyncKeyState(static_cast<int>(_iKey));
        return (iState & 0x8000) != 0;
    }

    bool InputManager::Init()
    {
        LOG_INFO("Initializing InputManager");

        InitKeybinds();

        return true;
    }

    void InputManager::ProcessInput()
    {
        for (auto& [action, key] : m_InputActions)
        {
            bool bIsPressed = KeyDown(key);
            switch (m_InputActionStates[action])
            {
            case EInputActionState::None:
            {
                m_InputActionStates[action] = bIsPressed ? EInputActionState::JustPressed : EInputActionState::None;
                break;
            }
            case EInputActionState::JustPressed:
            case EInputActionState::Pressed:
            {
                m_InputActionStates[action] = bIsPressed ? EInputActionState::Pressed : EInputActionState::Released;
                break;
            }
            case EInputActionState::Released:
            {
                m_InputActionStates[action] = bIsPressed ? EInputActionState::JustPressed : EInputActionState::None;
                break;
            }
            default:
                ASSERT("Unknown EInputActionState {0}", m_InputActionStates[action]);
                m_InputActionStates[action] = EInputActionState::None;
                break;
            }
        }
    }

    void InputManager::Update(float dt, EntityManager* entityManager)
    {
        ProcessInput();

        // Update entities
        auto inputComponents = entityManager->GetAllComponentInstances<InputComponent>();

        for (auto component : inputComponents)
        {
            for (auto& action : component->inputActions)
            {
                action.m_Active = IsButtonActionActive(action.m_Action, action.m_ActionTriggerState);
                action.m_JustPressed = IsButtonActionActive(action.m_Action, EInputActionState::JustPressed);
            }
        }
    }

    void InputManager::Shutdown()
    {
        m_InputActions.clear();
        m_InputActionStates.clear();
    }

    bool InputManager::IsButtonActionActive(EInputAction _eAction, EInputActionState _eState) const
    {
        ASSERT(m_InputActionStates.find(_eAction) != m_InputActionStates.end(), "Unknown input action: {}", _eAction);
        return m_InputActionStates.at(_eAction) == _eState;
    }

    void InputManager::InitKeybinds()
    {
        m_InputActionStates.clear();
        m_InputActions.clear();

        //changed some inputs
        m_InputActions["PlayerShootUp"] = VK_UP;
        m_InputActions["PlayerShootLeft"] = VK_LEFT;
        m_InputActions["PlayerShootDown"] = VK_DOWN;
        m_InputActions["PlayerShootRight"] = VK_RIGHT;
		m_InputActions["PauseGame"] = 'P';//VK_ESCAPE;
        m_InputActions["RestartGame"] = 'R';
        m_InputActions["PlayerMoveUp"] = 'W';
        m_InputActions["PlayerMoveLeft"] = 'A';
        m_InputActions["PlayerMoveDown"] = 'S';
        m_InputActions["PlayerMoveRight"] = 'D';
        m_InputActions["PanCameraUp"] = 'Y';
        m_InputActions["PanCameraLeft"] = 'Y';
        m_InputActions["PanCameraDown"] = 'Y';
        m_InputActions["PanCameraRight"] = 'Y';
        m_InputActions["Start"] = VK_RETURN;
    }

    bool InputManager::IsActionActive(InputComponent* inputComponent, EInputAction targetAction)
    {
        auto found = std::find_if(
            std::begin(inputComponent->inputActions),
            std::end(inputComponent->inputActions),
            [targetAction](Engine::InputAction e)
        {
            return e.m_Action == targetAction && e.m_Active == true;
        });

        return found != std::end(inputComponent->inputActions);
    }

    bool InputManager::WasJustPressed(InputComponent* inputComponent, EInputAction targetAction)
    {
        auto found = std::find_if(
            std::begin(inputComponent->inputActions),
            std::end(inputComponent->inputActions),
            [targetAction](Engine::InputAction e)
            {
                return e.m_Action == targetAction && e.m_JustPressed == true;
            });

        return found != std::end(inputComponent->inputActions);
    }
}
