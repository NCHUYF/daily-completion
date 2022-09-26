//*****************************************************
//    
//    @copyright      �����ά�����
//    @version        v4.0
//    @file           AllocMemoryPoolDef.H
//    @author         fanHong
//    @date           2017/11/3 11:08
//    @brief          �ڴ��
//
//*****************************************************

#pragma once

namespace CommBase
{
	//! �ڴ�ؽӿ�
	class COMMBASE_API IAllocMemoryPool
	{
	public:
		virtual ~IAllocMemoryPool(void)
		{
		}

		/**
		* ����ָ�����ȵ��ڴ�
		* @param [in] size				�ڴ泤��
		* @param [in] nGrowBy			�ڴ����
		* @param [in] CalcBestBlockSize	Ĭ��ΪTRUE
		*/
		virtual LPVOID Alloc(size_t size, size_t nGrowBy, BOOL CalcBestBlockSize = TRUE) = 0;

		/**
		* �ͷ��ڴ��
		* @param [in] buffer			�ڴ滺��
		* @param [in] FreeEmptyMemory	Ĭ��ΪFALSE
		*/
		virtual void Free(LPVOID buffer, BOOL FreeEmptyMemory = FALSE) = 0;

		/** �ͷ����С�*/
		virtual void FreeAll(void) = 0;

		/** ������� */
		virtual void ClearUp(void) = 0;

		/** ͳ���ܹ�������ֽ�����*/
		virtual ULONGLONG TotalAllocBytes(void) = 0;
	};
}