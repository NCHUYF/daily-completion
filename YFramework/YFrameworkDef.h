// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
// ��ı�׼�������� DLL �е������ļ��������������϶���� PROJECTLOADER_EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
// �κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ
// PROJECTLOADER_API ������Ϊ�Ǵ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�

#ifdef YFRAMEWORK_MODULE
#define YFRAMEWORK_API __declspec(dllexport)
#else
#define YFRAMEWORK_API __declspec(dllimport)
#ifdef DEBUG
#pragma comment(lib, "YFrameworkd.lib")
#else
#pragma comment(lib, "YFramework.lib")
#endif
#endif

// ͷ�ļ�����
#include "Delegate/Delegate.h"
#include "Singleton/BaseSingleton.h"
#include "IOCContainer/IOCContainer.h"

