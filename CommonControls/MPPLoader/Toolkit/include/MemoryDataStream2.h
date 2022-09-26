#pragma once

#include "IDataStream2.h"
#include "allocmemorypool2.h"

// begin namespace
namespace BwProj{ namespace toolkit{

/** @addtogroup DataStream
* @{
*/

//!C�����ڴ��ָ��ָ�룬���Զ��ͷţ�Ҫ������� malloc �����
class COMMONCONTROLS_API c_buffer_ptr
{
public:
	c_buffer_ptr ();
	c_buffer_ptr (LPBYTE buffer, DWORD size);
	c_buffer_ptr (c_buffer_ptr& ptr);
	/*virtual*/ ~c_buffer_ptr ();

	operator void* ();
	operator char* ();
	c_buffer_ptr& operator = (c_buffer_ptr& src);

	static c_buffer_ptr alloc (size_t size);
	DWORD length (void);
	LPBYTE get (void);
	LPBYTE release (void);
	void reset (LPBYTE buffer = NULL, size_t size = 0);

protected:
	LPBYTE	_buffer;	/**< �������� */
	DWORD	_size;		/**< ���泤�� */
};

//=====================================================================
// CMemoryDataReadStream
//=====================================================================
//! �ڴ����ݶ�ȡ����
class  CMemoryDataReadStream : public BwProj::toolkit::IRandomReadStream
{
public:
	CMemoryDataReadStream(LPVOID pBuffer, DWORD dwBufSize);
	CMemoryDataReadStream(c_buffer_ptr buffer);
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
	virtual DWORD GetPosition ();
	/**
	* ���õ�ǰָ��λ��
	* @return	�ɹ����أ�ʧ�ܷ��ؼ٣����ַ��Ч��
	*/
	virtual BOOL SetPosition (DWORD position);
	/**
	* ȡ�õ�ǰ�ɷ������ݳ���
	* @return	�������ݳ���
	*/
	virtual DWORD GetLength ();

	virtual void reset();

	/** ȡ��ԭʼ������ */
	LPVOID getOriginalBuffer (void);

protected:
	BwProj::toolkit::CAllocMemoryPool	_StringPool;

	/** �� _StringPool ����Ŀռ䣬���ڱ�����ʱ�ַ��� */
	LPCTSTR				_StringBuffer;

	/** ������ʼλ�� */
	LPBYTE				_DataBuffer;
	c_buffer_ptr		_buffer_ptr;

	/** ���ݻ��������� */
	DWORD				_DataBufferLength;

	/** ��ǰ��ȡλ�� */
	LPBYTE				_CurrentDataPos;
};

//=====================================================================
// CMemoryDataWriteStream2
//=====================================================================
//! �ļ�ӳ����Դ���ݴ洢����
class CMemoryDataWriteStream2 : public BwProj::toolkit::IRandomWriteStream
{
public:
	CMemoryDataWriteStream2(void);
	virtual ~CMemoryDataWriteStream2(void);

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
	virtual DWORD GetPosition ();
	/**
	* ���õ�ǰָ��λ��
	* @return	�ɹ����أ�ʧ�ܷ��ؼ٣����ַ��Ч��
	*/
	virtual BOOL SetPosition (DWORD position);
	/**
	* ȡ�õ�ǰ�ɷ������ݳ���
	* @return	�������ݳ���
	*/
	virtual DWORD GetLength ();

protected:
	class DATABUFFERINFO
	{
	public:
		DATABUFFERINFO(LPVOID pBuffer, DWORD nBufSize);

		/** �����ݻ�������д�����ݲ�����д��ߴ磬�����������������ֻд���ܹ�д������ߴ� */
		DWORD WriteBuffer (LPCVOID pBuffer, DWORD nBufSize);
		DWORD WriteBuffer (LPCVOID pBuffer, DWORD index, DWORD nBufSize);

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
	BOOL GetDataBufferByPosition (DWORD positon, size_t* bufferIndex, size_t* byteIndex);

	/** �����»����� */
	DATABUFFERINFO* AllocDataBuffer(void);

	/** �������������ռ�ڴ� */
	void ReleaseAllDataBuffer(void);

protected:
	BwProj::toolkit::CAllocMemoryPool			_DataBufferPool;
	/** Ĭ�������� Cache ��С */
	DWORD						_DefBufferBytes;
	/** ���ڴ洢���ݵĻ������б� */
	CAtlArray<DATABUFFERINFO*>	_DataBufferList;

	/** ��ǰָ��λ�� */
	DWORD						_CurPosition;
};

/** * @} */
// end namespace
}}