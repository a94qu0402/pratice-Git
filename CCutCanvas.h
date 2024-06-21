#pragma once
#include <afxwin.h>
class CCutCanvas :
	public CStatic
{
public:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnPaint();

public:
	double m_dZDepth;			//小矩形高
	double m_dLayerHeight;		//高
	double m_dCuttingSpacing;	//小矩形寬
	double m_dUpperWidth;		//上底
	double m_dLowerWidth;		//下底

	void GetCoorD2I(int iCoorLT_X, int iCoorLT_Y, int iCoorRB_X, int iCoorRB_Y, double dCoorLT_X, double dCoorLT_Y, double dCoorRB_X, double dCoorRB_Y,
		double dInputX, double dInputY, int &iOutputX, int &iOutputY);
};

