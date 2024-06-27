// DlgParam.cpp: 實作檔案
//

#include "pch.h"
#include "CutPath.h"
#include "DlgParam.h"

CFile CDlgParam::m_fileIntersectRatio;
CFile CDlgParam::m_fileCutPitch;

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
	, m_iFirstPathCnt(1)
	, m_iLastPathCnt(1)
	, m_iEdgeKeepCnt(1)
	, m_iDigits(6)
	, m_dIntersectRatio(0)
	, m_iZThrehold(100)
{
	m_iCurPath = 0;

	m_iDataArraySize = 0;

	m_bReverse = false;

	ReadINI();

	/*SetZPitchRatio();*/
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

	int iZPitchCtrlID[] = 
	{
		IDC_EDIT_Z_PITCH_RATIO_5,
		IDC_EDIT_Z_PITCH_RATIO_10,
		IDC_EDIT_Z_PITCH_RATIO_15,
		IDC_EDIT_Z_PITCH_RATIO_20,
		IDC_EDIT_Z_PITCH_RATIO_25,
		IDC_EDIT_Z_PITCH_RATIO_30,
		IDC_EDIT_Z_PITCH_RATIO_35,
		IDC_EDIT_Z_PITCH_RATIO_40,
		IDC_EDIT_Z_PITCH_RATIO_455,  
		IDC_EDIT_Z_PITCH_RATIO_50,
		IDC_EDIT_Z_PITCH_RATIO_55,
		IDC_EDIT_Z_PITCH_RATIO_60,
		IDC_EDIT_Z_PITCH_RATIO_65,
		IDC_EDIT_Z_PITCH_RATIO_70,
		IDC_EDIT_Z_PITCH_RATIO_75,
		IDC_EDIT_Z_PITCH_RATIO_80,
		IDC_EDIT_Z_PITCH_RATIO_85,
		IDC_EDIT_Z_PITCH_RATIO_90,
		IDC_EDIT_Z_PITCH_RATIO_95,
		IDC_EDIT_Z_PITCH_RATIO_100
	};

	for (int i = 0; i < NUM_Z_PITCH_RATIOS; i++)
	{
		DDX_Text(pDX, iZPitchCtrlID[i], m_ayZPitchRatio[i]);
		DDV_MinMaxDouble(pDX, m_ayZPitchRatio[i], 1.0, 100.0); 
	}

	DDX_Text(pDX, IDC_EDIT_FIRST_PATH_CNT, m_iFirstPathCnt);
	DDX_Text(pDX, IDC_EDIT_LAST_PATH_CNT, m_iLastPathCnt);
	DDX_Control(pDX, IDC_EDIT__EDGE_KEEP_CNT, m_editEdgeKeepCnt);
	DDX_Control(pDX, IDC_STATIC_EDGE_KEEP_CNT, m_staticEdgeKeepCnt);
	DDX_Text(pDX, IDC_EDIT__EDGE_KEEP_CNT, m_iEdgeKeepCnt);
	DDX_Text(pDX, IDC_EDIT_IDIGITS, m_iDigits);
	DDX_Control(pDX, IDC_EDIT_UPPER_WIDTH, m_editUpperW);
	DDX_Control(pDX, IDC_EDIT_LOWER_WIDTH, m_editLowerW);
	DDX_Control(pDX, IDC_EDIT_FIRST_PATH_CNT, m_editFirstPathCnt);
	DDX_Control(pDX, IDC_EDIT_LAST_PATH_CNT, m_editLastPathCnt);
	DDX_Text(pDX, IDC_EDIT_INTERSECT_RATIO, m_dIntersectRatio);
	DDX_Text(pDX, IDC_EDIT_Z_INTERSECT_THRESHOLD, m_iZThrehold);
}


BEGIN_MESSAGE_MAP(CDlgParam, CDialogEx)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTON_APPLY, &CDlgParam::OnBnClickedButtonApply)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// DlgParam 訊息處理常式


