#pragma once

#include <cstdint>
#include <vector>
#include <algorithm>

#include "graphic_component.h"

namespace Tiwaz::Graphic
{
	class RenderScene
	{
	public:
		~RenderScene()
		{
			for (Component::GraphicComponent* comp : m_components)
			{
				comp = nullptr;
			}

			m_components.clear();
		}

		void AddComponent(Component::GraphicComponent* component)
		{
			if (component != nullptr)
			{
				const std::vector<Component::GraphicComponent*>::iterator it = std::find(m_components.begin(), m_components.end(), component);

				if ((it == m_components.cend()) || m_components.empty())
				{
					m_components.emplace_back(component);
				}
			}
		}

		void RemoveComponent(const Component::GraphicComponent* component)
		{
			if (component != nullptr)
			{
				const std::vector<Component::GraphicComponent*>::iterator it = std::find(m_components.begin(), m_components.end(), component);

				if ((it != m_components.cend()) || (!m_components.empty()))
				{
					ptrdiff_t pd = std::distance(m_components.begin(), it);

					m_components[pd] = nullptr;
					m_components.erase(m_components.cbegin() + pd);
				}
			}
		}

		const std::vector<Component::GraphicComponent*>* Components() { return &m_components; }

	private:
		std::vector<Component::GraphicComponent*> m_components;
	};
}

namespace Tiwaz::Global
{
	extern Graphic::RenderScene* RENDER_SCENE;
}