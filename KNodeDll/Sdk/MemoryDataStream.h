//*****************************************************
//    
//    @copyright      �����ά�����
//    @version        v4.0
//    @file           MemoryDataStream.H
//    @author         fanHong
//    @date           2017/11/3 11:26
//    @brief          �ڴ�����������
//
//*****************************************************

#pragma once

#include <vector>
#include "IDataStream.h"
#include "AllocMemoryPool.h"

namespace CommBase
{
	//!C�����ڴ��ָ��ָ�룬���Զ��ͷţ�Ҫ������� malloc �����
	class COMMBASE_API CBufferPtr
	{
	public:
		CBufferPtr();
		CBufferPtr(LPBYTE buffer, DWORD size);
		CBufferPtr(CBufferPtr& ptr);
		/*virtual*/ ~CBufferPtr();

		operator void* ();
		operator char* ();
		CBufferPtr& operator = (CBufferPtr& src);

		static CBufferPtr alloc(size_t size);
		DWORD length(void);
		LPBYTE get(void);
		LPBYTE release(void);
		void reset(LPBYTE buffer = NULL, size_t size = 0);

	protected:
		LPBYTE	_buffer;	/**< �������� */
		DWORD	_size;		/**< ���泤�� */
	};

	//=====================================================================
	// CMemoryDataReadStream
	//=====================================================================
	//! �ڴ����ݶ�ȡ����
	class COMMBASE_API CMemoryDataReadStream : public IRandomReadStream
	{
	public:
		CMemoryDataReadStream();
		CMemoryDataReadStream(const CString& strFile);
		CMemoryDataReadStream(LPVOID pBuffer, DWORD dwBufSize);
		CMemoryDataReadStream(CBufferPtr buffer);
		~CMemoryDataReadStream(void);

		/**
		* ��ȡָ���ֽڵ�������
		* @param [in] pBuffer		��������
		* @param [in] nBufSize		��������С
		* @param [out] nBytesRead	�ֽ���
		* @return ���ض�ȡָ���ֽڵ��������Ƿ�ɹ�
		* - TRUE �ɹ��� FALSE ʧ��
		*/
		virtual BOOL Read(LPVOID pBuffer, DWORD nBufSize, DWORD& nBytesRead);

		/**
		* ȡ�ᵱǰָ��λ��
		* @return	����ָ��λ��
		*/
		virtual DWORD GetPosition();
		/**
		* ���õ�ǰָ��λ��
		* @return	�ɹ����أ�ʧ�ܷ��ؼ٣����ַ��Ч��
		*/
		virtual BOOL SetPosition(DWORD position);
		/**
		* ȡ�õ�ǰ�ɷ������ݳ���
		* @return	�������ݳ���
		*/
		virtual DWORD GetLength();

		/** ȡ��ԭʼ������ */
		LPVOID getOriginalBuffer(void);

		/**
		* ���ļ��ж�ȡ����
		* @return	�ɹ�����TRUE
		*/
		virtual BOOL ReadFromFile(const CString& strFile);

		/**
		* д�뵽�ļ���
		* @return	�ɹ�����TRUE
		*/
		virtual BOOL WritToFile(const CString& strFile);

	protected:
		/** ������ʼλ�� */
		LPBYTE				_DataBuffer;
		CBufferPtr			_buffer_ptr;

		/** ���ݻ��������� */
		DWORD				_DataBufferLength;

		/** ��ǰ��ȡλ�� */
		LPBYTE				_CurrentDataPos;
	};

	//=====================================================================
	// CMemoryDataWriteStream
	//=====================================================================
	//! �ļ�ӳ����Դ���ݴ洢����
	class COMMBASE_API CMemoryDataWriteStream : public IRandomWriteStream
	{
	public:
		CMemoryDataWriteStream(const CString& strFile, int nBufSize = 0x2000);
		CMemoryDataWriteStream(int nBufSize = 0x2000 /*8K*/);
		~CMemoryDataWriteStream(void);

		/**
		* ��ȡ�������ݻ�������ַ
		*/
		DWORD CopyBuffer(LPVOID output);

