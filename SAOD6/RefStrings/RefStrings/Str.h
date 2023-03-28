#pragma once
#include "_str.h"
#include <stdexcept>

class Str {
	_str* m_pStr;
public:
	Str() { m_pStr = new _str; }		//если не копия, то создаем
	Str(const char* p) {		// новый ресурс
		m_pStr = new _str(p);
	}
	~Str() {
		m_pStr->Release(); 	// Не уничтожаем ресурс!
	}				// Уменьшаем счетчик ссылок!

	Str(const Str& s)
	{
		m_pStr = s.m_pStr; 	// ссылаемся на тот же ресурс
		m_pStr->AddRef(); 	// отмечаем, что сослались
	}

	Str& operator = (const Str& s) {
		if (this != &s) {
			s.m_pStr->AddRef(); // Важен порядок?!
			m_pStr->Release();
			m_pStr = s.m_pStr;
		}
		return *this;
	}

	Str& operator += (const Str& s) {
		int length = len() + s.len();
		if (s.len() != 0) {		// добавление ничего не изменит!
			_str* pstrTmp = new _str; 	// Новый ресурс
			delete[] pstrTmp->m_pszData;

			pstrTmp->m_pszData = new char[length + 1];
			strcpy_s(pstrTmp->m_pszData, length + 1, m_pStr->m_pszData);
			strcat_s(pstrTmp->m_pszData, length + 1, s.m_pStr->m_pszData);

			m_pStr->Release();
			m_pStr = pstrTmp;
		}
		return *this;
	}

	operator const char* ()const { return m_pStr->m_pszData; }

	char operator [](int i)const
	{
		if (i < 0 or i >= len())
		{
			throw out_of_range("Index out of range");
		}
		return m_pStr->m_pszData[i];
	}

	char& operator [](int i)
	{
		if (i < 0 or i >= len())
		{
			throw out_of_range("Index out of range");
		}
		int length = len();
		if (len() != 0) {		// добавление ничего не изменит!
			_str* pstrTmp = new _str; 	// Новый ресурс
			delete[] pstrTmp->m_pszData;

			pstrTmp->m_pszData = new char[length + 1];
			strcpy_s(pstrTmp->m_pszData, length + 1, m_pStr->m_pszData);

			m_pStr->Release();
			m_pStr = pstrTmp;
		}
		return m_pStr->m_pszData[i];

	}

	int len() const {
		return strlen(m_pStr->m_pszData);
	}
};