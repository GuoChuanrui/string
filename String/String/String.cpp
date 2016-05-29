#include<iostream>
using namespace std;

class String
{
public:
	String(const char* str = "")
		:_str(new char[strlen(str)+1])
	{
		strcpy(_str,str);
	}

	String(const String & s)
		:_str(new char[strlen(s._str) + 1])
	{
		strcpy(_str, s._str);
	}


	/*String(const String& s)    //tmp 调用构造函数，函数调用之后就释放了，后面析构时崩溃，感觉是没给this开辟空间
	{
		String tmp(s._str);
		swap(_str,tmp._str);
	}*/

	~String()
	{
		if(_str)
		{
			delete[] _str;
			_str = NULL;
		}
	}

	String& operator= (const String& s)
	{
		if(this != &s)
		{
			delete[] _str;
			_str = new char[strlen(s._str)+1];
			strcpy(_str,s._str);
			return *this;
		}
	}


	//运算符重载
	bool operator>(const String& s)
	{
		int i = 0;
		while(_str[i] && s._str[i] && (_str[i] == s._str[i]))
		{
			++i;
		}
		if((_str[i] - s._str[i])> 0)
			return true;
		return false;
	}

	bool operator>= (const String& s)
	{
		return (*this > s) || (*this == s);
	}

	bool operator< (const String& s)
	{
		return !(*this >= s);
	}
	bool operator<= (const String& s)
	{
		return !(*this > s);
	}

	bool operator== (const String& s)
	{
		int i = 0;
		while(_str[i] && s._str[i] && (_str[i] == s._str[i]))
		{
			++i;
		}
		if((_str[i] - s._str[i]) == 0)
			return true;
		return false;
	}

private:
	char* _str;
};


void Test1()
{
	String s1("hello");
	String s2(s1);
	String s3("hello");
	cout<<(s1<=s2)<<endl;
}
int main()
{
	Test1();
	return 0;
}