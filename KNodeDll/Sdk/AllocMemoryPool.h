//*****************************************************
//    
//    @copyright      �����ά�����
//    @version        v4.0
//    @file           AllocMemoryPool.H
//    @author         fanHong
//    @date           2017/11/3 11:16
//    @brief          �ڴ��
//
//*****************************************************

#pragma once

#include "CriticalSection.h"
#include "AllocMemoryPoolDef.h"
#include <atlcoll.h>

namespace CommBase
{
	//! �ڴ�ط������
	class COMMBASE_API CAllocMemoryPool : public IAllocMemoryPool
	{
	public:
		CAllocMemoryPool(size_t ChunkSizeRadix = 32);

		virtual ~CAllocMemoryPool(void);

		/**
		* ����ָ�����ȵ��ڴ�
		* nGrowBy���Զ�����ȡ��С��ƽ����(��ƽ������������)�����ܳ��� MAXBYTE
		* ������� ����С size * nGrowBy ���ڴ�
		* @param [in] size				ÿ���ڴ泤��
		* @param [in] nGrowBy			Ҫ������ڴ����
		* @param [in] CalcBestBlockSize	Ĭ��ΪTRUE������
		*/
		virtual LPVOID Alloc(size_t size, size_t nGrowBy, BOOL CalcBestBlockSize = TRUE);

		/**
		* �ͷ��ڴ��
		* @param [in] buffer			�ڴ滺��
		* @param [in] FreeEmptyMemory	Ĭ��ΪFALSE
		*/
		virtual void Free(LPVOID buffer, BOOL FreeEmptyMemory = FALSE);

		/** �ͷ����С�*/
		virtual void FreeAll(void);

		/** ������� */
		virtual void ClearUp(void);

		/** ͳ���ܹ�������ֽ�����*/
		virtual ULONGLONG TotalAllocBytes(void);

	protected:
#pragma pack(push, 1)
		/** ����ṹ */
		typedef struct tagMEMORYHEAD
		{
			/** �ڴ�������� */
			size_t ChunkCount;
			/** �ڴ����䳤�ȣ����������ͷCHUNKHEAD�ĳ��ȣ� */
			size_t ChunkSize;
			/** û�з����ȥ���ڴ������ */
			size_t NotAllocCount;
			/** �ڴ��������� */
			size_t GroupCount;
			/** ÿ����ڴ������ */
			size_t GroupLength;
			/** ���һ�η��䣯�ͷŵ������� */
			size_t LastOpGroup;
			/** ���һ�η��䣯�ͷŵ��ڴ������ */
			size_t LastOpChunk;
		} MEMORYHEAD, *PMEMORYHEAD;

		/** �����ڴ���ͷ����Ϣ( 8 byte ) */
		typedef struct tagCHUNKHEAD
		{
			/** �Ƿ��ѷ����ȥ */
			UCHAR		bAlloc;
			/** ���ڵ������� */
			UCHAR		nGroupIndex;
			/** ���ڵ��ڴ������ */
			UCHAR		nChunkIndex;
			/** ��ǰ��û�з�����ڴ������ */
			UCHAR		nGroupNotAlloc;
			/** �ڴ�����ͷ */
			MEMORYHEAD* pMemory;
		} CHUNKHEAD, *PCHUNKHEAD;
#pragma pack(pop)

		/*
		�ڴ����ṹͼ
		+--------------------------------------------------------------------------------------+
		|    ���鳤��        |   �ڴ�� 1                     |    �ڴ�� 2                    |
		+--------------------------------------------------------------------------------------+
		| sizeof(MEMORYHEAD) | sizeof(CHUNKHEAD) + ChunkSize | sizeof(CHUNKHEAD) + ChunkSize |
		+--------------------------------------------------------------------------------------+
		*/
		/** �ڴ��б����� */
		CAtlArray<PMEMORYHEAD>	_MemoryArray;
		/** ����û������ڴ����ڴ��б� */
		CAtlArray<PMEMORYHEAD>	_CanAllocMemory;

