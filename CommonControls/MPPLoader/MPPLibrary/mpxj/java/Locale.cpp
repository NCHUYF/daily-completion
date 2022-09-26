#include "stdafx.h"
#include "Locale.h"
#include <locale.h>

///////////////////////////////////////////////////////////////////////////////////////////////////
// Locale
//
std::auto_ptr<Locale> Locale::_default;

Locale::Locale(char const* _Locale)
{
	// ��������
	char* loc = setlocale(LC_ALL, _Locale);

	// ���Դ���_���Ҵ���.����
	char* nextToken = NULL;
	char* langToken = strtok_s(loc, "_", &nextToken);
	char* natiToken = strtok_s(NULL, ".", &nextToken);

	_langCode = langToken;
	_nationCode = natiToken;
	_nationNumber = atol(nextToken);
}

Locale* Locale::getDefault()
{
	if (!_default.get()) {
		_default.reset(new Locale(""));
	}
	return _default.get();
}

LPCTSTR Locale::getLanguageCode()
{
	return _langCode;
}

LPCTSTR Locale::getNationCode()
{
	return _nationCode;
}