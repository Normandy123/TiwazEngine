#pragma once

#include <cstdint>

namespace Tiwaz
{
	class EngineObject
	{
	public:
		EngineObject()
		{

		}

		virtual ~EngineObject()
		{
			m_ID = 0;
		}

		virtual void Init() {}
		virtual void Update() {}
		virtual void Exit() {}

		void SetObjectID(const uint64_t & ID) { m_ID = ID; }

		inline const uint64_t object_ID() { return m_ID; }

	protected:
		uint64_t m_ID = 0;
	};
}