// SubjectManager.cpp : implementation file
//

#include "stdafx.h"
#include "ExamOnline.h"
#include "SubjectManager.h"
#include "ADOCOnn.h"
#include "SubjectModify.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSubjectManager dialog


CSubjectManager::CSubjectManager(CWnd* pParent /*=NULL*/)
	: CDialog(CSubjectManager::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSubjectManager)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CSubjectManager::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSubjectManager)
	DDX_Control(pDX, IDC_EDIT1, m_subject);
	DDX_Control(pDX, IDC_LIST1, m_subjectlist);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSubjectManager, CDialog)
	//{{AFX_MSG_MAP(CSubjectManager)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	ON_BN_CLICKED(IDC_BUTTON3, OnButton3)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSubjectManager message handlers

BOOL CSubjectManager::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_subjectlist.SetExtendedStyle(LVS_EX_FLATSB   //��ƽ�����ʾ������
		|LVS_EX_FULLROWSELECT					//��������ѡ��
		|LVS_EX_HEADERDRAGDROP					//���������϶�
		|LVS_EX_ONECLICKACTIVATE				//����ѡ����
		|LVS_EX_GRIDLINES						//����������
		);	
	m_subjectlist.InsertColumn(0,"��Ŀ���",LVCFMT_LEFT,130,0);
	m_subjectlist.InsertColumn(1,"��Ŀ����",LVCFMT_LEFT,200,1);
//	MessageBox("subject");
	insertItem();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


//��ӿ�Ŀ
void CSubjectManager::OnButton1() 
{
	CString subject;
	m_subject.GetWindowText(subject);
	CString sql="insert into tb_subject(subject) values('"+subject+"')";
	ADOConn m_ado;
	m_ado.OnInitADOConn();
	if(m_ado.ExecuteSQL((_bstr_t)sql))
	{
			m_subjectlist.DeleteAllItems();
//			MessageBox("��ӿ�Ŀ�ɹ���");
			insertItem();
	}else
	{
		MessageBox("��ӿ�Ŀʧ�ܣ�");
	}
	m_subject.SetWindowText("");
	m_ado.ExitConn();
}


void CSubjectManager::insertItem()
{
	ADOConn m_ado;
	m_ado.OnInitADOConn();
	_RecordsetPtr m_ptr;
	CString sql="select * from tb_subject";
	m_ptr=m_ado.GetRecordSet((_bstr_t)sql);
	while(!m_ptr->adoEOF)
	{
		CString id,name;
		id=(char *)(_bstr_t)m_ptr->GetCollect("id");
		name=(char *)(_bstr_t)m_ptr->GetCollect("subject");
		int index=m_subjectlist.GetItemCount();
		m_subjectlist.InsertItem(index,"");
		m_subjectlist.SetItemText(index,0,id);
		m_subjectlist.SetItemText(index,1,name);
		m_ptr->MoveNext();
	}
	m_ado.ExitConn();
}

//ɾ����Ŀ
void CSubjectManager::OnButton2() 
{
	if(MessageBox("���Ҫɾ����","ϵͳ��ʾ",MB_OKCANCEL|MB_ICONQUESTION)!=IDOK)  return;
	else
	{
	int i=m_subjectlist.GetSelectionMark();
	CString sql;
	CString name=m_subjectlist.GetItemText(i,1);
	sql.Format("delete from tb_subject where subject='%s'",name);
	ADOConn m_ado;
	m_ado.OnInitADOConn();
	if(m_ado.ExecuteSQL((_bstr_t)sql))
	{
			m_subjectlist.DeleteAllItems();
		//	MessageBox("ɾ����Ŀ�ɹ���");
			insertItem();
	}else
	{
		MessageBox("ɾ����Ŀʧ�ܣ�");
	}
	m_ado.ExitConn();
	}
}

//�޸Ŀ�Ŀ
void CSubjectManager::OnButton3() 
{
	int index=m_subjectlist.GetSelectionMark();
	CSubjectModify dlg;
	dlg.id=m_subjectlist.GetItemText(index,0);
	dlg.subject=m_subjectlist.GetItemText(index,1);
	if(dlg.DoModal()==IDOK)
	{
		m_subjectlist.DeleteAllItems();
	//	MessageBox("444");
		insertItem();
	}
}
