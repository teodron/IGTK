#pragma once


template<typename TBuffer>
IGTK::ImageBaseRaw<TBuffer>::ImageBaseRaw()
{
	this->m_data.emplace_back(1);
	printf("Constructor from base class called\n");
}

IGTK::ImageBaseColor::ImageBaseColor()
{
	this->m_data.emplace_back(2, 0, 0);
	printf("Constructor from derived class called\n");
}

IGTK::ImageBaseColor::ImageBaseColor(const std::string& fileName)
{
	this->m_data.emplace_back(3, 0, 0);
	printf("Constructor from derived class called\n");
}

IGTK::ImageBaseGrayscale::ImageBaseGrayscale()
{
	this->m_data.emplace_back(4);
	printf("Constructor from derived class called\n");
}

IGTK::ImageBaseGrayscale::ImageBaseGrayscale(const std::string& fileName)
{
	this->m_data.emplace_back(5);
	printf("Constructor from derived class called\n");
}

