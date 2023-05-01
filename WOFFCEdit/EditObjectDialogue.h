#pragma once
#include "afxdialogex.h"
#include "resource.h"
#include "afxwin.h"
#include <vector>
#include <string>
#include "SceneObject.h"
#include "ToolMain.h"

class EditObjectDialogue : public CDialogEx
{
	DECLARE_DYNAMIC(EditObjectDialogue)

public:
	EditObjectDialogue(CWnd* pParent = NULL);
	virtual ~EditObjectDialogue();

	// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG3 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void ProcessSingleObject();
	virtual void ProcessMultipleObjects();
	virtual void EditSingleObject();
	virtual void EditMultipleObjects();

	afx_msg void End();		//kill the dialogue
	afx_msg void EditObject();
	afx_msg void SelectModel();	//Item has been selected
	afx_msg void SelectTexture();	//Item has been selected

	std::vector<std::wstring> m_availableTextures;
	std::vector<std::wstring> m_availableModels;
	std::vector<SceneObject>* m_sceneGraph;
	std::vector<int>* m_selectedObjectIDs;
	std::vector<SceneObject>* m_selectedObjects;
	int* m_selectedObjectID;
	SceneObject* m_selectedObject;
	std::wstring texChoice;
	std::wstring modelChoice;
	ToolMain* m_toolObject;
	CWnd* pWnd;



	DECLARE_MESSAGE_MAP()
public:
	// Control variable for more efficient access of the listbox
	CListBox m_texListBox;
	CListBox m_modelListBox;
	CListBox m_selectIDBox;

	float positionX, positionY, positionZ, rotateX, rotateY, rotateZ,
		scaleX, scaleY, scaleZ;

	virtual BOOL OnInitDialog() override;
	virtual void PostNcDestroy();
	virtual void SetObjectData(ToolMain* tool);
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();

	//afx_msg void OnBnClickedChngModel();
	//afx_msg void OnBnClickedChngTex();
	//afx_msg void OnLbnSelchangeList1();
};


INT_PTR CALLBACK CreateObjectProc(HWND   hwndDlg, UINT   uMsg, WPARAM wParam, LPARAM lParam);


