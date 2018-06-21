#include "render_scene.h"

#include "graphic_component.h"

namespace Tiwaz::Graphic
{
	RenderScene::RenderScene()
	{

	}

	RenderScene::~RenderScene()
	{
		for (Component::GraphicComponent* component : m_components)
		{
			component = nullptr;
		}

		m_components.clear();
	}

	void RenderScene::AddComponent(Component::GraphicComponent * component)
	{
		if (component != nullptr)
		{
			const std::vector<Component::GraphicComponent*>::iterator it = std::find(m_components.begin(), m_components.end(), component);

			if (it == m_components.cend())
			{
				m_components.push_back(component);
			}
		}
	}

	void RenderScene::RemoveComponent(Component::GraphicComponent * component)
	{
		if (component != nullptr)
		{
			const std::vector<Component::GraphicComponent*>::iterator it = std::find(m_components.begin(), m_components.end(), component);

			if (it != m_components.cend())
			{
				ptrdiff_t pd = std::distance(m_components.begin(), it);

				m_components[pd] = nullptr;
				m_components.erase(m_components.cbegin() + pd);
			}
		}
	}
}

namespace Tiwaz::Global
{
	Graphic::RenderScene* RENDER_SCENE;
}