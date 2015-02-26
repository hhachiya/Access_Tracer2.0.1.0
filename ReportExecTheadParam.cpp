// ReportExecTheadParam.cpp: CReportExecTheadParam クラスのインプリメンテーション
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ClickReporter.h"
#include "ReportExecTheadParam.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// 構築/消滅
//////////////////////////////////////////////////////////////////////

CReportExecTheadParam::CReportExecTheadParam(CClickReporterDoc* m_Doc, CClickReporterApp* m_App, CClickReporterView* m_View)
{
	this->m_Doc = m_Doc;
	this->m_App = m_App;
	this->m_View = m_View;
}

CReportExecTheadParam::~CReportExecTheadParam()
{

}
