// ExamInfoManager.cpp : implementation file
//

#include "stdafx.h"
#include "ExamOnline.h"
#include "ExamInfoManager.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CExamInfoManager dialog


CExamInfoManager::CExamInfoManager(CWnd* pParent /*=NULL*/)
	: CDialog(CExamInfoManager::IDD, pParent)
{
	//{{AFX_DATA_INIT(CExamInfoManager)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CExamInfoManager::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CExamInfoManager)
	DDX_Control(pDX, IDC_LIST1, m_examinfolist);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CExamInfoManager, CDialog)
	//{{AFX_MSG_MAP(CExamInfoManager)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CExamInfoManager message handlers

BOOL CExamInfoManager::OnInitDialog() 
{
	CDialog::OnInitDialog();
		m_examinfolist.SetExtendedStyle(LVS_EX_FLATSB   //��ƽ�����ʾ������
		|LVS_EX_FULLROWSELECT					//��������ѡ��
		|LVS_EX_HEADERDRAGDROP					//���������϶�
		|LVS_EX_ONECLICKACTIVATE				//����ѡ����
		|LVS_EX_GRIDLINES						//����������
		);	
	m_examinfolist.InsertColumn(0,"���",LVCFMT_LEFT,60,0);
	m_examinfolist.InsertColumn(1,"��Ŀ",LVCFMT_LEFT,60,1);
	m_examinfolist.InsertColumn(2,"����",LVCFMT_LEFT,130,2);
	m_examinfolist.InsertColumn(3,"����",LVCFMT_LEFT,200,3);
	m_examinfolist.InsertColumn(4,"��ȷ��",LVCFMT_LEFT,100,4);
	m_examinfolist.InsertColumn(5,"��Ĵ�",LVCFMT_LEFT,100,5);
	m_examinfolist.InsertColumn(6,"��ֵ",LVCFMT_LEFT,60,6);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
