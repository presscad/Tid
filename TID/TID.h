// TID.h : TID Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error �ڰ������� PCH �Ĵ��ļ�֮ǰ������stdafx.h�� 
#endif
#include "resource.h"       // ������
#include "TIDView.h"
#include "ModCore.h"
// CTIDApp:
// �йش����ʵ�֣������ TID.cpp
//

class CTIDDoc; 
class CTIDApp : public CWinAppEx
{
public:
	BYTE m_ciFileType;		//0.TID_FILE|1.MOD_FILE
	BOOL m_bChildProcess;	//�ӽ���ģʽ
	UINT m_uiActiveHeightSerial;
	UINT m_uiActiveLegSerial[4];
public:
	CTIDApp();
// ��д
public:
	virtual BOOL InitInstance();
	virtual BOOL SaveState(LPCTSTR lpszSectionName = NULL, CFrameImpl* pFrameImpl = NULL);
	CTIDDoc* GetTIDDoc();
	CTIDView* GetTIDView();
	void* GetActiveTowerInstance();
// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CTIDApp theApp;
extern IModModel* gpModModel;
#ifdef NEW_VERSION_TIDCORE
#include "TidCplus.h"
extern ITidModel* gpTidModel;
#endif