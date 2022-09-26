//*****************************************************
//    
//    @copyright      ���������;
//    @version        v3.0
//    @file           BaseControlDefine.H
//    @author         mahaidong;
//    @date           2015/4/9 10:45
//    @brief          ��׼�ؼ���Ϣ��ö�ٶ���;
//*****************************************************

#pragma once

// ѡ����Ϣ
#define LCN_SELECTED				(WM_USER + 1001)
// �������
#define LCN_LEFTCLICK				(WM_USER + 1002)
// �Ҽ�����
#define LCN_RIGHTCLICK				(WM_USER + 1003)
// ˫���¼�
#define LCN_DBLCLICK				(WM_USER + 1004)
// ��ʼ�༭�¼�
#define LCN_BEGINEDIT				(WM_USER + 1005)
// �����༭�¼�
#define LCN_ENDEDIT					(WM_USER + 1006)
// �����ӵ����¼�
#define LCN_HYPERLINK				(WM_USER + 1007)
// ���ؼ�������Ϣ(�ڲ�ʹ��)
#define LIST_CTRL_END				(WM_USER + 1008)
// ��ǩ�ؼ�����رձ�ǩ
#define TAB_ITEM_CLOSE				(WM_USER + 1009)
// �б�ؼ�����Ҽ�
#define LISTBOX_RCLK				(WM_USER + 1314)
// �б�ؼ�������˫��
#define LISTBOX_LDBCLK				(WM_USER + 1315)
// �б�ؼ�������
#define LISTBOX_LCLK				(WM_USER + 1316)
// ��ɽ����༭�¼�
#define LCN_ENDEDITDONE				(WM_USER + 1317)
// ��ͷ�����ʼ������Ϣ
#define LCH_COLUMN_BEGINSORT		(WM_USER + 1318)
// ��ͷ���������Ϣ
#define LCH_COLUMN_ENDSORT			(WM_USER + 1319)

// ʱ����ؼ��������������Ϣ
#define  TIMELINE_LBUTTONDOWN		(WM_USER + 1320)
// ʱ����ؼ����������Ϣ
#define  TIMELINE_LBUTTONUP			(WM_USER + 1321)
// ʱ����ؼ����˫����Ϣ
#define  TIMELINE_DBLCLICK			(WM_USER + 1322)
// ʱ����ؼ��Ҽ���������Ϣ
#define  TIMELINE_RIGHTCLICK		(WM_USER + 1323)
// ʱ����ؼ��ƶ��ؼ�֡��Ϣ
#define  TIMELINE_MOVECURFRAME		(WM_USER + 1324)

// ȷ��
#define LCNR_OK						(LRESULT) 0		
// ȡ��
#define LCNR_CANCEL					(LRESULT) 1	

#define TCS_SHOWCLOSEBTN 0x0001
#define TCS_SHOWADDBTN	 0x0002
#define TCS_ENABLEEDIT	 0x0003

#define TCN_DELETEITEM (TCN_FIRST - 10)
#define TCN_ENDEDITITEM (TCN_FIRST - 11)

// ѡ��״̬���ı���¼�
#define TCN_CHECKSTATUS_CHANGE (TCN_FIRST - 30)

/**
*  @class    ���б�ؼ��༭��־λ
*
*  @brief  ������ö����������ö��ֵʱ����BaseControl�е�TreeListCfg.cpp�и�ö��ֵ��ӱ�־λ
*/
enum ETreeListEditFlag
{
	eDiffColText = 1 << 9,			///< ����ɫ�ı���ʾ
	eNoneEdit = 1 << 10,			///< �ޱ༭			1024
	eNormalEdit = 1 << 11,			///< ��ͨ�༭			2048
	eValidEdit = 1 << 12,			///< ����༭			4096
	eFileNameEdit = 1 << 14,		///< �ļ����༭		16384
	eDateTimeEdit = 1 << 15,		///< ���ڱ༭��		32768
	eDropListCobEdit = 1 << 16,		///< ����ѡ���		65536
	eDropDownCobEdit = 1 << 17,		///< �ɱ༭������ѡ���  131072
	eCheckBoxEdit = 1 << 18,		///< ��ѡ��			262144
	eCheckBox3StateEdit = 1 << 19,	///< ��̬��ѡ��		524288
	eHyperLinkEdit = 1 << 20,		///< ������			1048576
	eAngleEdit = 1 << 21,			///< �Ƕ�			2097152
	eTreeComboEdit = 1 << 22,		///< ��������			4194304
	eProgressEdit = 1 << 23,		///< ������			8388608
	eTreeCheckComboEdit = 1 << 24,	///< ��������ѡ��		16777216
	eRangelEdit = 1 << 25,			///< ��Χ�༭�ؼ�		
	eAutoSearchCombo = 1 << 26,		///< �Զ�������Ͽ�	
	eTreeComboManualEdit = 1 << 27,		///< �ɱ༭����������
	eTreeCheckComboManualEdit = 1 << 28,		///< �ɱ༭����������ѡ��
};

/**
*  @class    У��༭��־λ;
*
*  @brief
*/
enum EValidEditControlFlag
{
	eVeDecimal = 1,			///< ��������С��
	eVeNegative = 1 << 1,	///< �������븺��
	eVeDotNum = 1 << 2,		///< ��������С��λ��
	eVeNoZero = 1 << 3,		///< ��ֹ����0	��CValidEditδʵ�֣�,��ģ̬�Ի�����ʹ��CValidEditEx��ʵ��
	eVeNoEmpty = 1 << 4,	///< ������Ϊ��	��CValidEditδʵ�֣�,��ģ̬�Ի�����ʹ��CValidEditEx��ʵ��
	eVePreZero = 1 << 5,	///< ����ǰ����
	eVeNotPositive = 1 << 6,///< ��ֹ��������
	eVeDigitLimit = 1 << 7,	///< ��������λ��
	eVeLimitLength = 1 << 8,///< �������볤��
	eVeLimitRange = 1 << 9, ///< �������뷶Χ
};

/**
*  @class    ���ڸ�ʽ;
*
*  @brief
*/
enum EDateTimeEditFlag
{
	eDateSlashYMD = 1,			///< б�������� 2016/1/26
	eDateChineseYMD = 1 << 1,	///< ���������� 2016��1��26��
	eDateDashYMD = 1 << 2,		///< ���������� 2016-1-26
	eDateYear = 1 << 3,			///< �� 2017
};

enum ETreeComboEditControlFlag
{
	eTreeHasSelAll = 1,			///< �Զ����ȫѡ
	eTreeHasNoLimit = 1 << 1,	///< �Զ���Ӳ���
	eTreeAutoWidth = 1 << 2,	///< �Զ������������
	eTreeSelNotByText = 1 << 3,    ///< ѡ���Ƿ�ͨ������ֵ
};

/**
*  @class    ��������־λ;
*
*  @brief
*/
enum EProgressControlFlag
{
	ePrgShowText = 1,			///< ��ʾ��������
};

#define LIST_HEAD_HEIGHT	28	///< ���οؼ���ͷ��
#define LIST_ROW_HEIGHT		26	///< ���οؼ��и�


struct TabInfo
{
	CString tabName;
	CWnd *pChildren;
	CRect rectSize;
	CRect closeBtPos;
	CRect iconPos;
	CRect txtPos;
	bool bSelected;
	bool bCloseBtnHightLight;
};
typedef std::vector<TabInfo> TabInfoList;

struct TabNotify : public NMHDR
{
	TabInfo tabInfo;
};

struct ComboCheckBoxNotify : public NMHDR
{
	int triggleItemIndex;	// ��ǰ�¼�����ʱ�����������item
};
