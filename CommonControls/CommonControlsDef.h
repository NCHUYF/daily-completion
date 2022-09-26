// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
// ��ı�׼�������� DLL �е������ļ��������������϶���� PROJECTLOADER_EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
// �κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ
// PROJECTLOADER_API ������Ϊ�Ǵ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�

#define ID_YES							1
#define ID_ALLYES						2
#define ID_NO							3
#define ID_ALLNO						4

#ifdef COMMONCONTROLS_MODULE
#define COMMONCONTROLS_API __declspec(dllexport)
#else
#define COMMONCONTROLS_API __declspec(dllimport)
#ifdef DEBUG
#pragma comment(lib, "CommonControlsd.lib")
#else
#pragma comment(lib, "CommonControls.lib")
#endif
#endif

#include "ProgressBar/IProgress.h"
#include "ScreenShot/ScreenShot.h"
#include "ResourceOverride/ResourceOverride.h"

#include "Control/ControlDefine.h"
#include "Control/Edit/AngleEdit.h"
#include "Control/Edit/ValidEdit.h"
#include "Control/Edit/ValidEditEx.h"
#include "Control/Edit/ScaleEdit.h"
#include "Control/Edit/EditXpVer.h"
#include "Control/Edit/NumEdit.h"
#include "Control/Edit/MoveBar.h"
#include "Control/Edit/EditValue.h"
#include "control/Edit/CCustomCEdit.h"
#include "Control/ComboBox/TreeComboBox.h"
#include "Control/ComboBox/AutoWidthComboBox.h"
#include "Control/ComboBox/CustomComboBox.h"
#include "Control/ComboBox/ComboAnyOne.h"
#include "Control/ComboBox/ComboCheckBoxs.h"
#include "Control/Static/ColorStatic.h"
#include "Control/Split/SplitCtrl.h"
#include "Control/TreeList/TreeListCfg.h"
#include "Control/TreeList/TreeListCtrl.h"
#include "Control/TreeList/StandardTreeListCtrl.h"
#include "Control/TreeList/IEventHandle.h"
#include "Control/TabContainer/EditableTabCtrl.h"
#include "Control/TabContainer/InputEdit.h"
#include "Control/TabContainer/TabContainer.h"
#include "control/DefImage.h"
#include "Control/PicContainer/ThumbnailButton.h"
#include "Control/PicContainer/ThumbNailControl.h"
#include "Control/HyperLink/HyperLink.h"
#include "Control/Timeline/TimelineCtrlDef.h"

#include "DialogManager/TabPagedDialog.h"
#include "DialogManager/BatchOperDlg.h"
#include "DialogManager/MSRegDlg.h"
#include "DialogManager/BaseDialog.h"

#include "LockClient/LockClientService.h"
#include "ScreenRecording/ScreenRecorder.h"

// MPP��������ļ�
//using namespace BwProj::toolkit;
#include "MPPLoader/Toolkit/include/Toolkit.h"
#include "MPPLoader/MPPLibrary/JavaJREImpl.h"
#include "MPPLoader/MPPLibrary/mpxj/mpplibrary.h"

// BCG��������ļ�
#include "BCGControlEx/BCGControlsExportDef.h"

using namespace PlatformKernel;

#include "Property/PropertyDef.h"

#include "GanttCtrl/GanttDef.h"

// unity�ӿ�
#include "UnityViewer/UnityViewerDef.h"