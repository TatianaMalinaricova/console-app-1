
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

void CStaticHistogram::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	GetParent()->SendMessage(CApplicationDlg::WM_DRAW_HISTOGRAM, (WPARAM)lpDrawItemStruct);
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

	for (int i = 0; i < 256; i++)
	{
		tmp_hist[i] = i;
	}
}

void CApplicationDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_IMAGE, m_ctrlImage);
	DDX_Control(pDX, IDC_HIST, m_ctrlHist);
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
	ON_MESSAGE(WM_DRAW_HISTOGRAM, OnDrawHistogram)
	ON_WM_DESTROY()
	ON_STN_CLICKED(IDC_IMAGE, &CApplicationDlg::OnStnClickedImage)
	ON_COMMAND(ID_HISTOGRAM_RED, OnHistogramRed)
	ON_COMMAND(ID_HISTOGRAM_GREEN, OnHistogramGreen)
	ON_COMMAND(ID_HISTOGRAM_BLUE, OnHistogramBlue)

END_MESSAGE_MAP()


void CApplicationDlg::OnDestroy()
{
	Default();
}

LRESULT CApplicationDlg::OnDrawHistogram(WPARAM wParam, LPARAM lParam)
{
	LPDRAWITEMSTRUCT lpDI = (LPDRAWITEMSTRUCT)wParam;

	CDC * pDC = CDC::FromHandle(lpDI->hDC);
	CRect r(lpDI->rcItem);
	

	if (p_image != nullptr) {

	//	skalovanie y osi hist = hodnota_hist * vyska_okna / max_hodnota_hist
//		float scaleX = ((float)r.Width()) / (float)256;
//		float scaleY = ((float)r.Height()) / (float)max_hist;
		float scale = (float)r.Height() / ((float)max_hist);
		
		if (checkbox_red == TRUE)
		{
			COLORREF farbaR = RGB(255, 0, 0);
			Draw_hist(pDC, m_hR, farbaR, r, scale);
		}

		if (checkbox_green == TRUE)
		{
			COLORREF farbaG = RGB(0, 255, 0);
			Draw_hist(pDC, m_hG, farbaG, r, scale);
		}

		if (checkbox_blue == TRUE)
		{
			COLORREF farbaB = RGB(0, 0, 255);
			Draw_hist(pDC, m_hB, farbaB, r, scale);
		}
	}
	else
	{
		CRect rect(lpDI->rcItem);
//		CBrush brush;
//		brush.CreateSolidBrush(RGB(255, 255, 255));
//		pDC->FillRect(&rect, &brush);
//		DeleteObject(brush);
		float scale = (float)r.Height() / ((float)255);
		COLORREF farbaB = RGB(0, 0, 255);
		Draw_hist(pDC, tmp_hist, farbaB, r, scale);
	}

	return S_OK;
}

void CApplicationDlg::Draw_hist(CDC *pDC, int *v_f, COLORREF farba, CRect r, float scale)
{
	for (int i = 0; i < 256; i++)
	{
/*		pDC->FillSolidRect( (int)((float)i* ((float)r.Width() / (float)256)),
			r.Height() - (int)(log10f((float)v_f[i]*scale)),
			(int)((float)1*((float)r.Width() / (float)256)) + 1,
			(int)(log10f((float)v_f[i])*scale),
			farba);
*/
		pDC->FillSolidRect((int)((float)i* ((float)r.Width() / (float)256)),
			r.Height() - (int)(((float)v_f[i] * scale)),
			(int)((float)1 * ((float)r.Width() / (float)256)) + 1,
			(int)(((float)v_f[i])*scale),
			farba);
			
	}

}

void CApplicationDlg::Histogram()
{
	int i, j;
	int width = p_image->GetWidth();
	int height = p_image->GetHeight();
	max_hist = 0;

	for (i = 0; i < 256; i++)
	{
		m_hR[i] = 0;
		m_hG[i] = 0;
		m_hB[i] = 0;
	}

	int tmpR, tmpG, tmpB;
	COLORREF pixelColor = 0;
	
	for (i = 0; i < width; i++)
	{
		for (j = 0; j < height; j++)
		{
			pixelColor = p_image->GetPixel(i, j);

			tmpR = int(GetRValue(pixelColor));
			tmpG = int(GetGValue(pixelColor));
			tmpB = int(GetBValue(pixelColor));

			m_hR[tmpR]++;
			m_hG[tmpG]++;
			m_hB[tmpB]++;

			if ((max_hist < m_hR[tmpR]) || (max_hist < m_hG[tmpG]) || (max_hist < m_hB[tmpB]))
			{
				max_hist = m_hR[tmpR];

				if (m_hG[tmpG] > max_hist)
					max_hist = m_hG[tmpG];
				if (m_hB[tmpB] > max_hist)
					max_hist = m_hB[tmpB];
			}
		}
	}
}

