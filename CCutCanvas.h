#pragma once
#include <afxwin.h>
class CCutCanvas :
	public CStatic
{
public:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnPaint();

public:
	double m_dZDepth;			//�p�x�ΰ�
	double m_dLayerHeight;		//��
	double m_dCuttingSpacing;	//�p�x�μe
	double m_dUpperWidth;		//�W��
	double m_dLowerWidth;		//�U��

	void GetCoorD2I(int iCoorLT_X, int iCoorLT_Y, int iCoorRB_X, int iCoorRB_Y, double dCoorLT_X, double dCoorLT_Y, double dCoorRB_X, double dCoorRB_Y,
		double dInputX, double dInputY, int &iOutputX, int &iOutputY);
};

