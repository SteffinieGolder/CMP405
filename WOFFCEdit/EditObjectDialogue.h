#pragma once
#include "afxdialogex.h"
#include "resource.h"
#include "afxwin.h"
#include <vector>
#include <string>
#include "SceneObject.h"
#include "ToolMain.h"

/*Class which controls the Edit object dialogue window.
* Object attributes are updated based on the selections made/values entered by the user. 
* Can edit single and multiple objects. 
*/

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
	virtual void ProcessSingleObject();					//Prepare edit window for single object.
	virtual void ProcessMultipleObjects();				//Prepare edit window for multiple objects. 
	virtual void EditSingleObject();					//Applies changes to a single object.
	virtual void EditMultipleObjects();					//Applies changes to multiple objects. 

	afx_msg void End();									//Kill the dialogue
	afx_msg void EditObject();							//Apply changes to the selected object. Determines which edit function to run depending on amount of selected objects.
	afx_msg void SelectModel();							//Model has been selected
	afx_msg void SelectTexture();						//Texture has been selected

	std::vector<std::wstring> m_availableTextures;		//Textures available in the tool.
	std::vector<std::wstring> m_availableModels;		//Models available in the tool. 
	std::vector<SceneObject>* m_sceneGraph;				//Vector of objects in the scene. 
	int* m_selectedObjectID;							//ID of single selected object.
	std::vector<int>* m_selectedObjectIDs;				//Vector of multiple selected object IDs.
	SceneObject* m_selectedObject;						//The selected object.
	std::wstring texChoice;								//Path name of selected texture.
	std::wstring modelChoice;							//Path name of selected model.
	ToolMain* m_toolObject;								//ToolMain
	CWnd* pWnd;											//Window



	DECLARE_MESSAGE_MAP()
public:
	//Control variable for more efficient access of the listboxes
	CListBox m_texListBox;								//List box for textures
	CListBox m_modelListBox;							//List box for models
	CListBox m_selectIDBox;								//List box for selected object IDs

	float positionX, positionY, positionZ, rotateX, rotateY, rotateZ,
		scaleX, scaleY, scaleZ;							//Values used to set new object positions, scales and rotations

	virtual BOOL OnInitDialog() override;				//Dialogue init
	virtual void PostNcDestroy();						//Post destroy function
	virtual void SetObjectData(ToolMain* tool);			//Sets the data for this dialogue
	afx_msg void OnBnClickedOk();						//Run when ok button is clicked
	afx_msg void OnBnClickedCancel();					//Run when cancel button is clicked
};


INT_PTR CALLBACK CreateObjectProc(HWND   hwndDlg, UINT   uMsg, WPARAM wParam, LPARAM lParam);


