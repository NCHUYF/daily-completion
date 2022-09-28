#include "pch.h"
#include "AchievementSystem.h"
#include "../Model/GameModel.h"

void AchievementSystem::Init()
{
	GetModel<GameModel>()->_cnt.RegisterChangedEvent([&](int oldVal, int val)
	{
		if (oldVal > 5 && val == 5)
		{
			MessageBox(::GetActiveWindow(), L"�����ɾ�[��ɱ]", L"��ϲ��", MB_OK);
		}
		else if (oldVal > 0 && val == 0)
		{
			MessageBox(::GetActiveWindow(), L"�����ɾ�[ɱ����]", L"��ϲ��", MB_OK);
		}
	});
}
