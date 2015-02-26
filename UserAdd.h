#pragma warning (disable: 4786)	//to eliminate wrong VC warnings concerning STL
#include <string>
using namespace std;
#if !defined(AFX_USERADD_H__DBE1A5D0_0C83_4B17_96FC_CC2CFDC8EE90__INCLUDED_)
#define AFX_USERADD_H__DBE1A5D0_0C83_4B17_96FC_CC2CFDC8EE90__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// UserAdd.h : �w�b�_�[ �t�@�C��
//

/////////////////////////////////////////////////////////////////////////////
// CUserAdd �_�C�A���O

class CUserAdd : public CDialog
{
// �R���X�g���N�V����
public:
	CString m_buttonTitle;
	CString m_strTitle;
	char m_mail_address[256];
	char m_name[256];
	char m_company[256];
	char m_item1[256];
	char m_item2[256];
	CUserAdd(CWnd* pParent = NULL);   // �W���̃R���X�g���N�^
	void SetData(string address, string name, string company, string item1, string item2);
// �_�C�A���O �f�[�^
	//{{AFX_DATA(CUserAdd)
	enum { IDD = IDD_USER_ADD };
	CButton	m_ok_button;
	CEdit	m_name_edit;
	CEdit	m_item2_edit;
	CEdit	m_item1_edit;
	CEdit	m_company_edit;
	CEdit	m_mail_address_edit;
	//}}AFX_DATA


// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CUserAdd)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CUserAdd)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_USERADD_H__DBE1A5D0_0C83_4B17_96FC_CC2CFDC8EE90__INCLUDED_)
