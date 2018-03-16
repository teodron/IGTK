#pragma once

namespace IGTK
{
	struct ColorPixel
	{
		unsigned char m_r;
		unsigned char m_g;
		unsigned char m_b;

		ColorPixel(const unsigned char& iR = 0, const unsigned char& iG = 0, const unsigned char& iB = 0) : m_r(iR), m_g(iG), m_b(iB) {};
	};

	struct GrayscalePixel
	{
		unsigned char m_g;
		GrayscalePixel(const unsigned char& iG = 0) : m_g(iG) {};
	};
}