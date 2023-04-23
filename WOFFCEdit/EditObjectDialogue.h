#pragma once
#include "afxdialogex.h"
#include "resource.h"
#include "afxwin.h"

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
	afx_msg void End();		//kill the dialogue
	afx_msg void EditObject();


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


