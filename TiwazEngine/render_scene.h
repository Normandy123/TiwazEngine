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

		void RemoveComponent(const Component::GraphicComponent* component);

		const std::vector<Component::GraphicComponent*>* Components() { return std::addressof(m_components); }

	private:
		std::vector<Component::GraphicComponent*> m_components;
	};
}

namespace Tiwaz::Global
{
	extern Graphic::RenderScene* RENDER_SCENE;
}