//*****************************************************
//    
//    @copyright      �����ά�����
//    @version        v4.0
//    @file           Exception.H
//    @author         fanHong
//    @date           2017/11/3 13:14
//    @brief          �쳣����
//
//*****************************************************

#pragma once

namespace CommBase
{
	//! �����쳣��
	class COMMBASE_API Exception
	{
	public:
		/**
		* ���캯��
		* @param [in] info		������Ϣ�ַ���
		* @param [in] detail	��ϸ��Ϣ�ַ�����Ĭ��ΪNULL��
		*/
		Exception(LPCTSTR info, LPCTSTR detail = NULL);
		virtual ~Exception();

		/**
		* ȡ�ó�����Ϣ
		*/
		virtual LPCTSTR	what(void);
		/**
		* ȡ����ϸ��Ϣ
		*/
		virtual LPCTSTR detail(void);
	protected:
		/** ������Ϣ */
		CString	_info;
		/** ��ϸ��Ϣ */
		CString _detail;
	};

	/** �����׳��쳣���� */
	/** �����׳��쳣���� */
#ifndef RaiseError
#define RaiseError(info) throw toolkit::Exception (info)
#endif

#ifndef RaiseError2
#define RaiseError2(info,detail) throw toolkit::Exception (info,detail)
#endif

#ifndef ThrowError
#define ThrowError(info) throw toolkit::Exception (info)
#endif

#ifndef ThrowError2
#define ThrowError2(info,detail) throw toolkit::Exception (info,detail)
#endif

	/** ����ASSERT �쳣���� */
#ifndef ASSERT_THROW
#define ASSERT_THROW(ExpVal,info) if (!(ExpVal)) throw toolkit::Exception (info)
#endif
}