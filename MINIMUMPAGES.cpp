// MINIMUMPAGES.cpp : �C���v�������e�[�V���� �t�@�C��
//

#include "stdafx.h"
#include "ClickReporter.h"
#include "MINIMUMPAGES.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMINIMUMPAGES �_�C�A���O


CMINIMUMPAGES::CMINIMUMPAGES(CWnd* pParent /*=NULL*/)
	: CDialog(CMINIMUMPAGES::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMINIMUMPAGES)
		// ���� - ClassWizard �͂��̈ʒu�Ƀ}�b�s���O�p�̃}�N����ǉ��܂��͍폜���܂��B
	//}}AFX_DATA_INIT

	//init m_mnpt
	memset(m_mnp,0,256);

}


void CMINIMUMPAGES::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMINIMUMPAGES)
	DDX_Control(pDX, IDC_MINIMU_PAGES, m_mnp_edit);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMINIMUMPAGES, CDialog)
	//{{AFX_MSG_MAP(CMINIMUMPAGES)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMINIMUMPAGES ���b�Z�[�W �n���h��

void CMINIMUMPAGES::OnOK() 
{
	// TODO: ���̈ʒu�ɂ��̑��̌��ؗp�̃R�[�h��ǉ����Ă�������

	//get line from edit
	m_mnp_edit.GetLine(0,m_mnp,256);

	CDialog::OnOK();
}
