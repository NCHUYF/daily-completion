#include "stdafx.h"
#include "AllocMemoryPool.h"
#include "CriticalSection.h"
#include <malloc.h>
#include <math.h>

namespace CommBase
{
	CAllocMemoryPool::CAllocMemoryPool(size_t ChunkSizeRadix)
	{
		_ChunkSizeRadix = ChunkSizeRadix;
		_AllocCount = 0;
	}

	CAllocMemoryPool::~CAllocMemoryPool(void)
	{
		ATLASSERT(_AllocCount == 0);

		FreeAll();
	}

	/** ����ָ�����ȵ��ڴ桡*/
	LPVOID CAllocMemoryPool::Alloc(size_t size, size_t nGrowBy, BOOL CalcBestBlockSize)
	{
		ATLASSERT(nGrowBy > 0);

		if (size <= 0) return NULL;

		CCriticalSectionSync mutex(_CriticalMutex);

		// ���ҿ����ڴ�飬���û�ҵ�������
		PCHUNKHEAD chunk = NULL;
		if (!LookupMemoryChunk(chunk, size))
		{
			ExtandMemoryChunk(size, nGrowBy, CalcBestBlockSize);

			// ���������������û���ҵ������ڴ棬�򷵻�NULL
			if (!LookupMemoryChunk(chunk, size))
				return NULL;
		}

		ATLASSERT(chunk->pMemory != NULL);

		return AllocChunk(chunk);
	}

	/** �ͷ��ڴ�顡*/
	void CAllocMemoryPool::Free(LPVOID buffer, BOOL FreeEmptyMemory)
	{
		if (buffer == NULL) return;

		CCriticalSectionSync mutex(_CriticalMutex);

		// �ͷ��ڴ��
		PCHUNKHEAD chunk = (PCHUNKHEAD)(((char*)buffer) - sizeof(CHUNKHEAD));

		ATLASSERT(chunk != NULL && chunk->pMemory != NULL);

		FreeChunk(chunk);

		// �ͷ��ڴ�
		if (FreeEmptyMemory && chunk->pMemory->NotAllocCount == 0)
		{
			for (size_t i = 0; i < _MemoryArray.GetCount(); i++)
			{
				if (_MemoryArray[i] == chunk->pMemory)
				{
					FreeMemoryAt(i);
					break;
				}
			}
		}
	}

	/** �ͷ����С�*/
	void CAllocMemoryPool::FreeAll(void)
	{
		CCriticalSectionSync mutex(_CriticalMutex);

		while (_MemoryArray.GetCount())
			FreeMemoryAt(_MemoryArray.GetCount() - 1);
	}

	void CAllocMemoryPool::ClearUp(void)
	{
		CCriticalSectionSync mutex(_CriticalMutex);

		for (int i = (int)_MemoryArray.GetCount() - 1; i >= 0; i--)
		{
			PMEMORYHEAD memory = _MemoryArray[i];
			if (memory->NotAllocCount == memory->ChunkCount)
				FreeMemoryAt(i);
		}
	}

	/** ͳ���ܹ�������ֽ�����*/
	ULONGLONG CAllocMemoryPool::TotalAllocBytes(void)
	{
		CCriticalSectionSync mutex(_CriticalMutex);

		ULONGLONG count = 0;

		for (int i = (int)_MemoryArray.GetCount() - 1; i >= 0; i--)
		{
			PMEMORYHEAD memory = _MemoryArray[i];
			count += sizeof(MEMORYHEAD) + memory->ChunkCount *
				(sizeof(CHUNKHEAD) + memory->ChunkSize);
		}

		return count;
	}

	// �ͷ�ָ���������ڴ��
	void CAllocMemoryPool::FreeMemoryAt(const size_t& index)
	{
		ATLASSERT(index >= 0 && index < _MemoryArray.GetCount());

		// �ӿ����б����Ƴ�
		int CanAllocIndex = -1;
		if (FindCanAllocMemory(_MemoryArray[index], CanAllocIndex))
			_CanAllocMemory.RemoveAt(CanAllocIndex);

		// �ͷ��ڴ�
		char* buffer = (char*)_MemoryArray[index];
		delete[] buffer;
		//free (_MemoryArray[index]);
		_MemoryArray.RemoveAt(index);
	}

