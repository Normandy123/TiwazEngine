#pragma once

namespace TiwazEngine
{
	template<typename T> class Singleton
	{
	public:
		static T& Instance()
		{
			if (m_instance == nullptr)
			{
				m_instance = new T();
			}

			return *(m_instance);
		}

	protected:
		explicit Singleton()
		{
			if (m_instance == nullptr)
			{
				m_instance = dynamic_cast<T>(this);
			}
		}

		virtual ~Singleton()
		{
			if (m_instance != nullptr)
			{
				delete m_instance;
				m_instance = nullptr;
			}
		}

	private:
		static T* m_instance;
	};
}