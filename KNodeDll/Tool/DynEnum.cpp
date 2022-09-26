#include "StdAfx.h"
#include "DynEnum.h"
#include "../Sdk/XmlDocument.h"

namespace CommBase
{
	///< ����ö��������ϢMap
	static CString s_strLastError;
	static EnumTextInfoMap s_enumTextInfoMap;

	void ParseEnumInfo(CXmlElement* pElement, EnumTextInfoArray& enumTextInfos)
	{
		// ��������EnumInfo�ڵ�
		CXmlElements *pEnumInfoElms = pElement->GetChildElements();
		size_t nElmCount = pEnumInfoElms->GetCount();
		for (size_t i = 0; i < nElmCount; ++i)
		{
			CXmlElement *pEnumElmInfo = pEnumInfoElms->GetAt(i);

			EnumTextInfo info;
			info.Value = _ttoi(pEnumElmInfo->GetAttrValue(L"Value"));
			info.Text = pEnumElmInfo->GetAttrValue(L"Text");
			// show���������������Ĭ�϶�ȡtext����
			info.Show = pEnumElmInfo->GetAttrValue(L"Show", info.Text);

			enumTextInfos.push_back(info);
		}
	}

	bool ParseEnum(CXmlElement* pElement)
	{
		// ��������Enum�ڵ�
		CXmlElements *pEnumElms = pElement->GetChildElements();
		size_t nElmCount = pEnumElms->GetCount();
		for (size_t i = 0; i < nElmCount; ++i)
		{
			CXmlElement *pEnumElm = pEnumElms->GetAt(i);
			CString strEnumName = pEnumElm->GetAttrValue(L"Name");

			// ���ö����Ϣ�Ƿ�����ظ�
			EnumTextInfoArray& enumTextInfos = s_enumTextInfoMap[strEnumName];
			if (!enumTextInfos.empty())
			{
				// ���ڸ�Ϊ�׳��쳣
				CString strError;
				strError.Format(L"ö��(%s)��Ϣ�������ظ����ã�", strEnumName);
				s_strLastError = strError;
				continue;
			}

			// ����EnumInfo�ڵ�
			ParseEnumInfo(pEnumElm, enumTextInfos);
		}

		return true;
	}

	EnumTextInfoArray* GetInfosByEnumName(const CString& strEnumName)
	{
		// ö����
		CString strRealName = strEnumName;

		// �Ȳ���ָ������ö����
		EnumTextInfoMapIter findIter = s_enumTextInfoMap.find(strRealName);
		if (findIter != s_enumTextInfoMap.end())
			return &(findIter->second);

		return NULL;
	}

	CDynEnum::CDynEnum()
	{
	}

	CDynEnum::~CDynEnum()
	{
	}

	CString CDynEnum::Enum2Text(const CString& strEnumName, int nEnumValue)
	{
		EnumTextInfoArray *pInfos = GetInfosByEnumName(strEnumName);
		if (NULL == pInfos)
			return L"";

		// ��������ö���ַ���
		EnumTextInfoArrayIter endIter = pInfos->end();
		for (EnumTextInfoArrayIter iter = pInfos->begin(); iter != endIter; ++iter)
		{
			if (iter->Value == nEnumValue)
				return iter->Text;
		}

		return L"";
	}

	CString CDynEnum::Enum2Show(const CString& strEnumName, int nEnumValue)
	{
		EnumTextInfoArray *pInfos = GetInfosByEnumName(strEnumName);
		if (NULL == pInfos)
			return L"";

		// ��������ö��ֵ
		EnumTextInfoArrayIter endIter = pInfos->end();
		for (EnumTextInfoArrayIter iter = pInfos->begin(); iter != endIter; ++iter)
		{
			if (iter->Value == nEnumValue)
				return iter->Show;
		}

		return L"";
	}

	int CDynEnum::Text2Enum(const CString& strEnumName, const CString& strEnumText)
	{
		EnumTextInfoArray *pInfos = GetInfosByEnumName(strEnumName);
		if (NULL == pInfos)
			return 0;

		// ��������ö���ַ���
		EnumTextInfoArrayIter endIter = pInfos->end();
		for (EnumTextInfoArrayIter iter = pInfos->begin(); iter != endIter; ++iter)
		{
			if (iter->Text == strEnumText)
				return iter->Value;
		}

		return 0;
	}

	int CDynEnum::Show2Enum(const CString& strEnumName, const CString& strEnumShow)
	{
		EnumTextInfoArray *pInfos = GetInfosByEnumName(strEnumName);
		if (NULL == pInfos)
			return 0;

		// ��������ö����ʾ�ַ���
		EnumTextInfoArrayIter endIter = pInfos->end();
		for (EnumTextInfoArrayIter iter = pInfos->begin(); iter != endIter; ++iter)
		{
			if (iter->Show == strEnumShow)
				return iter->Value;
		}

		return 0;
	}

	CString CDynEnum::Show2Text(const CString& strEnumName, const CString& strEnumShow)
	{
		EnumTextInfoArray *pInfos = GetInfosByEnumName(strEnumName);
		if (NULL == pInfos)
			return L"";

		// ��������ö����ʾ�ַ���
		EnumTextInfoArrayIter endIter = pInfos->end();
		for (EnumTextInfoArrayIter iter = pInfos->begin(); iter != endIter; ++iter)
		{
			if (iter->Show == strEnumShow)
				return iter->Text;
		}

		return L"";
	}

	CString CDynEnum::Text2Show(const CString& strEnumName, const CString& strEnumText)
	{
		EnumTextInfoArray *pInfos = GetInfosByEnumName(strEnumName);
		if (NULL == pInfos)
			return L"";

		// ��������ö���ַ���
		EnumTextInfoArrayIter endIter = pInfos->end();
		for (EnumTextInfoArrayIter iter = pInfos->begin(); iter != endIter; ++iter)
		{
			if (iter->Text == strEnumText)
				return iter->Show;
		}

		return L"";
	}

	EnumTextInfoArray CDynEnum::GetEnumInfoArray(const CString& strEnumName)
	{
		EnumTextInfoArray *pInfos = GetInfosByEnumName(strEnumName);
		if (NULL != pInfos)
			return *pInfos;

		return EnumTextInfoArray();
	}

	bool CDynEnum::LoadEnumConfig(const CString& strXmlFile)
	{
		CXmlDocument xmlDoc;
		if (!xmlDoc.LoadFile(strXmlFile, fmtXML))
		{
			s_strLastError = L"����ö�������ļ�ʧ�ܣ�";
			return false;
		}

		CXmlElement* pRootElm = xmlDoc.GetElementRoot();
		if (NULL == pRootElm)
			return false;

		// ����Enum�ڵ�
		if (!ParseEnum(pRootElm))
			return false;

		return true;
	}

	CString CDynEnum::GetLastError()
	{
		return s_strLastError;
	}
}