		/** Ĭ����С�ڴ���С */
		size_t					_ChunkSizeRadix;

		/** ������Ĵ��� */
		ULONGLONG				_AllocCount;
		/** �̻߳����� */
		CCriticalSectionHandle	_CriticalMutex;

	protected:

		/**
		* �ͷ�ָ���������ڴ��
		* @param [out] index	�ڴ������
		*/
		void FreeMemoryAt(const size_t& index);
		/**
		* �����ڴ�飬�����ڴ���ַ
		* @param [in] chunk	�ڴ�ṹ����
		*/
		LPVOID AllocChunk(PCHUNKHEAD chunk);
		/**
		* �ͷ��ڴ��
		* @param [in] chunk	�ڴ�ṹ����
		*/
		void FreeChunk(PCHUNKHEAD chunk);
		/**
		* ����ָ�����ȵ��ڴ��
		* @param [out] RequestedSize		ÿһ��������С
		* @param [out] nGrowBy				�ڴ����
		* @param [out] CalcBestBlockSize
		*/
		void ExtandMemoryChunk(const size_t& RequestedSize, const size_t& nGrowBy, const BOOL& CalcBestBlockSize);
		/**
		* ȡ�õ�N�������
		* @param [in] memory		�ڴ�ṹ����
		* @param [in] group			����
		* @return ��������
		*/
		__inline PCHUNKHEAD GetGroupChunkHead(PMEMORYHEAD memory, size_t group);
		/**
		* ȡ�õ�N���ڴ����
		* @param [in] memory		�ڴ�ṹ����
		* @param [in] GroupIndex	�������
		* @param [in] ChunkIndex	�ڴ������
		* @return ��������
		*/
		__inline PCHUNKHEAD GetMemoryChunkHead(PMEMORYHEAD memory, size_t GroupIndex, size_t ChunkIndex);
		/**
		* ���ҿ��õ��ڴ��
		* @param [out] chunk			�ڴ��ṹ
		* @param [out] RequestedSize	�����С
		* @return ���ز��ҿ��õ��ڴ���Ƿ�ɹ�
		* - TRUE �ɹ��� FALSE ʧ��
		*/
		BOOL LookupMemoryChunk(PCHUNKHEAD& chunk, const size_t& RequestedSize);
		/**
		* �����������ʺϲ��Ҵ��ڿ����ڴ������ڴ���������
		* @param [out] RequestedSize	�����С
		* @param [out] bestMemory		���ʺ��ڴ��ṹ
		* @return ���ز����������ʺϲ��Ҵ��ڿ����ڴ������ڴ����������Ƿ�ɹ�
		* - TRUE �ɹ��� FALSE ʧ��
		*/
		BOOL FindBestMemoryHead(const size_t& RequestedSize, PMEMORYHEAD& bestMemory);
		/**
		* ���ҿ����ڴ��
		* @param [in] memory	�ڴ��ṹ
		* @param [out] index	�����ڴ������
		* @return ���ز��ҿ����ڴ���Ƿ�ɹ�
		* - TRUE �ɹ��� FALSE ʧ��
		*/
		BOOL FindCanAllocMemory(const PMEMORYHEAD memory, int& index);
		/**
		* ������ѵ��ڴ�鳤��
		* @param [out] sRequestedMemoryBlockSize	�����ڴ�鳤��
		* @return ������ѵ��ڴ�鳤��
		*/
		size_t CalculateBestMemoryBlockSize(const size_t &sRequestedMemoryBlockSize);
		/**
		* ������Ҫ���ڴ������
		* @param [out] sMemorySize	�ڴ�鳤��
		* @return ������Ҫ���ڴ������
		*/
		size_t CalculateNeededChunks(const size_t &sMemorySize);
		/**
		* ������ѵĿ�����
		* @param [out] GrowBy		�ڴ��ܿ���
		* @param [out] GroupCount	�ڴ�������
		* @return ����������ѵĿ�����
		*/
		size_t CalculateBestMemoryChunkCount(const size_t& GrowBy, size_t& GroupCount);
	};
}