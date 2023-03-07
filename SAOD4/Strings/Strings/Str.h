#pragma once
using namespace std;
class Str
{
	char* m_pszText;
public:
	Str(const char *p)
	{
		if (p)
		{
			m_pszText = new char[strlen(p) + 1];
			strcpy_s(m_pszText, strlen(p) + 1, p);
		}
		else
		{
			m_pszText = new char[1] {0};
		}
	}

	Str(const Str& s)
	{
		m_pszText = new char[strlen(s.m_pszText) + 1];
		strcpy_s(m_pszText, strlen(s.m_pszText) + 1, s.m_pszText);
	}

	~Str()
	{
		delete[]m_pszText;
	}

	operator const char* ()const { return m_pszText; }

	const Str& operator =(const Str& s)
	{
		if (&s == this) return *this;
		delete[] m_pszText;
		
		m_pszText = new char[strlen(s.m_pszText) + 1];
		strcpy_s(m_pszText, strlen(s.m_pszText) + 1, s.m_pszText);
		return *this;
	}

	Str& operator +=(const char* sz)
	{
		// 1) Создаём временный массив, в который скопируем первую и вторую "строки".
		// 2) Чистим текущий, суем в него временный.
		// 3) Чистим временный.
		// 4) Возвращаем результат.
		 
		// 1)
		const int iniSum = strlen(m_pszText) + strlen(sz) + 1;
		char* tempSum = new char[iniSum];
		tempSum[iniSum - 1] = '\0';
		for (int i = 0; i < strlen(m_pszText); i++)
		{
			tempSum[i] = m_pszText[i];
		}
		for (int i = strlen(m_pszText), start = 0; i < strlen(sz) + strlen(m_pszText); i++, start++)
		{
			tempSum[i] = sz[start];
		}
		// 2)
		delete[] m_pszText;
		m_pszText = new char[strlen(tempSum) + 1];
		strcpy_s(m_pszText, strlen(tempSum) + 1, tempSum);
		// 3)
		delete[] tempSum;
		// 4)
		return *this;
	};

	Str operator +(const char* sz)const
	{
		const int iniSum = strlen(m_pszText) + strlen(sz) + 1;
		char* tempSum = new char[iniSum];
		tempSum[iniSum - 1] = '\0';
		for (int i = 0; i < strlen(m_pszText); i++)
		{
			tempSum[i] = m_pszText[i];
		}
		for (int i = strlen(m_pszText), start = 0; i < strlen(sz) + strlen(m_pszText); i++, start++)
		{
			tempSum[i] = sz[start];
		}

		Str result(tempSum);

		delete[] tempSum;

		return result;
	}
};

