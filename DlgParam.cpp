// DlgParam.cpp: 實作檔案
//

#include "pch.h"
#include "CutPath.h"
#include "DlgParam.h"
#include "afxdialogex.h"
#include <vector>


#define RGB_WHITE		RGB (255, 255, 255)
#define RGB_BLUE		RGB (0, 0, 255)
#define RGB_LIGHTGRAY	RGB (185, 182, 185)
#define RGB_ORANGE		RGB (255, 97, 0)
#define RGB_GRAY		RGB (85, 82, 85)
#define RGB_BLACK		RGB	(0, 0, 0)
#define RGB_RED			RGB(255, 0, 0)
#define MIN_VALUE		 1e-9


// DlgParam 對話方塊
extern AFX_EXTENSION_MODULE CutPathDLL;

IMPLEMENT_DYNAMIC(CDlgParam, CDialogEx)

CDlgParam::CDlgParam(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_PARAM, pParent)
	, m_dZDepth(0)
	, m_dLayerHeight(0)
	, m_dCuttingSpacing(0)
	, m_dUpperWidth(0)
	, m_dLowerWidth(0)
	, m_dZPitchRatio5(100)
	, m_dZPitchRatio10(100)
	, m_dZPitchRatio15(100)
	, m_dZPitchRatio20(100)
	, m_dZPitchRatio25(100)
	, m_dZPitchRatio30(100)
	, m_dZPitchRatio35(100)
	, m_dZPitchRatio40(100)
	, m_dZPitchRatio45(100)
	, m_dZPitchRatio50(100)
	, m_dZPitchRatio55(100)
	, m_dZPitchRatio60(100)
	, m_dZPitchRatio65(100)
	, m_dZPitchRatio70(100)
	, m_dZPitchRatio75(100)
	, m_dZPitchRatio80(100)
	, m_dZPitchRatio85(100)
	, m_dZPitchRatio90(100)
	, m_dZPitchRatio95(100)
	, m_dZPitchRatio100(100)
	, m_iFirstPathCnt(1)
	, m_iLastPathCnt(1)
	, m_iEdgeKeepCnt(1)
	, m_iDigits(6)
	, m_bIntersect(FALSE)
	, m_dIntersectRatio(0)
{
	m_iCurPath = 0;

	m_iDataArraySize = 0;

	m_bReverse = false;

	ReadINI();
}

CDlgParam::~CDlgParam()
{
}

void CDlgParam::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_Z_DEPTH, m_dZDepth);
	DDX_Text(pDX, IDC_EDIT_LAYER_HEIGHT, m_dLayerHeight);
	DDX_Text(pDX, IDC_EDIT_CUTTING_SPACING, m_dCuttingSpacing);
	DDX_Text(pDX, IDC_EDIT_UPPER_WIDTH, m_dUpperWidth);
	DDX_Text(pDX, IDC_EDIT_LOWER_WIDTH, m_dLowerWidth);
	DDX_Text(pDX, IDC_EDIT_Z_PITCH_RATIO_5, m_dZPitchRatio5);
	DDX_Text(pDX, IDC_EDIT_Z_PITCH_RATIO_10, m_dZPitchRatio10);
	DDX_Text(pDX, IDC_EDIT_Z_PITCH_RATIO_15, m_dZPitchRatio15);
	DDX_Text(pDX, IDC_EDIT_Z_PITCH_RATIO_20, m_dZPitchRatio20);
	DDX_Text(pDX, IDC_EDIT_Z_PITCH_RATIO_25, m_dZPitchRatio25);
	DDX_Text(pDX, IDC_EDIT_Z_PITCH_RATIO_30, m_dZPitchRatio30);
	DDX_Text(pDX, IDC_EDIT_Z_PITCH_RATIO_35, m_dZPitchRatio35);
	DDX_Text(pDX, IDC_EDIT_Z_PITCH_RATIO_40, m_dZPitchRatio40);
	DDX_Text(pDX, IDC_EDIT_Z_PITCH_RATIO_455, m_dZPitchRatio45);
	DDX_Text(pDX, IDC_EDIT_Z_PITCH_RATIO_50, m_dZPitchRatio50);
	DDX_Text(pDX, IDC_EDIT_Z_PITCH_RATIO_55, m_dZPitchRatio55);
	DDX_Text(pDX, IDC_EDIT_Z_PITCH_RATIO_60, m_dZPitchRatio60);
	DDX_Text(pDX, IDC_EDIT_Z_PITCH_RATIO_65, m_dZPitchRatio65);
	DDX_Text(pDX, IDC_EDIT_Z_PITCH_RATIO_70, m_dZPitchRatio70);
	DDX_Text(pDX, IDC_EDIT_Z_PITCH_RATIO_75, m_dZPitchRatio75);
	DDX_Text(pDX, IDC_EDIT_Z_PITCH_RATIO_80, m_dZPitchRatio80);
	DDX_Text(pDX, IDC_EDIT_Z_PITCH_RATIO_85, m_dZPitchRatio85);
	DDX_Text(pDX, IDC_EDIT_Z_PITCH_RATIO_90, m_dZPitchRatio90);
	DDX_Text(pDX, IDC_EDIT_Z_PITCH_RATIO_95, m_dZPitchRatio95);
	DDX_Text(pDX, IDC_EDIT_Z_PITCH_RATIO_100, m_dZPitchRatio100);
	DDX_Text(pDX, IDC_EDIT_FIRST_PATH_CNT, m_iFirstPathCnt);
	DDX_Text(pDX, IDC_EDIT_LAST_PATH_CNT, m_iLastPathCnt);
	DDX_Control(pDX, IDC_EDIT__EDGE_KEEP_CNT, m_editEdgeKeepCnt);
	DDX_Control(pDX, IDC_STATIC_EDGE_KEEP_CNT, m_staticEdgeKeepCnt);
	DDX_Control(pDX, IDC_CHECK_INTERSECT, m_chkIntersect);
	DDX_Text(pDX, IDC_EDIT__EDGE_KEEP_CNT, m_iEdgeKeepCnt);
	DDX_Text(pDX, IDC_EDIT_IDIGITS, m_iDigits);
	DDX_Check(pDX, IDC_CHECK_INTERSECT, m_bIntersect);
	DDX_Control(pDX, IDC_EDIT_UPPER_WIDTH, m_editUpperW);
	DDX_Control(pDX, IDC_EDIT_LOWER_WIDTH, m_editLowerW);
	DDX_Control(pDX, IDC_EDIT_FIRST_PATH_CNT, m_editFirstPathCnt);
	DDX_Control(pDX, IDC_EDIT_LAST_PATH_CNT, m_editLastPathCnt);
	DDX_Text(pDX, IDC_EDIT_INTERSECT_RATIO, m_dIntersectRatio);
}


