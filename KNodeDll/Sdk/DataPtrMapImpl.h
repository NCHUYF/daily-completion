////*****************************************************
////    
////    @copyright      �����ά�����
////    @version        v4.0
////    @file           ObjectFastNew.H
////    @author         fanHong
////    @date           2017/11/3 11:18
////    @brief          ���ļ��������ṩ����ӳ��Ĺ��ܣ�ʵ�ֺϲ���ͬ���ݵĴ洢�����ʣ�����
////					  �ڴ����ġ� ֧�ֶ��߳�
////
////*****************************************************
//
//#pragma once
//
//#include "CriticalSection.h"
//
//namespace CommBase
//{
//	//! ����ӳ�书��ʵ��ģ����
//	template <class T, class SrcDataImpl, class MapDataImpl = SrcDataImpl>
//	class CDataPtrMapImpl
//	{
//	public:
//		/** ��������ָ������ */
//		typedef SrcDataImpl* SrcDataPtr;
//		typedef MapDataImpl* MapDataPtr;
//		typedef CDataPtrMapImpl<T, SrcDataImpl, MapDataImpl> ThisDefines;
//
//		/** ����ֻ�����ʾ����4���ֽڣ� */
//		class ATL_NO_VTABLE RHandle
//		{
//		public:
//			RHandle(void)
//			{
//				_DataVal = NULL;
//			}
//
//			RHandle(MapDataPtr val)
//			{
//				_DataVal = val;
//			}
//
//			// ��ֵ
//			RHandle& operator=(const RHandle& pszSrc)
//			{
//				_DataVal = pszSrc._DataVal;
//				return *this;
//			}
//
//			// �Ƚ�
//			bool operator==(const RHandle& pszSrc) const
//			{
//				return _DataVal == pszSrc._DataVal;
//			}
//
//			__inline const MapDataImpl& operator*() const _THROW0()
//			{
//				return (*get());
//			}
//
//			__inline const MapDataPtr operator->() const _THROW0()
//			{
//				return (get());
//			}
//
//			// ȡ��ֵ
//			__inline const MapDataPtr get(void) const
//			{
//				return _DataVal;
//			}
//
//		protected:
//			MapDataPtr		_DataVal;
//		};
//
//		/** �����д�ķ��ʾ����8���ֽڣ� */
//		class ATL_NO_VTABLE RWHandle : public RHandle
//		{
//		public:
//			RWHandle(void)
//			{
//				_DataMap = NULL;
//			}
//
//			RWHandle(ThisDefines* map, MapDataPtr val)
//				: RHandle(val)
//			{
//				_DataMap = map;
//			}
//
//			RWHandle(RWHandle& pszSrc)
//			{
//				operator = (pszSrc);
//			}
//
//			// ��ֵ
//			RWHandle& operator = (const RWHandle& pszSrc)
//			{
//				_DataVal = pszSrc._DataVal;
//				_DataMap = pszSrc._DataMap;
//				return *this;
//			}
//
//			// �Ƚ�
//			bool operator == (const RWHandle& pszSrc)
//			{
//				return _DataVal == pszSrc._DataVal && _DataMap == pszSrc._DataMap;
//			}
//
//			// ����ֵ
//			__inline void set(SrcDataImpl srcData)
//			{
//				set(&srcData);
//			}
//
//			__inline void set(const SrcDataPtr srcData)
//			{
//				(*(RHandle*)this) = _DataMap->MapData(srcData);
//			}
//
//		protected:
//			ThisDefines*	_DataMap;
//		};
//
//		/**
//		* �Ƚ�ԭʼ������ӳ�������Ƿ���ȣ��������ش˺���
//		* @param [in] srcData	ԭʼ����
//		* @param [in] mapData	ӳ������
//		* @return ����ԭʼ������ӳ�������Ƿ����
//		* - true ��ȣ� false �����
//		*/
//		bool DataEquap(const SrcDataPtr srcData, const MapDataPtr mapData);
//		/**
//		* ����ԭʼ���ݵ�ӳ�����ݣ��������ش˺���
//		* @param [in] srcData	ԭʼ����
//		* @param [in] mapData	ӳ������
//		*/
//		void CopyToMap(const SrcDataPtr srcData, MapDataPtr mapData);
//		/**
//		* ����ӳ�����ݣ������أ�
//		* @param [in] srcData	ԭʼ����
//		* @return ����ӳ�����ݶ���
//		*/
//		MapDataPtr AllocMapData(const SrcDataPtr srcData);
//		/**
//		* �ͷ�ӳ�����ݣ������أ�
//		* @param [in] mapData	ӳ������
//		*/
//		void FreeMapData(const SrcDataPtr mapData);
//		/**
//		* ɾ�����й�������
//		*/
//		virtual ~CDataPtrMapImpl(void);
//		/**
//		* ɾ����������
//		*/
//		void DeleteAll(void);
//		/**
//		* ������ݣ���������Ѵ��ڣ��򷵻��Ѵ��ڵľ��
//		*/
//		__inline RHandle MapData(SrcDataImpl srcData, bool CancelEqual = false)
//		{
//			return MapData(&srcData, CancelEqual);
//		}
//		/**
//		* ������ݣ���������Ѵ��ڣ��򷵻��Ѵ��ڵľ��
//		*/
//		RHandle MapData(const SrcDataPtr srcData, bool CancelEqual = false);
//		/**
//		* ��ֻ�����ת���ɿ�д���
//		* @param [in] handle	ֻ�����
//		* @return ����ת����Ŀ�д���
//		*/
//		RWHandle R2RWHandle(RHandle handle);
//		/**
//		* ȡ����������
//		*/
//		size_t GetDataCount(void);
//		/**
//		* ȡ������ MapID
//		* @param [in] handle	ֻ�����
//		* @return �������� MapID
//		* - û�ҵ����� -1
//		*/
//		int GetHandleId(RHandle handle);
//		/**
//		* ���� MapID ���ؾ��
//		* @param [in] id	���� MapID
//		* @return �������ݾ��
//		*/
//		RHandle GetHandleOfId(int id);
//
//	protected:
//		CAtlArray<MapDataPtr>	_MapArray;
//		CCriticalSectionHandle	_DataMutex;
//	};
//
//
//
//	template <class T, class SrcDataImpl, class MapDataImpl>
//	bool CDataPtrMapImpl<T, SrcDataImpl, MapDataImpl>::DataEquap(const SrcDataPtr srcData, const MapDataPtr mapData)
//	{
//		// �������ش˺���
//		//ATLASSERT(FALSE);
//		return false;
//	}
//
//	template <class T, class SrcDataImpl, class MapDataImpl>
//	void CDataPtrMapImpl<T, SrcDataImpl, MapDataImpl>::CopyToMap(const SrcDataPtr srcData, MapDataPtr mapData)
//	{
//		// �������ش˺���
//		//ATLASSERT(FALSE);
//	}
//
//	template <class T, class SrcDataImpl, class MapDataImpl>
//	typename CDataPtrMapImpl<T, SrcDataImpl, MapDataImpl>::MapDataPtr CDataPtrMapImpl<T, SrcDataImpl, MapDataImpl>::AllocMapData(const SrcDataPtr srcData)
//	{
//		// Ĭ�ϴ����޲ε�����
//		return new MapDataImpl;
//	}
//
//	template <class T, class SrcDataImpl, class MapDataImpl>
//	void CDataPtrMapImpl<T, SrcDataImpl, MapDataImpl>::FreeMapData(const SrcDataPtr mapData)
//	{
//		delete mapData;
//	}
//
//	template <class T, class SrcDataImpl, class MapDataImpl>
//	CDataPtrMapImpl<T, SrcDataImpl, MapDataImpl>::~CDataPtrMapImpl(void)
//	{
//		DeleteAll();
//	}
//
//	template <class T, class SrcDataImpl, class MapDataImpl>
//	void CDataPtrMapImpl<T, SrcDataImpl, MapDataImpl>::DeleteAll(void)
//	{
//		T* pT = static_cast<T*>(this);
//
//		for (size_t i = 0; i < _MapArray.GetCount(); i++)
//		{
//			pT->FreeMapData(_MapArray[i]);
//		}
//
//		_MapArray.RemoveAll();
//	}
//
//	template <class T, class SrcDataImpl, class MapDataImpl>
//	typename CDataPtrMapImpl<T, SrcDataImpl, MapDataImpl>::RHandle CDataPtrMapImpl<T, SrcDataImpl, MapDataImpl>::MapData(const SrcDataPtr srcData, bool CancelEqual = false)
//	{
//		try
//		{
//			CCriticalSectionSync mutex(_DataMutex);
//
//			T* pT = static_cast<T*>(this);
//
//			if (!CancelEqual)
//			{
//				// ѭ����ǰӳ�����ݣ������Ƿ������ȵ�ֵ
//				for (size_t i = 0; i < _MapArray.GetCount(); i++)
//				{
//					if (pT->DataEquap(srcData, _MapArray[i]))
//					{
//						return RHandle(_MapArray[i]);
//					}
//				}
//			}
//
//			// ����������ѭ��û���ҵ���ͬ��ֵ�������Ӵ�ֵ
//			MapDataPtr newMap = pT->AllocMapData(srcData);
//			ATLASSERT(newMap);
//
//			// �������ݲ���ӵ�����
//			pT->CopyToMap(srcData, newMap);
//			_MapArray.Add(newMap);
//
//			return RHandle(newMap);
//		}
//		catch (...)
//		{
//			//::MessageBox (::GetActiveWindow (), _T("���ش�����رչ��̡�"), _T("MapData"), MB_ICONERROR);
//		}
//		return RHandle(NULL);
//	}
//
//	template <class T, class SrcDataImpl, class MapDataImpl>
//	typename CDataPtrMapImpl<T, SrcDataImpl, MapDataImpl>::RWHandle CDataPtrMapImpl<T, SrcDataImpl, MapDataImpl>::R2RWHandle(RHandle handle)
//	{
//		T* pT = static_cast<T*>(this);
//		return RWHandle(pT, handle.get());
//	}
//
//	template <class T, class SrcDataImpl, class MapDataImpl>
//	size_t CDataPtrMapImpl<T, SrcDataImpl, MapDataImpl>::GetDataCount(void)
//	{
//		CCriticalSectionSync mutex(_DataMutex);
//		return _MapArray.GetCount();
//	}
//
//	template <class T, class SrcDataImpl, class MapDataImpl>
//	int CDataPtrMapImpl<T, SrcDataImpl, MapDataImpl>::GetHandleId(RHandle handle)
//	{
//		CCriticalSectionSync mutex(_DataMutex);
//
//		T* pT = static_cast<T*>(this);
//
//		// ѭ����ǰӳ�����ݣ������Ƿ������ȵ�ֵ
//		for (size_t i = 0; i < _MapArray.GetCount(); i++)
//		{
//			if (pT->DataEquap(handle.get(), _MapArray[i]))
//			{
//				return (int)i;
//			}
//		}
//
//		return -1;
//	}
//
//	template <class T, class SrcDataImpl, class MapDataImpl>
//	typename CDataPtrMapImpl<T, SrcDataImpl, MapDataImpl>::RHandle CDataPtrMapImpl<T, SrcDataImpl, MapDataImpl>::GetHandleOfId(int id)
//	{
//		CCriticalSectionSync mutex(_DataMutex);
//
//		ATLASSERT(id >= 0 && id < (int)_MapArray.GetCount());
//		if (id < 0 || id >= (int)_MapArray.GetCount())
//			return RHandle();
//
//		return RHandle(_MapArray[id]);
//	}
//
//	//! �ַ���Ӱ����� */
//	class COMMBASE_API CStringShareControl : public CDataPtrMapImpl <CStringShareControl, CString>
//	{
//	public:
//		/**
//		* �Ƚ�ԭʼ������Ӱ�������Ƿ����
//		* @param [in] srcData	ԭʼ����
//		* @param [in] mapData	ӳ������
//		* @return ����ԭʼ������ӳ�������Ƿ����
//		* - true ��ȣ� false �����
//		*/
//		bool DataEquap(const SrcDataPtr srcData, const MapDataPtr mapData);
//
//		/**
//		* ����ԭʼ���ݵ�ӳ������
//		* @param [in] srcData	ԭʼ����
//		* @param [in] mapData	ӳ������
//		*/
//		void CopyToMap(const SrcDataPtr srcData, MapDataPtr mapData);
//	};
//
//	/** ����CShareString���� */
//	typedef CStringShareControl::RWHandle CShareString;
//	/** ����CShareStringR���� */
//	typedef CStringShareControl::RHandle CShareStringR;
//
//	/** ���幤�����ַ���ֵ����ת�� */
//	ULONGLONG ShareString2ULong(CShareString ws);
//	CShareString ULong2ShareString(ULONGLONG ul);
//	ULONG ShareString2ULong(CShareStringR ws);
//	CShareStringR ULong2ShareString(ULONG ul);
//}