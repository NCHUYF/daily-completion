#pragma once

#include "..\TaskField.h"

/**
 * Task fields grouped into logical collections.
 * ÿ����������ֵΪTF_START���������ж�����������
 */
class TaskFieldLists
{
public:
	const static TaskField CUSTOM_COST[];

	const static TaskField CUSTOM_DATE[];

	const static TaskField CUSTOM_DURATION[];

	const static TaskField CUSTOM_FLAG[];

	const static TaskField CUSTOM_FINISH[];

	const static TaskField CUSTOM_NUMBER[];

	const static TaskField CUSTOM_START[];

	const static TaskField CUSTOM_TEXT[];

	const static TaskField CUSTOM_OUTLINE_CODE[];

	const static TaskField ENTERPRISE_COST[];

	const static TaskField ENTERPRISE_DATE[];

	const static TaskField ENTERPRISE_DURATION[];

	const static TaskField ENTERPRISE_FLAG[];

	const static TaskField ENTERPRISE_NUMBER[];

	const static TaskField ENTERPRISE_TEXT[];

	const static TaskField ENTERPRISE_CUSTOM_FIELD[];

	const static TaskField BASELINE_COSTS[];

	const static TaskField BASELINE_DURATIONS[];

	const static TaskField BASELINE_ESTIMATED_DURATIONS[];

	const static TaskField BASELINE_STARTS[];

	const static TaskField BASELINE_ESTIMATED_STARTS[];

	const static TaskField BASELINE_FINISHES[];

	const static TaskField BASELINE_ESTIMATED_FINISHES[];

	const static TaskField BASELINE_WORKS[];

	// �������鳤��
	static int ArrayLength(TaskField* fields);

};