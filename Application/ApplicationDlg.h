
// ApplicationDlg.h : header file
//

#pragma once

#include <GdiPlus.h>

class CStaticImage : public CStatic
{
public:
	// Overridables (for owner draw only)
	void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) override;
};

class CStaticHistogram : public CStatic
{
public:
	// Overridables (for owner draw only)
	void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) override;
};


// CApplicationDlg dialog
class CApplicationDlg : public CDialogEx
{
	// Construction
public:
	enum
	{
		WM_DRAW_IMAGE = (WM_USER + 1),
		WM_DRAW_HISTOGRAM
	};

	CApplicationDlg(CWnd* pParent = NULL);

	
// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_APPLICATION_DIALOG };
#endif

protected:
	void DoDataExchange(CDataExchange* pDX) override;	// DDX/DDV support

	void OnOK() override {}
	void OnCancel() override {}


	// Implementation
protected:
	HICON m_hIcon;
	CImage *p_image = nullptr;
	CImage *grayscale_image = nullptr;
	// Generated message map functions
	BOOL OnInitDialog() override;
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnFileOpen();
	afx_msg void OnUpdateFileOpen(CCmdUI *pCmdUI);
	afx_msg void OnFileClose();
	afx_msg void OnUpdateFileClose(CCmdUI *pCmdUI);
	afx_msg void OnClose();
	afx_msg LRESULT OnDrawImage(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnDrawHistogram(WPARAM wParam, LPARAM lParam);
	afx_msg void Draw_hist(CDC *, int *, COLORREF farba, CRect, float);
	afx_msg void OnDestroy();
	afx_msg void OnHistogramRed();
	afx_msg void OnHistogramGreen();
	afx_msg void OnHistogramBlue();
	afx_msg void OnUpdateHistogramRed(CCmdUI *pCmdUI);
	afx_msg void OnUpdateHistogramGreen(CCmdUI *pCmdUI);
	afx_msg void OnUpdateHistogramBlue(CCmdUI *pCmdUI);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnFilterGrayscale();
	afx_msg void OnUpdateFilterGrayscale(CCmdUI *pCmdUI);

	void Histogram();
	void Grayscale();
protected:
	CStaticImage m_ctrlImage;
	CStaticHistogram m_ctrlHist;
	CPoint m_ptImage;
	CPoint m_ptImage2;
	int m_hR[256] = {0};
	int m_hG[256] = {0};
	int m_hB[256] = {0};
	int tmp_hist[256] = {0};
	int max_hist = 0;
	int min_hist = 0;
	bool checkbox_red = true;
	bool checkbox_green = true;
	bool checkbox_blue = true;
	bool m_bhist = false;
	BYTE *byte_ptr;
	int pitch; //kolko realne ma bitmapa na sirku
	int width = 0;
	int height = 0;
	UINT_PTR id=0;
	bool checkbox_grayscale = FALSE;
	bool m_bgrayscale = false;

public:
	afx_msg void OnStnClickedImage();
};
