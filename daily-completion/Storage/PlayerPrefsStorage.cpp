#include "pch.h"
#include "PlayerPrefsStorage.h"

PlayerPrefsStorage::PlayerPrefsStorage()
{
	_strDataPath = CPathConfig::GetSystemPath();
}

void PlayerPrefsStorage::SaveInt(std::string key, int val)
{
	// д���ļ���;
	if (!_doc.LoadFile(_strDataPath, fmtXMLUTF8))
	{
		ASSERT(FALSE);
		return;
	}

	auto pRoot = _doc.GetElementRoot();
}

int PlayerPrefsStorage::LoadInt(std::string key)
{
	return 0;
}