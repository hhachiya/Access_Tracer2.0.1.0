#if !defined(AFX_SEARCH_H__308994DA_5885_4249_BB89_BD3AF5B91228__INCLUDED_)
#define AFX_SEARCH_H__308994DA_5885_4249_BB89_BD3AF5B91228__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Search.h : �w�b�_�[ �t�@�C��
//

/////////////////////////////////////////////////////////////////////////////
// CSearch �_�C�A���O

class CSearch : public CDialog
{
// �R���X�g���N�V����
public:
	char m_page1[256];
	char m_page2[256];
	char m_wayin[256];
	char m_wayout[256];
	char m_referrer[256];
	CSearch(CWnd* pParent = NULL);   // �W���̃R���X�g���N�^

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CSearch)
	enum { IDD = IDD_SEARCH };
	CEdit	m_referrer_edit;
	CEdit	m_page1_edit;
	CEdit	m_page2_edit;
	CEdit	m_wayout_edit;
	CEdit	m_wayin_edit;
	//}}AFX_DATA


// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CSearch)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CSearch)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_SEARCH_H__308994DA_5885_4249_BB89_BD3AF5B91228__INCLUDED_)
