#pragma once




template<typename TBuffer>
IGTK::ImageBaseRawOneConstructor<TBuffer>::ImageBaseRawOneConstructor(const std::string& fileName)
{
	this->m_data = new TBuffer[4096 * 2160];
	this->m_size = 4096 * 2160;
	printf("Image object with one constructor of type %s was created\n", typeid(TBuffer).name());
	
}

template<typename TBuffer>
IGTK::ImageBaseRawOneConstructor<TBuffer>::~ImageBaseRawOneConstructor()
{
	printf("Memory was cleared for image object with one constructor of type %s\n", typeid(TBuffer).name());
	if(this->m_size != 0 && this->m_data != nullptr)
		delete[] this->m_data;
	this->m_size = 0;
}

template<typename TBuffer>
IGTK::ImageBaseRawRuleOfFive<TBuffer>::ImageBaseRawRuleOfFive()
{
	printf("Empty image object with one constructor of type %s was created\n", typeid(TBuffer).name());
	this->m_data = nullptr;
	this->m_size = 0;
}

template<typename TBuffer>
IGTK::ImageBaseRawRuleOfFive<TBuffer>::ImageBaseRawRuleOfFive(const std::string& fileName)
{
	this->m_data = new TBuffer[4096 * 2160];
	this->m_size = 4096 * 2160;
	printf("Image object with rule of 5 of type %s was created\n", typeid(TBuffer).name());
}

template<typename TBuffer>
IGTK::ImageBaseRawRuleOfFive<TBuffer>::ImageBaseRawRuleOfFive(const IGTK::ImageBaseRawRuleOfFive<TBuffer>& otherImage)
{
	if (this->m_size != 0)
		delete[] this->m_data;
	this->m_size = otherImage.m_size;
	this->m_data = new TBuffer[this->m_size];
	for(size_t i = 0; i<this->m_size; i++)
		this->m_data[i] = otherImage.m_data[i];
	
	printf("Image object with rule of 5 of type %s was created based on another image\n", typeid(TBuffer).name());
}


template<typename TBuffer>
IGTK::ImageBaseRawRuleOfFive<TBuffer>::~ImageBaseRawRuleOfFive()
{
	printf("Memory was cleared for image object with rule of 5 of type %s\n", typeid(TBuffer).name());
	if (this->m_size != 0)
		delete[] this->m_data;
	this->m_size = 0;
}

template<typename TBuffer>
IGTK::ImageBaseRawRuleOfFive<TBuffer>& IGTK::ImageBaseRawRuleOfFive<TBuffer>::operator = (const IGTK::ImageBaseRawRuleOfFive<TBuffer>& otherImage)
{
	if (this->m_size != 0)
		delete[] this->m_data;
	this->m_size = otherImage.m_size;
	this->m_data = new TBuffer[this->m_size];
	for (size_t i = 0; i<this->m_size; i++)
		this->m_data[i] = otherImage.m_data[i];
	printf("Image object with rule of 5 of type %s was copied\n", typeid(TBuffer).name());
	return *this;
}

template<typename TBuffer>
IGTK::ImageBaseRawRuleOfFive<TBuffer>::ImageBaseRawRuleOfFive(IGTK::ImageBaseRawRuleOfFive<TBuffer>&& otherImage)
{
	if (this->m_size != 0)
		delete[] this->m_data;

	this->m_size = otherImage.m_size;
	this->m_data = otherImage.m_data;
	
	otherImage.m_size = 0;
	otherImage.m_data = nullptr;
	printf("Image object with rule of 5 of type %s was moved in another object\n", typeid(TBuffer).name());
}

template<typename TBuffer>
IGTK::ImageBaseRawRuleOfFive<TBuffer>& IGTK::ImageBaseRawRuleOfFive<TBuffer>::operator = (IGTK::ImageBaseRawRuleOfFive<TBuffer>&& otherImage)
{
	if (this->m_size != 0)
		delete[] this->m_data;

	this->m_size = otherImage.m_size;
	this->m_data = otherImage.m_data;

	otherImage.m_size = 0;
	otherImage.m_data = nullptr;
	printf("Image object with rule of 5 of type %s was moved in another object\n", typeid(TBuffer).name());
	return *this;
}
