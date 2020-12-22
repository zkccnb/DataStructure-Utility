#include <iostream>
#include <memory>
#include<assert.h>

template <typename T>
class SmartPtr
{
public:
	SmartPtr(T *ptr = nullptr) : _ptr(ptr)
	{
		if (_ptr)
		{
			_count = new size_t(1);
		}
		else
		{
			_count = new size_t(0);
		}
	}

	~SmartPtr()
	{
		(*this->_count)--;
		if (*this->_count == 0)
		{
			delete this->_ptr;
			delete this->_count;
		}
	}

	SmartPtr(const SmartPtr &ptr) //拷贝构造
	{
		if (this != &ptr)
		{
			this->_ptr = ptr._ptr;
			this->_count = ptr._count;
			(*this->_count)++;
		}
	}

	SmartPtr &operator=(const SmartPtr &ptr) //赋值运算符重载
	{
		if (this->_ptr == ptr._ptr)
		{
			return *this;
		}
		if (this->_ptr)//赋值时，等号左边的自减
		{
			(*this->_count)--;
			if (this->_count == 0)
			{
				delete this->_ptr;
				delete this->_count;
			}
		}
		this->_ptr = ptr._ptr;
		this->_count = ptr._count;
		(*this->_count)++;//赋值时，等号右边的自增
		return *this;
	}

	T &operator*()//重载解引用运算符
	{
		if (this->_ptr == nullptr) assert(this->_ptr == nullptr);//当维护指针为空时报错
		return *(this->_ptr);
	}

	T *operator->()//重载箭头运算符
	{
		if(this->_ptr==nullptr) assert(this->_ptr == nullptr);//当维护指针为空时报错
		return this->_ptr;
	}

	size_t use_count()
	{
		return *this->count;
	}

private: T *_ptr;//维护的指针
		 size_t *_count;//引用计数
};