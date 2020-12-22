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

	SmartPtr(const SmartPtr &ptr) //��������
	{
		if (this != &ptr)
		{
			this->_ptr = ptr._ptr;
			this->_count = ptr._count;
			(*this->_count)++;
		}
	}

	SmartPtr &operator=(const SmartPtr &ptr) //��ֵ���������
	{
		if (this->_ptr == ptr._ptr)
		{
			return *this;
		}
		if (this->_ptr)//��ֵʱ���Ⱥ���ߵ��Լ�
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
		(*this->_count)++;//��ֵʱ���Ⱥ��ұߵ�����
		return *this;
	}

	T &operator*()//���ؽ����������
	{
		if (this->_ptr == nullptr) assert(this->_ptr == nullptr);//��ά��ָ��Ϊ��ʱ����
		return *(this->_ptr);
	}

	T *operator->()//���ؼ�ͷ�����
	{
		if(this->_ptr==nullptr) assert(this->_ptr == nullptr);//��ά��ָ��Ϊ��ʱ����
		return this->_ptr;
	}

	size_t use_count()
	{
		return *this->count;
	}

private: T *_ptr;//ά����ָ��
		 size_t *_count;//���ü���
};