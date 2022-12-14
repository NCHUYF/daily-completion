//*****************************************************
//    
//    @copyright      变电三维设计组
//    @version        v4.0
//    @file           AllocMemoryPoolDef.H
//    @author         fanHong
//    @date           2017/11/3 11:08
//    @brief          内存池
//
//*****************************************************

#pragma once

namespace CommBase
{
	//! 内存池接口
	class COMMBASE_API IAllocMemoryPool
	{
	public:
		virtual ~IAllocMemoryPool(void)
		{
		}

		/**
		* 分配指定长度的内存
		* @param [in] size				内存长度
		* @param [in] nGrowBy			内存块数
		* @param [in] CalcBestBlockSize	默认为TRUE
		*/
		virtual LPVOID Alloc(size_t size, size_t nGrowBy, BOOL CalcBestBlockSize = TRUE) = 0;

		/**
		* 释放内存块
		* @param [in] buffer			内存缓存
		* @param [in] FreeEmptyMemory	默认为FALSE
		*/
		virtual void Free(LPVOID buffer, BOOL FreeEmptyMemory = FALSE) = 0;

		/** 释放所有　*/
		virtual void FreeAll(void) = 0;

		/** 清楚所有 */
		virtual void ClearUp(void) = 0;

		/** 统计总共分配的字节数　*/
		virtual ULONGLONG TotalAllocBytes(void) = 0;
	};
}