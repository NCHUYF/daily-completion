//*****************************************************
//    
//    @copyright      �����ά�����
//    @version        v4.0
//    @file           PlatformKernel.h
//    @author         JZL
//    @data           2017/11/27 10:13
//    @brief          ƽ̨�ӿ�ͷ�ļ�
//
//*****************************************************

#pragma once

// ���嵼��API
#ifdef CONTROLUI_MODULE
#define CONTROL_UI __declspec(dllexport)
#else
#define CONTROL_UI __declspec(dllimport)
#ifdef DEBUG
#pragma comment(lib, "UIControld.lib")
#else
#pragma comment(lib, "UIControl.lib")
#endif
#endif

// �ַ�������
typedef std::vector<CString> CStringVector;
typedef CStringVector::iterator CStringVectorIter;


#include "ControlDefine.h"
#include "ControlTool.h"

#include "Edit\AngleEdit.h"
#include "Edit\ValidEdit.h"
#include "Edit\ValidEditEx.h"
#include "Edit\ScaleEdit.h"
#include "Edit\EditXpVer.h"
#include "Edit\NumEdit.h"
#include "Edit\EditValue.h"
#include "Edit\CCustomCEdit.h"
#include "ComboBox\TreeComboBox.h"
#include "ComboBox\AutoWidthComboBox.h"
#include "ComboBox\CustomComboBox.h"
#include "ComboBox\ColorComboBox.h"
#include "ComboBox\ControlTool.h"
#include "ComboBox\ValidCombo.h"
#include "Split\SplitCtrl.h"
#include "TreeList\TreeListCfg.h"
#include "TreeList\TreeListCtrl.h"
#include "TreeList\StandardTreeListCtrl.h"
#include "TreeList\IEventHandle.h"