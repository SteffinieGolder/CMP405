#include "EditObjectDialogue.h"

#include "stdafx.h"
#include <string>
#include <sstream>


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
void EditObjectDialogue::SetObjectData(ToolMain* tool)
{
	m_toolObject = tool;
	m_sceneGraph = &m_toolObject->m_sceneGraph;

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

	if (m_toolObject->ShouldSelectMultiple())
	{
		m_selectedObjectIDs = &m_toolObject->m_selectedObjects;
		//m_selectedObjects = selectedObjects;
		ProcessMultipleObjects();
		
	}

	else {
		m_selectedObjectID = &m_toolObject->m_selectedObject;
		ProcessSingleObject();
	}
}

void EditObjectDialogue::ProcessSingleObject()
{
	std::wstring listBoxEntry = std::to_wstring(*m_selectedObjectID);
	m_selectIDBox.AddString(listBoxEntry.c_str());

	for (int i = 0; i < m_sceneGraph->size(); i++)
	{
		int currentID = (m_sceneGraph->at(i).ID);

		if (currentID == *m_selectedObjectID)
		{
			m_selectedObject = &m_sceneGraph->at(i);
			break;
		}
	}

	if (m_selectedObject)
	{
		pWnd = GetDlgItem(IDC_POSX);
		pWnd->SetWindowText(std::to_wstring(m_selectedObject->posX).c_str());

		pWnd = GetDlgItem(IDC_POSY);
		pWnd->SetWindowText(std::to_wstring(m_selectedObject->posY).c_str());

		pWnd = GetDlgItem(IDC_POSZ);
		pWnd->SetWindowText(std::to_wstring(m_selectedObject->posZ).c_str());

		pWnd = GetDlgItem(IDC_ROTX);
		pWnd->SetWindowText(std::to_wstring(m_selectedObject->rotX).c_str());

		pWnd = GetDlgItem(IDC_ROTY);
		pWnd->SetWindowText(std::to_wstring(m_selectedObject->rotY).c_str());

		pWnd = GetDlgItem(IDC_ROTZ);
		pWnd->SetWindowText(std::to_wstring(m_selectedObject->rotZ).c_str());

		pWnd = GetDlgItem(IDC_SCALEX);
		pWnd->SetWindowText(std::to_wstring(m_selectedObject->scaX).c_str());

		pWnd = GetDlgItem(IDC_SCALEY);
		pWnd->SetWindowText(std::to_wstring(m_selectedObject->scaY).c_str());

		pWnd = GetDlgItem(IDC_SCALEZ);
		pWnd->SetWindowText(std::to_wstring(m_selectedObject->scaZ).c_str());
	}
}

void EditObjectDialogue::ProcessMultipleObjects()
{
	for (int i = 0; i < m_selectedObjectIDs->size(); i++)
	{
		std::wstring listBoxEntry = std::to_wstring(m_selectedObjectIDs->at(i));
		m_selectIDBox.AddString(listBoxEntry.c_str());
	}

	pWnd = GetDlgItem(IDC_POSX);
	pWnd->SetWindowText(std::to_wstring(0).c_str());

	pWnd = GetDlgItem(IDC_POSY);
	pWnd->SetWindowText(std::to_wstring(0).c_str());

	pWnd = GetDlgItem(IDC_POSZ);
	pWnd->SetWindowText(std::to_wstring(0).c_str());

	pWnd = GetDlgItem(IDC_ROTX);
	pWnd->SetWindowText(std::to_wstring(0).c_str());

	pWnd = GetDlgItem(IDC_ROTY);
	pWnd->SetWindowText(std::to_wstring(0).c_str());

	pWnd = GetDlgItem(IDC_ROTZ);
	pWnd->SetWindowText(std::to_wstring(0).c_str());

	pWnd = GetDlgItem(IDC_SCALEX);
	pWnd->SetWindowText(std::to_wstring(1).c_str());

	pWnd = GetDlgItem(IDC_SCALEY);
	pWnd->SetWindowText(std::to_wstring(1).c_str());

	pWnd = GetDlgItem(IDC_SCALEZ);
	pWnd->SetWindowText(std::to_wstring(1).c_str());
}

