#pragma once

#include <string>
#include <vector>
#include <conio.h>
#include "PixelDataStructures.h"
namespace IGTK
{

	class NameObject
	{
		public:
			char* objectName;

			NameObject()
			{
				objectName = new char[100];
			}

			NameObject(const NameObject& nameObj) : NameObject()
			{
				strcpy_s(objectName, 100, nameObj.objectName);
			}

			NameObject& operator = (const NameObject& nameObj)
			{
				strcpy_s(objectName, 100, nameObj.objectName);
				return *this;
			}

			~NameObject()
			{
				printf("%s was destroyed\n\n", objectName);
				if(objectName!=nullptr)
					delete[] objectName;
			}
	};

	template<typename TBuffer>
	class ImageBaseRaw
	{
		public:
			ImageBaseRaw();
			~ImageBaseRaw() = default;

			//constructor with initializer list:
			ImageBaseRaw(const ImageBaseRaw& otherImage) : m_data(otherImage.m_data), m_name(otherImage.m_name) { printf("Constructor from base class called\n"); }
			
			void SetName(const char* objectName) { strcpy_s(m_name.objectName,20,objectName); return; }
		protected:
			std::vector<TBuffer> m_data;
			NameObject m_name;
	};

	class ImageBaseColor : public ImageBaseRaw<ColorPixel>
	{
	public:
		ImageBaseColor();
		ImageBaseColor(const std::string& path);

		//delegating base class constructor from derived class constructor:
		ImageBaseColor(const ImageBaseColor& otherImage) : ImageBaseRaw<ColorPixel>(otherImage) { printf("Constructor from derived class called\n"); };

		ImageBaseColor(ImageBaseColor&& otherImage) = default;
		~ImageBaseColor() = default;
		ImageBaseColor& operator = (const ImageBaseColor& otherImage) = default;
		ImageBaseColor& operator = (ImageBaseColor&& otherImage) = default;
	};

	class ImageBaseGrayscale : public ImageBaseRaw<GrayscalePixel>
	{
		public:
			ImageBaseGrayscale();
			ImageBaseGrayscale(const std::string& path);

			//delegating base class constructor from derived class constructor:
			ImageBaseGrayscale(const ImageBaseGrayscale& otherImage) : ImageBaseRaw<GrayscalePixel>(otherImage) { printf("Constructor from derived class called\n"); };

			ImageBaseGrayscale(ImageBaseGrayscale&& otherImage) = default;
			~ImageBaseGrayscale() = default;
			ImageBaseGrayscale& operator = (const ImageBaseGrayscale& otherImage) = default;
			ImageBaseGrayscale& operator = (ImageBaseGrayscale&& otherImage) = default;
	};
}


#include "ImageBase.hpp"