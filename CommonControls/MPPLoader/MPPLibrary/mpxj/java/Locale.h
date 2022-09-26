#pragma once

///////////////////////////////////////////////////////////////////////////////////////////////////
// ���ػ�
//
class Locale
{
public:
	Locale(char const* _Locale);
	static Locale* getDefault();

	LPCTSTR getLanguageCode();

	LPCTSTR getNationCode();

private:
	CString _langCode;		// ���Դ���
	CString _nationCode;	// ���Ҵ���
	int _nationNumber;		// ���ұ���

	static std::auto_ptr<Locale> _default;
};