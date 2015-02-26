// DetailReport.cpp : �C���v�������e�[�V���� �t�@�C��
//

#include "stdafx.h"
#include "ClickReporter.h"
#include "DetailReport.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDetailReport �_�C�A���O


CDetailReport::CDetailReport(CWnd* pParent /*=NULL*/)
	: CDialog(CDetailReport::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDetailReport)
		// ���� - ClassWizard �͂��̈ʒu�Ƀ}�b�s���O�p�̃}�N����ǉ��܂��͍폜���܂��B
	//}}AFX_DATA_INIT
}


void CDetailReport::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDetailReport)
	DDX_Control(pDX, IDC_DETAIL, m_detail);
	//}}AFX_DATA_MAP

	if(!m_detail.GetHeaderCtrl()->GetItemCount()){
		m_detail.InsertColumn(0,"",LVCFMT_LEFT,18,-1);
		m_detail.InsertColumn(1,"�A�N�Z�X����",LVCFMT_LEFT,180,-1);
		m_detail.InsertColumn(2,"�{���y�[�W",LVCFMT_LEFT,200,-1);

		//Full Row Select
		ListView_SetExtendedListViewStyle(m_detail.m_hWnd, LVS_EX_FULLROWSELECT );
	}

	// set image list
	CImageList* m_pImage = new CImageList();
	m_pImage->Create(16,16,TRUE,4,4);
	m_pImage->Add(AfxGetApp()->LoadIcon(IDI_WAYIN));
	m_pImage->Add(AfxGetApp()->LoadIcon(IDI_WAYOUT));
	m_pImage->Add(AfxGetApp()->LoadIcon(IDI_MIDDLE));
	m_pImage->Add(AfxGetApp()->LoadIcon(IDI_WAYINOUT));
	m_detail.SetImageList(m_pImage,LVSIL_SMALL);

	//set data at list
	for(unsigned int i=0;i<details.size();i++){
		int nItem = m_detail.InsertItem(i, "", 0);

		if(i==0){
			if(details.size() == 1)
				m_detail.SetItem( nItem, 0, LVIF_IMAGE, "", 3, 0, 0, 0);	//wayinout
			else
				m_detail.SetItem( nItem, 0, LVIF_IMAGE, "", 0, 0, 0, 0);	//wayin
		}else if(i==details.size()-1)
			m_detail.SetItem( nItem, 0, LVIF_IMAGE, "", 1, 0, 0, 0);		//wayout
		else
			m_detail.SetItem( nItem, 0, LVIF_IMAGE, "", 2, 0, 0, 0);		//middle

		for(unsigned int j=0;j< details[i].size();j++)
			m_detail.SetItem(nItem, j+1, LVIF_TEXT, details[i][j].c_str(), 0, 0, 0, 0);
	}
}


BEGIN_MESSAGE_MAP(CDetailReport, CDialog)
	//{{AFX_MSG_MAP(CDetailReport)
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_DETAIL_COPY_AS_IT_IS, OnDetailCopyAsItIs)
	ON_COMMAND(ID_DETAIL_COPY_EXCHANGE_DATE_CLIENT, OnDetailCopyExchangeDateClient)
	ON_COMMAND(ID_VIEW_PAGE, OnViewPage)
	ON_WM_CANCELMODE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDetailReport ���b�Z�[�W �n���h��

void CDetailReport::SetDetailData(vector< vector< string > > details)
{
	this->details = details;
}

void CDetailReport::OnContextMenu(CWnd* pWnd, CPoint point) 
{
	// TODO: ���̈ʒu�Ƀ��b�Z�[�W �n���h���p�̃R�[�h��ǉ����Ă�������
	//get selected index
	int index = m_detail.GetNextItem(-1,LVNI_SELECTED);

	//show menu
	if(index >= 0){	
		CMenu menu;
		menu.LoadMenu(MAKEINTRESOURCE(IDR_MENU_DETAIL));
		CMenu* submenu = menu.GetSubMenu(0);
		submenu->TrackPopupMenu(TPM_CENTERALIGN,point.x,point.y,this);
	}
}


void CDetailReport::OnDetailCopyAsItIs() 
{
	// TODO: ���̈ʒu�ɃR�}���h �n���h���p�̃R�[�h��ǉ����Ă�������
	//get selected index
	int index = m_detail.GetNextItem(-1,LVNI_SELECTED);

	if(index >= 0){
		string date = m_detail.GetItemText(index,0);
		string file = m_detail.GetItemText(index,1);
		string agent = m_detail.GetItemText(index,2);

		CString toCopy;
		toCopy.Format("%s\t%s\t%s",date.c_str(),file.c_str(),agent.c_str());

		//############################
		// Get Frame Pointer
		CMainFrame *pFrame = (CMainFrame *) AfxGetMainWnd();
		//############################

		//copy to clipboard
		pFrame->CopyToClipboard(toCopy);
	}
}

void CDetailReport::OnDetailCopyExchangeDateClient() 
{
	// TODO: ���̈ʒu�ɃR�}���h �n���h���p�̃R�[�h��ǉ����Ă�������
	//get selected index
	int index = m_detail.GetNextItem(-1,LVNI_SELECTED);

	if(index >= 0){
		string date = m_detail.GetItemText(index,0);
		string file = m_detail.GetItemText(index,1);
		string agent = m_detail.GetItemText(index,2);

		CString toCopy;
		toCopy.Format("%s\t%s\t%s",agent.c_str(),file.c_str(),date.c_str());

		//############################
		// Get Frame Pointer
		CMainFrame *pFrame = (CMainFrame *) AfxGetMainWnd();
		//############################

		//copy to clipboard
		pFrame->CopyToClipboard(toCopy);
	}
}

void CDetailReport::OnViewPage() 
{
	// TODO: ���̈ʒu�ɃR�}���h �n���h���p�̃R�[�h��ǉ����Ă�������
	//get selected index
	int index = m_detail.GetNextItem(-1,LVNI_SELECTED);

	if(index >= 0){
		string date = m_detail.GetItemText(index,1);
		string path = m_detail.GetItemText(index,2);

		//get web_url from registory
		CWinApp* pApp = AfxGetApp();
		string web_url = pApp->GetProfileString("report","web_url");

		if(!web_url.size()){
			AfxMessageBox("�E�F�b�u�T�C�gURL���ݒ肳��Ă��܂���B");
			return;
		}

		CString fqdn;
		fqdn.Format("%s%s",web_url.c_str(),path.c_str());
		::ShellExecute(NULL,"open",fqdn,NULL,NULL,SW_SHOWNORMAL);
	}	
}

BOOL CDetailReport::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: ���̈ʒu�ɏ������̕⑫������ǉ����Ă�������
	SetWindowText(m_strTitle);
	
	return TRUE;  // �R���g���[���Ƀt�H�[�J�X��ݒ肵�Ȃ��Ƃ��A�߂�l�� TRUE �ƂȂ�܂�
	              // ��O: OCX �v���p�e�B �y�[�W�̖߂�l�� FALSE �ƂȂ�܂�
}


