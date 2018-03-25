#include "stdafx.h"
#include <iostream> 
#include "myString.h"
#define MAX_PATH 256
using namespace std;



myString::myString()
	{
		/*m_size = MAX_PATH;
		m_pString = new char[size];
		if (m_pString)
			memset(m_pString, 0, size);*/
		m_pString = new char[1];
		m_pString[0] = '\0';

		cout << "default constructor" << endl;

	}

myString::myString(const char *pdata )
{
		//m_size = MAX_PATH;
	cout << "constructor with char *" << pdata << endl;
	if (NULL != pdata)
	{
		int newsize = strlen(pdata) + 1;
		m_pString = new char[newsize];
		if (m_pString)
			memcpy(m_pString, pdata, newsize);

	}
	else
	{
		m_pString = new char[1];
		m_pString[0] = '\0';

		cout << "constructor" << endl;
	}
	
		
}

myString::myString(const myString &other)
{
	cout << "copy constructor" << endl;
	if (other.m_pString)
	{
		int size = strlen(other.m_pString) + 1;
		if (m_pString)
			delete[]m_pString;
		m_pString = new char[size];
		if (m_pString)
			strcpy(m_pString, other.m_pString);

	}
	else
	{
		if (m_pString)
			delete[]m_pString;
		m_pString = NULL;
	}
		
}

myString & myString::operator = (const myString &other)
{
	cout << "operator =" << endl;
	if (this == &other)
	{
		return *this;
	}
	if (other.m_pString)
	{
		int size = strlen(other.m_pString) + 1;
		if (m_pString)
			delete[]m_pString;
		m_pString = new char[size];
		if (m_pString)
			strcpy(m_pString, other.m_pString);

	}
	else
	{
		if (m_pString)
			delete[]m_pString;
		m_pString = NULL;
	}
	return *this;
}
void myString::printString()
{
	cout << "prtint string: " <<m_pString<< endl;
}
myString::~myString()
	{
		if (m_pString)
		{
			delete[]m_pString;
			m_pString = NULL;
		}
			
	}

myString & operator + (const myString & left, const myString & right)
{
	
	char *buff = new char[strlen(left.m_pString) + strlen(right.m_pString) + 1];
	strcpy(buff, left.m_pString);
	strcat(buff, right.m_pString);
	myString * pstr = new myString(buff);
	delete[] buff;

	return *pstr;
}

