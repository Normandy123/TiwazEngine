#pragma once

namespace Tiwaz
{
	template<typename T> class ComponentHolder
	{
	public:
		~ComponentHolder()
		{
			if (object != nullptr)
			{
				delete object;
				object = nullptr;
			}
		}

		T* AccessObject()
		{
			return object;
		}

	private:
		T * object;
	};
}