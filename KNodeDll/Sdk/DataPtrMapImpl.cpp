#include "StdAfx.h"
//#include "Sdk/DataPtrmapImpl.h"
//
//namespace CommBase
//{
//	/** �Ƚ�ԭʼ������Ӱ�������Ƿ���� */
//	bool CStringShareControl::DataEquap(const SrcDataPtr srcData, const MapDataPtr mapData)
//	{
//		return *srcData == *mapData;
//	}
//
//	/** ����ԭʼ���ݵ�ӳ������ */
//	void CStringShareControl::CopyToMap(const SrcDataPtr srcData, MapDataPtr mapData)
//	{
//		*mapData = *srcData;
//	}
//
//	/*
//	���幤�����ַ���ֵ����ת��
//	*/
//	ULONGLONG ShareString2ULong(CShareString ws)
//	{
//
//		ULONGLONG val = 0;
//		memcpy_s(&val, sizeof(ULONGLONG), &ws, sizeof(CShareString));
//
//		return val;
//	}
//
//	CShareString ULong2ShareString(ULONGLONG ul)
//	{
//
//		CShareString ws;
//		memcpy_s(&ws, sizeof(CShareString), &ul, sizeof(ULONGLONG));
//
//		return ws;
//	}
//
//	ULONG ShareString2ULong(CShareStringR ws)
//	{
//
//		ULONG val = 0;
//		memcpy_s(&val, sizeof(ULONG), &ws, sizeof(CShareStringR));
//
//		return val;
//	}
//
//	CShareStringR ULong2ShareString(ULONG ul)
//	{
//
//		CShareStringR ws;
//		memcpy_s(&ws, sizeof(CShareStringR), &ul, sizeof(ULONG));
//
//		return ws;
//	}
//}