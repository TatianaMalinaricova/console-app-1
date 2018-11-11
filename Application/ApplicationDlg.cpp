
// ApplicationDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Application.h"
#include "ApplicationDlg.h"
#include "afxdialogex.h"
#include <utility>
#include <tuple>
#include <vector>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#ifndef MIN_SIZE
#define MIN_SIZE 300
#endif

void CStaticImage::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	GetParent()->SendMessage( CApplicationDlg::WM_DRAW_IMAGE, (WPARAM)lpDrawItemStruct);
}

// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg() : CDialogEx(IDD_ABOUTBOX) {}

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	void DoDataExchange(CDataExchange* pDX) override    // DDX/DDV support
	{
		CDialogEx::DoDataExchange(pDX);
	}

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};


BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// CApplicationDlg dialog

CApplicationDlg::CApplicationDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_APPLICATION_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CApplicationDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_IMAGE, m_ctrlImage);
}

BEGIN_MESSAGE_MAP(CApplicationDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
	ON_UPDATE_COMMAND_UI(ID_FILE_OPEN, OnUpdateFileOpen)
	ON_COMMAND(ID_FILE_CLOSE, OnFileClose)
	ON_UPDATE_COMMAND_UI(ID_FILE_CLOSE, OnUpdateFileClose)
	ON_WM_CLOSE()
	ON_WM_SIZE()
	ON_WM_SIZING()
	ON_MESSAGE(WM_DRAW_IMAGE, OnDrawImage)
	ON_WM_DESTROY()
	ON_STN_CLICKED(IDC_IMAGE, &CApplicationDlg::OnStnClickedImage)
END_MESSAGE_MAP()


void CApplicationDlg::OnDestroy()
{
	Default();
}

LRESULT CApplicationDlg::OnDrawImage(WPARAM wParam, LPARAM lParam)
{
	LPDRAWITEMSTRUCT lpDI = (LPDRAWITEMSTRUCT)wParam;

	CDC * pDC = CDC::FromHandle(lpDI->hDC);
	
	//DRAW BITMAP
	if (p_image != nullptr) {

		CBitmap bitmap;
		CDC mDC;
		CBitmap *p_Oldbitmap;
		BITMAP  bi;

		bitmap.Attach(p_image->Detach());
		mDC.CreateCompatibleDC(pDC);
		
		CRect r(lpDI->rcItem);

		p_Oldbitmap = mDC.SelectObject(&bitmap);
		bitmap.GetBitmap(&bi);

		//skalovanie obrazka
		float fw = 1.;
		float fh = 1.;
		float f = 1.;
		fh = (float)r.Height() / (float)bi.bmHeight;
		fw = (float)r.Width() / (float)bi.bmWidth;
		int r_x = r.Width();int r_y = r.Height();
		float tmp_x = 0;float tmp_y = 0;

		if ((bi.bmWidth > r.Width()) && (bi.bmHeight <= r.Height()))
		{
			tmp_x = (float)bi.bmWidth*((float)bi.bmWidth / (float)r_x);
			tmp_y = (float)bi.bmHeight*((float)bi.bmWidth / (float)r_x);
		}
		if ((bi.bmHeight > r.Height()) && (bi.bmWidth <= r.Width()))
		{
			tmp_x = (float)bi.bmWidth*((float)bi.bmHeight / (float)r_y);
			tmp_y = (float)bi.bmHeight*((float)bi.bmHeight / (float)r_y);
		}

		if (((bi.bmWidth < r.Width()) && (bi.bmHeight < r.Height())) || ((bi.bmWidth > r.Width()) && (bi.bmHeight > r.Height())))
		{
			if (r.Height() > r.Width())
			{
				tmp_x = (float)bi.bmWidth*((float)bi.bmWidth / (float)r_x);
				tmp_y = (float)bi.bmHeight*((float)bi.bmWidth / (float)r_x);
			}
			else
			{
				tmp_x = (float)bi.bmWidth*((float)bi.bmHeight / (float)r_y);
				tmp_y = (float)bi.bmHeight*((float)bi.bmHeight / (float)r_y);
			}
		}

		int m_x = m_ptImage.x;
		int m_y = m_ptImage.y;

		pDC->StretchBlt(0,0, r.Width(), r.Height(), &mDC,0,0, tmp_x*fw, tmp_y*fh,SRCCOPY);
		mDC.SelectObject(p_Oldbitmap);

		p_image->Attach((HBITMAP)bitmap.Detach());

		return S_OK;
	}
	
}

void CApplicationDlg::OnSize(UINT nType,int cx,int cy)
{
	if (::IsWindow(m_ctrlImage.GetSafeHwnd()))
	{
		m_ctrlImage.MoveWindow(0, 0, cx, cy);
	}
	__super::OnSize(nType, cx, cy);
	
	Invalidate();
}


void CApplicationDlg::OnClose()
{
	EndDialog(0);
}

BOOL CApplicationDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	CRect rct;
	CRect rctClient;
	GetClientRect(&rctClient);
	
	m_ctrlImage.GetWindowRect(&rct);
	m_ptImage.x = rctClient.Width() - rct.Width();
	m_ptImage.y = rctClient.Height() - rct.Height();


	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CApplicationDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CApplicationDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CApplicationDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CApplicationDlg::OnFileOpen()
{
	//GET FILE NAME AND CREATE GDIPLUS BITMAP
	// vytvorime file dialog na iba citanie a prepisom promptu, s filtrom .jpg a .png
	CFileDialog file_dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, _T("Jpg Files (*.jpg)|*.jpg|Png Files (*.png)|*.png||"));

	// zobrazi file dialog
	if (file_dlg.DoModal() == IDOK) {
		CString path_name = file_dlg.GetPathName();
	
		// rusenie objektu CImage pred vytvorenim noveho
		if (p_image != nullptr)
		{
			delete p_image;
			p_image = nullptr;
		}
		p_image = new CImage();
		p_image->Load(path_name);

		//prekreslenie, zavolane po OnDrawImage
		Invalidate();
	}
	else {
		::MessageBox(NULL, __T("Chyba pri zobrazeni file dialogu."), __T("Error"), MB_OK);
	}
}


void CApplicationDlg::OnUpdateFileOpen(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(TRUE);
}


void CApplicationDlg::OnFileClose()
{
	
}


void CApplicationDlg::OnUpdateFileClose(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(TRUE);
}

void CApplicationDlg::OnStnClickedImage()
{
	// TODO: Add your control notification handler code here
}
