// ClickReporter.h : CLICKREPORTER �A�v���P�[�V�����̃��C�� �w�b�_�[ �t�@�C��
//
#if !defined(AFX_CLICKREPORTER_H__E6A141B4_6CD3_4D8A_A2E1_96A494BFDD9F__INCLUDED_)
#define AFX_CLICKREPORTER_H__E6A141B4_6CD3_4D8A_A2E1_96A494BFDD9F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // ���C�� �V���{��

#include <string>
using namespace std;

/////////////////////////////////////////////////////////////////////////////
// CClickReporterApp:
// ���̃N���X�̓���̒�`�Ɋւ��Ă� ClickReporter.cpp �t�@�C�����Q�Ƃ��Ă��������B
//

class CClickReporterApp : public CWinApp
{
public:
	//int GetDatesToExpire(CString key="");
	CClickReporterApp();
	CProgressCtrl*	m_wndProgressCtrl;

// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CClickReporterApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
	//{{AFX_MSG(CClickReporterApp)
	afx_msg void OnAppAbout();
		// ���� - ClassWizard �͂��̈ʒu�Ƀ����o�֐���ǉ��܂��͍폜���܂��B
		//        ���̈ʒu�ɐ��������R�[�h��ҏW���Ȃ��ł��������B
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_CLICKREPORTER_H__E6A141B4_6CD3_4D8A_A2E1_96A494BFDD9F__INCLUDED_)
