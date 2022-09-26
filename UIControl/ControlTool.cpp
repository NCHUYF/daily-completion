#include "stdafx.h"
#include "ControlTool.h"

namespace ControlUI
{
	BEGIN_DYN_ENUM(ETreeListEditFlag)
	{
		{ eNoneEdit, _T("�ޱ༭") },
		{ eNormalEdit, _T("��ͨ�༭") },
		{ eValidEdit, _T("����༭") },
		{ eFileNameEdit, _T("�ļ����༭") },
		{ eDateTimeEdit, _T("���ڱ༭��") },
		{ eDropListCobEdit, _T("����ѡ���") },
		{ eDropDownCobEdit, _T("�ɱ༭������ѡ���") },
		{ eCheckBoxEdit, _T("��ѡ��") },
		{ eCheckBox3StateEdit, _T("��̬��ѡ��") },
		{ eHyperLinkEdit, _T("������") },
		{ eAngleEdit, _T("�Ƕ�") },
		{ eTreeComboEdit, _T("��������") },
		{ eProgressEdit, _T("������") },
		{ eTreeCheckComboEdit, _T("��������ѡ��") },
		{ eRangelEdit, _T("��Χ�༭�ؼ�") },
		{ eAutoSearchCombo, _T("�Զ�������Ͽ�") },
		{ eTreeComboManualEdit, _T("�ɱ༭����������") },
		{ eTreeCheckComboManualEdit, _T("�ɱ༭����������ѡ��") },
		{ NULL, NULL }
	}
	END_DYN_ENUM(ETreeListEditFlag);

	int ControlUI::CControlTool::GetOptionEnum(const CString& str)
	{
		//��Option�ؼ��ֶ�ӦֵΪ0��Ϊ��ʱ
		if (str == L"0" || str == L"")
			return 0;

		std::vector<CString> ArrStr;
		CStringTool::SplitString((LPCTSTR)str, ArrStr, L"|");

		//��ȡ��һ���ؼ���
		int nEditFlag = TextToETreeListEditFlag(ArrStr.at(0));
		int nSubFlag = 0;
		for (int i = 1; i < (int)ArrStr.size(); ++i)
		{
			switch (nEditFlag)
			{
				//������Ϊ�༭��
			case eNoneEdit:
			case eValidEdit:
			case eRangelEdit:
			{
				//���������༭��ר�ñ�־λ
				nSubFlag += TextToEValidEditControlFlag(ArrStr.at(i));
				break;
			}
			//������Ϊ��������
			case eTreeComboEdit:
			case eTreeComboManualEdit:
			{
				//��������������ר�ñ�־λ
				nSubFlag += TextToETreeComboEditControlFlag(ArrStr.at(i));
				break;
			}
			//������Ϊ���ڱ༭��
			case eDateTimeEdit:
			{
				//��������������ר�ñ�־λ
				nSubFlag += TextToEDateTimeEditFlag(ArrStr.at(i));
				break;
			}
			//������Ϊ������
			case eProgressEdit:
			{
				//��������������ר�ñ�־λ
				nSubFlag += TextToEProgressControlFlag(ArrStr.at(i));
				break;
			}
			case eTreeCheckComboEdit:
			{
				//����������������ѡ���־λ
				nSubFlag += TextToETreeComboEditControlFlag(ArrStr.at(i));
				break;
			}
			default:
				break;
			}
		}
		return nEditFlag + nSubFlag;
	}
}