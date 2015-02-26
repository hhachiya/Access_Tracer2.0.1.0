// ClickReporter.cpp : �A�v���P�[�V�����p�N���X�̋@�\��`���s���܂��B
//

#include "stdafx.h"
#include "ClickReporter.h"

#include "MainFrm.h"
#include "ClickReporterDoc.h"
#include "ClickReporterView.h"
#include "Cipher.h"
#include "LICENCE.h"
#include "Tools.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CClickReporterApp

BEGIN_MESSAGE_MAP(CClickReporterApp, CWinApp)
	//{{AFX_MSG_MAP(CClickReporterApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
		// ���� - ClassWizard �͂��̈ʒu�Ƀ}�b�s���O�p�̃}�N����ǉ��܂��͍폜���܂��B
		//        ���̈ʒu�ɐ��������R�[�h��ҏW���Ȃ��ł��������B
	//}}AFX_MSG_MAP
	// �W���̃t�@�C����{�h�L�������g �R�}���h
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CClickReporterApp �N���X�̍\�z

CClickReporterApp::CClickReporterApp()
{
	// TODO: ���̈ʒu�ɍ\�z�p�R�[�h��ǉ����Ă��������B
	// ������ InitInstance ���̏d�v�ȏ��������������ׂċL�q���Ă��������B
}

/////////////////////////////////////////////////////////////////////////////
// �B��� CClickReporterApp �I�u�W�F�N�g

CClickReporterApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CClickReporterApp �N���X�̏�����

BOOL CClickReporterApp::InitInstance()
{
	AfxEnableControlContainer();

	// �W���I�ȏ���������
	// ���������̋@�\���g�p�����A���s�t�@�C���̃T�C�Y��������
	// ��������Έȉ��̓���̏��������[�`���̒�����s�K�v�Ȃ���
	// ���폜���Ă��������B

#ifdef _AFXDLL
	Enable3dControls();		// ���L DLL �̒��� MFC ���g�p����ꍇ�ɂ͂������Ăяo���Ă��������B
#else
	Enable3dControlsStatic();	// MFC �ƐÓI�Ƀ����N���Ă���ꍇ�ɂ͂������Ăяo���Ă��������B
#endif

	// �ݒ肪�ۑ�����鉺�̃��W�X�g�� �L�[��ύX���܂��B
	// TODO: ���̕�������A��Ж��܂��͏����ȂǓK�؂Ȃ��̂�
	// �ύX���Ă��������B
	SetRegistryKey(_T("Interlog"));
	LoadStdProfileSettings();  // �W���� INI �t�@�C���̃I�v�V���������[�ނ��܂� (MRU ���܂�)

	// �A�v���P�[�V�����p�̃h�L�������g �e���v���[�g��o�^���܂��B�h�L�������g �e���v���[�g
	//  �̓h�L�������g�A�t���[�� �E�B���h�E�ƃr���[���������邽�߂ɋ@�\���܂��B

	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CClickReporterDoc),
		RUNTIME_CLASS(CMainFrame),       // ���C�� SDI �t���[�� �E�B���h�E
		RUNTIME_CLASS(CClickReporterView));
	AddDocTemplate(pDocTemplate);

	// DDE�Afile open �ȂǕW���̃V�F�� �R�}���h�̃R�}���h���C������͂��܂��B
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// �R�}���h���C���Ńf�B�X�p�b�` �R�}���h���w�肵�܂��B
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// ���C�� �E�B���h�E�����������ꂽ�̂ŁA�\���ƍX�V���s���܂��B
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();

	/*
	// chang the path of INI file
	if( m_pszProfileName ) {
		delete ((void*)m_pszProfileName);
		m_pszProfileName = new char[MAX_PATH];
		if( !m_pszProfileName ) {
			AfxMessageBox("�������s���G���[�ł��B");
			return FALSE;
		}
		::GetCurrentDirectory(MAX_PATH, (LPTSTR)m_pszProfileName);
		AfxMessageBox(m_pszProfileName);
		strcat((LPTSTR)m_pszProfileName, "\\ClickReporter.ini");
	}
	*/

	//##################################
	// Licence Stuff
	//##################################
	// set licence file path
	char lfilename[256];
	GetLicenceFilePath(lfilename);
	
	// if licence file exists or not
	if(::GetFileAttributes(lfilename) != 0xFFFFFFFF){

		// get days left to expire date
		int left_day;
		if((left_day = GetDatesToExpire()) == -1000){
			AfxMessageBox("�s���ȃ��C�Z���X�L�[���o�^����Ă��܂��B���C�Z���X���w�����Ă��������B");

			CLICENCE dlg;
			dlg.DoModal();
			//return 0;
		}

		// 
		if(left_day >= 0 && left_day <= 15){
			CString msg;
			msg.Format(_T("���C�Z���X�̊����܂ŁA����%d���ł��B"),left_day);
			AfxMessageBox(msg);
		}else if(left_day < 0){
			CString msg;
			msg.Format(_T("���C�Z���X�̊������؂�܂����B�w�����Ă��������B"),left_day);
			AfxMessageBox(msg);

			CLICENCE dlg;
			dlg.DoModal();
			//return 0;
		}

	}else{
		// get current time
		CTime current = CTime::GetCurrentTime();
		time_t current_b = current.GetTime();		//seconds

		//open file
		CFile lfile(lfilename,CFile::modeCreate|CFile::modeWrite);

		// set expire time after 15 days 
		time_t expire_b = current_b + 86400*15;
		CTime expire(expire_b);

		CString expire_s = expire.Format("%Y/%m/%d");

		// cipher
		CCipher* cipher = new CCipher("Trial","Trial",expire_s);
		cipher->encode();

		lfile.Write(cipher->key,cipher->key.GetLength());
		lfile.Close();
	}
	//##################################

	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// �A�v���P�[�V�����̃o�[�W�������Ŏg���� CAboutDlg �_�C�A���O

class CAboutDlg : public CDialog
{
public:

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA
	CAboutDlg();

	// ClassWizard ���z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �̃T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:
	//{{AFX_MSG(CAboutDlg)
		// ���b�Z�[�W �n���h���͂���܂���B
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// ���b�Z�[�W �n���h���͂���܂���B
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// �_�C�A���O�����s���邽�߂̃A�v���P�[�V���� �R�}���h
void CClickReporterApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}
