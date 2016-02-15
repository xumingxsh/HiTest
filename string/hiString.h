#pragma once

/**
*    @defgroup 字符串处理函数
*    @brief    主要负责对各种编码字符串之间进行转换，注意：本版本不可以作为dll的导出函数使用，因为用到了string（主要是指MT运行时的dll）。
*	 @author  徐敏荣
*    @date    2012-07-17
*
* @par 修订历史
*    @version v0.5 \n
*	 @author  徐敏荣
*    @date    2012-07-17
*    @li 初始版本
* @{
*/ 

#include <string>
#include <sstream>
#include <vector>

namespace Hi
{
	/**
	*   @brief 将utf-8编码的字符串转换为unicode编码的字符串。
	*   @param[in] str	utf-8编码的字符串
	*   @retval unicode编码的字符串
	*   @note 如果失败，返回""
	*/
	std::wstring u82uc(const char* str);

	/**
	*   @brief 将unicode编码的字符串转换为utf-8编码的字符串。
	*   @param[in] str	ansi编码的字符串
	*   @retval utf-8编码的字符串
	*   @note 如果失败，返回""
	*/
	std::string uc2u8(const wchar_t* str);

	/**
	*   @brief 将utf-8编码的字符串转换为unicode编码的字符串。
	*   @param[in] str	utf-8编码的字符串
	*   @retval unicode编码的字符串
	*   @note 如果失败，返回""
	*/
	std::string uc2as(const wchar_t* str);

	/**
	*   @brief 将ansi编码的字符串转换为unicode编码的字符串。
	*   @param[in] str	ansi编码的字符串
	*   @retval unicode编码的字符串
	*   @note 如果失败，返回""
	*/
	std::wstring as2uc(const char* str);

	/**
	*   @brief 将utf-8编码的字符串转换为ansi编码的字符串。
	*   @param[in] str	utf-8编码的字符串
	*   @retval ansi编码的字符串
	*   @note 如果失败，返回""
	*/
	std::string u82as(const char* str);

	/**
	*   @brief 将ansi编码的字符串转换为utf-8编码的字符串。
	*   @param[in] str	ansi编码的字符串
	*   @retval utf-8编码的字符串
	*   @note 如果失败，返回""
	*/
	std::string as2u8(const char* str);

	/// @fn	unsigned long char2ipv4(const char* ip);
	///
	/// @brief	将IPv4字符串转换为unsigned long.
	///
	/// @author	Xuminrong
	/// @date	2014-8-22
	///
	/// @param	ip	IPv4字符串.
	///
	/// @return	IPv4的unsigned long表示.
	unsigned int a2ipv4(const char* ip);

	/// @fn	std::string dword2ipv4(unsigned long ip);
	///
	/// @brief	将IPv4的unsigned long转换为字符串.
	///
	/// @author	Xuminrong
	/// @date	2014-8-22
	///
	/// @param	ip	IPv4的unsigned long.
	///
	/// @returnIPv4字符串.
	std::string uint2ipv4(unsigned int ip);

	/// @fn	bool replace(std::string& source, const char* old, const char* newStr);
	///
	/// @brief	替换字符串.
	///
	/// @author	Xuminrong
	/// @date	2014-8-25
	///
	/// @param [in,out]	source	要处理的字符串.
	/// @param	old			  	要替换的字符串.
	/// @param	newStr		  	替换后的字符串.
	///
	/// @return	true 成功, false 失败.
	bool replace(std::string& source, const char* old, const char* newStr);

	void toLower(std::string& source);

	void toUpper(std::string& source);

	std::string toLower(const char* source);

	std::string toUpper(const char* source);

	void split(const char* ch, const char* delimiter, std::vector<std::string>& dest);
}


namespace Hi
{
	/// @fn	template<class T> string number2string(T value)
	///
	/// @brief	数字转换成字符串.
	///
	/// @author	Xuminrong
	/// @date	2014-8-22
	///
	/// @exception	FormatException	Thrown when the format of the ? is incorrect.
	///
	/// @typeparam	T	转换前的类型.
	/// @param	value	需要转换的数字.
	///
	/// @return	转换的字符串.
	template<class T>
	std::string n2string(T value)
	{
		std::stringstream oss;
		oss << value;
		if (oss.fail())
		{
			return "";
		}
		return oss.str();
	}
	
	template<size_t N>
	void mem_cpy(char (&dest)[N], const std::string source)
	{
		int len = N > source.size() ? source.size() : N;
		::memcpy(dest, source.c_str(), len);
	}

	template<size_t N, size_t L>
	void mem_cpy_arr(char (&dest)[N], const char (&src)[L])
	{
		int len = N > L ? L : N;
		::memcpy(dest, src, len);
	}
}

/**//** @}*/ // 字符串处理函数