// ClickReporterView.h : CClickReporterView �N���X�̐錾����уC���^�[�t�F�C�X�̒�`�����܂��B
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CLICKREPORTERVIEW_H__A4FC9EB4_B064_4564_ADD3_EF4856F4D808__INCLUDED_)
#define AFX_CLICKREPORTERVIEW_H__A4FC9EB4_B064_4564_ADD3_EF4856F4D808__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <string>
#include <vector>

using namespace std;

class CClickReporterView : public CFormView
{
protected: // �V���A���C�Y�@�\�݂̂���쐬���܂��B
	CClickReporterView();
	DECLARE_DYNCREATE(CClickReporterView)

public:
	//{{AFX_DATA(CClickReporterView)
	enum { IDD = IDD_CLICKREPORTER_FORM };
	CStatic	m_daterange;
	CMonthCalCtrl	m_date_to_calendar;
	CMonthCalCtrl	m_date_from_calendar;
	CListCtrl	m_user_list;
	//}}AFX_DATA

// �A�g���r���[�g
public:
	CClickReporterDoc* GetDocument();

// �I�y���[�V����
public:

// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CClickReporterView)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �̃T�|�[�g
	virtual void OnInitialUpdate(); // �\�z��̍ŏ��̂P�x�����Ăяo����܂��B
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
public:
	int m_sort_index;
	BOOL m_sort_order;
	string m_search_referrer;
	string m_search_wayin;
	string m_search_wayout;
	string m_search_page1;
	string m_search_page2;
	virtual ~CClickReporterView();
	int AddToList(int index);
#ifdef _DEBUG  
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

private:
	static int CALLBACK SortData(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort);

protected:

// �������ꂽ���b�Z�[�W �}�b�v�֐�
protected:
	//{{AFX_MSG(CClickReporterView)
	afx_msg void OnNetConfig();
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnShowDetail();
	afx_msg void OnEditSelectedUser();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnLicenceInfo();
	afx_msg void OnSearch();
	afx_msg void OnDblclkUserList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSearchMinimumPages();
	afx_msg void OnColumnclickUserList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSearchReferrer();
	afx_msg void OnViewReferrerpage();
	afx_msg void OnInsertitemUserList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDateSelect();
	afx_msg void OnSelchangeMonthcalendarTo(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSelchangeMonthcalendarFrom(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSetDate();
	afx_msg void OnSearchNoRobot();
	afx_msg void OnUpdateSearchNoRobot(CCmdUI* pCmdUI);
	afx_msg void OnSearchOnlyMail();
	//}}AFX_MSG
public:
	int m_robot_view_status;
	int m_mail_view_status;
	int view_cnt;
	afx_msg void OnViewAll();
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // ClickReporterView.cpp �t�@�C�����f�o�b�O���̎��g�p����܂��B
inline CClickReporterDoc* CClickReporterView::GetDocument()
   { return (CClickReporterDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_CLICKREPORTERVIEW_H__A4FC9EB4_B064_4564_ADD3_EF4856F4D808__INCLUDED_)