BEGIN_MESSAGE_MAP(CDlgParam, CDialogEx)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTON_APPLY, &CDlgParam::OnBnClickedButtonApply)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_CHECK_INTERSECT, &CDlgParam::OnBnClickedCheckIntersect)
END_MESSAGE_MAP()


// DlgParam 訊息處理常式


BOOL CDlgParam::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	ReadINI();

	UpdateData(FALSE);

	CWnd* pPictureCtrl = GetDlgItem(IDC_PICTURE_PAINTINGAREA);
	CWnd* pGrapthCtrl = GetDlgItem(IDC_PICTURE_INTERSECT_RATIO);

	// 獲得客戶區域大小
	CRect rectClient;
	pPictureCtrl->GetClientRect(&rectClient);
	m_iClientW = rectClient.Width();
	m_iClientH = rectClient.Height();

	// 計算預留區域(上下左右各預留 5 %)
	GetReservedRect();	
	
	//計算 Inflat 後的 Boundingbox (上下左右各預留 5 %)
	GetInflatBoundingBox();

	// 計算 Client Rect Ratio 並設定 D2I 映射
	GetClientRectRatio();

	// 根據 pithch 計算畫面分割幾個區塊
	GetBlockCount();

	// 刪除文件
	/*DeleteCutPathFile();*/

	// 開啟文件
	OpenCutPathFile();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX 屬性頁應傳回 FALSE
}


void CDlgParam::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 在此加入您的訊息處理常式程式碼
					   // 不要呼叫圖片訊息的 CDialogEx::OnPaint()

	// 取得DC
	CWnd* pPictureCtrl = GetDlgItem(IDC_PICTURE_PAINTINGAREA);
	CDC* pCtrlDC = pPictureCtrl->GetDC();
	

	// 繪製背景
	CRect rectClient;
	pPictureCtrl->GetClientRect(&rectClient);
	pCtrlDC->FillSolidRect(&rectClient, RGB(255, 255, 255));

	// 下列 function 會 change pen, 所以先將 dc 內的 pen 儲存
	// 繪製梯形
	DrawTrapezoid(pCtrlDC);
	
	// 繪製基準線(x=0, y=0)
	DrawOriginLine(pCtrlDC);

	// 繪製格線
	DrawGridLines(pCtrlDC);
	
	// 繪製切割道
	DrawCutPath(pCtrlDC);

	// 釋放 DC
	pPictureCtrl->ReleaseDC(pCtrlDC);
}

void CDlgParam::OnBnClickedButtonApply()
{
	UpdateData(TRUE);

	// 計算預留區域(上下左右各預留 5 %)
	GetReservedRect();

	// 計算 Inflat 後的 Boundingbox (上下左右各預留 5 %)
	GetInflatBoundingBox();

	// 計算 Client Rect Ratio 並設定 D2I 的映射
	GetClientRectRatio();

	// 根據 pithch 計算畫面分割幾個區塊
	GetBlockCount();

	// 參數檢查
	if(CheckParam())
		Invalidate();	// 輸入參數合理的話更新畫面

	// 刪除文件
	/*DeleteCutPathFile();*/

	// 開啟文件
	OpenCutPathFile();

	WriteINI();

}

void CDlgParam::D2ISetUp(CPoint dotLT, double dCoorLT_X, double dCoorLT_Y, double dRatioX, double dRatioY)
{
	m_dotRectLT.x = dotLT.x;
	m_dotRectLT.y = dotLT.y;

	m_dCoorLT_X = dCoorLT_X;
	m_dCoorLT_Y = dCoorLT_Y;

	m_dRatioX = dRatioX;
	m_dRatioY = dRatioY;
}

void CDlgParam::D2I(double dCoorX, double dCoorY, CPoint &dotResult)
{
	double dX = (dCoorX - m_dCoorLT_X) * m_dRatioX;
	double dY = (dCoorY - m_dCoorLT_Y) * m_dRatioY;

	dotResult.x = m_dotRectLT.x + (int)dX;
	dotResult.y = m_dotRectLT.y - (int)dY;
}

double CDlgParam::GetCutLayerWidth(double dCoorZ)
{
	double dL = 0.5 * (m_dUpperWidth - m_dLowerWidth);
	double dSubL = dL * (dCoorZ / m_dZDepth);
	double dCutLength = m_dUpperWidth - 2.0 * dSubL;

	return dCutLength;
}

bool CDlgParam::IsDoubleEqual (double d1,double d2)
{
	bool bEqual = true;
	double dValue = pow(10, -m_iDigits); // 計算 10 的 - 次方，即 0.0...01

	double dDif = d1 - d2;

	if (fabs(dDif) <= dValue)
		bEqual = true;
	else
		bEqual = false;

	return bEqual;
}

void CDlgParam::OnClose()
{
	// TODO: 在此加入您的訊息處理常式程式碼和 (或) 呼叫預設值
	CDialogEx::OnClose();
}


void CDlgParam::OnBnClickedCheckIntersect()
{ 
	BOOL bChecked = m_chkIntersect.GetCheck();

}

