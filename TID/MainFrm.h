// MainFrm.h : CMainFrame ��Ľӿ�
//

#include <afxframewndex.h>


#include "DialogPanel.h"
#include "TowerTreeDlg.h"
#include "TowerPropertyDlg.h"

#pragma once
class CMainFrame : public CFrameWndEx
{
	
protected: // �������л�����
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// ����
public:

// ����
public:

// ��д
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//virtual BOOL LoadFrame(UINT nIDResource, DWORD dwDefaultStyle = WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, CWnd* pParentWnd = NULL, CCreateContext* pContext = NULL);

// ʵ��
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
	CTowerTreeDlg* GetTowerTreePage() { return (CTowerTreeDlg*)m_towerTreeView.GetDlgPtr(); }
	CTowerPropertyDlg* GetTowerPropertyPage() { return (CTowerPropertyDlg*)m_towerPropertyView.GetDlgPtr(); }

protected:  // �ؼ���Ƕ���Ա
	//CMouseStatusBar m_wndStatusBar;
	CMFCToolBar     m_wndToolBar;
	CDialogPanel	m_towerPropertyView;
	CDialogPanel	m_towerTreeView;

// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnApplicationLook(UINT id);
	DECLARE_MESSAGE_MAP()
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
};