LRESULT CApplicationDlg::OnDrawImage(WPARAM wParam, LPARAM lParam)
{
	LPDRAWITEMSTRUCT lpDI = (LPDRAWITEMSTRUCT)wParam;

	CDC * pDC = CDC::FromHandle(lpDI->hDC);
	
	//DRAW BITMAP
	if (p_image != nullptr) {
		CBitmap bmp;
		CDC bmDC;
		CBitmap *pOldbmp;
		BITMAP  bi;

		bmp.Attach(p_image->Detach());
		bmDC.CreateCompatibleDC(pDC);

		CRect r(lpDI->rcItem);

		pOldbmp = bmDC.SelectObject(&bmp);
		bmp.GetBitmap(&bi);

		pDC->FillSolidRect(r.left, r.top, r.Width(), r.Height(), RGB(255, 255, 255));

		double dWtoH = (double)bi.bmWidth / (double)bi.bmHeight;
		UINT nHeight = r.Height();
		UINT nWidth = (UINT)(dWtoH * (double)nHeight);

		if (nWidth > (UINT)r.Width())
		{
			nWidth = r.Width();
			nHeight = (UINT)(nWidth / dWtoH);
			_ASSERTE(nHeight <= (UINT)r.Height());
		}

		//aby boli pekne farby
		pDC->SetStretchBltMode(HALFTONE);

		pDC->StretchBlt(r.left + (r.Width() - nWidth) / 2, r.top + (r.Height() - nHeight) / 2, nWidth, nHeight, &bmDC, 0, 0, bi.bmWidth, bi.bmHeight, SRCCOPY);
		bmDC.SelectObject(pOldbmp);

		p_image->Attach((HBITMAP)bmp.Detach());

		return S_OK;
	}
	
}

void CApplicationDlg::OnSize(UINT nType,int cx,int cy)
{
	if (::IsWindow(m_ctrlImage.GetSafeHwnd()))
	{
		m_ctrlImage.MoveWindow(cx*0.2, 0, cx-(cx*0.2), cy);
	}
	__super::OnSize(nType, cx, cy);
	
	if (::IsWindow(m_ctrlHist.GetSafeHwnd()))
	{
		m_ctrlHist.MoveWindow(0, (int)(0.5*cy), cx - (cx*0.8), (int)(0.5*cy));
	}

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
		if (p_image == nullptr)
		{
			p_image = new CImage();
			if (p_image->Load(path_name))
			{
				delete p_image;
				p_image = nullptr;
			}
			else
				Histogram();	
		}
		else
		{
			p_image->Detach();
			if (p_image->Load(path_name))
			{
				delete p_image;
				p_image = nullptr;
			}
			else
			{
				Histogram();
			}
		}

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
	delete p_image;
	p_image = nullptr;
	Invalidate();
}


void CApplicationDlg::OnUpdateFileClose(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(TRUE);
}

void CApplicationDlg::OnStnClickedImage()
{
	// TODO: Add your control notification handler code here
}

void CApplicationDlg::OnHistogramRed()
{
//	::MessageBox(NULL, __T("Red"), __T("Error"), MB_OK);

	CMenu *Menu = GetMenu();
	
	if (GetMenuState(*Menu, ID_HISTOGRAM_RED, MF_BYCOMMAND | MF_CHECKED))
	{
		checkbox_red = FALSE;
		Menu->GetSubMenu(1)->CheckMenuItem(ID_HISTOGRAM_RED, MF_UNCHECKED);
	}
	else
	{
		Menu->GetSubMenu(1)->CheckMenuItem(ID_HISTOGRAM_RED, MF_CHECKED);
		checkbox_red = TRUE;
	}
	Invalidate();

}

void CApplicationDlg::OnUpdateHistogramRed(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(TRUE);
}

void CApplicationDlg::OnHistogramGreen()
{
	CMenu *Menu = GetMenu();

	if (GetMenuState(*Menu, ID_HISTOGRAM_GREEN, MF_BYCOMMAND | MF_CHECKED))
	{
		checkbox_green = FALSE;
		Menu->GetSubMenu(1)->CheckMenuItem(ID_HISTOGRAM_GREEN, MF_UNCHECKED);
	}
	else
	{
		Menu->GetSubMenu(1)->CheckMenuItem(ID_HISTOGRAM_GREEN, MF_CHECKED);
		checkbox_green = TRUE;
	}

	Invalidate();
}

void CApplicationDlg::OnUpdateHistogramGreen(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(TRUE);
}

void CApplicationDlg::OnHistogramBlue()
{
	CMenu *Menu = GetMenu();

	if (GetMenuState(*Menu, ID_HISTOGRAM_BLUE, MF_BYCOMMAND | MF_CHECKED))
	{
		checkbox_blue = FALSE;
		Menu->GetSubMenu(1)->CheckMenuItem(ID_HISTOGRAM_BLUE, MF_UNCHECKED);
	}
	else
	{
		Menu->GetSubMenu(1)->CheckMenuItem(ID_HISTOGRAM_BLUE, MF_CHECKED);
		checkbox_blue = TRUE;
	}

	Invalidate();

}

void CApplicationDlg::OnUpdateHistogramBlue(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(TRUE);
}