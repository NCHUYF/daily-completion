#pragma once

#include <exception>
// begin namespace
namespace BwProj {

/** @addtogroup exception
* @{
*/

//! �����쳣��
class COMMONTOOLS_API Exception
{
public:
	/**
	* ���캯��
	* @param [in] info		������Ϣ�ַ���
	* @param [in] detail	��ϸ��Ϣ�ַ�����Ĭ��ΪNULL��
	*/
	Exception (LPCTSTR info, LPCTSTR detail = NULL);
	Exception(const Exception& e);
	virtual ~Exception ();

	/**
	* ȡ�ó�����Ϣ
	*/
	virtual LPCTSTR	what (void) const;
	/**
	* ȡ����ϸ��Ϣ
	*/
	virtual LPCTSTR detail (void) const;
protected:
	/** ������Ϣ */
	CString	_info;
	/** ��ϸ��Ϣ */
	CString _detail;
};

/** �����׳��쳣���� */
#define RaiseError(info) throw BwProj::Exception (info)
#define RaiseError2(info,detail) throw BwProj::Exception (info,detail)
#define ThrowError(info) throw BwProj::Exception (info)
#define ThrowError2(info,detail) throw BwProj::Exception (info,detail)

/** ����ASSERT �쳣���� */
#define ASSERT_THROW(ExpVal,info) if (!(ExpVal)) throw BwProj::Exception (info)

/** * @} */
// end namespace
}
