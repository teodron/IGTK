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
		}

		GenericResource(GenericResource&& movableResource)
		{
			PRINT_FUNC();
			*this = std::move(movableResource); // if it has a name, it is an lvalue. use std::move to hide the name
		}

		GenericResource& operator=(GenericResource&& movableResource)
		{
			PRINT_FUNC();
			std::swap(*this, movableResource);
			return *this;
		}

		void Set()
		{
			mIsSet = true;
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
		MoveSemantics();
		~MoveSemantics();

	private:
		GenericResource mResource;
	};

}