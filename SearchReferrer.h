#if !defined(AFX_SEARCHREFERRER_H__741F5CE2_3EC1_45F6_83B0_ECCCB230CD85__INCLUDED_)
#define AFX_SEARCHREFERRER_H__741F5CE2_3EC1_45F6_83B0_ECCCB230CD85__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SearchReferrer.h : �w�b�_�[ �t�@�C��
//

/////////////////////////////////////////////////////////////////////////////
// CSearchReferrer �_�C�A���O

class CSearchReferrer : public CDialog
{
// �R���X�g���N�V����
public:
	char m_referrer[512];
	CSearchReferrer(CWnd* pParent = NULL);   // �W���̃R���X�g���N�^

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CSearchReferrer)
	enum { IDD = IDD_SEARCH_REFERRER };
	CEdit	m_referrer_edit;
	//}}AFX_DATA


// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CSearchReferrer)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CSearchReferrer)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_SEARCHREFERRER_H__741F5CE2_3EC1_45F6_83B0_ECCCB230CD85__INCLUDED_)
