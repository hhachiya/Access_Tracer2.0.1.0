#if !defined(AFX_NET_CONF_H__4BFFEDD4_C632_42E6_9011_DC30B02FA34B__INCLUDED_)
#define AFX_NET_CONF_H__4BFFEDD4_C632_42E6_9011_DC30B02FA34B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// NET_CONF.h : �w�b�_�[ �t�@�C��
//

/////////////////////////////////////////////////////////////////////////////
// CNET_CONF �_�C�A���O

class CNET_CONF : public CDialog
{
// �R���X�g���N�V����
public:
	CNET_CONF(CWnd* pParent = NULL);   // �W���̃R���X�g���N�^

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CNET_CONF)
	enum { IDD = IDD_NET_CONF };
	CEdit	m_tpg;
	CEdit	m_web;
	CEdit	m_sto;
	CEdit	m_lpt;
	CEdit	m_pas;
	CEdit	m_usr;
	CEdit	m_url;
	//}}AFX_DATA


// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CNET_CONF)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CNET_CONF)
	virtual void OnOK();
	afx_msg void OnLogplace0();
	afx_msg void OnLogplace1();
	afx_msg void OnFilePath();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_NET_CONF_H__4BFFEDD4_C632_42E6_9011_DC30B02FA34B__INCLUDED_)