int CDlgParam::GenLayerCutPath(double dCoorZ, double dPitch, double ayResult[], int iMaxSize)
{
	double dTolerance = pow(10, -m_iDigits);
	double dCutLength = GetCutLayerWidth(dCoorZ);  // 切口寬度

	// 計算切道數
	int iArraySize = static_cast<int>((dCutLength / dPitch) + dTolerance);

	if (iArraySize == 0)
	{
		// 特例，切口寬度 < 增量 x ; 只取頭尾兩切割道
		ayResult[0] = -0.5 * dCutLength;
		ayResult[1] = 0.5 * dCutLength;

		return 2;
	}

	double dGap = dCutLength - iArraySize * dPitch;

	if (dGap > dTolerance)	// 偵測出殘量，殘量要分配兩端，所以頭尾要各加一點
		iArraySize += 3;
	else
		iArraySize += 1;	// 植樹問題，切道數 = 間隔數 + 1 

	if (IsDoubleEqual(dCutLength, m_dUpperWidth) == true)
	{
		m_iFirstSize = iArraySize;
	}
	else {
		// 與上層間的切割道數差,必須是 0 或 2！
		while ((m_iFirstSize - iArraySize) % 2 != 0) 
		{
			iArraySize--;
			
			dGap += dPitch;

			if (IsDoubleEqual(dGap, dPitch))
			{
				iArraySize += 2;
			}
		}
	}

	double dXCur = -dCutLength / 2;

	for (int i = 0; i < iArraySize; i++) 
	{
		ayResult[i] = dXCur;

		if (i == 0 || i == (iArraySize - 2)) 
		{
			dXCur += (IsDoubleEqual(dGap, 0.0) ? dPitch : dGap / 2);
		}
		else 
		{
			dXCur += dPitch;
		}
	}

	m_dPitch = dPitch;

	m_iIntersectSt = m_iEdgeKeepCnt - 1;
	m_iIntersectEd = iArraySize - m_iEdgeKeepCnt;

	SaveCutPathFile((double)iArraySize / dCutLength);// 輸出文字檔案

	return iArraySize;
}

int CDlgParam::GenIntersectLayerCutPath(double ayResult[], int iMaxSize)
{
	double dCutLength = GetCutLayerWidth(m_dLastCoorZ);  // 切口寬度
	double dTolerance = pow(10, -m_iDigits);

	// 未交錯的部分，切割道間距為 m_dCuttingSpacing
	int iArraySize = static_cast<int>((dCutLength / m_dCuttingSpacing) + dTolerance);	// 計算切道數

	if (iArraySize == 0)	// 特例，切口寬度 < 增量 x ; 只取頭尾兩切割道
	{
		ayResult[0] = -0.5 * dCutLength;
		ayResult[1] = 0.5 * dCutLength;

		return 2;
	}

	double dGap = dCutLength - iArraySize * m_dCuttingSpacing;	// 計算未考慮交錯的 gap

	if (dGap > dTolerance)	// 偵測出殘量，殘量要分配兩端，所以頭尾要各加一點
		iArraySize += 3;
	else
		iArraySize += 1;	// 植樹問題，切道數 = 間隔數 + 1 

	if (IsDoubleEqual(dCutLength, m_dUpperWidth) == true)
	{
		m_iFirstSize = iArraySize;
	}
	else 
	{
		// 與上層間的切割道數差,必須是 0 或 2！
		while ((m_iFirstSize - iArraySize) % 2 != 0)
		{
			iArraySize--;

			dGap += m_dCuttingSpacing;

			if (IsDoubleEqual(dGap, m_dCuttingSpacing))
			{
				iArraySize += 2;
			}
		}
	}


	//交錯的部分，切割道間距為 m_dCuttingSpacing * (m_dIntersectRatio + 1)
	double dNoIntersect, dIntersect;	//無交錯, 交錯的切口寬度

	if (!IsDoubleEqual(dGap, 0.0))		// 有 gap
		dNoIntersect = dGap + ((m_iEdgeKeepCnt - 2) * m_dCuttingSpacing) * 2;
	else
		dNoIntersect = ((m_iEdgeKeepCnt - 1) * m_dCuttingSpacing) * 2;

	dIntersect = dCutLength - dNoIntersect;							// 計算交錯的部分的切道寬度 = 切到寬度 - 不交錯的部分
	
	double dPitch = m_dCuttingSpacing * (m_dIntersectRatio + 1);	// 交錯後的增量 x = 增量 x * 交錯比

	if (dPitch > dIntersect)										// 交錯比後的增量 x 若大於切口寬度需要調整
		dPitch = m_dCuttingSpacing;

	iArraySize = (int)((dIntersect / dPitch) + dTolerance);			// 計算有交錯部分的切道數

	double dIntersectGap = dIntersect - iArraySize * dPitch;		// 計算交錯的 gap

	dIntersectGap /= iArraySize;									// 每個交錯切割 path 需要分擔部分的 gap

	iArraySize -= 1;												// 頭尾不打
	
	dPitch += dIntersectGap;										// pitch 加上需要分擔的 gap

	m_dPitch = dPitch;

	iArraySize += m_iEdgeKeepCnt * 2;								// 交錯部分的切道數 + 邊緣保留的切道數

	double dXCur = -dCutLength / 2;

	for (int i = 0; i < iArraySize; i++)
	{
		ayResult[i] = dXCur;

		if (i == 0 || i == (iArraySize - 2))									// 起刀和收刀的切割道  
			dXCur += (IsDoubleEqual(dGap, 0.0) ? m_dCuttingSpacing : dGap / 2);
		else if (i < m_iEdgeKeepCnt-1 || i >= iArraySize - m_iEdgeKeepCnt)		// 邊緣保留的切割道 
			dXCur += m_dCuttingSpacing;
		else																	// 交錯的切割道
			dXCur += dPitch ;
	}

	SaveCutPathFile((double)iArraySize / dCutLength);// 輸出文字檔案

	return iArraySize;
}

double CDlgParam::GetLayerHeight()
{
	int iPercentage = static_cast<int>((m_dLastCoorZ / m_dZDepth) * 100.0);
	iPercentage -= iPercentage % 5;

	switch (iPercentage)
	{
	case 0:
		return m_dLayerHeight * (m_dZPitchRatio5 / 100.);
		break;
	case 5:
		return m_dLayerHeight * (m_dZPitchRatio10 / 100.);
		break;
	case 10:
		return m_dLayerHeight * (m_dZPitchRatio15 / 100.);
		break;
	case 15:
		return m_dLayerHeight * (m_dZPitchRatio20 / 100.);
		break;
	case 20:
		return m_dLayerHeight * (m_dZPitchRatio25 / 100.);
		break;
	case 25:
		return m_dLayerHeight * (m_dZPitchRatio30 / 100.);
		break;
	case 30:
		return m_dLayerHeight * (m_dZPitchRatio35 / 100.);
		break;
	case 35:
		return m_dLayerHeight * (m_dZPitchRatio40 / 100.);
		break;
	case 40:
		return m_dLayerHeight * (m_dZPitchRatio45 / 100.);
		break;
	case 45:
		return m_dLayerHeight * (m_dZPitchRatio50 / 100.);
		break;
	case 50:
		return m_dLayerHeight * (m_dZPitchRatio55 / 100.);
		break;
	case 55:
		return m_dLayerHeight * (m_dZPitchRatio60 / 100.);
		break;
	case 60:
		return m_dLayerHeight * (m_dZPitchRatio65 / 100.);
		break;
	case 65:
		return m_dLayerHeight * (m_dZPitchRatio70 / 100.);
		break;
	case 70:
		return m_dLayerHeight * (m_dZPitchRatio75 / 100.);
		break;
	case 75:
		return m_dLayerHeight * (m_dZPitchRatio80 / 100.);
		break;
	case 80:
		return m_dLayerHeight * (m_dZPitchRatio85 / 100.);
		break;
	case 85:
		return m_dLayerHeight * (m_dZPitchRatio90 / 100.);
		break;
	case 90:
		return m_dLayerHeight * (m_dZPitchRatio95 / 100.);
		break;
	case 95:
		return m_dLayerHeight * (m_dZPitchRatio100 / 100.);
		break;
	default:
		return m_dLayerHeight * (m_dZPitchRatio100 / 100.);
		break;
	}
}

