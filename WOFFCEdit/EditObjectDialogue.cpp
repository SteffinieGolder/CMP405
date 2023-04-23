#include "EditObjectDialogue.h"

#include "stdafx.h"

//EditObjectDialogue.cpp : implementation file
//

IMPLEMENT_DYNAMIC(EditObjectDialogue, CDialogEx)

//Message map.  Just like MFCMAIN.cpp.  This is where we catch button presses etc and point them to a handy dandy method.
BEGIN_MESSAGE_MAP(EditObjectDialogue, CDialogEx)
	ON_COMMAND(IDOK, &EditObjectDialogue::End)					//ok button
	ON_BN_CLICKED(IDOK, &EditObjectDialogue::OnBnClickedOk)
	//ON_LBN_SELCHANGE(IDC_LIST1, &CreateObjectDialogue::CreateObject)	//listbox
END_MESSAGE_MAP()

EditObjectDialogue::EditObjectDialogue(CWnd* pParent)			//constructor used in modeless
	: CDialogEx(IDD_DIALOG3, pParent)
{
}

EditObjectDialogue::~EditObjectDialogue()
{
}

void EditObjectDialogue::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	///DDX_Control(pDX, IDC_LIST1, m_listBox);
}

void EditObjectDialogue::End()
{
	DestroyWindow();	//destory the window properly.  INcluding the links and pointers created.  THis is so the dialogue can start again. 
}

void EditObjectDialogue::EditObject()
{
}

BOOL EditObjectDialogue::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	//uncomment for modal only
/*	//roll through all the objects in the scene graph and put an entry for each in the listbox
	int numSceneObjects = m_sceneGraph->size();
	for (size_t i = 0; i < numSceneObjects; i++)
	{
		//easily possible to make the data string presented more complex. showing other columns.
		std::wstring listBoxEntry = std::to_wstring(m_sceneGraph->at(i).ID);
		m_listBox.AddString(listBoxEntry.c_str());
	}*/

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void EditObjectDialogue::PostNcDestroy()
{
}

void EditObjectDialogue::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnOK();
}

