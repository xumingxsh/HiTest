#pragma once

/**
*    @defgroup �ַ���������
*    @brief    ��Ҫ����Ը��ֱ����ַ���֮�����ת����ע�⣺���汾��������Ϊdll�ĵ�������ʹ�ã���Ϊ�õ���string����Ҫ��ָMT����ʱ��dll����
*	 @author  ������
*    @date    2012-07-17
*
* @par �޶���ʷ
*    @version v0.5 \n
*	 @author  ������
*    @date    2012-07-17
*    @li ��ʼ�汾
* @{
*/ 

#include <string>
#include <sstream>
#include <vector>

namespace Hi
{
	/**
	*   @brief ��utf-8������ַ���ת��Ϊunicode������ַ�����
	*   @param[in] str	utf-8������ַ���
	*   @retval unicode������ַ���
	*   @note ���ʧ�ܣ�����""
	*/
	std::wstring u82uc(const char* str);

	/**
	*   @brief ��unicode������ַ���ת��Ϊutf-8������ַ�����
	*   @param[in] str	ansi������ַ���
	*   @retval utf-8������ַ���
	*   @note ���ʧ�ܣ�����""
	*/
	std::string uc2u8(const wchar_t* str);

	/**
	*   @brief ��utf-8������ַ���ת��Ϊunicode������ַ�����
	*   @param[in] str	utf-8������ַ���
	*   @retval unicode������ַ���
	*   @note ���ʧ�ܣ�����""
	*/
	std::string uc2as(const wchar_t* str);

	/**
	*   @brief ��ansi������ַ���ת��Ϊunicode������ַ�����
	*   @param[in] str	ansi������ַ���
	*   @retval unicode������ַ���
	*   @note ���ʧ�ܣ�����""
	*/
	std::wstring as2uc(const char* str);

	/**
	*   @brief ��utf-8������ַ���ת��Ϊansi������ַ�����
	*   @param[in] str	utf-8������ַ���
	*   @retval ansi������ַ���
	*   @note ���ʧ�ܣ�����""
	*/
	std::string u82as(const char* str);

	/**
	*   @brief ��ansi������ַ���ת��Ϊutf-8������ַ�����
	*   @param[in] str	ansi������ַ���
	*   @retval utf-8������ַ���
	*   @note ���ʧ�ܣ�����""
	*/
	std::string as2u8(const char* str);

	/// @fn	unsigned long char2ipv4(const char* ip);
	///
	/// @brief	��IPv4�ַ���ת��Ϊunsigned long.
	///
	/// @author	Xuminrong
	/// @date	2014-8-22
	///
	/// @param	ip	IPv4�ַ���.
	///
	/// @return	IPv4��unsigned long��ʾ.
	unsigned int a2ipv4(const char* ip);

	/// @fn	std::string dword2ipv4(unsigned long ip);
	///
	/// @brief	��IPv4��unsigned longת��Ϊ�ַ���.
	///
	/// @author	Xuminrong
	/// @date	2014-8-22
	///
	/// @param	ip	IPv4��unsigned long.
	///
	/// @returnIPv4�ַ���.
	std::string uint2ipv4(unsigned int ip);

	/// @fn	bool replace(std::string& source, const char* old, const char* newStr);
	///
	/// @brief	�滻�ַ���.
	///
	/// @author	Xuminrong
	/// @date	2014-8-25
	///
	/// @param [in,out]	source	Ҫ������ַ���.
	/// @param	old			  	Ҫ�滻���ַ���.
	/// @param	newStr		  	�滻����ַ���.
	///
	/// @return	true �ɹ�, false ʧ��.
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
	/// @brief	����ת�����ַ���.
	///
	/// @author	Xuminrong
	/// @date	2014-8-22
	///
	/// @exception	FormatException	Thrown when the format of the ? is incorrect.
	///
	/// @typeparam	T	ת��ǰ������.
	/// @param	value	��Ҫת��������.
	///
	/// @return	ת�����ַ���.
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

/**//** @}*/ // �ַ���������