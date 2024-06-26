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
	, m_dIntersectRatio(0)
	, m_iZThrehold(100)
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
	SetZPitchRatio();

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

	// 設定 Z pitch ratio
	SetZPitchRatio();

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

		// 開啟文件
		OpenCutPathFile();

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

/**
* void CDlgParam::D2I(double dCoorX, double dCoorY, CPoint &dotResult)
*
* 功能說明:
* 	將雙精度浮點數座標轉換為整數座標，並儲存到dotResult中。
*
* Input:
* 	double dCoorX: X座標的雙精度浮點數。
* 	double dCoorY: Y座標的雙精度浮點數。
* 	CPoint &dotResult: 用於儲存轉換後的整數座標的CPoint對象。
*
* Output:
* 	無
*
* Remark:
* 	1. 根據比例將浮點數座標轉換為對應的整數座標。
* 	2. 轉換後的X座標加上左上角的X偏移量。
* 	3. 轉換後的Y座標減去左上角的Y偏移量（因為Y軸方向相反）。
*/
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

/**
* bool CDlgParam::IsDoubleEqual(double d1, double d2)
*
* 功能說明:
* 	比較兩個雙精度浮點數是否在允許的誤差範圍內相等。
*
* Input:
* 	double d1: 第一個浮點數。
* 	double d2: 第二個浮點數。
*
* Output:
* 	bool: 如果兩個浮點數相等，返回true；否則返回false。
*
* Remark:
* 	1. 計算允許的誤差範圍，取決於m_iDigits。
* 	2. 計算兩個浮點數之差，並檢查其是否在允許的誤差範圍內。
* 	3. 使用fabs函數來取絕對值。
*/
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


/**
 * GenLayerCutPath - 生成指定層的切割路徑
 *
 * @param dCoorZ: 當前Z座標
 * @param dPitch: 切割間距
 * @param ayResult: 存放結果的陣列
 * @param iMaxSize: 結果陣列的最大尺寸
 *
 * @return 生成的切割道數
 *
 * 此函數根據給定的Z座標和切割間距生成切割層的路徑。它首先計算需要的切割道數，
 * 根據道數和切割寬度進行特例處理。如果寬度與上一層相等，會記錄初始大小。
 * 函數會根據計算結果更新每個切割點的位置，並保存切割路徑到文件。
 */
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

/**
 * GenIntersectLayerCutPath - 生成交錯層的切割路徑
 *
 * @param ayResult: 存放結果的陣列
 * @param iMaxSize: 結果陣列的最大尺寸
 *
 * @return 生成的切割道數
 *
 * 此函數根據最後一次切割的Z座標生成交錯層的切割路徑。它首先計算不交錯部分的切割道數，
 * 根據道數和切割寬度進行特例處理。接著計算交錯部分的切割道數，並調整交錯的間距。
 * 函數會根據計算結果更新每個切割點的位置，並保存切割路徑到文件。
 */
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

/**
* double CDlgParam::GetLayerHeight()
*
* 功能說明:
* 	根據當前的Z深度比例計算層的高度，並返回對應的高度值。
*
* Input:
* 	無
*
* Output:
* 	double: 返回計算出的層高度。
*
* Remark:
* 	1. 計算當前Z深度相對於總深度的百分比，並根據百分比取整至最接近的5的倍數。
* 	2. 根據計算出的百分比返回相應比例的層高度。
* 	3. 使用多個比例參數來調整不同深度下的層高度。
*/
double CDlgParam::GetLayerHeight()
{
	int iPercentage = int((m_dLastCoorZ / m_dZDepth) * 100.0);
	iPercentage -= iPercentage % 5;

	// 計算索引
	int iIndex = iPercentage / 5;

	if (iIndex >= 0 && iIndex < sizeof(m_ayZPitchRatio) / sizeof(m_ayZPitchRatio[0]))
		return m_dLayerHeight * (m_ayZPitchRatio[iIndex] / 100.0);
	else // 如果索引超出範圍，使用最後一個比例
		return m_dLayerHeight * (m_dZPitchRatio100 / 100.0);
}

