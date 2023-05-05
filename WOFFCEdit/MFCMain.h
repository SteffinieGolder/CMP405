#pragma once

#include <afxwin.h> 
#include <afxext.h>
#include <afx.h>
#include "pch.h"
#include "Game.h"
#include "ToolMain.h"
#include "resource.h"
#include "MFCFrame.h"
#include "SelectDialogue.h"
#include "EditObjectDialogue.h"


class MFCMain : public CWinApp 
{
public:
	MFCMain();
	~MFCMain();
	BOOL InitInstance();
	int  Run();

private:

	CMyFrame * m_frame;							//Handle to the frame where all our UI is
	HWND m_toolHandle;							//Handle to the MFC window
	ToolMain m_ToolSystem;						//Instance of Tool System that we interface to. 
	CRect WindowRECT;							//Window area rectangle. 
	SelectDialogue m_ToolSelectDialogue;		//For modeless dialogue, declare it here
	EditObjectDialogue m_editObjectDialogue;	//Edit object dialogue instance. 

	int m_width;		
	int m_height;
	
	//Interface funtions for menu and toolbar etc
	afx_msg void MenuFileQuit();
	afx_msg void MenuFileSaveTerrain();
	afx_msg void MenuEditSelect();
	afx_msg	void ToolBarButton1();
	afx_msg	void MenuObjectEditObject();
	afx_msg	void MenuObjectCreateBox();
	afx_msg	void MenuObjectCreateCup();
	afx_msg void ToolbarDeleteObject();

	void MenuObjectCreateObject(std::string* modelPath, std::string* texPath);


	DECLARE_MESSAGE_MAP()	// required macro for message map functionality  One per class
};
