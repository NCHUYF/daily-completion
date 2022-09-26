//////////////////////////////////////////////////////////////////////
// �ļ����ƣ�List.h
// ����������ͨ��˳���б��࣬�̳���CSimpleArray
// ������ʶ��zengjiangyou	2018.05.17
// �޸ı�ʶ��
// �޸�������
// �ļ���Ȩ��������΢�¼������޹�˾
//////////////////////////////////////////////////////////////////////
#pragma once

class CStringElementTraitsEx :public CElementTraits<CString>
{
public:
	static ULONG Hash(_In_ const CString& element) throw()
	{
		ULONG nHash = 0;
		LPCTSTR pch = element;
		while (*pch != 0)
		{
			nHash = (nHash << 5) + nHash + (*pch);
			pch++;
		}

		return(nHash);
	}
};

namespace toolkit
{
	namespace data
	{
		/** @addtogroup Toolkit
		* @{
		*/
		//! ͨ��˳���б�ģ����
		template<class T>
		class CBwList : public CSimpleArray<T>
		{
		public:
			/**
			* �ȽϺ���ָ��ص�����
			* @param [in] src CBwList�б�
			*/
			typedef bool (*COMPARE)(T pNodeA, T pNodeB, PVOID field);

			CBwList(){}

			/**
			* ����������
			* @param [in] src CBwList�б�
			*/
			CBwList(const CBwList<T> &src):CSimpleArray(src){}

			/**
			* ����������(����CSimpleArray)
			* @param [in] src CSimpleArray�б�
			*/
			CBwList(const CSimpleArray<T>& src):CSimpleArray(src){}

			/**
			* ����������(����CAtlArray)
			* @param [in] src CAtlArray�б�
			*/
			CBwList(const CAtlArray<T>& src)
			{
				Changelist(src);
			}

			/**
			* ��ֵ����
			* @param [in] src ����������BwList��Ҳ������CSimpleArray
			*/
			CBwList<T>& operator=(const CSimpleArray<T>& src)
			{
				__super::operator = (src);
				return *this;
			}

			/**
			* ��ֵ����������CAtlArray��
			* @param [in] src CAtlArray�б�
			*/
			CBwList<T>& operator=(const CAtlArray<T>& src)
			{
				Changelist(src);
				return *this;
			}

			/**
			* ��ȡ����
			* @return ����
			*/
			inline int GetCount(void) const
			{
				return this->GetSize();
			}

			/**
			* ��ȡָ����������Ŀ����
			* @param [in] index ����
			* @return ��Ŀ����(��֧���޸�)
			*/
			inline const T& GetAt(int index) const
			{
				return __super::operator [](index);
			}

			/**
			* ����б�
			* @param [in] list	�б�
			*/
			void AddList(const CBwList<T> &list)
			{
				int intCount = list.GetCount();
				for (int i = 0; i < intCount; i++)
				{
					this->Add(list.GetAt(i));
				}
			}

			/**
			* ��ָ���������²���һ��ֵ
			* @param [in] nIndex ����
			* @param [in] t	ֵ
			* @return 
			*/
			BOOL InsertAt( int nIndex, const T& t )
			{
				if ( nIndex < 0 )
					return FALSE;

				if ( nIndex >= m_nSize )
					return ( Add( t ) != -1 );

				if ( m_nSize == m_nAllocSize )
				{
					int nNewAllocSize = ( m_nAllocSize == 0 ) ? 1 : ( m_nSize * 2 );
					T* aT = static_cast<T*>(realloc( m_aT, nNewAllocSize * sizeof( T ) ));
					if ( aT == NULL )
						return FALSE;
					m_nAllocSize = nNewAllocSize;
					m_aT = aT;
				}
				MoveMemory( (LPVOID)( m_aT + nIndex + 1 ), (LPVOID)( m_aT + nIndex ), ( m_nSize - nIndex ) * sizeof( T ) );
				InternalSetAtIndex( nIndex, t );
				m_nSize++;
				return TRUE;
			}

			/**
			* ɾ���б���ָ�루��T����ָ������ʱ���˷����Ĺ��ܵ�ͬ��RemoveAll��
			*/
			void DeleteAll()
			{
				int count = GetCount();
				if (count == 0)
					return;

				//��ȡT������,������һ���ַ�Ϊ*����TΪָ��(���磺int *)
				CString TType = typeid(T).name();				
				if (TType.Right(1) == L"*")
				{
					for (int i = 0; i < count; i++)
					{
						T t = GetAt(i);
						delete t ;
						t = NULL;
					}
				}				
				RemoveAll();
			}			


			/**
			* ������
			* @param [in] compareFun ����ȽϺ���
			* @param [in] field ��չ����
			*/
			void Sort(COMPARE compareFun = DefaultLessCompare, PVOID field = NULL)
			{
				if (GetSize() > 0)
				{
					SortOfMid(compareFun, 0, GetSize() - 1, field);
				}
			}

		private:

			/**
			* Ĭ��С�ڱȽ�
			* @param [in] left		�Ƚ����ֵ
			* @param [in] right	�Ƚ��ұ�ֵ
			* @param [in] field	��չ�ֶ�
			* @return �Ƿ�С��
			*/
			static bool DefaultLessCompare(T left, T right, PVOID field = NULL) 
			{
				return left < right;
			}

			/**
			* ����
			* @param [in] compareFun	�ȽϺ���
			* @param [in] left	        �Ƚ����ֵ
			* @param [in] right	    �Ƚ��ұ�ֵ
			*/
			void SortOfMid(COMPARE compareFun, int left, int right, PVOID field)
			{
				int l_hold = left;
				int r_hold = right;

				T pivot = __super::operator [](left);

				while (left < right)
				{
					T rightvalue = __super::operator [](right);
					T leftvalue = __super::operator [](left);

					while (!compareFun(rightvalue, pivot, field) && (left < right))
					{
						right --;
						rightvalue = __super::operator [](right);
					}

					if (left != right)
					{
						__super::operator [](left) = __super::operator [](right);
						left ++;
						leftvalue = __super::operator [](left);
					}

					while (compareFun(leftvalue, pivot, field) && (left < right))
					{
						left ++;
						leftvalue = __super::operator [](left);
					}

					if (left != right)
					{
						__super::operator [](right) = __super::operator [](left);
						right--;
						rightvalue = __super::operator [](right);
					}
				}

				__super::operator [](left) = pivot;

				int cur = left;
				left = l_hold;
				right = r_hold;

				if (left < cur)
					SortOfMid (compareFun, left, cur - 1, field);
				if (right > cur)
					SortOfMid (compareFun, cur + 1, right, field);
			}

			/**
			* �б�ת��
			* @param [in] src CAtlArray�б�
			*/
			void Changelist(const CAtlArray<T> &src)
			{
				this->RemoveAll();
				for (size_t i = 0; i < src.GetCount(); i++)
				{
					this->Add(src.GetAt(i));
				}
			}
		};/** * @} */
	}
}