#pragma once
#include "GenericHandle.h"

namespace IGTK
{
	template <typename TInner>
	class CursorGuard
	{
	public:

		CursorGuard(TInner* inData)
		{
			m_handle = new GenericHandle<TInner>(inData);
			m_handle->IncRefCount();
		}

		CursorGuard(const CursorGuard& inOtherGuard)
		{
			m_handle = inOtherGuard.m_handle;
			m_handle->IncRefCount();
		}

		CursorGuard& operator =(const CursorGuard& inOtherGuard)
		{
			m_handle->DecRefCount();
			m_handle = inOtherGuard.m_handle;
			m_handle->IncRefCount();
			return *this;
		}


		~CursorGuard()
		{
			m_handle->DecRefCount();
		}

		bool inline IsValid() const
		{
			return m_handle->m_isValid;
		}

		size_t inline GetRefCount() const
		{
			if (m_handle != nullptr)
				return m_handle->m_refCount;
			else
				return 0;
		}

		void SetNewPointer(TInner* inData)
		{
			m_handle->DecRefCount();
			m_handle = new GenericHandle<TInner>(inData);
			m_handle->IncRefCount();
		}

		void Invalidate()
		{
			m_handle->Invalidate();
		}

		TInner* operator -> ()
		{
			return m_handle->m_data;
		}

		TInner& operator * ()
		{
			return *(m_handle->m_data);
		}

		bool operator == (TInner* iPointer)
		{
			if (IsValid())
				return m_handle->m_data == iPointer;
			else if (iPointer == nullptr)
				return true;
			else
				return false;
		}

		bool operator == (CursorGuard& iCursorGuard)
		{
			if (m_handle->m_isValid && iCursorGuard.m_handle->m_isValid)
				return m_handle->m_data == iCursorGuard.m_handle->m_data;
			else if ((!m_handle->m_isValid && !iCursorGuard.m_handle->m_isValid))
				return true;
			else
				return false;
		}


	private:
		// Prevent heap allocation
		void * operator new   (size_t);
		void * operator new[](size_t);
		void   operator delete   (void *);
		void   operator delete[](void*);
	private:
		GenericHandle<TInner>* m_handle;
	};
}
