#pragma once

namespace Engine
{
	class Entity;
}

namespace Game
{
	class HealtManager
	{
	public:
		static HealtManager* Get();// { ASSERT(m_Instance != nullptr, "Healt Manager is not initialized!"); return m_Instance; }
		bool Init();
		bool ShutDown();

		void UpdateEntityHealt(Engine::Entity* collider);
	private:
		inline static HealtManager* m_Instance = nullptr;
	};
}
