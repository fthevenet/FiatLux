// LeftView.cpp : implementation of the CLeftView class
//

#include "stdafx.h"
#include "Fiat Lux.h"

#include "Fiat LuxDoc.h"
#include "LeftView.h"
#include "Resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


// Image list indexes
#define ILI_HARD_DISK       0
#define ILI_FLOPPY          1
#define ILI_CD_ROM          2
#define ILI_NET_DRIVE       3
#define ILI_RAM_DRIVE       4
#define ILI_CLOSED_FOLDER   5
#define ILI_OPEN_FOLDER     6
#define ILI_LWO				7
#define ILI_LWO_OPEN		8				

/////////////////////////////////////////////////////////////////////////////
// CLeftView

IMPLEMENT_DYNCREATE(CLeftView, CTreeView)

BEGIN_MESSAGE_MAP(CLeftView, CTreeView)
	//{{AFX_MSG_MAP(CLeftView)
	ON_WM_DESTROY()
	ON_NOTIFY_REFLECT(TVN_ITEMEXPANDING, OnItemexpanding)
	ON_NOTIFY_REFLECT(TVN_SELCHANGED, OnSelchanged)
	ON_MESSAGE (WM_USER, OnDriveContentsChanged)
	ON_NOTIFY_REFLECT(TVN_ITEMEXPANDED, OnItemexpanded)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLeftView construction/destruction

CLeftView::CLeftView() : m_event (FALSE, TRUE)
{
	// TODO: add construction code here
	m_lock = FALSE;
	init = TRUE;
}

CLeftView::~CLeftView()
{
}

BOOL CLeftView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	if (!CTreeView::PreCreateWindow (cs)) 
		return FALSE;

    cs.style |= TVS_HASLINES | TVS_LINESATROOT | TVS_HASBUTTONS | TVS_EDITLABELS ;

	return CTreeView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CLeftView drawing

void CLeftView::OnDraw(CDC* pDC)
{
	CFiatLuxDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}


void CLeftView::OnInitialUpdate()
{
	CTreeView::OnInitialUpdate();
	
	// TODO: You may populate your TreeView with items by directly accessing
	//  its tree control through a call to GetTreeCtrl().
	CTreeView::OnInitialUpdate ();
    m_imglDrives.Create (IDR_DRIVEIMAGES, 16, 1, RGB (255, 0, 255));
    GetTreeCtrl ().SetImageList (&m_imglDrives, TVSIL_NORMAL);
    
	
      
	
	if (init)
	{
	
		InitTree ();
		init = FALSE;
	
	 char szPath[MAX_PATH];
      ::GetCurrentDirectory (sizeof (szPath), szPath);
      
	  if (!ExpandPath (szPath 	 ,TRUE))
	  {
			AfxMessageBox("Invalide Path" , 1, 1);
	  }
	}



}


void CLeftView::OnSelectionChanged (CString& strPathName)
{
    //
    // NOTE: Override this function in a derived class to respond
    // to selection changes differently. The default implementation
    // calls UpdateAllViews to update other views of the document.
    //
	if ((!strPathName.Right(3).CompareNoCase("lwo")) && (!m_lock))
	{	
	//	CFiatLuxDoc* pDoc = GetDocument();
	//	pDoc->OnOpenDocument(strPathName);
	
	//	CWinApp* MyApp = AfxGetApp( ); 
		


		AfxGetApp( )->OpenDocumentFile( strPathName );

		

	GetDocument ()->UpdateAllViews (this,
        (LPARAM) (LPCTSTR) strPathName);
		
	}
	
}

/////////////////////////////////////////////////////////////////////////////
// CLeftView diagnostics

#ifdef _DEBUG
void CLeftView::AssertValid() const
{
	CTreeView::AssertValid();
}

void CLeftView::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}

