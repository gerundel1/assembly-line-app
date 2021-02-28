// Name: German Malikov
// Seneca Student ID: 130968191
// Seneca email: gmalikov@myseneca.ca
// Date of completion: 2020-11-10
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#include "Utilities.h"
	void Utilities::setFieldWidth(size_t newWidth)
	{
		m_widthField = newWidth;
		
	}
	size_t Utilities::getFieldWidth() const
	{
		return size_t(m_widthField);
	}
	std::string Utilities::extractToken(const std::string& str, size_t& next_pos, bool& more)
	{
		bool isNext = true;
		size_t last_pos = str.find(m_delimiter, next_pos);
		std::string temp;
		if (last_pos - next_pos == 0) {
			throw "The token is empty!";
		}
		if (last_pos == std::string::npos) {
			temp = str.substr(next_pos);
			isNext = false;
		}
		else
			temp = str.substr(next_pos, last_pos - next_pos);
		next_pos = ++last_pos;
		if (more && m_widthField < temp.length())
			m_widthField = temp.length();
		more = isNext;
		return temp;
	}
	void Utilities::setDelimiter(char newDelimiter)
	{
		m_delimiter = newDelimiter;
	}
	char Utilities::getDelimiter()
	{
		return m_delimiter;
	}

	char Utilities::m_delimiter = ',';