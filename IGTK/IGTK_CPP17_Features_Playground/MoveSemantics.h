#pragma once
#include <iostream>
#include <Windows.h>
#include "Macros.h"

namespace IGTK
{
	class GenericResource
	{
	public:
		GenericResource(int inPayload = 0) : mPayload(inPayload)
		{
			PRINT_FUNC();
			Sleep(50);
			Set();
		}

		GenericResource(GenericResource&& movableResource)
		{
			PRINT_FUNC();
			*this = std::move(movableResource); // if it has a name, it is an lvalue. use std::move to hide the name
		}

		GenericResource& operator=(GenericResource&& movableResource)
		{
			PRINT_FUNC();
			int oldPayload = mPayload;
			mPayload = movableResource.mPayload;
			mIsSet = movableResource.mIsSet;
			movableResource.mPayload = oldPayload;
			movableResource.mIsSet = false;
			return *this;
		}

		void Set()
		{
			mIsSet = true;
		}
		int GetValue() const
		{
			if (mIsSet)
			{
				return mPayload;
			}
			return 0;
		}

		void CloneFrom(const GenericResource& other)
		{
			PRINT_FUNC();
			*this = other;
		}

		GenericResource Clone()
		{
			PRINT_FUNC();
			GenericResource clone(*this);
			return clone;
		}

		void Clean()
		{
			PRINT_FUNC();
			if (mIsSet)
			{
				Sleep(50);
				mIsSet = false;
				mPayload = 0;
			}
		}

		~GenericResource()
		{
			Clean();
		}

	private:

		void ShallowCopy(const GenericResource& rhsResource)
		{
			PRINT_FUNC();
			mIsSet = rhsResource.mIsSet;
			mPayload = rhsResource.mPayload;
		}

		void DeepCopy(const GenericResource& rhsResource)
		{
			PRINT_FUNC();
			Sleep(500);
			Clean();
			ShallowCopy(rhsResource);
		}

		GenericResource(const GenericResource& rhsResource)
		{
			PRINT_FUNC();
			*this = rhsResource;
		}

		GenericResource& operator=(const GenericResource& rhsResource)
		{
			PRINT_FUNC();
			DeepCopy(rhsResource);

			return *this;
		}

		bool mIsSet = false;
		int mPayload = 0;
	};

	class MoveSemantics
	{
	public:
		MoveSemantics(int value) : mResource(value)
		{
		}
		~MoveSemantics();

		MoveSemantics(MoveSemantics&& other) = default;
		MoveSemantics& operator=(MoveSemantics&& other) = default;

		MoveSemantics(const MoveSemantics& other)
		{
			mResource.CloneFrom(other.mResource);
		}

		MoveSemantics& operator=(const MoveSemantics& other)
		{
			mResource.CloneFrom(other.mResource);
		}

		operator int()
		{
			return mResource.GetValue();
		}
	private:
		GenericResource mResource;
	};

}