// CutPath.cpp: 定義 DLL 的初始化常式。
//

#include "pch.h"
#include "framework.h"
#include "CutPath.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

HINSTANCE g_hResource = NULL;

static AFX_EXTENSION_MODULE CutPathDLL = { NULL, NULL };//hModule(模組), hResource(資源)

CDlgParam g_DlgParam;

void ChangeResource(BOOL bChange)
{
	static CPtrArray ayHINST;
	static int iCutPath = 0;
	if (bChange)
	{
		HINSTANCE *pHInst = new HINSTANCE;
		*pHInst = AfxGetResourceHandle();
		AfxSetResourceHandle((g_hResource) ? g_hResource : CutPathDLL.hModule);
		ayHINST.Add(pHInst);
		iCutPath++;
	}
	else
	{
		HINSTANCE *pHInst;
		pHInst = (HINSTANCE*)ayHINST.GetAt(iCutPath - 1);
		AfxSetResourceHandle(*pHInst); // restore the old resource chain
		iCutPath--;
	}

	if (iCutPath == 0)
	{
		int iSize = ayHINST.GetSize();
		for (int i = 0; i < iSize; i++)
		{
			HINSTANCE *pHInst;
			pHInst = (HINSTANCE*)ayHINST.GetAt(i);
			if (pHInst)
				delete pHInst;
		}
		ayHINST.RemoveAll();
	}
}



__declspec(dllexport) void PASCAL SetParametersDialog()
{
	CDlgParam dlg;

	ChangeResource(TRUE);

	INT_PTR nResponse = dlg.DoModal();

	g_DlgParam = dlg;

	int i = 5;

	ChangeResource(TRUE);
}

__declspec(dllexport) bool PASCAL GetFirstCutPath(double* pCoorX, double* pCoorZ)
{
	return g_DlgParam.GetFirstCutPoint (pCoorX, pCoorZ);
}

__declspec(dllexport) bool PASCAL GetNextCutPath(double* pCoorX, double* pCoorZ)
{
	return g_DlgParam.GetNextCutPoint (pCoorX, pCoorZ);//res
}
//
//TODO:  如果這個 DLL 是動態地對 MFC DLL 連結，
//		那麼從這個 DLL 匯出的任何會呼叫
//		MFC 內部的函式，都必須在函式一開頭加上 AFX_MANAGE_STATE
//		巨集。
//
//		例如: 
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// 此處為正常函式主體
//		}
//
//		這個巨集一定要出現在每一個
//		函式中，才能夠呼叫 MFC 的內部。這意味著
//		其必須是函式內的第一個陳述式
//		，甚至必須在任何物件變數宣告前面
//		，因為它們的建構函式可能會產生對 MFC
//		DLL 內部的呼叫。
//
//		請參閱 MFC 技術提示 33 和 58 中的
//		詳細資料。
//

// CCutPathApp

BEGIN_MESSAGE_MAP(CCutPathApp, CWinApp)
END_MESSAGE_MAP()


// CCutPathApp 建構

CCutPathApp::CCutPathApp()
{
	// TODO:  在此加入建構程式碼，
	// 將所有重要的初始設定加入 InitInstance 中
	


}

CCutPathApp::~CCutPathApp()
{
	AfxTermExtensionModule(CutPathDLL);
}


// 唯一一個 CCutPathApp 物件

CCutPathApp theApp;


// CCutPathApp 初始化

BOOL CCutPathApp::InitInstance()
{
	CWinApp::InitInstance();

	AfxInitExtensionModule(CutPathDLL, m_hInstance);

	new CDynLinkLibrary(CutPathDLL);

	return TRUE;
}
