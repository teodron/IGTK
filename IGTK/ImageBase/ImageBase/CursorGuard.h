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
			if (inData != nullptr)
				m_isValid = new bool(true);
			else
				m_isValid = new bool(false);
		}

		CursorGuard(const CursorGuard& inOtherGuard)
		{
			m_handle = inOtherGuard.m_handle;
			m_isValid = inOtherGuard.m_isValid;
			m_handle->IncRefCount();
		}

		CursorGuard& operator =(const CursorGuard& inOtherGuard)
		{
			if (m_handle->m_refCount == 1)
			{
				delete m_isValid;
				m_isValid = nullptr;
			}
			m_handle->DecRefCount();
			m_handle = inOtherGuard.m_handle;
			m_isValid = inOtherGuard.m_isValid;
			m_handle->IncRefCount();
			return *this;
		}


		~CursorGuard()
		{
			if (m_handle->m_refCount == 1 || *m_isValid == false)
			{
				delete m_isValid;
			}
			m_handle->DecRefCount();
		}

		bool inline IsValid() const
		{
			if (m_isValid != nullptr)
				return *m_isValid;
			else
				return false;
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
			if (m_handle->m_refCount == 1)
				delete m_isValid;
			m_handle->DecRefCount();
			m_handle = new GenericHandle<TInner>(inData);
			m_handle->IncRefCount();
			if (inData != nullptr)
				m_isValid = new bool(true);
			else
				m_isValid = new bool(false);
		}

		void Invalidate()
		{
			*m_isValid = false;
			delete m_handle;
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
			if (*m_isValid&&*iCursorGuard.m_isValid)
				return m_handle->m_data == iCursorGuard.m_handle->m_data;
			else if ((!*m_isValid && !*iCursorGuard.m_isValid) || (!*m_isValid && iCursorGuard == nullptr) || (*this == nullptr && !*iCursorGuard.m_isValid))
				return true;
			else
				return false;
		}

	private:
		GenericHandle<TInner>* m_handle;
		bool* m_isValid;
	};
}
