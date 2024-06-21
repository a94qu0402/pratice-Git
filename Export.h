#include "pch.h"



__declspec(dllexport) void PASCAL SetParametersDialog();
__declspec(dllexport) bool PASCAL GetFirstCutPath(double* pCoorX, double* pCoorZ);
__declspec(dllexport) bool PASCAL GetNextCutPath(double* pCoorX, double* pCoorZ);
