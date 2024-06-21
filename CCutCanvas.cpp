#include "pch.h"
#include "CCutCanvas.h"
BEGIN_MESSAGE_MAP(CCutCanvas, CStatic)
	ON_WM_PAINT()
END_MESSAGE_MAP()

void CCutCanvas::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 在此加入您的訊息處理常式程式碼
					   // 不要呼叫圖片訊息的 CStatic::OnPaint()

	//獲得客戶區域大小
	CRect rectClient;
	GetClientRect(&rectClient);
	int iClientW = rectClient.Width();
	int iClientH = rectClient.Height();

	//客戶區域填滿白色
	dc.FillSolidRect(&rectClient, RGB(255, 255, 255));

	//計算 boundingbox
	double dWidth = max(m_dUpperWidth, m_dLowerWidth);
	double dHeight = m_dZDepth; 
	double dHe = dHeight * 0.05;

	
	
	//計算 inflat 後的 boundingbox (上下左右各 5 %)
	dWidth *= 1.1;
	dHeight	 *= 1.1;
	double dHalfW = dWidth / 2;
	double dH = dHeight;
	
	//
	CPoint dotLT(0, 0);
	double dRatioX = (double)iClientW / dWidth;
	double dRatioY = (double)iClientH / dHeight;


	////計算放縮比率
	//double dRatioX = iClientW / dWidth;
	//double dRatioY = iClientH / dHeight;
	//double dRatio = min(dRatioX, dRatioY);

	////換算長寬
	//dWidth *= dRatio;
	//dHeight *= dRatio;
	

	//換算上底、下底、高
	/*double dAdjustUpperW = m_dUpperWidth * dRatio;
	double dAdjustLowerW = m_dLowerWidth * dRatio;
	double dAdjustLayerH = m_dZDepth * dRatio;*/
	int iUpperLX, iUpperLY, iUpperRX, iUpperRY;
	int iLowerLX, iLowerLY, iLowerRX, iLowerRY;

	GetCoorD2I(rectClient.TopLeft().x, rectClient.TopLeft().y, rectClient.BottomRight().x, rectClient.BottomRight().y, -dHalfW, dHe, dHalfW, -dH,
		-m_dUpperWidth/2, 0, iUpperLX, iUpperLY);

	GetCoorD2I(rectClient.TopLeft().x, rectClient.TopLeft().y, rectClient.BottomRight().x, rectClient.BottomRight().y, -dHalfW, dHe, dHalfW, -dH,
		m_dUpperWidth / 2, 0, iUpperRX, iUpperRY);

	GetCoorD2I(rectClient.TopLeft().x, rectClient.TopLeft().y, rectClient.BottomRight().x, rectClient.BottomRight().y, -dHalfW, dHe, dHalfW, -dH,
		-m_dLowerWidth / 2, m_dZDepth, iLowerLX, iLowerLY);

	GetCoorD2I(rectClient.TopLeft().x, rectClient.TopLeft().y, rectClient.BottomRight().x, rectClient.BottomRight().y, -dHalfW, dHe, dHalfW, -dH,
		m_dLowerWidth / 2, m_dZDepth, iLowerRX, iLowerRY);

	////換算中心座標
	//int iCenterX = iClientW / 2;
	//int iCenterY = dAdjustLayerH * 0.05;//起始位置會需要留白5%的空間

	//設定線條粗細
	int iPenWidth = 3; 
	CPen pen(PS_SOLID, iPenWidth, RGB(0, 0, 0)); // 黑色實線
	CPen* pPenOld = dc.SelectObject(&pen);

	//繪製梯形
	/*dc.MoveTo(iCenterX - static_cast<int>(dAdjustUpperW/2), iCenterY );
	dc.LineTo(iCenterX + static_cast<int>(dAdjustUpperW / 2), iCenterY );
	dc.LineTo(iCenterX + static_cast<int>(dAdjustLowerW/2), iCenterY + static_cast<int>(dAdjustLayerH));
	dc.LineTo(iCenterX - static_cast<int>(dAdjustLowerW / 2), iCenterY + static_cast<int>(dAdjustLayerH));
	dc.LineTo(iCenterX - static_cast<int>(dAdjustUpperW / 2), iCenterY);*/

	dc.MoveTo(iUpperLX, iUpperLY);
	dc.LineTo(iUpperRX, iUpperRY);
	dc.LineTo(iLowerRX, iLowerRY);
	dc.LineTo(iLowerLX, iLowerLY);
	dc.LineTo(iUpperLX, iUpperLY);


	//還原舊的畫筆
	dc.SelectObject(pPenOld);

	////調整後的矩形大小
	//double dRectH = m_dLayerHeight * dRatio;
	//double dRectW = m_dCuttingSpacing * dRatio;

	// 設定紅色畫筆進行繪製
	CPen redPen(PS_SOLID, 1, RGB(255, 0, 0));
	CPen* pOldRedPen = dc.SelectObject(&redPen);

	//// 計算填滿整個客戶區域的縱橫線的數量
	//int iNumVerticalLines = iClientW / static_cast<int>(dRectW);
	//int iNumHorizontalLines = iClientH / static_cast<int>(dRectH);

	//// 繪製縱線
	//for (int i = 0; i < iNumVerticalLines; i++)
	//{
	//	// 計算縱線的位置
	//	int x = iCenterX + (i - iNumVerticalLines / 2) * dRectW;

	//	// 確保縱線在畫面範圍內
	//	if (x >= 0 && x <= iClientW)
	//	{
	//		// 繪製縱線
	//		dc.MoveTo(x, 0);
	//		dc.LineTo(x, iClientH);
	//	}
	//}

	//// 繪製橫線
	//for (int j = 0; j < iNumHorizontalLines; j++)
	//{
	//	// 計算橫線的位置
	//	int y = iCenterY + j * dRectH;

	//	// 確保橫線在畫面範圍內
	//	if (y >= 0 && y <= iClientH)
	//	{
	//		// 繪製橫線
	//		dc.MoveTo(0, y);
	//		dc.LineTo(iClientW, y);
	//	}
	//}
	int iX, iY;
	//for (double x = -dHalfW; x <= dHalfW; x += m_dCuttingSpacing)
	//{
	//	//繪製縱線
	//	GetCoorD2I(rectClient.TopLeft().x, rectClient.TopLeft().y, rectClient.BottomRight().x, rectClient.BottomRight().y, -dHalfW, 0, dHalfW, dH,
	//		x, 0, iX, iY);

	//	dc.MoveTo(iX, iY);

	//	GetCoorD2I(rectClient.TopLeft().x, rectClient.TopLeft().y, rectClient.BottomRight().x, rectClient.BottomRight().y, -dHalfW, 0, dHalfW, dH,
	//		x, dH, iX, iY);

	//	dc.LineTo(iX, iY);
	//}
	// 從中心向左繪製
	for (double x = 0; x >= -dHalfW; x -= m_dCuttingSpacing)
	{
		int iX, iY;
		// 繪製縱線
		GetCoorD2I(rectClient.TopLeft().x, rectClient.TopLeft().y, rectClient.BottomRight().x, rectClient.BottomRight().y,
			-dHalfW, dHe, dHalfW, -dH, x, 0, iX, iY);

		dc.MoveTo(iX, iY);
		GetCoorD2I(rectClient.TopLeft().x, rectClient.TopLeft().y, rectClient.BottomRight().x, rectClient.BottomRight().y,
			-dHalfW, dHe, dHalfW, -dH, x, dH, iX, iY);

		dc.LineTo(iX, iY);
	}

	// 從中心向右繪製
	for (double x = 0; x <= dHalfW; x += m_dCuttingSpacing)
	{
		int iX, iY;
		// 繪製縱線
		GetCoorD2I(rectClient.TopLeft().x, rectClient.TopLeft().y, rectClient.BottomRight().x, rectClient.BottomRight().y,
			-dHalfW, dHe, dHalfW, -dH, x, 0, iX, iY);

		dc.MoveTo(iX, iY);
		GetCoorD2I(rectClient.TopLeft().x, rectClient.TopLeft().y, rectClient.BottomRight().x, rectClient.BottomRight().y,
			-dHalfW, dHe, dHalfW, -dH, x, dH, iX, iY);

		dc.LineTo(iX, iY);
	}

	for (double y = 0; y <= dH; y += m_dLayerHeight)
	{
		//繪製橫線
		GetCoorD2I(rectClient.TopLeft().x, rectClient.TopLeft().y, rectClient.BottomRight().x, rectClient.BottomRight().y, -dHalfW, dHe, dHalfW, -dH,
			-dHalfW, y, iX, iY);

		dc.MoveTo(iX, iY);

		GetCoorD2I(rectClient.TopLeft().x, rectClient.TopLeft().y, rectClient.BottomRight().x, rectClient.BottomRight().y, -dHalfW, dHe, dHalfW, -dH,
			dHalfW, y, iX, iY);

		dc.LineTo(iX, iY);
	}

	// 還原舊的畫筆
	dc.SelectObject(pOldRedPen);

	// 繪製中心綠色線條
	CPen greenPen(PS_SOLID, 5, RGB(0, 255, 0));
	CPen* pOldGreenPen = dc.SelectObject(&greenPen);

	//繪製 y = 0
	int iLX, iLY, iRX, iRY;
	GetCoorD2I(rectClient.TopLeft().x, rectClient.TopLeft().y, rectClient.BottomRight().x, rectClient.BottomRight().y, -dHalfW, dHe, dHalfW, -dH,
		-dHe, 0, iLX, iRY);

	dc.MoveTo(iLX, iRY);

	GetCoorD2I(rectClient.TopLeft().x, rectClient.TopLeft().y, rectClient.BottomRight().x, rectClient.BottomRight().y, -dHalfW, dHe, dHalfW, -dH,
		-dHe, 0, iLX, iRY);

	dc.LineTo(iLX, iRY);
	//// 繪製垂直線條
	//dc.MoveTo(iCenterX, 0);
	//dc.LineTo(iCenterX, iClientH);

	//繪製 x = 0
	GetCoorD2I(rectClient.TopLeft().x, rectClient.TopLeft().y, rectClient.BottomRight().x, rectClient.BottomRight().y, -dHalfW, dHe, dHalfW, -dH,
		0, 0, iLX, iLY);
	dc.MoveTo(iLX, iLY);


	GetCoorD2I(rectClient.TopLeft().x, rectClient.TopLeft().y, rectClient.BottomRight().x, rectClient.BottomRight().y, -dHalfW, dHe, dHalfW, -dH,
		0, dH, iLX, iLY);

	dc.LineTo(iLX, iLY);
	// 繪製水平線條
	/*dc.MoveTo(0, iCenterY);
	dc.LineTo(iClientW, iCenterY);*/

	// 還原舊的畫筆
	dc.SelectObject(pOldGreenPen);
	dc.SelectObject(pPenOld);
}

