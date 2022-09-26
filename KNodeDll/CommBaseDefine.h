
#pragma once

// ������궨��
#define DECLARE_SINGLE_CLASS(ClassType)\
public:								   \
	static ClassType* Instance(); \
protected:							   \
	static ClassType* _pInstance;

// �������ʵ��
#define IMPL_SINGLE_CLASS(ClassType)   \
	ClassType* ClassType::_pInstance = NULL; \
	ClassType* ClassType::Instance()  \
{									   \
	if (_pInstance == NULL)			   \
	_pInstance = new ClassType();		   \
	return _pInstance;				   \
}


/*ע���������
*/
#define REGISTER_COMMAND(CmdName,CmdClass,CmdCheckMdl) \
void CmdFun##CmdClass()\
{\
	CmdClass cmdInstance;\
	cmdInstance.StartCommand(CmdName, CmdCheckMdl);\
	CLog::LogInfoV(L"ִ�����%s", CmdName);\
}\
class Register##CmdClass##Cmd \
{ \
	public: \
		Register##CmdClass##Cmd () \
		{\
		d3s::platform::command::CCommandMgr::GetCmdManager()->UnRegistExecuteFunc(CmdName);\
		d3s::platform::command::CCommandMgr::GetCmdManager()->RegistExecuteFunc(CmdName, CmdFun##CmdClass);\
		} \
		~Register##CmdClass##Cmd () \
		{\
		d3s::platform::command::CCommandMgr::GetCmdManager()->UnRegistExecuteFunc(CmdName);\
		} \
} Register##CmdClass##Cmd##Instance;

/*
* ע���������(��Ŀ�����ʽvoid CmdFunc(CString strCmd, ...)
*/
#define REGISTER_COMMAND_FUNCTION(CmdName,CmdFunc,CmdCheckMdl,...) \
void CmdFun##CmdName()\
{\
	if (CmdCheckMdl & eCheckProject || (CmdCheckMdl & eCheckViewPort))\
	{\
		if (CComandBase::GetState() != 1)\
		{\
			AfxGetMainWnd()->MessageBox(L"δ�ҵ����֤��Ϣ��", L"����", MB_ICONINFORMATION | MB_OK);\
			return;\
		}\
		d3s::views::tool::COperatorManager::GetInst()->SetActiveTool(NULL);\
		d3s::platform::frame::IMainFrame *pMainFrame = d3s::platform::frame::CFrameManager::GetMainFrame();\
		if (pMainFrame == NULL)\
			return;\
		d3s::views::view::IOsgViewPort *pActiveView = dynamic_cast<d3s::views::view::IOsgViewPort*>(pMainFrame->GetActiveViewPort());\
		if (pActiveView == NULL)\
		{\
			::MessageBox(GetActiveWindow(), L"��򿪹��̺��ټ���������", L"��ʾ", MB_OK|MB_ICONINFORMATION);\
			return; \
		}\
		if (!(CmdCheckMdl & eNoEmpSelection))\
		{\
			CommBase::SafeEmtpyAllSelect();\
		}\
	}\
	CmdFunc(L#CmdName, ##__VA_ARGS__);\
	CLog::LogInfoV(L"ִ�����%s", L#CmdName);\
}\
class Register##CmdName \
{ \
	public: \
		Register##CmdName() \
		{\
		d3s::platform::command::CCommandMgr::GetCmdManager()->UnRegistExecuteFunc(L#CmdName);\
		d3s::platform::command::CCommandMgr::GetCmdManager()->RegistExecuteFunc(L#CmdName, CmdFun##CmdName);\
		} \
		~Register##CmdName() \
		{\
		d3s::platform::command::CCommandMgr::GetCmdManager()->UnRegistExecuteFunc(L#CmdName);\
		} \
} Register##CmdName##Instance;