void CDlgParam::WriteINI()
{
	// 獲得程式所在路徑
	TCHAR szPath[MAX_PATH];
	GetModuleFileName(NULL, szPath, MAX_PATH);
	PathRemoveFileSpec(szPath);

	// 建立相對路徑下的 .ini
	CString strINIPath;
	strINIPath.Format(_T("%s\\config.ini"), szPath);

	// 寫入
	CString strValue;

	strValue.Format(_T("%f"), m_dZDepth);
	WritePrivateProfileString(_T("ENV"), _T("ZDepth"), strValue, strINIPath);

	strValue.Format(_T("%f"), m_dLayerHeight);
	WritePrivateProfileString(_T("ENV"), _T("LayerHeight"), strValue, strINIPath);

	strValue.Format(_T("%f"), m_dCuttingSpacing);
	WritePrivateProfileString(_T("ENV"), _T("CuttingSpacing"), strValue, strINIPath);

	strValue.Format(_T("%f"), m_dUpperWidth);
	WritePrivateProfileString(_T("ENV"), _T("UpperWidth"), strValue, strINIPath);

	strValue.Format(_T("%f"), m_dLowerWidth);
	WritePrivateProfileString(_T("ENV"), _T("LowerWidth"), strValue, strINIPath);

	strValue.Format(_T("%d"), m_iEdgeKeepCnt);
	WritePrivateProfileString(_T("ENV"), _T("EdgeKeepCnt"), strValue, strINIPath);

	strValue.Format(_T("%d"), m_iDigits);
	WritePrivateProfileString(_T("ENV"), _T("Digits"), strValue, strINIPath);
	
	strValue.Format(_T("%d"), m_iFirstPathCnt);
	WritePrivateProfileString(_T("ENV"), _T("FirstPathCnt"), strValue, strINIPath);

	strValue.Format(_T("%d"), m_iLastPathCnt);
	WritePrivateProfileString(_T("ENV"), _T("LastPathCnt"), strValue, strINIPath);

	strValue.Format(_T("%f"), m_dZPitchRatio5);
	WritePrivateProfileString(_T("ENV"), _T("ZPitchRatio5"), strValue, strINIPath);

	strValue.Format(_T("%f"), m_dZPitchRatio10);
	WritePrivateProfileString(_T("ENV"), _T("ZPitchRatio10"), strValue, strINIPath);

	strValue.Format(_T("%f"), m_dZPitchRatio15);
	WritePrivateProfileString(_T("ENV"), _T("ZPitchRatio15"), strValue, strINIPath);

	strValue.Format(_T("%f"), m_dZPitchRatio20);
	WritePrivateProfileString(_T("ENV"), _T("ZPitchRatio20"), strValue, strINIPath);

	strValue.Format(_T("%f"), m_dZPitchRatio25);
	WritePrivateProfileString(_T("ENV"), _T("ZPitchRatio25"), strValue, strINIPath);

	strValue.Format(_T("%f"), m_dZPitchRatio30);
	WritePrivateProfileString(_T("ENV"), _T("ZPitchRatio30"), strValue, strINIPath);

	strValue.Format(_T("%f"), m_dZPitchRatio35);
	WritePrivateProfileString(_T("ENV"), _T("ZPitchRatio35"), strValue, strINIPath);

	strValue.Format(_T("%f"), m_dZPitchRatio40);
	WritePrivateProfileString(_T("ENV"), _T("ZPitchRatio40"), strValue, strINIPath);

	strValue.Format(_T("%f"), m_dZPitchRatio45);
	WritePrivateProfileString(_T("ENV"), _T("ZPitchRatio45"), strValue, strINIPath);

	strValue.Format(_T("%f"), m_dZPitchRatio50);
	WritePrivateProfileString(_T("ENV"), _T("ZPitchRatio50"), strValue, strINIPath);

	strValue.Format(_T("%f"), m_dZPitchRatio55);
	WritePrivateProfileString(_T("ENV"), _T("ZPitchRatio55"), strValue, strINIPath);

	strValue.Format(_T("%f"), m_dZPitchRatio60);
	WritePrivateProfileString(_T("ENV"), _T("ZPitchRatio60"), strValue, strINIPath);

	strValue.Format(_T("%f"), m_dZPitchRatio65);
	WritePrivateProfileString(_T("ENV"), _T("ZPitchRatio65"), strValue, strINIPath);

	strValue.Format(_T("%f"), m_dZPitchRatio70);
	WritePrivateProfileString(_T("ENV"), _T("ZPitchRatio70"), strValue, strINIPath);

	strValue.Format(_T("%f"), m_dZPitchRatio75);
	WritePrivateProfileString(_T("ENV"), _T("ZPitchRatio75"), strValue, strINIPath);

	strValue.Format(_T("%f"), m_dZPitchRatio80);
	WritePrivateProfileString(_T("ENV"), _T("ZPitchRatio80"), strValue, strINIPath);

	strValue.Format(_T("%f"), m_dZPitchRatio85);
	WritePrivateProfileString(_T("ENV"), _T("ZPitchRatio85"), strValue, strINIPath);

	strValue.Format(_T("%f"), m_dZPitchRatio90);
	WritePrivateProfileString(_T("ENV"), _T("ZPitchRatio90"), strValue, strINIPath);

	strValue.Format(_T("%f"), m_dZPitchRatio95);
	WritePrivateProfileString(_T("ENV"), _T("ZPitchRatio95"), strValue, strINIPath);

	strValue.Format(_T("%f"), m_dZPitchRatio100);
	WritePrivateProfileString(_T("ENV"), _T("ZPitchRatio100"), strValue, strINIPath);

	strValue.Format(_T("%d"), m_bIntersect);
	WritePrivateProfileString(_T("ENV"), _T("Intersect"), strValue, strINIPath);

	strValue.Format(_T("%f"), m_dIntersectRatio);
	WritePrivateProfileString(_T("ENV"), _T("IntersectRatio"), strValue, strINIPath);
}

