#include "MFCMain.h"
#include "resource.h"


BEGIN_MESSAGE_MAP(MFCMain, CWinApp)
	ON_COMMAND(ID_FILE_QUIT,	&MFCMain::MenuFileQuit)
	ON_COMMAND(ID_FILE_SAVETERRAIN, &MFCMain::MenuFileSaveTerrain)
	ON_COMMAND(ID_EDIT_SELECT, &MFCMain::MenuEditSelect)
	ON_COMMAND(ID_CREATEOBJECT_BOX, &MFCMain::MenuObjectCreateBox)				//Function to run when user wants to create a default box.
	ON_COMMAND(ID_CREATEOBJECT_CUP, &MFCMain::MenuObjectCreateCup)				//Function to run when user wants to create a default cup.
	ON_COMMAND(ID_OBJECT_EDITOBJECTPROPERTIES, &MFCMain::MenuObjectEditObject)	//Function which runs the Edit object dialogue window. 
	ON_COMMAND(ID_BUTTON40001,	&MFCMain::ToolBarButton1)
	ON_UPDATE_COMMAND_UI(ID_INDICATOR_TOOL, &CMyFrame::OnUpdatePage)
END_MESSAGE_MAP()

BOOL MFCMain::InitInstance()
{
	//instanciate the mfc frame
	m_frame = new CMyFrame();
	m_pMainWnd = m_frame;

	m_frame->Create(	NULL,
					_T("World Of Flim-Flam Craft Editor"),
					WS_OVERLAPPEDWINDOW,
					CRect(100, 100, 1024, 768),
					NULL,
					NULL,
					0,
					NULL
				);

	//show and set the window to run and update. 
	m_frame->ShowWindow(SW_SHOW);
	m_frame->UpdateWindow();


	//get the rect from the MFC window so we can get its dimensions
	m_toolHandle = m_frame->m_DirXView.GetSafeHwnd();				//handle of directX child window
	m_frame->m_DirXView.GetClientRect(&WindowRECT);
	m_width		= WindowRECT.Width();
	m_height	= WindowRECT.Height();

	m_ToolSystem.onActionInitialise(m_toolHandle, m_width, m_height);

	return TRUE;
}

int MFCMain::Run()
{
	MSG msg;
	BOOL bGotMsg;

	PeekMessage(&msg, NULL, 0U, 0U, PM_NOREMOVE);

	while (WM_QUIT != msg.message)
	{
		if (true)
		{
			bGotMsg = (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE) != 0);
		}
		else
		{
			bGotMsg = (GetMessage(&msg, NULL, 0U, 0U) != 0);
		}

		if (bGotMsg)
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);

			m_ToolSystem.UpdateInput(&msg);
		}
		else
		{	
			//Checks if a single object has been selected.
			if (!m_ToolSystem.ShouldSelectMultiple())
			{
				//Display the ID of the selected object to the user. 
				int ID = m_ToolSystem.getCurrentSelectionID();
				std::wstring statusString = L"Selected Object: " + std::to_wstring(ID);
				m_ToolSystem.Tick(&msg);

				//send current object ID to status bar in The main frame
				m_frame->m_wndStatusBar.SetPaneText(1, statusString.c_str(), 1);
			}

			else 
			{
				//Compile a string consisting of object IDs in the vector. 
				std::wstring statusString = L"Selected Objects: ";

				for (int i = 0; i < m_ToolSystem.m_selectedObjects.size(); i++)
				{
					statusString += std::to_wstring(m_ToolSystem.m_selectedObjects.at(i));
					statusString += L", ";
				}

				m_ToolSystem.Tick(&msg);
				//Send object ID string to the status bar for display. 
				m_frame->m_wndStatusBar.SetPaneText(1, statusString.c_str(), 1);
			}
		}
	}

	return (int)msg.wParam;
}

void MFCMain::MenuFileQuit()
{
	//will post message to the message thread that will exit the application normally
	PostQuitMessage(0);
}

void MFCMain::MenuFileSaveTerrain()
{
	m_ToolSystem.onActionSaveTerrain();
}

void MFCMain::MenuEditSelect()
{
	//SelectDialogue m_ToolSelectDialogue(NULL, &m_ToolSystem.m_sceneGraph);		//create our dialoguebox //modal constructor
	//m_ToolSelectDialogue.DoModal();	// start it up modal

	//modeless dialogue must be declared in the class.   If we do local it will go out of scope instantly and destroy itself
	m_ToolSelectDialogue.Create(IDD_DIALOG1);	//Start up modeless
	m_ToolSelectDialogue.ShowWindow(SW_SHOW);	//show modeless
	m_ToolSelectDialogue.SetObjectData(&m_ToolSystem.m_sceneGraph, &m_ToolSystem.m_selectedObject);
}

void MFCMain::ToolBarButton1()
{
	
	m_ToolSystem.onActionSave();
}

//Pass appropriate model and texture to the create object function for a box. 
void MFCMain::MenuObjectCreateBox()
{
	std::string objStr = "'database/data/placeholder.cmo'";
	std::string texStr = "'database/data/placeholder.dds'";

	MenuObjectCreateObject(&objStr, &texStr);

}

//Pass appropriate model and texture to the create object function for a cup. 
void MFCMain::MenuObjectCreateCup()
{
	std::string objStr2 = "'database/data/cup._obj.cmo'";
	std::string texStr2 = "'database/data/cup.dds'";

	MenuObjectCreateObject(&objStr2, &texStr2);
}


void MFCMain::MenuObjectCreateObject(std::string* modelPath, std::string* texPath)
{
	//Add object to the scene and database. 
	m_ToolSystem.onActionCreateObject(modelPath, texPath);

}

//Prepare and create edit object window.
void MFCMain::MenuObjectEditObject()
{
	m_editObjectDialogue.Create(IDD_DIALOG3);	//Start up modeless
	m_editObjectDialogue.ShowWindow(SW_SHOW);	//show modeless
	m_editObjectDialogue.SetObjectData(&m_ToolSystem);
}

MFCMain::MFCMain()
{
}


MFCMain::~MFCMain()
{
}
