#if !defined(AFX_LICENCE_H__C93115DB_7B50_4381_926E_CB5EDB55FE8E__INCLUDED_)
#define AFX_LICENCE_H__C93115DB_7B50_4381_926E_CB5EDB55FE8E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LICENCE.h : �w�b�_�[ �t�@�C��
//

/////////////////////////////////////////////////////////////////////////////
// CLICENCE �_�C�A���O

class CLICENCE : public CDialog
{
// �R���X�g���N�V����
public:
	CLICENCE(CWnd* pParent = NULL);   // �W���̃R���X�g���N�^

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CLICENCE)
	enum { IDD = IDD_LICENCE_INFO };
	CEdit	m_key;
	CStatic	m_email;
	CStatic	m_expire;
	CStatic	m_username;
	//}}AFX_DATA


// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CLICENCE)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CLICENCE)
	afx_msg void OnClose();
	afx_msg void OnLicenceRegister();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void ShowLicenceInfo();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_LICENCE_H__C93115DB_7B50_4381_926E_CB5EDB55FE8E__INCLUDED_)
