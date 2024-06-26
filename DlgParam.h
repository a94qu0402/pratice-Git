#pragma once


// DlgParam 對話方塊

#define NUM_Z_PITCH_RATIOS 20
#define MAX_ARRAY_SIZE	100



class CDlgParam : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgParam)

public:
	CDlgParam(CWnd* pParent = nullptr);   // 標準建構函式
	virtual ~CDlgParam();

// 對話方塊資料
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_PARAM };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支援

	DECLARE_MESSAGE_MAP()
public:
    virtual BOOL OnInitDialog();

    afx_msg void OnBnClickedButtonApply();
    afx_msg void OnPaint();
    afx_msg void OnClose();
    afx_msg void OnBnClickedCheckIntersect();

    CButton m_chkIntersect;				// 交錯
    CEdit m_editEdgeKeepCnt;
    CStatic m_staticEdgeKeepCnt;
    CStatic m_PictureCtrl;
	CPoint m_dotRectLT;
	BOOL m_bIntersect;
	CEdit m_editUpperW;
	CEdit m_editLowerW;
	CEdit m_editFirstPathCnt;
	CEdit m_editLastPathCnt;

	// 使用者參數設定
    double m_dZDepth;					// 深度 Z
    double m_dLayerHeight;				// 增量 Z
    double m_dCuttingSpacing;			// 增量 X
    double m_dUpperWidth;				// 上開口寬度			
    double m_dLowerWidth;				// 下開口寬度
    double m_dMaxWidth;					// 開口寬度
	double m_dIntersectRatio;			// 交錯比

	int m_iFirstPathCnt;				// 首道切割道重複次數
	int m_iLastPathCnt;					// 末道切割道重複次數
	int m_iEdgeKeepCnt;					// 邊緣保留次數
	int m_iDigits;						// 小數點末幾位

	// 深度 Z 比率
	double m_dZPitchRatio5;				// 深度 Z 5%			
	double m_dZPitchRatio10;			// 深度 Z 10%
	double m_dZPitchRatio15;			// 深度 Z 15%
	double m_dZPitchRatio20;			// 深度 Z 20%
	double m_dZPitchRatio25;			// 深度 Z 25%
	double m_dZPitchRatio30;			// 深度 Z 30%
	double m_dZPitchRatio35;			// 深度 Z 35%
	double m_dZPitchRatio40;			// 深度 Z 40%
	double m_dZPitchRatio45;			// 深度 Z 45%
	double m_dZPitchRatio50;			// 深度 Z 50%
	double m_dZPitchRatio55;			// 深度 Z 55%
	double m_dZPitchRatio60;			// 深度 Z 60%
	double m_dZPitchRatio65;			// 深度 Z 65%
	double m_dZPitchRatio70;			// 深度 Z 70%
	double m_dZPitchRatio75;			// 深度 Z 75%
	double m_dZPitchRatio80;			// 深度 Z 80%
	double m_dZPitchRatio85;			// 深度 Z 85%
	double m_dZPitchRatio90;			// 深度 Z 90%
	double m_dZPitchRatio95;			// 深度 Z 95%
	double m_dZPitchRatio100;			// 深度 Z 100%
	double m_dZPitchRatio[NUM_Z_PITCH_RATIOS];

	////成員函式內部使用
	double m_dCoorLT_X;					// 客戶區域左上角 X 座標
	double m_dCoorLT_Y;					// 客戶區域左上角 Y 座標
	double m_dRatioX;					// X 軸 Ratio
	double m_dRatioY;					// Y 軸 Ratio
	double m_ayCoor[MAX_ARRAY_SIZE];	// 當前切割道
	double m_dLastCoorZ;				// 上一個深度 Z

	// 客戶區域相關
	int m_iWidthBlocks;					// 客戶區域寬分割區塊數
	int m_iClientW;						// 客戶區域寬度
	int m_iClientH;						// 客戶區域高度
	double m_dReservedW;				// 客戶區域預留寬度
	double m_dReservedH;				// 客戶區域預留高度

	// BoundingBox
	double m_dBoundingBoxW;				// Bounding box Width
	double m_dBoundingBoxH;				// Bounding box Height
	double m_dInflatW;					// Inflat Bounding box Width
	double m_dInflatHalfW;				// Inflat Bounding box Half Width
	double m_dInflatH;					// Inflat Bounding box Height 

	// 切割道相關
	int m_iFirstSize;					// 紀錄第一高度的切割道數
	int m_iDataArraySize;				// 當前高度的切割道數
	int m_iRealCutSize;					// 實際切割道數目
	int m_iCurPath;						// 當前在哪一個切割道
	int m_iRepeatPathCnt;				// 當前切割道重複次數
	int m_iIntersectSt;					// 開始進行交錯的 index
	int m_iIntersectEd;					// 結束進行交錯的 index
	bool m_bReverse;					// 切割道反序
	
	// 計算 cutpath
	double GetCutLayerWidth(double dCoorZ);								// 計算切口寬度
	bool   GetFirstCutPoint (double* pCoorX, double* pCoorZ);			// 計算首切割道的 x,y 座標
	bool   GetNextCutPoint (double* pCoorX, double* pCoorZ);			// 計算下一個切割道的 x,y 座標
	int    GenLayerCutPath(double dCoorZ, double dPitch, double ayResult[], int iMaxSize);	// 計算當前高度的 ArraySize
	int	   GenIntersectLayerCutPath(double ayResult[], int iMaxSize);	//  計算當前高度的 ArraySize(有交錯)
	double GetLayerHeight();											// 回傳考慮比率後的 LayerHeight

	// 數學計算
	bool IsDoubleEqual(double d1, double d2);							// 檢查 d1 是否等同 d2
	bool IsValidZPitchRatio(double dZPitchRatio);						// 檢查 Z Pitch Ratio 合法性

	// 座標轉換
	void D2ISetUp(CPoint dotLT, double dCoorLT_X, double dCoorLT_Y, double dRatioX, double dRatioY);// 座標基底
	void D2I(double dCoorX, double dCoorY, CPoint &dotResult);	// double 座標轉 int 座標

	// 繪製相關
	void DrawTrapezoid(CDC* pCtrlDC);	// 繪製梯形
	void DrawOriginLine(CDC* pCtrlDC);	// 繪製基準線(x=0, y=0)
	void DrawGridLines(CDC* pCtrlDC);	// 繪製格線
	void DrawCutPath(CDC* pCtrlDC);		// 繪製切割道

	// 計算 boundingbox
	void GetReservedRect();				// 計算預留空間(上下左右各預留 5 %)
	void GetInflatBoundingBox();		// 計算 Inflat 後的 Boundingbox (上下左右各預留 5 %)
	void GetClientRectRatio();			// 計算 Client Rect Ratio
	void GetBlockCount();				// 計算 Client Rect Width 分割幾個 Block

	// 輸入參數相關
	void WriteINI();					// 寫入 INI
	void ReadINI();						// 讀取 INI
	bool CheckParam();					// 參數檢查合法性

	CDlgParam* operator =(const CDlgParam &DlgParam);	// dlg '='

	// 檔案 - 有關 Intersect
	double m_dPitch;							// 用於紀錄每一層的 pitch
	CFile  m_fileIntersectRatio, m_fileCutPitch;		
	void SaveCutPathFile(double dRatio);		// 儲存資訊於檔案
	void OpenCutPathFile();						// 打開需要寫入的檔案

	CString SetFilePath(const CString& filename);			// 得到檔案路徑
	void OpenFile(CFile& file, const CString& filename);	// 打開檔案
};
