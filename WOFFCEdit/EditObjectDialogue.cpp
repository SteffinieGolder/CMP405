#include "EditObjectDialogue.h"

#include "stdafx.h"
#include <string>;

//EditObjectDialogue.cpp : implementation file
//

IMPLEMENT_DYNAMIC(EditObjectDialogue, CDialogEx)

//Message map.  Just like MFCMAIN.cpp.  This is where we catch button presses etc and point them to a handy dandy method.
BEGIN_MESSAGE_MAP(EditObjectDialogue, CDialogEx)
	ON_BN_CLICKED(IDOK, &EditObjectDialogue::EditObject)
	ON_LBN_SELCHANGE(IDC_LISTTEX, &EditObjectDialogue::SelectTexture)	//listbox
	ON_LBN_SELCHANGE(IDC_LISTMODEL, &EditObjectDialogue::SelectModel)	//listbox
	ON_BN_CLICKED(IDCANCEL, &EditObjectDialogue::OnBnClickedCancel)
END_MESSAGE_MAP()

EditObjectDialogue::EditObjectDialogue(CWnd* pParent)			//constructor used in modeless
	: CDialogEx(IDD_DIALOG3, pParent)
{
	m_availableTextures.push_back(L"database/data/cup.dds");
	m_availableTextures.push_back(L"database/data/placeholder.dds");

	m_availableModels.push_back(L"database/data/cup._obj.cmo");
	m_availableModels.push_back(L"database/data/placeholder.cmo");
}

EditObjectDialogue::~EditObjectDialogue()
{
}

void EditObjectDialogue::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LISTTEX, m_texListBox);
	DDX_Control(pDX, IDC_LISTMODEL, m_modelListBox);
	DDX_Control(pDX, IDC_SELECTIDLIST, m_selectIDBox);
}

///pass through pointers to the data in the tool we want to manipulate
void EditObjectDialogue::SetObjectData(std::vector<SceneObject>* SceneGraph, int* selectedItem, ToolMain* tool)
{
	for (int i = 0; i < m_availableTextures.size(); i++)
	{
		std::wstring listBoxEntry = m_availableTextures[i];
		m_texListBox.AddString(listBoxEntry.c_str());
	}

	for (int i = 0; i < m_availableModels.size(); i++)
	{
		std::wstring listBoxEntry = m_availableModels[i];
		m_modelListBox.AddString(listBoxEntry.c_str());
	}

	m_selectedObjectID = selectedItem;
	std::wstring listBoxEntry = std::to_wstring(*m_selectedObjectID);
	m_selectIDBox.AddString(listBoxEntry.c_str());

	m_sceneGraph = SceneGraph;
	m_toolObject = tool;

	//roll through all the objects in the scene graph and put an entry for each in the listbox
	int numSceneObjects = m_sceneGraph->size();
	for (int i = 0; i < numSceneObjects; i++)
	{
		int currentID = (m_sceneGraph->at(i).ID);

		if (currentID == *m_selectedObjectID)
		{
			selectedObj = &(m_sceneGraph->at(i));
		}
	}
}

void EditObjectDialogue::End()
{
	modelChoice.clear();
	texChoice.clear();
	DestroyWindow();	//destory the window properly.  INcluding the links and pointers created.  THis is so the dialogue can start again. 
}

void EditObjectDialogue::EditObject()
{
	if (selectedObj)
	{
		if (modelChoice.size() != 0)
		{
			selectedObj->model_path = std::string(modelChoice.begin(), modelChoice.end());
		}

		if (texChoice.size() != 0)
		{
			selectedObj->tex_diffuse_path = std::string(texChoice.begin(), texChoice.end());
		}
	}

	m_toolObject->UpdateSceneGraph();
	End();
}

void EditObjectDialogue::SelectModel()
{
	int index = m_modelListBox.GetCurSel();
	CString currentSelectionValue;

	m_modelListBox.GetText(index, currentSelectionValue);
	modelChoice = currentSelectionValue;
}

void EditObjectDialogue::SelectTexture()
{
	int index = m_texListBox.GetCurSel();
	CString currentSelectionValue;

	m_texListBox.GetText(index, currentSelectionValue);

	texChoice = currentSelectionValue;
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
	CDialogEx::OnOK();
}



void EditObjectDialogue::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnCancel();
	End();
}
