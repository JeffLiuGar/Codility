#pragma once
class myString {
private:
	char *m_pString;
public:
	myString();	

	myString(const char *pdata = NULL);	

	myString(const myString &other);

	void printString();

	friend myString & operator + (const myString & left,const myString & right);

	myString & operator=(const myString &other);
	~myString();

}; 