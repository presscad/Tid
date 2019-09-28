#if !defined(AFX_TOWERTREECTRL_H__60830DE4_02E4_4E38_9016_1A7412A838A3__INCLUDED_)
#define AFX_TOWERTREECTRL_H__60830DE4_02E4_4E38_9016_1A7412A838A3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TowerTreeCtrl.h : header file
//
//#include "SuperDropTarget.h"

/////////////////////////////////////////////////////////////////////////////
// CTowerTreeCtrl window
#define		TVGN_EX_ALL				0x000F
#define		DRAG_DELAY				60	//�Ϸ��ӳ�ʱ��
class CTowerTreeCtrl : public CTreeCtrl
{
	UINT        m_nTimerTicks;		//��������Ķ�ʱ����������ʱ��
	UINT        m_nScrollTimerID;	//��������Ķ�ʱ��
	CPoint      m_ptHover;			//���λ��
	UINT        m_nHoverTimerID;	//������ж�ʱ��
	DWORD       m_dwDragStart;		//������������һ�̵�ʱ��
	BOOL        m_bDragging;		//��ʶ�Ƿ������϶�������
	CImageList* m_pDragImage;		//�϶�ʱ��ʾ��ͼ���б�
	HTREEITEM   m_hItemDragS;		//���϶��Ľڵ�
	HTREEITEM	m_hItemDragD;		//�����϶��Ľڵ�
	BOOL		m_bSelectPending;
	CPoint		m_ptClick;
	HTREEITEM	m_hClickedItem;
	HTREEITEM	m_hFirstSelectedItem;
	BOOL		m_bSelectionComplete;
	
	DROPEFFECT (*DragOverFunc)(CTreeCtrl *pTreeCtrl, COleDataObject* pDataObject, DWORD dwKeyState, CPoint point);
	BOOL (*DropFunc)(CTreeCtrl *pTreeCtrl, COleDataObject* pDataObject, DROPEFFECT dropEffect, CPoint point);
	//���ڵ�֮������Ϸ�ʱ:�����ж��Ϸ�Դ�ڵ��Ƿ�Ϸ��ĺ���
	BOOL (*FireIsValidDragS)(CTowerTreeCtrl *pTreeCtrl, HTREEITEM hItemDragS);
	//���ڵ�֮������Ϸ�ʱ:�����ж��Ϸ�Ŀ��ڵ��Ƿ�Ϸ��ĺ���
	BOOL (*FireIsValidDragD)(CTowerTreeCtrl *pTreeCtrl, HTREEITEM hItemDragS, HTREEITEM hItemDragD);
	//���ڵ�֮������Ϸ�ʱ:�����Ƚ�Դ�ڵ���Ŀ��ڵ��������ͼ���ĺ���
	//����ֵ��<0 Դ�ڵ����ݼ������Ŀ��ڵ�  =0 �������  >0 Դ�ڵ����ݼ������Ŀ��ڵ�
	int (*FireCompareDataLevel)(CTowerTreeCtrl *pTreeCtrl, HTREEITEM hItemDragS, HTREEITEM hItemDragD);
	//����ָ���ڵ�������ӽڵ�ʱ���Խڵ���в����ĺ��� ����TRUE����ֹ����
	int (*FireVisitItem)(CTowerTreeCtrl *pTreeCtrl, HTREEITEM hItem);
	//ѡ��ָ���ڵ�ʱ���Խڵ㴥���Ĳ�������
	int (*FireSelectItem)(CTowerTreeCtrl *pTreeCtrl, HTREEITEM hItem);
// Construction
public:
	CTowerTreeCtrl();
	DECLARE_DYNCREATE(CTowerTreeCtrl)
// Attributes

// Operations
public:
	void SetDragOverFunc(DROPEFFECT (*func)(CTreeCtrl *pTreeCtrl, COleDataObject* pDataObject, DWORD dwKeyState, CPoint point)){DragOverFunc = func;}
	void SetDropFunc(BOOL (*func)(CTreeCtrl *pTreeCtrl, COleDataObject* pDataObject, DROPEFFECT dropEffect, CPoint point)){DropFunc = func;}
	void SetIsValidDragSFunc(BOOL (*func)(CTowerTreeCtrl *pTreeCtrl, HTREEITEM hItemDragS)){FireIsValidDragS = func;}
	void SetIsValidDragDFunc(BOOL (*func)(CTowerTreeCtrl *pTreeCtrl, HTREEITEM hItemDragS, HTREEITEM hItemDragD)){FireIsValidDragD = func;}
	void SetCompareDataLevelFunc(BOOL (*func)(CTowerTreeCtrl *pTreeCtrl, HTREEITEM hItemDragS, HTREEITEM hItemDragD)){FireCompareDataLevel = func;}
	void SetVisitItemFunc(BOOL (*func)(CTowerTreeCtrl *pTreeCtrl, HTREEITEM hItem)){FireVisitItem = func;}
	void SetSelectItemFunc(BOOL (*func)(CTowerTreeCtrl *pTreeCtrl, HTREEITEM hItem)){FireSelectItem = func;}
	void TraverseItem(HTREEITEM hItem);
	HTREEITEM CopyItem(HTREEITEM hBranch, HTREEITEM hNewParent, HTREEITEM hAfter);
	HTREEITEM CopyBranch(HTREEITEM hBranch, HTREEITEM hNewParent, HTREEITEM hAfter);
	//HTREEITEM GetDragSourceItem(){return m_hItemDragS;}
public:
	UINT GetSelectedCount() const;
	HTREEITEM GetNextItem(HTREEITEM hItem, UINT nCode);
	HTREEITEM GetFirstSelectedItem();
	HTREEITEM GetNextSelectedItem(HTREEITEM hItem);
	HTREEITEM GetPrevSelectedItem(HTREEITEM hItem);
	HTREEITEM ItemFromData(DWORD dwData, HTREEITEM hStartAtItem=NULL) const;

	BOOL SelectItemEx(HTREEITEM hItem, BOOL bSelect=TRUE);
	BOOL SelectItems(HTREEITEM hFromItem, HTREEITEM hToItem);
	void ClearSelection(BOOL bMultiOnly=FALSE);
protected:
  void SelectMultiple( HTREEITEM hClickedItem, UINT nFlags, CPoint point );
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTowerTreeCtrl)
	//}}AFX_VIRTUAL

// Implementation
public:
	//CSuperDropTarget m_dropTarget;
	BOOL m_bLMouseDown;
	virtual ~CTowerTreeCtrl();
	virtual	DROPEFFECT OnDragEnter(CWnd* pWnd, COleDataObject* pDataObject, DWORD dwKeyState, CPoint point);
	virtual DROPEFFECT OnDragOver(CWnd* pWnd, COleDataObject* pDataObject, DWORD dwKeyState, CPoint point);
	virtual DROPEFFECT OnDropEx(CWnd* pWnd, COleDataObject* pDataObject, DROPEFFECT dropEffect, DROPEFFECT dropList, CPoint point);
	virtual BOOL OnDrop(CWnd* pWnd, COleDataObject* pDataObject, DROPEFFECT dropEffect, CPoint point);
	//virtual void OnDragLeave(CWnd* pWnd);
protected:
	//{{AFX_MSG(CTowerTreeCtrl)
	afx_msg void OnDestroy();
	afx_msg void OnBegindrag(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg BOOL OnItemexpanding(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg BOOL OnSetfocus(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg BOOL OnKillfocus(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg BOOL OnSelchanged(NMHDR* pNMHDR, LRESULT* pResult);	
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TOWERTREECTRL_H__60830DE4_02E4_4E38_9016_1A7412A838A3__INCLUDED_)