CFiatLuxDoc* CLeftView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CFiatLuxDoc)));
	return (CFiatLuxDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CLeftView message handlers

void CLeftView::OnDestroy() 
{
	// Kill all running file change notification threads. 
/*	if (m_nThreadCount) 
	{
        m_event.SetEvent ();

        ::WaitForMultipleObjects (m_nThreadCount, m_hThreads, TRUE,
            INFINITE);
        for (UINT i=0; i<m_nThreadCount; i++)
            delete m_pThreads[i];
        m_nThreadCount = 0;
    }*/
    // Call the base class's OnDestroy handler.   

	CTreeView::OnDestroy();
	
	// TODO: Add your message handler code here
	
}

void CLeftView::OnItemexpanding(NMHDR* pnmh, LRESULT* pResult) 
{
	NM_TREEVIEW* pnmtv = (NM_TREEVIEW*) pnmh;
    HTREEITEM hItem = pnmtv->itemNew.hItem;
    CString strPathName = GetPathFromItem (hItem);
    *pResult = FALSE;
    
//	AfxMessageBox("OnItemexpanding");

	IsMediaValid (strPathName);
	m_lock = TRUE;
	// Reset the drive node if the drive is empty or the media changed.
    if (!IsMediaValid (strPathName))
	{
        HTREEITEM hRoot = GetDriveNode (hItem);
        GetTreeCtrl ().Expand (hRoot, TVE_COLLAPSE);
        DeleteChildren (hRoot);
        AddDummyNode (hRoot);
        *pResult = TRUE;
        return;
    }
    
	// Delete the item if strPathName no longer specifies a valid path.
    if (!IsPathValid (strPathName))
	{        
		GetTreeCtrl ().DeleteItem (hItem);
        *pResult = TRUE;
        return;
    }
    
	// If the item is expanding, delete the dummy item attached to it
    // and add folder items. If the item is collapsing instead, delete
    // its folder items and add a dummy item if appropriate.

    if (pnmtv->action == TVE_EXPAND)
	{  
		DeleteChildren (hItem);
        if (!AddDirectoryNodes (hItem, strPathName)) 
            *pResult = TRUE;

    }    
	/*	else 
	{       
	DeleteChildren (hItem); 
		if (IsDriveNode (hItem))
            AddDummyNode (hItem);
        else
            SetButtonState (hItem, strPathName);
    }*/
}

void CLeftView::OnSelchanged(NMHDR* pnmh, LRESULT* pResult) 
{
	HTREEITEM hItem = ((NM_TREEVIEW*) pnmh)->itemNew.hItem;
    NM_TREEVIEW* pnmtv = (NM_TREEVIEW*) pnmh;
	CString strPathName = GetPathFromItem (hItem);

    // Reset the drive node if the drive is empty or the media changed.
    
	
	
	
	if (!IsMediaValid (strPathName))
	{
        HTREEITEM hRoot = GetDriveNode (hItem);
        GetTreeCtrl ().Expand (hRoot, TVE_COLLAPSE);
        DeleteChildren (hRoot);
        AddDummyNode (hRoot);
        return;
    }
    
	// Delete the item if strPathName no longer specifies a valid path.
    if (!IsPathValid (strPathName))
	{   
		GetTreeCtrl ().DeleteItem (hItem);
        return;
    }
    
	// Update the item's button state if the item is not expanded.
    if (!(GetTreeCtrl ().GetItemState (hItem, TVIS_EXPANDED) &
        TVIS_EXPANDED) || !GetTreeCtrl ().ItemHasChildren (hItem))
        UpdateButtonState (hItem, strPathName);

	


	
	// Call the view's virtual OnSelectionChanged function.
    OnSelectionChanged (strPathName);
}

LONG CLeftView::OnDriveContentsChanged (UINT wParam, LONG lParam)
{
    RefreshDrive ((UINT) wParam);
    return 0;
}

/////////////////////////////////////////////////////////////////////////
// Public member functions

void CLeftView::RefreshDrive (UINT nDrive)
{
    
	// Find the HTREEITEM that corresponds to the target drive.
    CString strDrive = "?:\\";
    strDrive.SetAt (0, 0x41 + nDrive);

    HTREEITEM hItem =
        FindItem (GetTreeCtrl ().GetNextItem (NULL, TVGN_ROOT),
        strDrive);
    
	if (hItem == NULL) 
		return;
	
    // Reset the drive node if the drive is empty or the media changed.
    if (!IsMediaValid (strDrive))
	{
        GetTreeCtrl ().Expand (hItem, TVE_COLLAPSE);
        DeleteChildren (hItem);
        AddDummyNode (hItem); 
		return;
    }

    // Save the current drive and directory. 
	char szHome[MAX_PATH];
    ::GetCurrentDirectory (sizeof (szHome), szHome);

    // Change to the root directory of the target drive.
    if (!::SetCurrentDirectory ((LPCTSTR) strDrive))
        return; // Invalid drive specification
    
	// Refresh the drive node and all displayed subfolders.
    if (hItem != NULL) 
		RefreshDirectory (hItem);
    
	// Return to the original drive and directory.
    ::SetCurrentDirectory (szHome);
}


CString CLeftView::GetPathFromItem (HTREEITEM hItem)
{
    CString strPathName;

    while (hItem != NULL)
	{
        CString string = GetTreeCtrl ().GetItemText (hItem);
        if ((string.Right (1) != "\\") && !strPathName.IsEmpty ())
            string += "\\";
        strPathName = string + strPathName;
        hItem = GetTreeCtrl ().GetParentItem (hItem);
    }
    return strPathName;
}


BOOL CLeftView::ExpandPath (LPCTSTR pszPath, BOOL bSelectItem)
{
    if (::lstrlen (pszPath) < 3)
        return FALSE;
    
	// Begin by finding the corresponding drive node.
    CString strPathName = pszPath;    
	CString strDrive = strPathName.Left (3);
    
	HTREEITEM hItem =
        FindItem (GetTreeCtrl ().GetNextItem (NULL, TVGN_ROOT),
        strDrive);
    
	if (hItem == NULL)
        return FALSE;	// Invalid drive specification


    strPathName = strPathName.Right (strPathName.GetLength () - 3);

    // Now bore down through the directory structure searching for the
    // item that corresponds to the final directory name in pszPath.

	/*
	if (pnmtv->action == TVE_EXPAND)
	{  
		DeleteChildren (hItem);
        if (!AddDirectoryNodes (hItem, strPathName)) 
            *pResult = TRUE;

    }    
	else 
	{       
		DeleteChildren (hItem); 
		if (IsDriveNode (hItem))
            AddDummyNode (hItem);
        else
            SetButtonState (hItem, strPathName);
    }
*/


    while (strPathName.GetLength () > 0) 
	{
        GetTreeCtrl ().Expand (hItem, TVE_EXPAND);
        hItem = GetTreeCtrl ().GetChildItem (hItem);
        if (hItem == NULL)
            return FALSE;
        int nIndex = strPathName.Find ('\\');
        hItem = FindItem (hItem, nIndex == -1 ? strPathName :
            strPathName.Left (nIndex));
			
			if (hItem == NULL){
				AfxMessageBox("Invalid path name ");
				return FALSE; // Invalid path name  
			}

		
		if (nIndex == -1)
            strPathName.Empty ();  
		
		else
			strPathName = strPathName.Right (strPathName.GetLength () -
                nIndex - 1);

		
    }

	//AfxMessageBox(strPathName);


    GetTreeCtrl ().Expand (hItem, TVE_EXPAND);
    if (bSelectItem)
	{
		m_lock = TRUE;
		GetTreeCtrl ().Select (hItem, TVGN_CARET    );
		m_lock = FALSE;
	}


    return TRUE;
}


/////////////////////////////////////////////////////////////////////////
// Protected helper functions

UINT CLeftView::InitTree ()
{
    int nPos = 0;
    UINT nCount = 0; 
	CString strDrive = "?:\\";

    DWORD dwDriveList = ::GetLogicalDrives ();
    
	while (dwDriveList) 
	{
        if (dwDriveList & 1)
		{
            strDrive.SetAt (0, 0x41 + nPos);
            if (AddDriveNode (strDrive))    
				nCount++;
        }

        dwDriveList >>= 1; 
		nPos++;
    }    
	return nCount;
}


BOOL CLeftView::AddDriveNode (CString& strDrive)
{  
	HTREEITEM hItem;
    
	UINT nType = ::GetDriveType ((LPCTSTR) strDrive);
    UINT nDrive = (UINT) strDrive[0] - 0x41;
    
	switch (nType) {

    case DRIVE_REMOVABLE:
		
        hItem = GetTreeCtrl ().InsertItem (strDrive, ILI_FLOPPY,
            ILI_FLOPPY);
        AddDummyNode (hItem);
        //m_dwMediaID[nDrive] = GetSerialNumber (strDrive);
		
        break;

    case DRIVE_FIXED:
        hItem = GetTreeCtrl ().InsertItem (strDrive, ILI_HARD_DISK,
            ILI_HARD_DISK);
        SetButtonState (hItem, strDrive);
        
        break;
    
	case DRIVE_REMOTE:
        hItem = GetTreeCtrl ().InsertItem (strDrive, ILI_NET_DRIVE,
            ILI_NET_DRIVE);
        SetButtonState (hItem, strDrive);
       
		break;
    
	case DRIVE_CDROM:
        hItem = GetTreeCtrl ().InsertItem (strDrive, ILI_CD_ROM,
            ILI_CD_ROM); 
		AddDummyNode (hItem);
        m_dwMediaID[nDrive] = GetSerialNumber (strDrive);
        break;

    case DRIVE_RAMDISK:
        hItem = GetTreeCtrl ().InsertItem (strDrive, ILI_RAM_DRIVE,
            ILI_RAM_DRIVE);
        SetButtonState (hItem, strDrive);
        break;
    
	default:
        return FALSE; 
   }    
	return TRUE;
}


UINT CLeftView::AddDirectoryNodes (HTREEITEM hItem, CString& strPathName)
{
    HANDLE hFind;
    WIN32_FIND_DATA fd;

    UINT nCount = 0;

    CString strFileSpec = strPathName;
    if (strFileSpec.Right (1) != "\\")
        strFileSpec += "\\";
    strFileSpec += "*.*";

    if ((hFind = ::FindFirstFile ((LPCTSTR) strFileSpec, &fd)) ==
        INVALID_HANDLE_VALUE) {
        if (IsDriveNode (hItem))
            AddDummyNode (hItem);
        return 0;
    }

    do {
		CString strFileName = (LPCTSTR) &fd.cFileName;
        if (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)  {
            
            if ((strFileName != ".") && (strFileName != "..")) {
                HTREEITEM hChild =
                    GetTreeCtrl ().InsertItem ((LPCTSTR) &fd.cFileName,
                    ILI_CLOSED_FOLDER, ILI_OPEN_FOLDER, hItem, TVI_SORT);

                CString strNewPathName = strPathName;
                if (strNewPathName.Right (1) != "\\")
                    strNewPathName += "\\";

                strNewPathName += (LPCTSTR) &fd.cFileName;
                SetButtonState (hChild, strNewPathName);
                nCount++;
            }
    		
		}
    
			
	} while (::FindNextFile (hFind, &fd));

    ::FindClose (hFind);
	nCount += AddLwoNodes (hItem, strPathName);
    return nCount;
}
UINT CLeftView::AddLwoNodes (HTREEITEM hItem, CString& strPathName)
{
    HANDLE hFind;
    WIN32_FIND_DATA fd;

    UINT nCount = 0;

    CString strFileSpec = strPathName;
    if (strFileSpec.Right (1) != "\\")
        strFileSpec += "\\";
    strFileSpec += "*.*";

    if ((hFind = ::FindFirstFile ((LPCTSTR) strFileSpec, &fd)) ==
        INVALID_HANDLE_VALUE) {
        if (IsDriveNode (hItem))
            AddDummyNode (hItem);
        return 0;
    }

    do {
			CString strFileName = (LPCTSTR) &fd.cFileName;
				if (!strFileName.Right(3).CompareNoCase("lwo"))  {
            
					if ((strFileName != ".") && (strFileName != "..")) {
					HTREEITEM hChild =
						GetTreeCtrl ().InsertItem ((LPCTSTR) &fd.cFileName,
						ILI_LWO, ILI_LWO_OPEN, hItem, TVI_LAST );

					CString strNewPathName = strPathName;
					if (strNewPathName.Right (1) != "\\")
						strNewPathName += "\\";

					strNewPathName += (LPCTSTR) &fd.cFileName;
					SetButtonState (hChild, strNewPathName);
					nCount++;
				}
            }
	
		
	} while (::FindNextFile (hFind, &fd));

    ::FindClose (hFind);
    return nCount;
}



void CLeftView::SetButtonState (HTREEITEM hItem, CString& strPathName)
{
    if (HasSubdirectory (strPathName))
        AddDummyNode (hItem);
}

void CLeftView::UpdateButtonState (HTREEITEM hItem, CString& strPathName)
{
    if (HasSubdirectory (strPathName)) {
        if (!GetTreeCtrl ().ItemHasChildren (hItem)) {
            AddDummyNode (hItem);
            Invalidate ();
        }
    }
    else {
        if (GetTreeCtrl ().ItemHasChildren (hItem))
            DeleteChildren (hItem);
    }
}

BOOL CLeftView::HasSubdirectory (CString& strPathName)
{
    HANDLE hFind;
    WIN32_FIND_DATA fd;
    BOOL bResult = FALSE;

    CString strFileSpec = strPathName;
    if (strFileSpec.Right (1) != "\\")
        strFileSpec += "\\";
    strFileSpec += "*.*";

    if ((hFind = ::FindFirstFile ((LPCTSTR) strFileSpec, &fd)) !=
        INVALID_HANDLE_VALUE) {
        do {
            CString strFileName = (LPCTSTR) &fd.cFileName;
			if ((fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) || (!strFileName.Right(3).CompareNoCase("lwo"))) {
                //CString strFileName = (LPCTSTR) &fd.cFileName;
                if ((strFileName != ".") && (strFileName != ".."))
                    bResult = TRUE;
            }
        } while (::FindNextFile (hFind, &fd) && !bResult);
        ::FindClose (hFind);
    }

    return bResult;
}

BOOL CLeftView::IsDriveNode (HTREEITEM hItem)
{
    return (GetTreeCtrl ().GetParentItem (hItem) == NULL) ? TRUE : FALSE;
}

void CLeftView::AddDummyNode (HTREEITEM hItem)
{
    GetTreeCtrl ().InsertItem ("Dummy", 0, 0, hItem);
}

HTREEITEM CLeftView::FindItem (HTREEITEM hItem, CString& strTarget)
{
    while (hItem != NULL) {
        if (GetTreeCtrl ().GetItemText (hItem) == strTarget)
            break;
        hItem = GetTreeCtrl ().GetNextSiblingItem (hItem);
    }
    return hItem;
}

UINT CLeftView::DeleteChildren (HTREEITEM hItem)
{
    UINT nCount = 0;
    HTREEITEM hChild = GetTreeCtrl ().GetChildItem (hItem);

    while (hChild != NULL) {
        HTREEITEM hNextItem = GetTreeCtrl ().GetNextSiblingItem (hChild);
        GetTreeCtrl ().DeleteItem (hChild);
        hChild = hNextItem;
        nCount++;
    }
    return nCount;
}


HTREEITEM CLeftView::GetDriveNode (HTREEITEM hItem)
{
    HTREEITEM hParent;

    do {
        hParent = GetTreeCtrl ().GetParentItem (hItem);
        if (hParent != NULL)
            hItem = hParent;
    } while (hParent != NULL);
    return hItem;
}

DWORD CLeftView::GetSerialNumber (CString& strDrive)
{
    DWORD dwSerialNumber;
    if (!::GetVolumeInformation ((LPCTSTR) strDrive, NULL, 0,
        &dwSerialNumber, NULL, NULL, NULL, 0))
        dwSerialNumber = 0xFFFFFFFF;
    return dwSerialNumber;
}

BOOL CLeftView::IsMediaValid (CString& strPathName)
{
    // Return TRUE if the drive doesn't support removable media.
    UINT nDriveType = GetDriveType ((LPCTSTR) strPathName);
    if ((nDriveType != DRIVE_REMOVABLE) && (nDriveType != DRIVE_CDROM))
        return TRUE;

    // Return FALSE if the drive is empty (::GetVolumeInformation fails).
    DWORD dwSerialNumber;
    CString strDrive = strPathName.Left (3);
    UINT nDrive = (UINT) strDrive[0] - 0x41;

    if (!::GetVolumeInformation ((LPCTSTR) strDrive, NULL, 0,
        &dwSerialNumber, NULL, NULL, NULL, 0)) {
        m_dwMediaID[nDrive] = 0xFFFFFFFF;
        return FALSE;
    }

    // Also return FALSE if the disk's serial number has changed.
    if ((m_dwMediaID[nDrive] != dwSerialNumber) &&
        (m_dwMediaID[nDrive] != 0xFFFFFFFF)) {
        m_dwMediaID[nDrive] = dwSerialNumber;
        return FALSE;
    }

    // Update our record of the serial number and return TRUE.
    m_dwMediaID[nDrive] = dwSerialNumber;
    return TRUE;
}

BOOL CLeftView::IsPathValid (CString& strPathName)
{
    if (strPathName.GetLength () == 3)
        return TRUE;

    HANDLE hFind;
    WIN32_FIND_DATA fd;
    BOOL bResult = FALSE;

    if ((hFind = ::FindFirstFile ((LPCTSTR) strPathName, &fd)) !=
        INVALID_HANDLE_VALUE) {
            if ((fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) || (!strPathName.Right(3).CompareNoCase("lwo")))
                bResult = TRUE;
        ::CloseHandle (hFind);
    }
    return bResult;
}

void CLeftView::RefreshDirectory (HTREEITEM hItem)
{
    // If the item is not expanded, update its button state and return.
    if (!(GetTreeCtrl ().GetItemState (hItem, TVIS_EXPANDED) &
        TVIS_EXPANDED) || !GetTreeCtrl ().ItemHasChildren (hItem)) {
        if (!IsDriveNode (hItem)) {
            CString strPathName = GetPathFromItem (hItem);
            UpdateButtonState (hItem, strPathName);
            GetTreeCtrl ().Expand (hItem, TVE_COLLAPSE);
        }
        return;
    }

    // Delete items corresponding to subdirectories that no longer exist
    // and build a CStringList containing the names of all the items that
    // are children of hItem.
    CStringList list;
    WIN32_FIND_DATA fd;
    HANDLE hFind;

    HTREEITEM hChild = GetTreeCtrl ().GetChildItem (hItem);

    while (hChild != NULL) {
        HTREEITEM hNextItem = GetTreeCtrl ().GetNextSiblingItem (hChild);
        CString strDirName = GetTreeCtrl ().GetItemText (hChild);

        if ((hFind = ::FindFirstFile ((LPCTSTR) strDirName, &fd)) !=
            INVALID_HANDLE_VALUE) {
            if (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
                list.AddTail (strDirName);
            else
                GetTreeCtrl ().DeleteItem (hChild);
            ::FindClose (hFind);
        }
        else
            GetTreeCtrl ().DeleteItem (hChild);

        hChild = hNextItem;
    }

    // Add items for newly created subdirectories.
    if ((hFind = ::FindFirstFile ("*.*", &fd)) != INVALID_HANDLE_VALUE) {
        do {
            CString strFileName = (LPCTSTR) &fd.cFileName;
			if (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
                
                if ((strFileName != ".") && (strFileName != "..")) {
                    if (list.Find (strFileName) == NULL) {
                        hChild = GetTreeCtrl ().InsertItem (strFileName,
                            ILI_CLOSED_FOLDER, ILI_OPEN_FOLDER,
                            hItem, TVI_FIRST);
                        CString strPathName = GetPathFromItem (hChild);
                        SetButtonState (hChild, strPathName);
                        list.AddTail (strFileName);
                    }
                }
			else
			{
				if (!strFileName.Right(3).CompareNoCase("lwo"))  {
            
					if (list.Find (strFileName) == NULL) {
                        hChild = GetTreeCtrl ().InsertItem (strFileName,
                            ILI_LWO, ILI_LWO_OPEN,
                            hItem, TVI_LAST);
                        CString strPathName = GetPathFromItem (hChild);
                        SetButtonState (hChild, strPathName);
                        list.AddTail (strFileName);
				
					}
            	}
			}
			}	
		} while (::FindNextFile (hFind, &fd));
    ::FindClose (hFind);
    }

    // Remove all items from the CStringList.
    list.RemoveAll ();

    // Now repeat this procedure for hItem's children.
    hChild = GetTreeCtrl ().GetChildItem (hItem);

    while (hChild != NULL) {
        CString string = GetTreeCtrl ().GetItemText (hChild);
        ::SetCurrentDirectory ((LPCTSTR) string);
        RefreshDirectory (hChild); // Recursion!
        ::SetCurrentDirectory ("..");
        hChild = GetTreeCtrl ().GetNextSiblingItem (hChild);
    }
}






void CLeftView::OnItemexpanded(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	m_lock = FALSE;
	
	*pResult = 0;
}

void CLeftView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	// TODO: Add your specialized code here and/or call the base class
	CFiatLuxDoc* pDoc;
	pDoc = GetDocument();
	//
	if (IsPathValid(pDoc->m_DocPath))
		ExpandPath(pDoc->m_DocPath, TRUE);

//	AfxMessageBox(pDoc->m_DocPath,1,1);

	else
	{
		
		UINT nDrive = 1; 
		CString strDrive = "?:\\";

		DWORD dwDriveList = ::GetLogicalDrives ();
    
		while (dwDriveList) 
		{
			if (dwDriveList & 1)
			{
			    
				strDrive.SetAt (0, 0x41 + nDrive);
				HTREEITEM hItem =
					FindItem (GetTreeCtrl ().GetNextItem (NULL, TVGN_ROOT),
					strDrive);
    			GetTreeCtrl ().Expand (hItem, TVE_COLLAPSE);
				nDrive++;
			}

        dwDriveList >>= 1; 
		
		}  
	}
		
	
		
	//AfxMessageBox("Mem. alloc. for tri_normals failed", 1, 1);
	
}
