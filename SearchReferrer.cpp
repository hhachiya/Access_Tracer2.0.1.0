// SearchReferrer.cpp : �C���v�������e�[�V���� �t�@�C��
//

#include "stdafx.h"
#include "ClickReporter.h"
#include "SearchReferrer.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSearchReferrer �_�C�A���O


CSearchReferrer::CSearchReferrer(CWnd* pParent /*=NULL*/)
	: CDialog(CSearchReferrer::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSearchReferrer)
		// ���� - ClassWizard �͂��̈ʒu�Ƀ}�b�s���O�p�̃}�N����ǉ��܂��͍폜���܂��B
	//}}AFX_DATA_INIT

	//initialize variables
	memset(m_referrer,0,512);
}


void CSearchReferrer::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSearchReferrer)
	DDX_Control(pDX, IDC_SEARCH_REFERRER, m_referrer_edit);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSearchReferrer, CDialog)
	//{{AFX_MSG_MAP(CSearchReferrer)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSearchReferrer ���b�Z�[�W �n���h��

void CSearchReferrer::OnOK() 
{
	// TODO: ���̈ʒu�ɂ��̑��̌��ؗp�̃R�[�h��ǉ����Ă�������
	
	//get each data from edit
	m_referrer_edit.GetLine(0,m_referrer,512);
	
	CDialog::OnOK();
}