		/**
		* д�����ݵ�������
		* @param [in] pBuffer		�ֽ��ַ���
		* @param [in] nBufSize		�ֽڳ���
		* @return ����д�����ݵ��������Ƿ�ɹ�
		* - TRUE �ɹ��� FALSE ʧ��
		*/
		virtual BOOL Write(LPCVOID pBuffer, DWORD nBufSize);

		/**
		* ȡ�ᵱǰָ��λ��
		* @return	����ָ��λ��
		*/
		virtual DWORD GetPosition();
		/**
		* ���õ�ǰָ��λ��
		* @return	�ɹ����أ�ʧ�ܷ��ؼ٣����ַ��Ч��
		*/
		virtual BOOL SetPosition(DWORD position);
		/**
		* ȡ�õ�ǰ�ɷ������ݳ���
		* @return	�������ݳ���
		*/
		virtual DWORD GetLength();

		/**
		* ���ļ��ж�ȡ����
		* @return	�ɹ�����TRUE
		*/
		virtual BOOL ReadFromFile(const CString& strFile);

		/**
		* ������д�뵽�ļ���
		* @return	�ɹ�����TRUE
		*/
		virtual BOOL WriteToFile(const CString& strFile);

	protected:
		class DATABUFFERINFO
		{
		public:
			DATABUFFERINFO(LPVOID pBuffer, DWORD nBufSize);

			/** �����ݻ�������д�����ݲ�����д��ߴ磬�����������������ֻд���ܹ�д������ߴ� */
			DWORD WriteBuffer(LPCVOID pBuffer, DWORD nBufSize);
			DWORD WriteBuffer(LPCVOID pBuffer, DWORD index, DWORD nBufSize);

			/** ��ȡ��Ч���ݳߴ� */
			DWORD GetDataLength(void);

			/** ��ȡ��������д */
			DWORD GetBufferLength(void);

			/** ��ȡ��������ַ */
			LPBYTE GetBufferAddress(void);

		protected:
			/** ���ݻ�������ַ */
			LPBYTE				BufferAddress;

			/** �������ߴ� */
			DWORD				BufferLength;

			/** ��ǰ������д��λ�� */
			DWORD				BufferPos;
		};

		/** ��ȡ��һ���ܹ�����dwNeedLength���ȵĻ�����(���ص�ǰ���õĻ������������ǰ���������������һ��) */
		DATABUFFERINFO* GetNextDataBuffer(DWORD dwNeedLength);

		/** ȡ��ָ��λ�����ڵ������� */
		BOOL GetDataBufferByPosition(DWORD positon, size_t* bufferIndex, size_t* byteIndex);

		/** �����»����� */
		DATABUFFERINFO* AllocDataBuffer(void);

		/** �������������ռ�ڴ� */
		void ReleaseAllDataBuffer(void);

	protected:
		CAllocMemoryPool			_DataBufferPool;
		/** Ĭ�������� Cache ��С */
		DWORD						_DefBufferBytes;
		/** ���ڴ洢���ݵĻ������б� */
		CAtlArray<DATABUFFERINFO*>	_DataBufferList;

		/** ��ǰָ��λ�� */
		DWORD						_CurPosition;
	};

	/*����ZIP���ݶ�ȡ�ڴ�ṹ*/
	typedef struct _tag_FileMReadData
	{
		_tag_FileMReadData()
		{
			pFileDataStream = NULL;
		}

		CString strFileName; // �ļ�����
		CMemoryDataReadStream* pFileDataStream; // �ļ�����
	}FileMReadData;
	typedef std::vector<FileMReadData> FileMReadDataArray;

	/*����ZIP����д���ڴ�ṹ*/
	typedef struct _tag_FileMWriteData
	{
		_tag_FileMWriteData()
		{
			pFileDataStream = NULL;
		}

		CString strFileName; // �ļ�����
		CMemoryDataWriteStream* pFileDataStream; // �ļ�����
	}FileMWriteData;
	typedef std::vector<FileMWriteData> FileMWriteDataArray;

}