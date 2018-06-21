#pragma once

#include <cstdint>

#include <vector>
#include <algorithm>

namespace Tiwaz::Component
{
	class GraphicComponent;
}

namespace Tiwaz::Graphic
{
	class RenderScene
	{
	public:
		RenderScene();
		~RenderScene();

		void AddComponent(Component::GraphicComponent* component);

		void RemoveComponent(Component::GraphicComponent * component);

		const std::vector<Component::GraphicComponent*> Components() { return m_components; }

		const bool HasComponents() { return !m_components.empty(); };

	private:
		std::vector<Component::GraphicComponent*> m_components;
	};
}

namespace Tiwaz::Global
{
	extern Graphic::RenderScene* RENDER_SCENE;
}