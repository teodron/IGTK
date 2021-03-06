// ConsoleApplication1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include <conio.h>
#include "ImageBase.h"

struct ColorPixel
{
	unsigned char m_r;
	unsigned char m_g;
	unsigned char m_b;
};

struct GrayscalePixel
{
	unsigned char m_g;
};

int main()
{
	std::string path = "path";
	IGTK::ImageBaseRawOneConstructor<GrayscalePixel> OCGrayImage(path);
	
	{
		IGTK::ImageBaseRawOneConstructor<ColorPixel> OCColorImage(path);
		//IGTK::ImageBaseRawOneConstructor<ColorPixel> OCColorImageC(OCColorImage); //Error: Runtime error because generated copy constructor makes a shallow copy and when the object is destroyed, it tries to free the same memory as the original object (dangling pointer)

		//IGTK::ImageBaseRawOneConstructor<ColorPixel> OCColorImageD(std::move(OCColorImage));  //Error: Runtime error because generated move constructor does not set internal pointer to null

	}

	IGTK::ImageBaseRawRuleOfFive<GrayscalePixel> R5GrayImage(path);
	IGTK::ImageBaseRawRuleOfFive<ColorPixel> R5ColorImage(path);

	
	IGTK::ImageBaseRawRuleOfFive<ColorPixel> R5ColorImageC(R5ColorImage);

	//IGTK::ImageBaseRawOneConstructor<ColorPixel> OCColorImageB; // Error: no default constructor
	//OCColorImageB = OCColorImage;
	IGTK::ImageBaseRawRuleOfFive<ColorPixel> R5ColorImageB;
	R5ColorImageB = R5ColorImage;

	
	IGTK::ImageBaseRawRuleOfFive<ColorPixel> R5ColorImageD(std::move(R5ColorImage));

	//IGTK::ImageBaseRawOneConstructor<ColorPixel> OCColorImagedE; // Error: no default constructor
	//OCColorImagedE = std::move(OCColorImage);
	IGTK::ImageBaseRawRuleOfFive<ColorPixel> R5ColorImagedE;
	R5ColorImagedE = std::move(R5ColorImage);

	_getch();

    return 0;
}

