// CutPath.h: CutPath DLL 的主要標頭檔
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// 主要符號
#include "DlgParam.h"

// CCutPathApp
// 此類別的實作請參閱 CutPath.cpp
//

class CCutPathApp : public CWinApp
{
public:
	CCutPathApp();
	~CCutPathApp();
// 覆寫
public:
	virtual BOOL InitInstance();

	CDlgParam m_dlgParam;//teset
	DECLARE_MESSAGE_MAP()
};