void CDlgParam::ReadINI()
{
	// 獲得程式所在路徑
	TCHAR szPath[MAX_PATH];
	GetModuleFileName(NULL, szPath, MAX_PATH);
	PathRemoveFileSpec(szPath);

	// 相對路徑下的 .ini
	CString strINIPath;
	strINIPath.Format(_T("%s\\config.ini"), szPath);
	_TCHAR szBuf[MAX_PATH] = _T("");

	// 讀取
 	GetPrivateProfileString(_T("ENV"), _T("ZDepth"), _T("11"), szBuf, _countof(szBuf), strINIPath);
	m_dZDepth = _tstof(szBuf);

	GetPrivateProfileString(_T("ENV"), _T("LayerHeight"), _T("0.08"), szBuf, _countof(szBuf), strINIPath);
	m_dLayerHeight = _tstof(szBuf);

	GetPrivateProfileString(_T("ENV"), _T("CuttingSpacing"), _T("0.012"), szBuf, _countof(szBuf), strINIPath);
	m_dCuttingSpacing = _tstof(szBuf);

	GetPrivateProfileString(_T("ENV"), _T("UpperWidth"), _T("0.42"), szBuf, _countof(szBuf), strINIPath);
	m_dUpperWidth = _tstof(szBuf);

	GetPrivateProfileString(_T("ENV"), _T("LowerWidth"), _T("0.05"), szBuf, _countof(szBuf), strINIPath);
	m_dLowerWidth = _tstof(szBuf);

	GetPrivateProfileString(_T("ENV"), _T("EdgeKeepCnt"), _T("3"), szBuf, _countof(szBuf), strINIPath);
	m_iEdgeKeepCnt = _ttoi(szBuf);

	GetPrivateProfileString(_T("ENV"), _T("Digits"), _T("6"), szBuf, _countof(szBuf), strINIPath);
	m_iDigits = _ttoi(szBuf);

	GetPrivateProfileString(_T("ENV"), _T("FirstPathCnt"), _T("2"), szBuf, _countof(szBuf), strINIPath);
	m_iFirstPathCnt = _ttoi(szBuf);

	GetPrivateProfileString(_T("ENV"), _T("LastPathCnt"), _T("3"), szBuf, _countof(szBuf), strINIPath);
	m_iLastPathCnt = _ttoi(szBuf);

	GetPrivateProfileString(_T("ENV"), _T("ZPitchRatio5"), _T("100"), szBuf, _countof(szBuf), strINIPath);
	m_dZPitchRatio5 = _tstof(szBuf);

	GetPrivateProfileString(_T("ENV"), _T("ZPitchRatio10"), _T("100"), szBuf, _countof(szBuf), strINIPath);
	m_dZPitchRatio10 = _tstof(szBuf);

	GetPrivateProfileString(_T("ENV"), _T("ZPitchRatio15"), _T("100"), szBuf, _countof(szBuf), strINIPath);
	m_dZPitchRatio15 = _tstof(szBuf);

	GetPrivateProfileString(_T("ENV"), _T("ZPitchRatio20"), _T("95"), szBuf, _countof(szBuf), strINIPath);
	m_dZPitchRatio20 = _tstof(szBuf);

	GetPrivateProfileString(_T("ENV"), _T("ZPitchRatio25"), _T("95"), szBuf, _countof(szBuf), strINIPath);
	m_dZPitchRatio25 = _tstof(szBuf);

	GetPrivateProfileString(_T("ENV"), _T("ZPitchRatio30"), _T("90"), szBuf, _countof(szBuf), strINIPath);
	m_dZPitchRatio30 = _tstof(szBuf);

	GetPrivateProfileString(_T("ENV"), _T("ZPitchRatio35"), _T("90"), szBuf, _countof(szBuf), strINIPath);
	m_dZPitchRatio35 = _tstof(szBuf);

	GetPrivateProfileString(_T("ENV"), _T("ZPitchRatio40"), _T("85"), szBuf, _countof(szBuf), strINIPath);
	m_dZPitchRatio40 = _tstof(szBuf);

	GetPrivateProfileString(_T("ENV"), _T("ZPitchRatio45"), _T("85"), szBuf, _countof(szBuf), strINIPath);
	m_dZPitchRatio45 = _tstof(szBuf);

	GetPrivateProfileString(_T("ENV"), _T("ZPitchRatio50"), _T("80"), szBuf, _countof(szBuf), strINIPath);
	m_dZPitchRatio50 = _tstof(szBuf);

	GetPrivateProfileString(_T("ENV"), _T("ZPitchRatio55"), _T("80"), szBuf, _countof(szBuf), strINIPath);
	m_dZPitchRatio55 = _tstof(szBuf);

	GetPrivateProfileString(_T("ENV"), _T("ZPitchRatio60"), _T("70"), szBuf, _countof(szBuf), strINIPath);
	m_dZPitchRatio60 = _tstof(szBuf);

	GetPrivateProfileString(_T("ENV"), _T("ZPitchRatio65"), _T("70"), szBuf, _countof(szBuf), strINIPath);
	m_dZPitchRatio65 = _tstof(szBuf);

	GetPrivateProfileString(_T("ENV"), _T("ZPitchRatio70"), _T("60"), szBuf, _countof(szBuf), strINIPath);
	m_dZPitchRatio70 = _tstof(szBuf);

	GetPrivateProfileString(_T("ENV"), _T("ZPitchRatio75"), _T("60"), szBuf, _countof(szBuf), strINIPath);
	m_dZPitchRatio75 = _tstof(szBuf);

	GetPrivateProfileString(_T("ENV"), _T("ZPitchRatio80"), _T("50"), szBuf, _countof(szBuf), strINIPath);
	m_dZPitchRatio80 = _tstof(szBuf);

	GetPrivateProfileString(_T("ENV"), _T("ZPitchRatio85"), _T("50"), szBuf, _countof(szBuf), strINIPath);
	m_dZPitchRatio85 = _tstof(szBuf);

	GetPrivateProfileString(_T("ENV"), _T("ZPitchRatio90"), _T("40"), szBuf, _countof(szBuf), strINIPath);
	m_dZPitchRatio90 = _tstof(szBuf);

	GetPrivateProfileString(_T("ENV"), _T("ZPitchRatio95"), _T("40"), szBuf, _countof(szBuf), strINIPath);
	m_dZPitchRatio95 = _tstof(szBuf);

	GetPrivateProfileString(_T("ENV"), _T("ZPitchRatio100"), _T("30"), szBuf, _countof(szBuf), strINIPath);
	m_dZPitchRatio100 = _tstof(szBuf);

	GetPrivateProfileString(_T("ENV"), _T("Intersect"), _T("0"), szBuf, _countof(szBuf), strINIPath);
	m_bIntersect = _ttoi(szBuf);

	GetPrivateProfileString(_T("ENV"), _T("IntersectRatio"), _T("0.5"), szBuf, _countof(szBuf), strINIPath);
	m_dIntersectRatio = _tstof(szBuf);
}

