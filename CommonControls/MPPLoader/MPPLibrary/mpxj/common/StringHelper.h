#pragma once

class StringHelper
{
public:
	// �ַ�������
	static int lastIndexOf(CString str, CString find);

	// ת���ɵ��ֽ��ַ���
	static std::string w2String(LPCTSTR str);

	static CString Reverse(LPCTSTR str);

	static CString toString(int value);
	static CString toString(double value);
};