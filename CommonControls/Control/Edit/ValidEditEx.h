//*****************************************************
//    
//    @copyright      ���������
//    @version        v1.0
//    @file           ValidEdit.H
//    @author         KG
//    @date           2015/3/7 10:41
//    @brief          У��༭�ؼ�
//*****************************************************

#pragma once

/**
*  @class    У��༭�ؼ�
*
*  @brief
*/
class COMMONCONTROLS_API CValidEditEx : public CValidEdit
{
	DECLARE_DYNAMIC(CValidEditEx)
public:
	CValidEditEx();
	virtual ~CValidEditEx();

protected:
	DECLARE_MESSAGE_MAP()

	/**
	*  @brief    ʧȥ����
	*
	*  @param    CWnd * pNewWnd
	*  @return   void
	*/
	virtual void OnKillFocus(CWnd* pNewWnd);
};