bool CDlgParam::CheckParam()
{
	// 上開口寬度 < 下開口寬度
	if (m_dUpperWidth < m_dLowerWidth)
	{
		AfxMessageBox(_T("上開口寬度 < 下開口寬度"));

		m_editUpperW.SetFocus();

		return false;
	}

	// 起刀次數和收刀次數不能小於 1
	if(m_iFirstPathCnt < 1)
	{
		AfxMessageBox(_T("起刀次數不能小於 1"));

		m_editFirstPathCnt.SetFocus();

		return false;
	}

	if (m_iLastPathCnt < 1)
	{
		AfxMessageBox(_T("收刀次數不能小於 1"));

		m_editLastPathCnt.SetFocus();

		return false;
	}

	// 邊緣保留次數
	if (m_bIntersect && m_iEdgeKeepCnt <= 1)
	{
		AfxMessageBox(_T("邊緣保留次數不能小於 2"));

		m_bIntersect = false;

		return false;
	}

	// 深度比值不能小於 1 大於 100
	IsValidZPitchRatio(m_dZPitchRatio5);
	IsValidZPitchRatio(m_dZPitchRatio10);
	IsValidZPitchRatio(m_dZPitchRatio15);
	IsValidZPitchRatio(m_dZPitchRatio20);
	IsValidZPitchRatio(m_dZPitchRatio25);
	IsValidZPitchRatio(m_dZPitchRatio30);
	IsValidZPitchRatio(m_dZPitchRatio35);
	IsValidZPitchRatio(m_dZPitchRatio40);
	IsValidZPitchRatio(m_dZPitchRatio45);
	IsValidZPitchRatio(m_dZPitchRatio50);
	IsValidZPitchRatio(m_dZPitchRatio55);
	IsValidZPitchRatio(m_dZPitchRatio60);
	IsValidZPitchRatio(m_dZPitchRatio65);
	IsValidZPitchRatio(m_dZPitchRatio70);
	IsValidZPitchRatio(m_dZPitchRatio75);
	IsValidZPitchRatio(m_dZPitchRatio80);
	IsValidZPitchRatio(m_dZPitchRatio85);
	IsValidZPitchRatio(m_dZPitchRatio90);
	IsValidZPitchRatio(m_dZPitchRatio95);
	IsValidZPitchRatio(m_dZPitchRatio100);

	return true;
}

void CDlgParam::GetReservedRect()
{
	// 計算預留區域(上下左右各預留 5 %)
	m_dBoundingBoxW = max(m_dUpperWidth, m_dLowerWidth);
	m_dBoundingBoxH = m_dZDepth;
	m_dReservedH = m_dBoundingBoxH * 0.05;
	m_dReservedW = m_dBoundingBoxW * 0.05;
}

void CDlgParam::GetInflatBoundingBox()
{
	// 計算 Inflat 後的 Boundingbox (上下左右各預留 5 %)
	m_dInflatW = m_dBoundingBoxW * 1.1;
	m_dInflatH = m_dBoundingBoxH * 1.1;
	m_dInflatHalfW = m_dInflatW / 2;
}

void CDlgParam::GetClientRectRatio()
{
	// 計算 Client Rect Ratio
	CPoint dotLT(0, 0);
	double dRatioX = (double)m_iClientW / m_dInflatW;
	double dRatioY = (double)m_iClientH / m_dInflatH;

	// 設定 Double to Integer 映射
	D2ISetUp(dotLT, -m_dInflatHalfW, m_dReservedH, dRatioX, dRatioY);
}

void CDlgParam::GetBlockCount()
{
	// 根據 pithch 計算畫面分割幾個區塊
	m_iWidthBlocks = (int)(m_dBoundingBoxW / 2 / m_dCuttingSpacing);
	
}

void CDlgParam::DrawTrapezoid(CDC* pCtrlDC)
{
	// 設定線條粗細
	int iPenWidth = 3;
	CPen pen(PS_SOLID, iPenWidth, RGB_BLACK); // 黑色實線
	CPen* pOldPen = pCtrlDC->SelectObject(&pen);

	// 換算梯形上底、下底、高
	CPoint dotLUpper, dotRUpper, dotLLower, dotRLower;
	D2I(-m_dUpperWidth / 2, 0, dotLUpper);
	D2I(m_dUpperWidth / 2, 0, dotRUpper);
	D2I(-m_dLowerWidth / 2, -m_dZDepth, dotLLower);
	D2I(m_dLowerWidth / 2, -m_dZDepth, dotRLower);

	// 繪製梯形
	pCtrlDC->MoveTo(dotLUpper.x, dotLUpper.y);
	pCtrlDC->LineTo(dotRUpper.x, dotRUpper.y);
	pCtrlDC->LineTo(dotRLower.x, dotRLower.y);
	pCtrlDC->LineTo(dotLLower.x, dotLLower.y);
	pCtrlDC->LineTo(dotLUpper.x, dotLUpper.y);

	// 恢復畫筆
	pCtrlDC->SelectObject (pOldPen);
}

