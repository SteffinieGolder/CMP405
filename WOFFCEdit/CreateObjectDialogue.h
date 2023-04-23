#pragma once
#include "afxdialogex.h"
#include "resource.h"
#include "afxwin.h"
#include "SceneObject.h"
#include <vector>

// CreateObjectDialogue dialog

class CreateObjectDialogue : public CDialogEx
{
	DECLARE_DYNAMIC(CreateObjectDialogue)

public:
	//CreateObjectDialogue(CWnd* pParent, std::vector<SceneObject>* SceneGraph);   // modal // takes in out scenegraph in the constructor
	CreateObjectDialogue(CWnd* pParent = NULL);
	virtual ~CreateObjectDialogue();
	//void SetObjectData(std::vector<SceneObject>* SceneGraph, int* Selection);	//passing in pointers to the data the class will operate on.

	// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	afx_msg void End();		//kill the dialogue
	afx_msg void CreateObject();	

	//std::vector<SceneObject>* m_sceneGraph;
	//int* m_currentSelection;


	DECLARE_MESSAGE_MAP()
public:
	// Control variable for more efficient access of the listbox
	//CListBox m_listBox;
	virtual BOOL OnInitDialog() override;
	virtual void PostNcDestroy();
	afx_msg void OnBnClickedOk();
	//afx_msg void OnLbnSelchangeList1();
};


INT_PTR CALLBACK CreateObjectProc(HWND   hwndDlg, UINT   uMsg, WPARAM wParam, LPARAM lParam);