void EditObjectDialogue::End()
{
	modelChoice.clear();
	texChoice.clear();

	if (m_selectedObjectIDs != NULL)
	{
		m_selectedObjectIDs->clear();
	}

	m_selectedObject = NULL;
	m_selectedObjectID = NULL;
	DestroyWindow();	//destory the window properly.  INcluding the links and pointers created.  THis is so the dialogue can start again. 
}

void EditObjectDialogue::EditObject()
{
	if (m_toolObject->ShouldSelectMultiple()) 
	{
		if (m_selectedObjectIDs->size() != 0)
		{
			EditMultipleObjects();
		}
	}

	else {

		if (m_selectedObject)
		{
			EditSingleObject();
		}
	}

	End();
}

void EditObjectDialogue::EditSingleObject()
{
	if (modelChoice.size() != 0)
	{
		m_selectedObject->model_path = std::string(modelChoice.begin(), modelChoice.end());

	}

	if (texChoice.size() != 0)
	{
		m_selectedObject->tex_diffuse_path = std::string(texChoice.begin(), texChoice.end());
	}

	CString edit_PosX, edit_PosY, edit_PosZ,
		edit_RotX, edit_RotY, edit_RotZ,
		edit_ScaleX, edit_ScaleY, edit_ScaleZ;

	//Position changes////////////////////////////////////////
	pWnd = GetDlgItem(IDC_POSX);
	pWnd->GetWindowText(edit_PosX);
	swscanf_s(edit_PosX, L"%f", &positionX);

	if (positionX > -50 && positionX < 50)
	{
		m_selectedObject->posX = positionX;
	}

	pWnd = GetDlgItem(IDC_POSY);
	pWnd->GetWindowText(edit_PosY);
	swscanf_s(edit_PosY, L"%f", &positionY);

	if (positionY > -50 && positionY < 50)
	{
		m_selectedObject->posY = positionY;
	}

	pWnd = GetDlgItem(IDC_POSZ);
	pWnd->GetWindowText(edit_PosZ);
	swscanf_s(edit_PosZ, L"%f", &positionZ);

	if (positionZ > -50 && positionZ < 50)
	{
		m_selectedObject->posZ = positionZ;
	}

	//Rotation changes//////////////////////////
	pWnd = GetDlgItem(IDC_ROTX);
	pWnd->GetWindowText(edit_RotX);
	swscanf_s(edit_RotX, L"%f", &rotateX);

	if (rotateX >= -360 && rotateX <= 360)
	{
		m_selectedObject->rotX = rotateX;
	}

	pWnd = GetDlgItem(IDC_ROTY);
	pWnd->GetWindowText(edit_RotY);
	swscanf_s(edit_RotY, L"%f", &rotateY);

	if (rotateY >= -360 && rotateY <= 360)
	{
		m_selectedObject->rotY = rotateY;
	}

	pWnd = GetDlgItem(IDC_ROTZ);
	pWnd->GetWindowText(edit_RotZ);
	swscanf_s(edit_RotZ, L"%f", &rotateZ);

	if (rotateZ >= -360 && rotateZ <= 360)
	{
		m_selectedObject->rotZ = rotateZ;
	}

	//scale changes///////////////////////////
	pWnd = GetDlgItem(IDC_SCALEX);
	pWnd->GetWindowText(edit_ScaleX);
	swscanf_s(edit_ScaleX, L"%f", &scaleX);

	if (scaleX > 0)
	{
		m_selectedObject->scaX = scaleX;
	}

	pWnd = GetDlgItem(IDC_SCALEY);
	pWnd->GetWindowText(edit_ScaleY);
	swscanf_s(edit_ScaleY, L"%f", &scaleY);

	if (scaleY > 0)
	{
		m_selectedObject->scaY = scaleY;
	}

	pWnd = GetDlgItem(IDC_SCALEZ);
	pWnd->GetWindowText(edit_ScaleZ);
	swscanf_s(edit_ScaleZ, L"%f", &scaleZ);

	if (scaleZ > 0)
	{
		m_selectedObject->scaZ = scaleZ;
	}

	m_toolObject->UpdateDisplayList();
}

