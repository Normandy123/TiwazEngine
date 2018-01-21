#pragma once

namespace Tiwaz
{
	template<typename T> class Component_Holder
	{
	public:
		Component_Holder()
		{

		}

		~Component_Holder()
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