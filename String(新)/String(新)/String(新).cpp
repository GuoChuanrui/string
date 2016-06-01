#include<iostream>
#include<assert.h>
using namespace std;

class String
{
public:
	String(const char* str = "")
	{
		int len = strlen(str);
		_capacity = len+1;
		_size = len;
		_str = new char[_capacity];
		strcpy(_str,str);
	}

	String(const String& s)
		:_str(NULL)
	{
		String tmp(s._str);
		this->_Swap(tmp);
	}

	~String()
	{
		if(_str)
		{
			delete[] _str;
			_str = NULL;
		}
	}

	String& operator= (String s)
	{
		_Swap(s);
		return *this;
	}


	//插入
	void Insert(size_t pos,char ch)
	{
		assert(pos <= _size);
		_CheckCapacity(_size+2);
		size_t end = _size;
		while(end >= pos)
		{
			_str[end+1] = _str[end];
			--end;
		}
		_str[pos] = ch;
		++_size;
	}

	void Insert(size_t pos,const char* str)
	{
		assert(pos <= _size);
		size_t strSize = strlen(str);
		_CheckCapacity(_size+1+strSize);
		size_t end = _size;
		//挪动数据
		while(end >= pos)
		{
			_str[end+strSize] = _str[end];
			--end;
		}
		//插入字符串
		while(*str)
		{
			_str[pos++] = *str++;
		}
		_size += strSize;
	}


	//尾插
	void PushBack(char ch)
	{
		Insert(_size,ch);
	}

	//查找
	int Find(char ch)
	{
		char* str = _str;
		int begin = 0;
		while(str[begin])
		{
			if(str[begin] == ch)
			{
				return begin;
			}
			++begin;
		}
		return -1;
	}

	int Find(const char* src)
	{
		char* str = _str;
		int begin = 0;
		int cur = 0;
		int str_len = strlen(str);
		int src_len = strlen(src);
		for(begin = 0;begin < str_len;begin++)
		{
			for(cur = 0;cur < src_len;cur++)
			{
				if(str[cur+begin] != src[cur])
				{
					break;
				}
			}
			if(cur >= src_len)
			{
				return begin;
			}
		}	
		return -1;
	}

	void Erase(size_t pos)
	{
		assert(pos < _size-1);
		size_t end = pos+1;
		while(end <= _size)
		{
			_str[end-1] = _str[end];
			end++;
		}
		_size --;
	}

	void Erase(size_t pos ,size_t n)
	{
		assert(pos < _size-1);
		size_t end = pos+1;
		while(end <= _size)
		{
			_str[end-1] = _str[end+n];
			end++;
		}
		_size -= n;

	}


private:
	void _Swap(String& s)
	{
		swap(_str,s._str);
		swap(_size,s._size);
		swap(_capacity,s._capacity);
	}
	
	void _CheckCapacity(size_t size)    //检查容量并扩容
	{
		if(size > _capacity)
		{
			int newCapacity = size > 2*_capacity?size:2*_capacity;
			_str = (char*)realloc(_str,newCapacity);
			_capacity = newCapacity;
		}
	}

private:
	char* _str;
	size_t _size;
	size_t _capacity;
};


void Test1()
{
	String s1("hello world");
	String s2;
	//s1.Insert(6,"world");
	//cout<<s1.Find("wor")<<endl;

	s1.Erase(5,2);
}
int main()
{
	Test1();
	return 0;
}