void EditObjectDialogue::EditMultipleObjects()
{
	for (int i = 0; i < m_selectedObjectIDs->size(); i++)
	{
		for (int j = 0; j < m_sceneGraph->size(); j++)
		{
			if (m_selectedObjectIDs->at(i) == m_sceneGraph->at(j).ID)
			{
				if (modelChoice.size() != 0)
				{
					m_sceneGraph->at(j).model_path = std::string(modelChoice.begin(), modelChoice.end());

				}

				if (texChoice.size() != 0)
				{
					m_sceneGraph->at(j).tex_diffuse_path = std::string(texChoice.begin(), texChoice.end());
				}

				CString edit_PosX, edit_PosY, edit_PosZ,
					edit_RotX, edit_RotY, edit_RotZ,
					edit_ScaleX, edit_ScaleY, edit_ScaleZ;

				//Position changes////////////////////////////////////////
				pWnd = GetDlgItem(IDC_POSX);
				pWnd->GetWindowText(edit_PosX);
				swscanf_s(edit_PosX, L"%f", &positionX);

				if (positionX > -50 && positionX < 50)
				{
					m_sceneGraph->at(j).posX = positionX;
				}

				pWnd = GetDlgItem(IDC_POSY);
				pWnd->GetWindowText(edit_PosY);
				swscanf_s(edit_PosY, L"%f", &positionY);

				if (positionY > -50 && positionY < 50)
				{
					m_sceneGraph->at(j).posY = positionY;
				}

				pWnd = GetDlgItem(IDC_POSZ);
				pWnd->GetWindowText(edit_PosZ);
				swscanf_s(edit_PosZ, L"%f", &positionZ);

				if (positionZ > -50 && positionZ < 50)
				{
					m_sceneGraph->at(j).posZ = positionZ;
				}

				//Rotation changes//////////////////////////
				pWnd = GetDlgItem(IDC_ROTX);
				pWnd->GetWindowText(edit_RotX);
				swscanf_s(edit_RotX, L"%f", &rotateX);

				if (rotateX >= -360 && rotateX <= 360)
				{
					m_sceneGraph->at(j).rotX = rotateX;
				}

				pWnd = GetDlgItem(IDC_ROTY);
				pWnd->GetWindowText(edit_RotY);
				swscanf_s(edit_RotY, L"%f", &rotateY);

				if (rotateY >= -360 && rotateY <= 360)
				{
					m_sceneGraph->at(j).rotY = rotateY;
				}

				pWnd = GetDlgItem(IDC_ROTZ);
				pWnd->GetWindowText(edit_RotZ);
				swscanf_s(edit_RotZ, L"%f", &rotateZ);

				if (rotateZ >= -360 && rotateZ <= 360)
				{
					m_sceneGraph->at(j).rotZ = rotateZ;
				}

				//scale changes///////////////////////////
				pWnd = GetDlgItem(IDC_SCALEX);
				pWnd->GetWindowText(edit_ScaleX);
				swscanf_s(edit_ScaleX, L"%f", &scaleX);

				if (scaleX > 0)
				{
					m_sceneGraph->at(j).scaX = scaleX;
				}

				pWnd = GetDlgItem(IDC_SCALEY);
				pWnd->GetWindowText(edit_ScaleY);
				swscanf_s(edit_ScaleY, L"%f", &scaleY);

				if (scaleY > 0)
				{
					m_sceneGraph->at(j).scaY = scaleY;
				}

				pWnd = GetDlgItem(IDC_SCALEZ);
				pWnd->GetWindowText(edit_ScaleZ);
				swscanf_s(edit_ScaleZ, L"%f", &scaleZ);

				if (scaleZ > 0)
				{
					m_sceneGraph->at(j).scaZ = scaleZ;
				}
			}
		}
	}

	m_toolObject->UpdateDisplayList();
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