BOOL CDlgParam::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	ReadINI();

	UpdateData(FALSE);

	// 設定 Z pitch ratio
	/*SetZPitchRatio();*/

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

	// 參數檢查
	if(CheckParam())
	{
		// 計算預留區域(上下左右各預留 5 %)
		GetReservedRect();

		// 計算 Inflat 後的 Boundingbox (上下左右各預留 5 %)
		GetInflatBoundingBox();

		// 計算 Client Rect Ratio 並設定 D2I 的映射
		GetClientRectRatio();

		// 根據 pithch 計算畫面分割幾個區塊
		GetBlockCount();

		// 輸入參數合理的話更新畫面
		Invalidate();	

		WriteINI();
	}
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

	SaveCutPathFile((double)iArraySize / dCutLength);		// 輸出文字檔案

	return iArraySize;
}

int CDlgParam::GenIntersectLayerCutPath(double ayResult[], int iMaxSize)
{
	double dCutLength = GetCutLayerWidth(m_dLastCoorZ);		// 切口寬度
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

	SaveCutPathFile((double)iArraySize / dCutLength);							// 輸出文字檔案

	return iArraySize;
}

double CDlgParam::GetLayerHeight()
{
	int iPercentage = int((m_dLastCoorZ / m_dZDepth) * 100.0);
	iPercentage -= iPercentage % 5;

	// 計算索引
	int iIndex = iPercentage / 5;

	if (iIndex >= 0 && iIndex < sizeof(m_ayZPitchRatio) / sizeof(m_ayZPitchRatio[0]))
		return m_dLayerHeight * (m_ayZPitchRatio[iIndex] / 100.0);
	else // 如果索引超出範圍，使用最後一個比例
		return m_dLayerHeight * (m_ayZPitchRatio[NUM_Z_PITCH_RATIOS - 1] / 100.0);
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

	strValue.Format(_T("%f"), m_ayZPitchRatio[0]);
	WritePrivateProfileString(_T("ENV"), _T("ZPitchRatio5"), strValue, strINIPath);

	strValue.Format(_T("%f"), m_ayZPitchRatio[1]);
	WritePrivateProfileString(_T("ENV"), _T("ZPitchRatio10"), strValue, strINIPath);

	strValue.Format(_T("%f"), m_ayZPitchRatio[2]);
	WritePrivateProfileString(_T("ENV"), _T("ZPitchRatio15"), strValue, strINIPath);

	strValue.Format(_T("%f"), m_ayZPitchRatio[3]);
	WritePrivateProfileString(_T("ENV"), _T("ZPitchRatio20"), strValue, strINIPath);

	strValue.Format(_T("%f"), m_ayZPitchRatio[4]);
	WritePrivateProfileString(_T("ENV"), _T("ZPitchRatio25"), strValue, strINIPath);

	strValue.Format(_T("%f"), m_ayZPitchRatio[5]);
	WritePrivateProfileString(_T("ENV"), _T("ZPitchRatio30"), strValue, strINIPath);

	strValue.Format(_T("%f"), m_ayZPitchRatio[6]);
	WritePrivateProfileString(_T("ENV"), _T("ZPitchRatio35"), strValue, strINIPath);

	strValue.Format(_T("%f"), m_ayZPitchRatio[7]);
	WritePrivateProfileString(_T("ENV"), _T("ZPitchRatio40"), strValue, strINIPath);

	strValue.Format(_T("%f"), m_ayZPitchRatio[8]);
	WritePrivateProfileString(_T("ENV"), _T("ZPitchRatio45"), strValue, strINIPath);

	strValue.Format(_T("%f"), m_ayZPitchRatio[9]);
	WritePrivateProfileString(_T("ENV"), _T("ZPitchRatio50"), strValue, strINIPath);

	strValue.Format(_T("%f"), m_ayZPitchRatio[10]);
	WritePrivateProfileString(_T("ENV"), _T("ZPitchRatio55"), strValue, strINIPath);

	strValue.Format(_T("%f"), m_ayZPitchRatio[11]);
	WritePrivateProfileString(_T("ENV"), _T("ZPitchRatio60"), strValue, strINIPath);

	strValue.Format(_T("%f"), m_ayZPitchRatio[12]);
	WritePrivateProfileString(_T("ENV"), _T("ZPitchRatio65"), strValue, strINIPath);

	strValue.Format(_T("%f"), m_ayZPitchRatio[13]);
	WritePrivateProfileString(_T("ENV"), _T("ZPitchRatio70"), strValue, strINIPath);

	strValue.Format(_T("%f"), m_ayZPitchRatio[14]);
	WritePrivateProfileString(_T("ENV"), _T("ZPitchRatio75"), strValue, strINIPath);

	strValue.Format(_T("%f"), m_ayZPitchRatio[15]);
	WritePrivateProfileString(_T("ENV"), _T("ZPitchRatio80"), strValue, strINIPath);

	strValue.Format(_T("%f"), m_ayZPitchRatio[16]);
	WritePrivateProfileString(_T("ENV"), _T("ZPitchRatio85"), strValue, strINIPath);

	strValue.Format(_T("%f"), m_ayZPitchRatio[17]);
	WritePrivateProfileString(_T("ENV"), _T("ZPitchRatio90"), strValue, strINIPath);

	strValue.Format(_T("%f"), m_ayZPitchRatio[18]);
	WritePrivateProfileString(_T("ENV"), _T("ZPitchRatio95"), strValue, strINIPath);

	strValue.Format(_T("%f"), m_ayZPitchRatio[19]);
	WritePrivateProfileString(_T("ENV"), _T("ZPitchRatio100"), strValue, strINIPath);

	strValue.Format(_T("%f"), m_dIntersectRatio);
	WritePrivateProfileString(_T("ENV"), _T("IntersectRatio"), strValue, strINIPath);

	strValue.Format(_T("%d"), m_iZThrehold);
	WritePrivateProfileString(_T("ENV"), _T("ZThrehold"), strValue, strINIPath);
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
	m_ayZPitchRatio[0] = _tstof(szBuf);

	GetPrivateProfileString(_T("ENV"), _T("ZPitchRatio10"), _T("100"), szBuf, _countof(szBuf), strINIPath);
	m_ayZPitchRatio[1] = _tstof(szBuf);

	GetPrivateProfileString(_T("ENV"), _T("ZPitchRatio15"), _T("100"), szBuf, _countof(szBuf), strINIPath);
	m_ayZPitchRatio[2] = _tstof(szBuf);

	GetPrivateProfileString(_T("ENV"), _T("ZPitchRatio20"), _T("95"), szBuf, _countof(szBuf), strINIPath);
	m_ayZPitchRatio[3] = _tstof(szBuf);

	GetPrivateProfileString(_T("ENV"), _T("ZPitchRatio25"), _T("95"), szBuf, _countof(szBuf), strINIPath);
	m_ayZPitchRatio[4] = _tstof(szBuf);

	GetPrivateProfileString(_T("ENV"), _T("ZPitchRatio30"), _T("90"), szBuf, _countof(szBuf), strINIPath);
	m_ayZPitchRatio[5] = _tstof(szBuf);

	GetPrivateProfileString(_T("ENV"), _T("ZPitchRatio35"), _T("90"), szBuf, _countof(szBuf), strINIPath);
	m_ayZPitchRatio[6] = _tstof(szBuf);

	GetPrivateProfileString(_T("ENV"), _T("ZPitchRatio40"), _T("85"), szBuf, _countof(szBuf), strINIPath);
	m_ayZPitchRatio[7] = _tstof(szBuf);

	GetPrivateProfileString(_T("ENV"), _T("ZPitchRatio45"), _T("85"), szBuf, _countof(szBuf), strINIPath);
	m_ayZPitchRatio[8] = _tstof(szBuf);

	GetPrivateProfileString(_T("ENV"), _T("ZPitchRatio50"), _T("80"), szBuf, _countof(szBuf), strINIPath);
	m_ayZPitchRatio[9] = _tstof(szBuf);

	GetPrivateProfileString(_T("ENV"), _T("ZPitchRatio55"), _T("80"), szBuf, _countof(szBuf), strINIPath);
	m_ayZPitchRatio[10] = _tstof(szBuf);

	GetPrivateProfileString(_T("ENV"), _T("ZPitchRatio60"), _T("70"), szBuf, _countof(szBuf), strINIPath);
	m_ayZPitchRatio[11] = _tstof(szBuf);

	GetPrivateProfileString(_T("ENV"), _T("ZPitchRatio65"), _T("70"), szBuf, _countof(szBuf), strINIPath);
	m_ayZPitchRatio[12] = _tstof(szBuf);

	GetPrivateProfileString(_T("ENV"), _T("ZPitchRatio70"), _T("60"), szBuf, _countof(szBuf), strINIPath);
	m_ayZPitchRatio[13] = _tstof(szBuf);

	GetPrivateProfileString(_T("ENV"), _T("ZPitchRatio75"), _T("60"), szBuf, _countof(szBuf), strINIPath);
	m_ayZPitchRatio[14] = _tstof(szBuf);

	GetPrivateProfileString(_T("ENV"), _T("ZPitchRatio80"), _T("50"), szBuf, _countof(szBuf), strINIPath);
	m_ayZPitchRatio[15] = _tstof(szBuf);

	GetPrivateProfileString(_T("ENV"), _T("ZPitchRatio85"), _T("50"), szBuf, _countof(szBuf), strINIPath);
	m_ayZPitchRatio[16] = _tstof(szBuf);

	GetPrivateProfileString(_T("ENV"), _T("ZPitchRatio90"), _T("40"), szBuf, _countof(szBuf), strINIPath);
	m_ayZPitchRatio[17] = _tstof(szBuf);

	GetPrivateProfileString(_T("ENV"), _T("ZPitchRatio95"), _T("40"), szBuf, _countof(szBuf), strINIPath);
	m_ayZPitchRatio[18] = _tstof(szBuf);

	GetPrivateProfileString(_T("ENV"), _T("ZPitchRatio100"), _T("30"), szBuf, _countof(szBuf), strINIPath);
	m_ayZPitchRatio[19] = _tstof(szBuf);

	GetPrivateProfileString(_T("ENV"), _T("IntersectRatio"), _T("0"), szBuf, _countof(szBuf), strINIPath);
	m_dIntersectRatio = _tstof(szBuf);

	GetPrivateProfileString(_T("ENV"), _T("ZThrehold"), _T("100"), szBuf, _countof(szBuf), strINIPath);
	m_iZThrehold = _ttoi(szBuf);
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
	if (m_dIntersectRatio > 0 && m_iEdgeKeepCnt <= 1)
	{
		AfxMessageBox(_T("邊緣保留次數不能小於 2"));

		m_dIntersectRatio = 0;

		return false;
	}

	// 深度比值不能小於 1 大於 100
	for (double dRatio : m_ayZPitchRatio)
	{
		if (!IsValidZPitchRatio(dRatio))
		{
			return false; // 如果有一個值無效，返回 false
		}
	}

	// 交錯比不能小於 1
	if (m_dIntersectRatio < 0)
	{
		AfxMessageBox(_T("交錯比不能小於 0"));

		return false;
	}

	// 交錯深度 Z 的門檻
	if (m_iZThrehold < 0 || m_iZThrehold > 100)
	{
		AfxMessageBox(_T("交錯比深度 Z 需要介於 0 ~ 100 間"));

		return false;
	}

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
		}
		else 
		{
			// 一般點
			pCtrlDC->SelectObject(&penBlue);
			pCtrlDC->Ellipse(dotCenter.x - iRadius, dotCenter.y - iRadius, dotCenter.x + iRadius, dotCenter.y + iRadius);
		}
	} while (GetNextCutPoint(&dCoorX, &dCoorZ));

	

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
	m_iEdgeKeepCnt = DlgParam.m_iEdgeKeepCnt;
	m_iDigits = DlgParam.m_iDigits;
	m_dIntersectRatio = DlgParam.m_dIntersectRatio;
	m_iZThrehold = DlgParam.m_iZThrehold;

	for (int i = 0; i < NUM_Z_PITCH_RATIOS; i++)
	{
		m_ayZPitchRatio[i] = DlgParam.m_ayZPitchRatio[i];
	}
	
	
	return this;
}