void CDlgParam::DrawOriginLine(CDC* pCtrlDC)
{
	// 用綠色繪製中心線條
	CPen greenPen(PS_SOLID, 5, RGB(0, 255, 0));
	CPen* pOldPen = pCtrlDC->SelectObject(&greenPen);

	CPoint dotStart, dotEnd;

	// 繪製 y = 0
	D2I(-m_dBoundingBoxW/2, 0, dotStart);
	pCtrlDC->MoveTo(dotStart.x, dotStart.y);

	D2I(m_dBoundingBoxW/2, 0, dotEnd);
	pCtrlDC->LineTo(dotEnd.x, dotEnd.y);

	// 繪製 x = 0
	D2I(0, 0, dotStart);
	pCtrlDC->MoveTo(dotStart.x, dotStart.y);

	D2I(0, -m_dZDepth, dotEnd);
	pCtrlDC->LineTo(dotEnd.x, dotEnd.y);

	// 恢復畫筆
	pCtrlDC->SelectObject (pOldPen);
}

void CDlgParam::DrawGridLines(CDC* pCtrlDC)
{
	// 用紅色繪製方格
	CPen redPen(PS_SOLID, 1, RGB_RED);
	CPen* pOldPen = pCtrlDC->SelectObject(&redPen);
	CPoint dotStart, dotEnd;

	// 繪製縱線
	double dEpsilon = 1e-9; // 定義一個非常小的公差
	double dStartX = m_iWidthBlocks * -m_dCuttingSpacing;
	double dEndX = m_iWidthBlocks * m_dCuttingSpacing;

	for (double x = dStartX; x <= dEndX + dEpsilon; x += m_dCuttingSpacing) 
	{
		D2I(x, 0, dotStart);

		pCtrlDC->MoveTo(dotStart.x, dotStart.y);

		D2I(x, -m_dZDepth, dotEnd);

		pCtrlDC->LineTo(dotEnd.x, dotEnd.y);
	}

	// 繪製橫線
	for (double y = 0; y >= -m_dZDepth; y -= m_dLayerHeight)
	{
		D2I(-m_dBoundingBoxW/2, y, dotStart);

		pCtrlDC->MoveTo(dotStart.x, dotStart.y);

		D2I(m_dBoundingBoxW/2, y, dotEnd);

		pCtrlDC->LineTo(dotEnd.x, dotEnd.y);
	}

	// 恢復畫筆
	pCtrlDC->SelectObject(pOldPen);
}

void CDlgParam::DrawCutPath(CDC* pCtrlDC)
{
	CPen penBlue(PS_SOLID, 5, RGB(0, 0, 255));		// 藍色筆
	CPen penPurple(PS_SOLID, 5, RGB(255, 0, 255));	// 紫色筆
	CPen penOrange(PS_SOLID, 5, RGB(255, 165, 0));	// 橘色筆
	CPen penBlack(PS_SOLID, 1, RGB(0, 0, 0));		// 黑色筆
	CPen* pOldPen = pCtrlDC->SelectObject(&penBlue);
	CPoint dotCenter(0, 0);

	int iRadius = 2;		// 圓的半徑
	bool bFirstTime = true;	// 第一次進入需要 GetFirstCutPath
	double dCoorX, dCoorZ;

	do
	{
		if (bFirstTime)
		{
			GetFirstCutPoint (&dCoorX, &dCoorZ);
			bFirstTime = !bFirstTime;
		}

		D2I(dCoorX, dCoorZ, dotCenter);

		if (m_iCurPath == 0) 
		{
			// 起刀顏色變換
			for (int i = 0; i < m_iFirstPathCnt; i++) 
			{
				pCtrlDC->SelectObject(&penPurple);

				// 重複的切割位置偏移
				CPoint dotOffset = dotCenter;
				
				dotOffset.y -= i * 2;
		
				pCtrlDC->Ellipse(dotOffset.x - iRadius, dotOffset.y - iRadius, dotOffset.x + iRadius, dotOffset.y + iRadius);
			}
		}
		else if (m_iCurPath == m_iDataArraySize - 1) 
		{
			// 收刀顏色變換
			for (int i = 0; i < m_iLastPathCnt; i++) 
			{
				pCtrlDC->SelectObject(&penOrange);
				
				// 重複的切割位置偏移
				CPoint dotOffset = dotCenter;

				dotOffset.y += i * 2;
					
				pCtrlDC->Ellipse(dotOffset.x - iRadius, dotOffset.y - iRadius, dotOffset.x + iRadius, dotOffset.y + iRadius);

				
			}
			//SaveCutPathFile(-dCoorZ);// 輸出文字檔案
		}
		else 
		{
			// 一般點
			pCtrlDC->SelectObject(&penBlue);
			pCtrlDC->Ellipse(dotCenter.x - iRadius, dotCenter.y - iRadius, dotCenter.x + iRadius, dotCenter.y + iRadius);
		}
	} while (GetNextCutPoint(&dCoorX, &dCoorZ));

	m_fileIntersectRatio.Close();
	m_fileCut.Close();

	// 恢復畫筆
	pCtrlDC->SelectObject(pOldPen);
}

