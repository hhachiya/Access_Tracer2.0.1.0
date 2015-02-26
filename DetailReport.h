#if !defined(AFX_DETAILREPORT_H__696C5DD8_A00A_436B_AA85_0DBC02EB7768__INCLUDED_)
#define AFX_DETAILREPORT_H__696C5DD8_A00A_436B_AA85_0DBC02EB7768__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// DetailReport.h : �w�b�_�[ �t�@�C��
//
#pragma warning (disable: 4786)	//to eliminate wrong VC warnings concerning STL
#include <string>
#include <vector>
using namespace std;

/////////////////////////////////////////////////////////////////////////////
// CDetailReport �_�C�A���O

class CDetailReport : public CDialog
{
// �R���X�g���N�V����
public:
	CString m_strTitle;
	void SetDetailData(vector< vector< string > > details);
	CDetailReport(CWnd* pParent = NULL);   // �W���̃R���X�g���N�^

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CDetailReport)
	enum { IDD = IDD_DETAIL };
	CListCtrl	m_detail;
	vector < vector<string> > details;
	//}}AFX_DATA

// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CDetailReport)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CDetailReport)
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnDetailCopyAsItIs();
	afx_msg void OnDetailCopyExchangeDateClient();
	afx_msg void OnViewPage();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_DETAILREPORT_H__696C5DD8_A00A_436B_AA85_0DBC02EB7768__INCLUDED_)