void CDlgParam::SaveCutPathFile(double dRatio)
{
	CString str;

	// 寫入每個高度的 dRatio
	str.Format(_T("%.3f \n"), dRatio);

	m_fileIntersectRatio.SeekToEnd();

	m_fileIntersectRatio.Write(str, str.GetLength() * sizeof(TCHAR));

	// 寫入每個高度的 pitch
	str.Format(_T("%.3f \n"), m_dPitch);

	m_fileCutPitch.SeekToEnd();

	m_fileCutPitch.Write(str, str.GetLength() * sizeof(TCHAR));
}

void CDlgParam::OpenCutPathFile()
{
	CString strFilename = SetFilePath(_T("Intersect_Ratio.txt"));
	CString strFilename2 = SetFilePath(_T("CuttingSpacing.txt"));

	// 如果文件已經打開，則先關閉文件
	if (m_fileIntersectRatio.m_hFile != CFile::hFileNull)
	{
		m_fileIntersectRatio.Close();
	}

	if (m_fileCutPitch.m_hFile != CFile::hFileNull)
	{
		m_fileCutPitch.Close();
	}

	OpenFile(m_fileIntersectRatio, strFilename);
	OpenFile(m_fileCutPitch, strFilename2);
}


CString CDlgParam::SetFilePath(const CString & filename)
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

