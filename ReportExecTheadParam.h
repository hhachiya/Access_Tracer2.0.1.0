// ReportExecTheadParam.h: CReportExecTheadParam クラスのインターフェイス
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_REPORTEXECTHEADPARAM_H__811A88BB_880E_4556_9174_C720D6C5A94C__INCLUDED_)
#define AFX_REPORTEXECTHEADPARAM_H__811A88BB_880E_4556_9174_C720D6C5A94C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "stdafx.h"
#include "ClickReporter.h"
#include "ClickReporterDoc.h"
#include "ClickReporterView.h"
#include "MainFrm.h"

class CReportExecTheadParam  
{
public:
	CReportExecTheadParam(CClickReporterDoc* m_Doc, CClickReporterApp* m_App, CClickReporterView* m_View);
	CClickReporterDoc* m_Doc;
	CClickReporterApp* m_App;
	CClickReporterView* m_View;
	virtual ~CReportExecTheadParam();
};
#endif // !defined(AFX_REPORTEXECTHEADPARAM_H__811A88BB_880E_4556_9174_C720D6C5A94C__INCLUDED_)
