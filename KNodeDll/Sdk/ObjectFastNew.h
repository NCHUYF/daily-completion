//*****************************************************
//    
//    @copyright      �����ά�����
//    @version        v4.0
//    @file           ObjectFastNew.H
//    @author         fanHong
//    @date           2017/11/3 11:18
//    @brief          ��ʱ�������
//
//*****************************************************

#pragma once
#include <atlcoll.h>

namespace CommBase
{
	/*
	*	��ʱ����������ھ������ٴ������ͷŵĶ��������֧�ֶ��߳�
	*/
	template<class T>
	class CObjectFastNew
	{
	public:
		CObjectFastNew(size_t bufferObjectCount = 32)
		{
			_bufferCount = bufferObjectCount;
			_recycleList.SetCount(0, int(_bufferCount));
		}

		~CObjectFastNew()
		{
			clear();
		}

		void clear()
		{
			for (size_t i = 0; i < _recycleList.GetCount(); i++)
				delete _recycleList[i];
			_recycleList.RemoveAll();
		}

		// ��ȡһ���¶�����������������ǰ�ù���
		T* getnew()
		{
			// ���ɿյĶԿս�ȥ
			if (!_recycleList.GetCount())
			{
				for (size_t i = 0; i < _bufferCount; i++)
				{
					_recycleList.Add(new T());
				}
			}

			// ȡ�����һ��
			int getIndex = int(_recycleList.GetCount() - 1);
			T* newobj = _recycleList[getIndex];
			_recycleList.RemoveAt(getIndex);
			return newobj;
		}

		// ���ն���
		void recycle(T* object)
		{
			if (_recycleList.GetCount() >= _bufferCount)
				delete object;
			else
				_recycleList.Add(object);
		}

	protected:
		CAtlArray<T*>	_recycleList;
		size_t			_bufferCount;
	};
}