void CDlgParam::ReverseArray(double * arr, int iSize)
{
	for (int i = 0; i < iSize / 2; ++i)
	{
		double dTmp = arr[i];
		arr[i] = arr[iSize - i - 1];
		arr[iSize - i - 1] = dTmp;
	}
}

bool CDlgParam::GetFirstCutPoint (double* pCoorX, double* pCoorZ)
{
	m_bReverse = false;
	m_iRepeatPathCnt = 0;
	m_dLastCoorZ = 0.0;
	
	// 開啟文件
	OpenCutPathFile();

	m_iCurPath = 0;

	// 處理交錯
	if (m_dIntersectRatio > 0)
		m_iDataArraySize = GenIntersectLayerCutPath(m_ayCoor, MAX_ARRAY_SIZE);
	else
		m_iDataArraySize = GenLayerCutPath(m_dLastCoorZ, m_dCuttingSpacing, m_ayCoor, MAX_ARRAY_SIZE);

	*pCoorX = m_ayCoor[m_iCurPath];
	*pCoorZ = -m_dLastCoorZ;

	return true;
}


bool CDlgParam::GetNextCutPoint (double* pCoorX, double* pCoorZ)
{
	// 起刀重複執行
	if (m_iCurPath == 0 && m_iRepeatPathCnt < m_iFirstPathCnt - 1)
	{
		m_iRepeatPathCnt++;
	}
	// 收刀重複執行
	else if (m_iCurPath == m_iDataArraySize - 1 && m_iRepeatPathCnt < m_iLastPathCnt - 1)
	{
		m_iRepeatPathCnt++;
	}
	// 其他刀
	else   
	{
		m_iCurPath++;
		m_iRepeatPathCnt = 0;

		if (m_iCurPath >= m_iDataArraySize)		//換到下一個 Layrer
		{
			m_bReverse = !m_bReverse;			// 反向

			m_dLastCoorZ += GetLayerHeight();	// 更新 Z 軸座標

			if (m_dLastCoorZ > m_dZDepth && !IsDoubleEqual(m_dLastCoorZ, m_dZDepth))	// 已經到底了，結束判斷
			{
				m_fileIntersectRatio.Close();
				m_fileCutPitch.Close();
				return false;
			}

			m_iCurPath = 0;						// 重置當前切割道

			// 處理交錯
			int iCurDepth = (int)((m_dLastCoorZ / m_dZDepth) * 100);

			if (m_dIntersectRatio > 0 && iCurDepth <= m_iZThrehold)	// 如果啟用交錯模式且在交錯深度門檻內要使用交錯
				m_iDataArraySize = GenIntersectLayerCutPath(m_ayCoor, MAX_ARRAY_SIZE);
			else  
				m_iDataArraySize = GenLayerCutPath(m_dLastCoorZ, m_dCuttingSpacing, m_ayCoor, MAX_ARRAY_SIZE);

			if (m_bReverse)
			{
				ReverseArray(m_ayCoor, m_iDataArraySize);
			}
		}
	}
	 
	*pCoorX = m_ayCoor[m_iCurPath];
	*pCoorZ = -m_dLastCoorZ;
	
	return true;
}