CDlgParam* CDlgParam::operator =(const CDlgParam &DlgParam)
{
	m_dZDepth = DlgParam.m_dZDepth;
	m_dLayerHeight = DlgParam.m_dLayerHeight;
	m_dCuttingSpacing = DlgParam.m_dCuttingSpacing;
	m_dUpperWidth = DlgParam.m_dUpperWidth;
	m_dLowerWidth = DlgParam.m_dLowerWidth;
	m_iFirstPathCnt = DlgParam.m_iFirstPathCnt;
	m_iLastPathCnt = DlgParam.m_iLastPathCnt;
	m_bIntersect = DlgParam.m_bIntersect;
	m_iEdgeKeepCnt = DlgParam.m_iEdgeKeepCnt;
	m_iDigits = DlgParam.m_iDigits;
	m_dZPitchRatio5 = DlgParam.m_dZPitchRatio5;
	m_dZPitchRatio10 = DlgParam.m_dZPitchRatio10;
	m_dZPitchRatio15 = DlgParam.m_dZPitchRatio15;
	m_dZPitchRatio20 = DlgParam.m_dZPitchRatio20;
	m_dZPitchRatio25 = DlgParam.m_dZPitchRatio25;
	m_dZPitchRatio30 = DlgParam.m_dZPitchRatio30;
	m_dZPitchRatio35 = DlgParam.m_dZPitchRatio35;
	m_dZPitchRatio40 = DlgParam.m_dZPitchRatio40;
	m_dZPitchRatio45 = DlgParam.m_dZPitchRatio45;
	m_dZPitchRatio50 = DlgParam.m_dZPitchRatio50;
	m_dZPitchRatio55 = DlgParam.m_dZPitchRatio55;
	m_dZPitchRatio60 = DlgParam.m_dZPitchRatio60;
	m_dZPitchRatio65 = DlgParam.m_dZPitchRatio65;
	m_dZPitchRatio70 = DlgParam.m_dZPitchRatio70;
	m_dZPitchRatio75 = DlgParam.m_dZPitchRatio75;
	m_dZPitchRatio80 = DlgParam.m_dZPitchRatio80;
	m_dZPitchRatio85 = DlgParam.m_dZPitchRatio85;
	m_dZPitchRatio90 = DlgParam.m_dZPitchRatio90;
	m_dZPitchRatio95 = DlgParam.m_dZPitchRatio95;
	m_dZPitchRatio100 = DlgParam.m_dZPitchRatio100;
	m_dIntersectRatio = DlgParam.m_dIntersectRatio;
	
	return this;
}

void CDlgParam::SaveCutPathFile(double dCoorZ)
{
	CString str;
	double dCutLength = GetCutLayerWidth(dCoorZ) + MIN_VALUE;
	double dRatio = (double)m_iRealCutSize / dCutLength;

	// 寫入每個高度的 dRatio
	/*str.Format(_T("%.3f (%d / %.6f)\n"), dRatio, m_iRealCutSize, dCutLength);*/
	str.Format(_T("%.3f \n"), dCoorZ);

	m_fileIntersectRatio.SeekToEnd();

	m_fileIntersectRatio.Write(str, str.GetLength() * sizeof(TCHAR));

	// 寫入每個高度的 pitch
	str.Format(_T("%.3f \n"), m_dPitch);

	m_fileCut.SeekToEnd();

	m_fileCut.Write(str, str.GetLength() * sizeof(TCHAR));
}

void CDlgParam::OpenCutPathFile()
{
	CString strFilename = GetFilePath(_T("Intersect_Ratio.txt"));
	CString strFilename2 = GetFilePath(_T("CuttingSpacing.txt"));

	OpenFile(m_fileIntersectRatio, strFilename);
	OpenFile(m_fileCut, strFilename2);
}


CString CDlgParam::GetFilePath(const CString & filename)
{
	TCHAR szPath[MAX_PATH];
	GetModuleFileName(NULL, szPath, MAX_PATH);
	PathRemoveFileSpec(szPath);

	CString strFilename;
	strFilename.Format(_T("%s\\%s"), szPath, filename);
	return strFilename;
}

void CDlgParam::OpenFile(CFile& file,const  CString& filename)
{
	if (!file.Open(filename, CFile::modeWrite | CFile::modeCreate))
	{
		AfxMessageBox(_T("無法開啟文件: ") + filename);
	}
}

bool CDlgParam::IsValidZPitchRatio(double dZPitchRatio)
{
	if (dZPitchRatio < 1.0 || dZPitchRatio > 100.0)
	{
		AfxMessageBox(_T("深度 Z 輸入的數值有誤(合理 range:1.0~100.0)"));
		return false;
	}
	
	return true;
}

bool CDlgParam::GetFirstCutPoint (double* pCoorX, double* pCoorZ)
{
	m_bReverse = false;
	m_iRepeatPathCnt = 0;
	m_dLastCoorZ = 0.0;
	

	m_iCurPath = 0;

	// 處理交錯
	if (m_bIntersect)	
		m_iDataArraySize = GenIntersectLayerCutPath(m_ayCoor, MAX_ARRAY_SIZE);
	else
		m_iDataArraySize = GenLayerCutPath(m_dLastCoorZ, m_dCuttingSpacing, m_ayCoor, MAX_ARRAY_SIZE);

	*pCoorX = m_ayCoor[m_iCurPath];
	*pCoorZ = -m_dLastCoorZ;

	return true;
}

bool CDlgParam::GetNextCutPoint (double* pCoorX, double* pCoorZ)
{
	bool bIntersect = true;

	// 起刀重複執行
	if (m_iCurPath == 0 && m_iRepeatPathCnt < m_iFirstPathCnt - 1)
	{
		m_iRepeatPathCnt++;

		m_iRealCutSize = 1;
	}
	// 收刀重複執行
	else if (m_iCurPath == m_iDataArraySize - 1 && m_iRepeatPathCnt < m_iLastPathCnt - 1)
	{
		m_iRepeatPathCnt++;
	}
	else// 其他刀
	{
		m_iCurPath++;
		m_iRepeatPathCnt = 0;

		if (m_iCurPath >= m_iDataArraySize)	//換到下一個 Layrer
		{
			m_bReverse = !m_bReverse;

			m_dLastCoorZ += GetLayerHeight();

			if (m_dLastCoorZ > m_dZDepth && !IsDoubleEqual(m_dLastCoorZ, m_dZDepth))	// 已經到底了，結束判斷
				return false;

			m_iCurPath = 0;

			// 處理交錯
			if (m_bIntersect)	
				m_iDataArraySize = GenIntersectLayerCutPath(m_ayCoor, MAX_ARRAY_SIZE);
			else
				m_iDataArraySize = GenLayerCutPath(m_dLastCoorZ, m_dCuttingSpacing, m_ayCoor, MAX_ARRAY_SIZE);

			if (m_bReverse)
			{
				for (int i = 0; i < m_iDataArraySize / 2; ++i)
				{
					double dTmp = m_ayCoor[i];
					m_ayCoor[i] = m_ayCoor[m_iDataArraySize - i - 1];
					m_ayCoor[m_iDataArraySize - i - 1] = dTmp;
				}
			}
		}

		m_iRealCutSize++;
	}

	*pCoorX = m_ayCoor[m_iCurPath];
	*pCoorZ = -m_dLastCoorZ;
}

