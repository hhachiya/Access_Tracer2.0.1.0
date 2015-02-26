// HostnameResolveThreadParam.h: CHostnameResolveThreadParam クラスのインターフェイス
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_HOSTNAMERESOLVETHREADPARAM_H__A3A087B2_A75C_471D_9FE3_DAE2C3094848__INCLUDED_)
#define AFX_HOSTNAMERESOLVETHREADPARAM_H__A3A087B2_A75C_471D_9FE3_DAE2C3094848__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "stdafx.h"
#include "ClickReporter.h"
#include "ClickReporterDoc.h"
#include "ClickReporterView.h"
#include "MainFrm.h"

class CHostnameResolveThreadParam  
{
public:
	CHostnameResolveThreadParam(CClickReporterDoc* m_Doc, CClickReporterApp* m_App, CClickReporterView* m_View);
	CClickReporterDoc* m_Doc;
	CClickReporterApp* m_App;
	CClickReporterView* m_View;
	virtual ~CHostnameResolveThreadParam();
};

#endif // !defined(AFX_HOSTNAMERESOLVETHREADPARAM_H__A3A087B2_A75C_471D_9FE3_DAE2C3094848__INCLUDED_)
