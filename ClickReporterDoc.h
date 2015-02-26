// ClickReporterDoc.h : CClickReporterDoc �N���X�̐錾����уC���^�[�t�F�C�X�̒�`�����܂��B
//
/////////////////////////////////////////////////////////////////////////////
#pragma warning (disable: 4786)	//to eliminate wrong VC warnings concerning STL
#include <string>
#include <vector>
#include <wininet.h>
#include <winsock2.h>
//#include <ws2tcpip.h>
//#include <wspiapi.h>

using namespace std;
#include "CReport.h"

#if !defined(AFX_CLICKREPORTERDOC_H__4ABA8D45_1275_488D_B769_DC68F0EEF4F4__INCLUDED_)
#define AFX_CLICKREPORTERDOC_H__4ABA8D45_1275_488D_B769_DC68F0EEF4F4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CClickReporterDoc : public CDocument
{
protected: // �V���A���C�Y�@�\�݂̂���쐬���܂��B
	CClickReporterDoc();
	DECLARE_DYNCREATE(CClickReporterDoc)

// �A�g���r���[�g
public:

// �I�y���[�V����
public:

//�I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CClickReporterDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
public:
	virtual ~CClickReporterDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// �������ꂽ���b�Z�[�W �}�b�v�֐�
protected:
	//{{AFX_MSG(CClickReporterDoc)
	afx_msg void OnReportExec();
	afx_msg void OnResolveHostname();
	afx_msg void OnStopDataAnalyze();
	afx_msg void OnFileSaveOnlyShown();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	char m_filename[256];
	string m_analyze_status;
	string m_data;
	int m_data_analyze_flag;
	int month_text2num(string month);
	int GetTimeDifference(string stime1, string stime2);
	int GetNumTimeFromWebTime(string webtime, vector<int> &numtime);
	void GetNumTimeFromSofTime(string softime, vector<int> &numtime);
	int m_save_only_shown;
	void decrypt( int seed, char* TheString );
	string decURL( int seed, const char* table, string crypted );
	int m_download_progress;
	vector <CReport> m_report;

	//controlling function header
	static UINT HostnameResolveThread (LPVOID param);
	static UINT AccessDataAnalyzeThread (LPVOID param);
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_CLICKREPORTERDOC_H__4ABA8D45_1275_488D_B769_DC68F0EEF4F4__INCLUDED_)
