#pragma once
namespace IGTK
{

	template <typename TInner>
	struct GenericHandle
	{
		GenericHandle()
		{
			m_data = nullptr;
			m_refCount = 0;
			m_isValid = false;
		}

		GenericHandle(TInner* inData)
		{
			m_data = inData;
			m_refCount = 0;
			m_isValid = true;
			if (m_data == nullptr)
			{
				m_isValid = false;
			}
		}

		~GenericHandle()
		{
			if (m_data != nullptr)
				delete m_data;
			m_data = nullptr;
			m_isValid = false;
		}

		void IncRefCount()
		{
			m_refCount++;
		}

		void DecRefCount()
		{
			m_refCount--;
			if (m_refCount == 0)
			{
				delete this;
			}
		}

		void Invalidate()
		{
			if (m_data != nullptr)
				delete m_data;
			m_data = nullptr;
			m_isValid = false;
		}

		TInner* m_data;
		size_t m_refCount;
		bool m_isValid;
	};

}