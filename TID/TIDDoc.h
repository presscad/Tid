// TIDDoc.h :  CTIDDoc ��Ľӿ�
//


#pragma once

class CTIDDoc : public CDocument
{
protected: // �������л�����
	CTIDDoc();
	DECLARE_DYNCREATE(CTIDDoc)

// ����
public:

// ����
public:

// ��д
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
// ʵ��
public:
	virtual ~CTIDDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
	CView* GetView(const CRuntimeClass *pClass);
protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnFileOpen();
	afx_msg void OnExportSwapInfoFile();
public:
	virtual void DeleteContents();
};


