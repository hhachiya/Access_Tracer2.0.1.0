#if !defined(AFX_MINIMUMPAGES_H__18CBACBC_A972_4F56_902B_F4715356C1DA__INCLUDED_)
#define AFX_MINIMUMPAGES_H__18CBACBC_A972_4F56_902B_F4715356C1DA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MINIMUMPAGES.h : �w�b�_�[ �t�@�C��
//

/////////////////////////////////////////////////////////////////////////////
// CMINIMUMPAGES �_�C�A���O

class CMINIMUMPAGES : public CDialog
{
// �R���X�g���N�V����
public:
	char m_mnp[256];
	CMINIMUMPAGES(CWnd* pParent = NULL);   // �W���̃R���X�g���N�^

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CMINIMUMPAGES)
	enum { IDD = IDD_MINIMUM_PAGES };
	CEdit	m_mnp_edit;
	//}}AFX_DATA


// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CMINIMUMPAGES)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CMINIMUMPAGES)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_MINIMUMPAGES_H__18CBACBC_A972_4F56_902B_F4715356C1DA__INCLUDED_)