	// �����ڴ�飬�����ڴ���ַ
	LPVOID CAllocMemoryPool::AllocChunk(PCHUNKHEAD chunk)
	{
		_AllocCount++;

		// �����ڴ��ַ
		chunk->bAlloc = TRUE;
		chunk->pMemory->NotAllocCount--;

		// �����ڴ�����ڶΣ������ö�ֵ
		PCHUNKHEAD group = GetGroupChunkHead(chunk->pMemory, chunk->nGroupIndex);
		group->nGroupNotAlloc--;

		chunk->pMemory->LastOpGroup = chunk->nGroupIndex;
		chunk->pMemory->LastOpChunk = chunk->nChunkIndex;

		// �Ƴ������ڴ������
		if (chunk->pMemory->NotAllocCount == 0)
		{
			int CanAllocIndex = -1;
			if (FindCanAllocMemory(chunk->pMemory, CanAllocIndex))
				_CanAllocMemory.RemoveAt(CanAllocIndex);
		}

		// ���ؿ�д�ڴ��ַ
		return (void*)(((char*)chunk) + sizeof(CHUNKHEAD));
	}

	// �ͷ��ڴ��
	void CAllocMemoryPool::FreeChunk(PCHUNKHEAD chunk)
	{
		_AllocCount--;

		// �����ڴ��
		chunk->bAlloc = FALSE;
		chunk->pMemory->NotAllocCount++;

		// �����ڴ�����ڶΣ������ö�ֵ
		PCHUNKHEAD group = GetGroupChunkHead(chunk->pMemory, chunk->nGroupIndex);
		group->nGroupNotAlloc++;

		chunk->pMemory->LastOpGroup = chunk->nGroupIndex;
		chunk->pMemory->LastOpChunk = chunk->nChunkIndex;

		// ��������ڴ������
		if (chunk->pMemory->NotAllocCount == 1)
		{
			int CanAllocIndex = -1;
			if (!FindCanAllocMemory(chunk->pMemory, CanAllocIndex))
				_CanAllocMemory.Add(chunk->pMemory);
		}
	}

	// ����ָ�����ȵ��ڴ��
	void CAllocMemoryPool::ExtandMemoryChunk(const size_t& RequestedSize, const size_t& nGrowBy,
		const BOOL& CalcBestBlockSize)
	{
		// ����Ҫ������ڴ�鳤�ȡ��ڴ������
		size_t bestChunkSize = CalcBestBlockSize ? CalculateBestMemoryBlockSize(RequestedSize) : RequestedSize;

		size_t GroupCount = 0;
		size_t bestChunkCount = CalculateBestMemoryChunkCount(nGrowBy, GroupCount);

		// ������������ܴ��� 256
		ATLASSERT(GroupCount <= MAXBYTE);

		size_t memSize = sizeof(MEMORYHEAD) + (sizeof(CHUNKHEAD) + bestChunkSize) * bestChunkCount;

		// �����ڴ棬����дͷ�ṹ����
		PMEMORYHEAD memory = (PMEMORYHEAD) new char[memSize];
		ATLASSERT(memory != NULL);

		memory->ChunkCount = bestChunkCount;
		memory->NotAllocCount = bestChunkCount;
		memory->ChunkSize = bestChunkSize;
		memory->GroupCount = GroupCount;
		memory->GroupLength = GroupCount;
		memory->LastOpGroup = 0;
		memory->LastOpChunk = 0;

		// ��ʹ��ÿ����������
		for (size_t i = 0; i < memory->GroupCount; i++)
		{
			for (size_t j = 0; j < memory->GroupLength; j++)
			{
				PCHUNKHEAD chunk = GetMemoryChunkHead(memory, i, j);

				if (j == 0)
				{
					chunk->nGroupNotAlloc = (UCHAR)memory->GroupLength;
				}

				chunk->pMemory = memory;
				chunk->nGroupIndex = (UCHAR)i;
				chunk->nChunkIndex = (UCHAR)j;
				chunk->bAlloc = FALSE;
			}
		}

		// ���ӵ������б�
		_MemoryArray.Add(memory);

		// ��ӵ��ɷ�����ڴ��б���
		_CanAllocMemory.Add(memory);
	}

	// ȡ�õ�N�������
	CAllocMemoryPool::PCHUNKHEAD CAllocMemoryPool::GetGroupChunkHead(
		CAllocMemoryPool::PMEMORYHEAD memory, size_t group)
	{
		return GetMemoryChunkHead(memory, group, 0);
	}

