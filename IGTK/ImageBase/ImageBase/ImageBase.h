#pragma once

#include <string>
namespace IGTK
{

	template<typename TBuffer>
	class ImageBaseRaw
	{
		protected:
			TBuffer*	m_data;
			size_t		m_size;

			//std::vector<TBuffer> m_buffer;
	};

	template<typename TBuffer>
	class ImageBaseRawOneConstructor : public ImageBaseRaw<TBuffer>
	{
	public:
		ImageBaseRawOneConstructor(const std::string& fileName);
		~ImageBaseRawOneConstructor();
	};

	template<typename TBuffer>
	class ImageBaseRawRuleOfFive : public ImageBaseRaw<TBuffer>
	{
	public:
		ImageBaseRawRuleOfFive();
		ImageBaseRawRuleOfFive(const std::string& fileName);
		ImageBaseRawRuleOfFive(const ImageBaseRawRuleOfFive& otherImage);
		ImageBaseRawRuleOfFive(ImageBaseRawRuleOfFive&& otherImage);
		~ImageBaseRawRuleOfFive();
		ImageBaseRawRuleOfFive& operator = (const ImageBaseRawRuleOfFive& otherImage);
		ImageBaseRawRuleOfFive& operator = (ImageBaseRawRuleOfFive&& otherImage);
	};
}


#include "ImageBase.hpp"