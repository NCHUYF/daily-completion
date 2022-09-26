
#pragma once

namespace BwProj { namespace toolkit {

/** @addtogroup DataStream
* @{
*/

//=====================================================================
// IByteReadStream
//=====================================================================
//! �������ݶ�ȡ�����Ļ���
class IByteReadStream
{
public:
	virtual ~IByteReadStream () {}

	/** 
	* ��ȡָ���ֽڵ������� �����麯����
	* @param [in] pBuffer		��������
	* @param [in] nBufSize		��������С
	* @param [out] nBytesRead	�ֽ���
	* @return	����TRUE
	*/
	virtual BOOL Read(LPVOID pBuffer, DWORD nBufSize, DWORD& nBytesRead) = 0;
};

typedef std::auto_ptr<IByteReadStream> ByteReadStream_ptr;

//=====================================================================
// IByteWriteStream
//=====================================================================
//! ��������д������Ļ���
class  IByteWriteStream
{
public:
	virtual ~IByteWriteStream () {}

	/** 
	* д�����ݵ������� �����麯����
	* @param [in] pBuffer	��������
	* @param [in] nBufSize	��������С
	* @return	����TRUE
	*/
	virtual BOOL Write(const void* pBuffer, DWORD nBufSize)  = 0;
};

typedef std::auto_ptr<IByteWriteStream> ByteWriteStream_ptr;

//=====================================================================
// STRING_STREAM_HEAD
//=====================================================================
//! �����ַ����ı���ͷ�ṹ��4�ֽڣ�
struct STRING_STREAM_HEAD
{
	USHORT	bUnicode;		/**< �Ƿ���˫�ֽ��ַ�����TRUE, FALSE��*/
	USHORT	nByteLength;	/**< �ַ������ȣ�����������0��*/
};

struct StringStreamData : public STRING_STREAM_HEAD
{
	LPBYTE	Buffer;		// �ַ�����ַ
};

//=====================================================================
// IDataReadStream
//=====================================================================
//! ��������ȡ��
class COMMONCONTROLS_API IDataReadStream : public IByteReadStream
{
public:
	IDataReadStream (void);
	virtual ~IDataReadStream (void);

	virtual BYTE ReadByte(void);
	
	/**
	* ��ȡlong��ʽ��ֵ
	* @return	����long��ʽ��ֵ
	*/
	virtual long ReadLong (void);

	/**
	* ��ȡ__int64��ʽ��ֵ
	* @return	����__int64��ʽ��ֵ
	*/
	virtual __int64 ReadI64 (void);

	/**
	* ��ȡLPCWSTR��ʽ�ַ���
	* @return	����LPCTSTR��ʽ�ַ���
	*/
	virtual LPCWSTR ReadString (void);

	// ���������ֽڣ������������ֽ���
	virtual size_t skip(size_t bytes);

	// ��ԭλ��
	virtual void reset() = 0;

	virtual DWORD available() = 0;

	/** 
	* ȡ������
	* @return	��������
	*/
	virtual StringStreamData ReadStringData (void);

protected:
	BYTE*	_lastString;
	size_t	_lastStrLen;
};

typedef std::auto_ptr<IDataReadStream> DataReadStream_ptr;
typedef std::shared_ptr<IDataReadStream> DataReadStreamPtr;

//! �漴���ݶ�ȡ��
class IRandomReadStream : public IDataReadStream
{
public:
	/**
	* ȡ�ᵱǰָ��λ��
	* @return	����ָ��λ��
	*/
	virtual DWORD GetPosition () = 0;
	/**
	* ���õ�ǰָ��λ��
	* @return	�ɹ����أ�ʧ�ܷ��ؼ٣����ַ��Ч��
	*/
	virtual BOOL SetPosition (DWORD position) = 0;
	/**
	* ȡ�õ�ǰ�ɷ������ݳ���
	* @return	�������ݳ���
	*/
	virtual DWORD GetLength () = 0;

	virtual DWORD available();
};

typedef std::auto_ptr<IRandomReadStream> RandomReadStream_ptr;

//=====================================================================
// IDataWriteStream
//=====================================================================
//! �������洢��
class COMMONCONTROLS_API IDataWriteStream : public IByteWriteStream
{
public:

	/**
	* ��ȡLPCTSTR��ʽ�ַ���
	* @param [out] val	Ҫд���long��ʽ����ֵ
	*/
	virtual void WriteLong (const long& val);

	/**
	* ��ȡLPCTSTR��ʽ�ַ���
	* @param [out] val	Ҫд���__int64��ʽ����ֵ
	*/
	virtual void WriteI64 (const __int64& val);

	/**
	* ��ȡLPCWSTR��ʽ�ַ���
	* @param [in] val	Ҫд���LPCWSTR��ʽ���ַ���
	*/
	virtual void WriteString (LPCWSTR val);

	/** 
	* д����
	* @param [in] val	д����
	*/
	virtual void WriteString (LPCSTR val);

};

typedef std::auto_ptr<IDataWriteStream> DataWriteStream_ptr;

//! �漴����д��
class  COMMONCONTROLS_API IRandomWriteStream : public IDataWriteStream
{
public:
	/**
	* ȡ�ᵱǰָ��λ��
	* @return	����ָ��λ��
	*/
	virtual DWORD GetPosition () = 0;
	/**
	* ���õ�ǰָ��λ��
	* @return	�ɹ����أ�ʧ�ܷ��ؼ٣����ַ��Ч��
	*/
	virtual BOOL SetPosition (DWORD position) = 0;
	/**
	* ȡ�õ�ǰ�ɷ������ݳ���
	* @return	�������ݳ���
	*/
	virtual DWORD GetLength () = 0;
};

typedef std::auto_ptr<IRandomWriteStream> RandomWriteStream_ptr;

/** * @} */
}}	// end namespace