/**
*
* void GetCoorD2I(int iCoorLT_X, int iCoorLT_Y, int iCoorRB_X, int iCoorRB_Y, double dCoorLT_X, double dCoorLT_Y, double dCoorRB_X, double dCoorRB_Y,
	double dInputX, double dInputY, int &iOutputX, int &iOutputY)
*	功能說明:
*		兩矩形座標映射，給定一整數座標矩形A(給定左上/右下座標)，給定一浮點數座標矩形B(給定左上/右下座標)，使用者指定矩形A的浮點數座標，函式會回傳矩形B對應的座標
*
*	Input:
*		iCoorLT_X:	整數座標矩形A左上角 X座標(pixel)
*		iCoorLT_Y:	整數座標矩形A左上角 Y座標(pixel)
*		iCoorRB_X:	整數座標矩形A右下角 X座標(pixel)
*		iCoorRB_Y:	整數座標矩形A右下角 Y座標(pixel)
*		dCoorLT_X:	浮點數座標矩形B左上角 X座標(mm)
*		dCoorLT_Y:	浮點數座標矩形B左上角 Y座標(mm)
*		dCoorRB_X:	浮點數座標矩形B右下角 X座標(mm)
*		dCoorRB_Y:	浮點數座標矩形B右下角 Y座標(mm)
*		dInputX:	輸入浮點數座標矩形B X座標(mm)
*		dInputY:	輸入浮點數座標矩形B Y座標(mm)
*
*	Output:
*		dInputX:	數座標矩形A X座標(pixel)
*		dInputY:	數座標矩形A Y座標(pixel)
*
*	Remark:
*		範圍外也會正確
*
*/
void CCutCanvas::GetCoorD2I(int iCoorLT_X, int iCoorLT_Y, int iCoorRB_X, int iCoorRB_Y, double dCoorLT_X, double dCoorLT_Y, double dCoorRB_X, double dCoorRB_Y, double dInputX, double dInputY, int & iOutputX, int & iOutputY)
{
	double dParaX = (dInputX - dCoorLT_X) / (dCoorRB_X - dCoorLT_X);
	double dParaY = (dInputY - dCoorLT_Y) / (dCoorRB_Y - dCoorLT_Y);

	iOutputX = (int)((double)iCoorLT_X + dParaX * (double)(iCoorRB_X - iCoorLT_X));
	iOutputY = (int)((double)iCoorLT_Y - dParaY * (double)(iCoorRB_Y - iCoorLT_Y));
}


