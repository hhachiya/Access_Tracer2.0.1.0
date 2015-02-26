// LICENCE.cpp : �C���v�������e�[�V���� �t�@�C��
//

#include "stdafx.h"
#include "ClickReporter.h"
#include "LICENCE.h"
#include "Cipher.h"
#include "Tools.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLICENCE �_�C�A���O


CLICENCE::CLICENCE(CWnd* pParent /*=NULL*/)
	: CDialog(CLICENCE::IDD, pParent)
{
	//{{AFX_DATA_INIT(CLICENCE)
		// ���� - ClassWizard �͂��̈ʒu�Ƀ}�b�s���O�p�̃}�N����ǉ��܂��͍폜���܂��B
	//}}AFX_DATA_INIT
}


void CLICENCE::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLICENCE)
	DDX_Control(pDX, IDC_KEY, m_key);
	DDX_Control(pDX, IDC_EMAIL, m_email);
	DDX_Control(pDX, IDC_EXPIRE, m_expire);
	DDX_Control(pDX, IDC_USERNAME, m_username);
	//}}AFX_DATA_MAP
	// set licence file path

	ShowLicenceInfo();
}


BEGIN_MESSAGE_MAP(CLICENCE, CDialog)
	//{{AFX_MSG_MAP(CLICENCE)
	ON_BN_CLICKED(IDC_CLOSE, OnClose)
	ON_BN_CLICKED(IDC_LICENCE_REGISTER, OnLicenceRegister)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLICENCE ���b�Z�[�W �n���h��

void CLICENCE::OnClose() 
{
	// TODO: ���̈ʒu�ɃR���g���[���ʒm�n���h���p�̃R�[�h��ǉ����Ă�������
	CDialog::OnOK();
}

void CLICENCE::OnLicenceRegister() 
{
	// TODO: ���̈ʒu�ɃR���g���[���ʒm�n���h���p�̃R�[�h��ǉ����Ă�������
	char line[1024];
	int l = m_key.GetLine(0,line,1024);
	line[l] = '\0';

	// if key is less than 10 characters
	if(l < 10){
		AfxMessageBox("���C�Z���X�L�[�����͂���Ă��܂���");
		return;
	}

	// check token character :
	int tok_cnt = 0;
	for(unsigned int i=0;i<strlen(line);i++)
		if(line[i] == ':') tok_cnt++;

	if(tok_cnt < 2){
		AfxMessageBox("�s���ȃ��C�Z���X�L�[�����͂���܂����B");
		return;
	}

	// check the expire date given in key
	int dates;
	if((dates = GetDatesToExpire(line)) == -1000){
		AfxMessageBox("�s���ȃ��C�Z���X�L�[�����͂���܂����B");
		return;
	}else if(dates < 0){
		AfxMessageBox("���C�Z���X�̊������؂�Ă��܂��B�w�����ĉ������B");
		return;
	}

	char lfilename[256];
	GetLicenceFilePath(lfilename);

	// if licence file exists or not
	if(::GetFileAttributes(lfilename) != 0xFFFFFFFF){
		//open file
		CFile lfile(lfilename,CFile::modeCreate|CFile::modeWrite);
		lfile.Write(line,strlen(line));
		lfile.Close();
	}
	ShowLicenceInfo();
}

void CLICENCE::ShowLicenceInfo()
{
	//########################################
	//# Get Licence Information From File
	//########################################
	char lfilename[256];
	GetLicenceFilePath(lfilename);

	// if licence file exists or not
	if(::GetFileAttributes(lfilename) != 0xFFFFFFFF){
		char line[1024];

		// open file
		CFile lfile(lfilename,CFile::modeRead);
		int l = lfile.Read(line,1024);
		line[l] = '\0';
		lfile.Close();

		// seperate line by : and get name and email expire
		CString name = strtok(line,":");			//name
		CString email = strtok(NULL,":");			//email
		CString expire_s = strtok(NULL,":");		//expire

		// decode expire
		CCipher* cipher = new CCipher(name,email,expire_s);
		if(cipher->decode() == FALSE) return;

		// Set each data at static control
		m_username.SetWindowText(cipher->name);
		m_email.SetWindowText(cipher->email);
		m_expire.SetWindowText(cipher->expire);
	}
	//########################################
	//# Get Licence Information From File
	//########################################

}
