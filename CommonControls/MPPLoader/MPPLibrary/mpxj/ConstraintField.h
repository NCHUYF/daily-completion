#pragma once

#include "FieldType.h"

/**
 * Instances of this type represent constraint fields.
 */
enum ConstraintField
{
	CF_UNIQUE_ID,//(DataType.INTEGER),
	CF_TASK1,//(DataType.INTEGER),
	CF_TASK2,//(DataType.INTEGER);
	CF_FINISH,
};

// ��ȡö��ֵ��Ӧ�ĸ�����Ϣ
class ConstraintFieldClass : public FieldType
{
public:
	static FieldType* getInstance(int type);
};