	// ȡ�õ�N���ڴ����
	CAllocMemoryPool::PCHUNKHEAD CAllocMemoryPool::GetMemoryChunkHead(
		CAllocMemoryPool::PMEMORYHEAD memory, size_t GroupIndex, size_t ChunkIndex)
	{
		// �����ڴ����������
		size_t index = GroupIndex * memory->GroupLength + ChunkIndex;

		// �����ڴ�����ڵ�ַ
		return (PCHUNKHEAD)(((char*)memory) + sizeof(MEMORYHEAD) +
			index * (sizeof(CHUNKHEAD) + memory->ChunkSize));
	}

	// ���ҿ��õ��ڴ��
	BOOL CAllocMemoryPool::LookupMemoryChunk(CAllocMemoryPool::PCHUNKHEAD& chunk,
		const size_t& RequestedSize)
	{
		// ���ҿ����ڴ�ͷ
		PMEMORYHEAD bestMemory = NULL;
		if (!FindBestMemoryHead(RequestedSize, bestMemory))
			return FALSE;

		// �Ȳ����飨һ���ҵõ���
		size_t GroupIndex = bestMemory->LastOpGroup;
		if (GetGroupChunkHead(bestMemory, GroupIndex)->nGroupNotAlloc == 0)
		{
			for (size_t i = 0; i < bestMemory->GroupCount; i++)
			{
				PCHUNKHEAD group = GetGroupChunkHead(bestMemory, i);
				if (group->nGroupNotAlloc)
				{
					GroupIndex = i;
					break;
				}
			}
		}

		// ���ҿ��õ��ڴ��

		// �� LastOpChunk ��ʼ������
		for (size_t i = bestMemory->LastOpChunk; i < bestMemory->GroupLength; i++)
		{
			chunk = GetMemoryChunkHead(bestMemory, GroupIndex, i);
			if (!chunk->bAlloc)
				return TRUE;
		}

		// �� 0 ��ʼ�� LastOpChunk ����
		for (size_t i = 0; i < bestMemory->LastOpChunk; i++)
		{
			chunk = GetMemoryChunkHead(bestMemory, GroupIndex, i);
			if (!chunk->bAlloc)
				return TRUE;
		}

		return TRUE;
	}

	// �����������ʺϲ��Ҵ��ڿ����ڴ������ڴ���������
	BOOL CAllocMemoryPool::FindBestMemoryHead(const size_t& RequestedSize, PMEMORYHEAD& bestMemory)
	{
		bestMemory = NULL;

		// �ӿ����ڴ���в���
		for (size_t i = 0; i < _CanAllocMemory.GetCount(); i++)
		{
			PMEMORYHEAD memory = _CanAllocMemory[i];

			if (memory->NotAllocCount && memory->ChunkSize >= RequestedSize)
			{
				if (bestMemory == NULL)
					bestMemory = memory;
				else if (memory->ChunkSize < bestMemory->ChunkSize)
					bestMemory = memory;
			}
		}

		return bestMemory != NULL;
	}

	// ���ҿ����ڴ��
	BOOL CAllocMemoryPool::FindCanAllocMemory(const PMEMORYHEAD memory, int& index)
	{
		for (int i = 0; i < (int)_CanAllocMemory.GetCount(); i++)
		{
			if (_CanAllocMemory[i] == memory)
			{
				index = i;
				return TRUE;
			}
		}

		return FALSE;
	}

	// ������ѵ��ڴ�鳤��
	size_t CAllocMemoryPool::CalculateBestMemoryBlockSize(const size_t &sRequestedMemoryBlockSize)
	{
		size_t uiNeededChunks = CalculateNeededChunks(sRequestedMemoryBlockSize);
		return size_t((uiNeededChunks * _ChunkSizeRadix));
	}

	size_t CAllocMemoryPool::CalculateNeededChunks(const size_t &sMemorySize)
	{
		float f = (float)(((float)sMemorySize) / ((float)_ChunkSizeRadix));
		return ((size_t)ceil(f));
	}

	// ������ѵĿ�����
	size_t CAllocMemoryPool::CalculateBestMemoryChunkCount(const size_t& GrowBy, size_t& GroupCount)
	{
		GroupCount = (size_t)ceil(sqrtl((long)GrowBy));
		return (size_t)powl((long)GroupCount, 2);
	}
}