void CDlgParam::SetZPitchRatio()
{
	// 初始化 m_dZPitchRatio 數組
	double dZPitchRatios[] = 
	{
		m_dZPitchRatio5, m_dZPitchRatio10, m_dZPitchRatio15, m_dZPitchRatio20,
		m_dZPitchRatio25, m_dZPitchRatio30, m_dZPitchRatio35, m_dZPitchRatio40,
		m_dZPitchRatio45, m_dZPitchRatio50, m_dZPitchRatio55, m_dZPitchRatio60,
		m_dZPitchRatio65, m_dZPitchRatio70, m_dZPitchRatio75, m_dZPitchRatio80,
		m_dZPitchRatio85, m_dZPitchRatio90, m_dZPitchRatio95, m_dZPitchRatio100
	};

	// 將臨時數組的值賦值給成員數組
	for (int i = 0; i < NUM_Z_PITCH_RATIOS; ++i) 
	{
		m_ayZPitchRatio[i] = dZPitchRatios[i];
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

/**
 * DrawCutPath - 繪製切割路徑
 *
 * @param pCtrlDC: 繪圖設備上下文指針
 *
 * 此函數在給定的繪圖設備上下文中繪製切割路徑。根據當前切割路徑的狀態選擇不同顏色的筆，
 * 並在指定位置繪製圓點。函數會根據起始點和終點分別使用不同顏色，並在一般點使用藍色。
 * 繪製完後，函數會關閉文件並恢復原來的畫筆。
 */
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
	m_fileCutPitch.Close();

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
	m_iZThrehold = DlgParam.m_iZThrehold;
	
	return this;
}

/**
 * SaveCutPathFile - 保存切割路徑文件
 *
 * @param dRatio: 當前高度的比例
 *
 * 此函數將當前高度的比例和切割間距寫入對應的文件。首先，將比例寫入 `m_fileIntersectRatio` 文件，
 * 然後將切割間距寫入 `m_fileCutPitch` 文件。每次寫入都會將文件指針移動到文件末尾。
 */
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

/**
 * GetFirstCutPoint - 獲取第一個切割點
 *
 * @param pCoorX: 用於存儲X坐標的指針
 * @param pCoorZ: 用於存儲Z坐標的指針
 *
 * @return 返回布爾值表示是否成功獲取切割點
 *
 * 此函數初始化一些狀態變數，並根據是否需要交錯來生成切割路徑數據。
 * 如果需要交錯，調用 `GenIntersectLayerCutPath` 來生成交錯層的切割路徑；
 * 否則，調用 `GenLayerCutPath` 來生成普通層的切割路徑。
 * 最後將第一個切割點的坐標存儲在 `pCoorX` 和 `pCoorZ` 中。
 */
bool CDlgParam::GetFirstCutPoint (double* pCoorX, double* pCoorZ)
{
	m_bReverse = false;
	m_iRepeatPathCnt = 0;
	m_dLastCoorZ = 0.0;
	

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

/**
 * GetNextCutPoint - 獲取下一個切割點
 *
 * @param pCoorX: 用於存儲X坐標的指針
 * @param pCoorZ: 用於存儲Z坐標的指針
 *
 * @return 返回布爾值表示是否成功獲取下一個切割點
 *
 * 此函數用於獲取下一個切割點的坐標。根據當前的切割路徑位置和狀態，
 * 函數會判斷是否需要重複起刀或收刀的操作，並根據當前層的狀態決定是否切換到下一層。
 * 在每層中會根據是否需要交錯來生成新的切割路徑數據，並在需要時反轉數據順序。
 * 最後將下一個切割點的坐標存儲在 `pCoorX` 和 `pCoorZ` 中。
 */
bool CDlgParam::GetNextCutPoint (double* pCoorX, double* pCoorZ)
{
	bool bIntersect = true;

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

		if (m_iCurPath >= m_iDataArraySize)	//換到下一個 Layrer
		{
			m_bReverse = !m_bReverse;

			m_dLastCoorZ += GetLayerHeight();

			if (m_dLastCoorZ > m_dZDepth && !IsDoubleEqual(m_dLastCoorZ, m_dZDepth))	// 已經到底了，結束判斷
				return false;

			m_iCurPath = 0;

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
}

