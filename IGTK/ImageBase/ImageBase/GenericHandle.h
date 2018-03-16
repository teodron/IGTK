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
		}

		GenericHandle(TInner* inData)
		{
			m_data = inData;
			m_refCount = 0;
		}

		~GenericHandle()
		{
			if (m_data != nullptr)
				delete m_data;
			m_data = nullptr;
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
		}

		TInner* m_data;
		size_t m_refCount;
	};

}