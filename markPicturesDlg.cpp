
// markPicturesDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "markPictures.h"
#include "markPicturesDlg.h"
#include "afxdialogex.h"



using namespace cv;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CmarkPicturesDlg 对话框



CmarkPicturesDlg::CmarkPicturesDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MARKPICTURES_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CmarkPicturesDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CmarkPicturesDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_PREV, &CmarkPicturesDlg::OnBnClickedButtonPrev)
	ON_BN_CLICKED(IDC_BUTTON_NEXT, &CmarkPicturesDlg::OnBnClickedButtonNext)
	ON_BN_CLICKED(IDC_BUTTON_NEXT, &CmarkPicturesDlg::OnBnClickedButtonNext)
	ON_BN_CLICKED(IDC_BUTTON_PREV, &CmarkPicturesDlg::OnBnClickedButtonPrev)
	ON_BN_CLICKED(IDC_BUTTON_FILEINFO, &CmarkPicturesDlg::OnBnClickedButtonFileinfo)
	ON_BN_CLICKED(IDC_BUTTON_PATH, &CmarkPicturesDlg::OnBnClickedButtonPath)
END_MESSAGE_MAP()


// CmarkPicturesDlg 消息处理程序

BOOL CmarkPicturesDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	namedWindow("view", WINDOW_AUTOSIZE);
	HWND hWnd = (HWND)cvGetWindowHandle("view");
	HWND hParent = ::GetParent(hWnd);
	::SetParent(hWnd, GetDlgItem(IDC_STATIC_PIC)->m_hWnd);
	::ShowWindow(hParent, SW_HIDE);

	// load the info 
	void loadPicture(std::string infoFile, std::vector<headInfo> & infos);
	loadPicture("E:\\DataContest\\yuncong\\yuncong_data\\Mall_train.txt", infos);
	
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CmarkPicturesDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CmarkPicturesDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CmarkPicturesDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void loadPicture(std::string infoFile, std::vector<headInfo> & infos)
{
	infos.clear();

	std::ifstream input(infoFile);

	std::string line;
	while (getline(input, line))
	{
		headInfo hi;
		std::istringstream record(line);

		record >> hi.imgName;

		std::string strCnt;
		record >> strCnt;
		hi.cnt = std::stoi(strCnt);

		for (int i = 0; i < hi.cnt; i++)
		{
			record >> strCnt;
			//标志位(1) x y w h
			cv::Rect rc;
			record >> strCnt;
			rc.x = std::stoi(strCnt);
			record >> strCnt;
			rc.y = std::stoi(strCnt);
			record >> strCnt;
			rc.width = std::stoi(strCnt);
			record >> strCnt;
			rc.height = std::stoi(strCnt);

			hi.rects.push_back(rc);
		}

		infos.push_back(hi);
	}
	input.close();
}
// 下一张

static int index = 0; // the index of current picture

void CmarkPicturesDlg::OnBnClickedButtonNext()
{
		// TODO: 在此添加控件通知处理程序代码
	GetDlgItem(IDC_STATIC_PIC)->GetClientRect(&m_pic_rect);
	// m_pic_rect.Width\

	cv::Mat mat = imread(m_imgPath + infos[index].imgName);
	// 画框
	// cv::rectangle(mat, cv::Rect(0, 0, 100, 100), cv::Scalar(255, 0, 0), 2);
	for (int i = 0; i < infos[index].cnt; i++)
	{
		cv::rectangle(mat, infos[index].rects[i],
			cv::Scalar(0, 0, 255), 2);
	}

	cv::Mat mat2;
	cv::resize(mat, mat2, cv::Size(m_pic_rect.Width(), m_pic_rect.Height()));
	imshow("view", mat2);

	index++;
}


void CmarkPicturesDlg::OnBnClickedButtonPrev()
{
	// TODO: 在此添加控件通知处理程序代码
	// TODO: 在此添加控件通知处理程序代码
	if (index > 0)
	{
		index -= 1;
	}
	GetDlgItem(IDC_STATIC_PIC)->GetClientRect(&m_pic_rect);
	// m_pic_rect.Width\

	cv::Mat mat = imread(m_imgPath + infos[index].imgName);
	// 画框
	// cv::rectangle(mat, cv::Rect(0, 0, 100, 100), cv::Scalar(255, 0, 0), 2);
	for (int i = 0; i < infos[index].cnt; i++)
	{
		cv::rectangle(mat, infos[index].rects[i],
			cv::Scalar(0, 0, 255), 2);
	}

	cv::Mat mat2;
	cv::resize(mat, mat2, cv::Size(m_pic_rect.Width(), m_pic_rect.Height()));
	imshow("view", mat2);
}


void CmarkPicturesDlg::OnBnClickedButtonFileinfo()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strFile = _T("");

	CFileDialog dlgFile(TRUE, NULL, NULL, OFN_HIDEREADONLY, _T("Describe Files (*.txt)|*.txt|All Files (*.*)|*.*||"), NULL);

	if (dlgFile.DoModal())
	{
		strFile = dlgFile.GetPathName();
	}
	//AfxMessageBox(strFile);
	GetDlgItem(IDC_STATIC_INFO)->SetWindowText(strFile);
	loadPicture(strFile.GetBuffer(), infos);

	index = 0;
}


void CmarkPicturesDlg::OnBnClickedButtonPath()
{
	// TODO: 在此添加控件通知处理程序代码
	char szPath[MAX_PATH];     //存放选择的目录路径 
	CString str;

	ZeroMemory(szPath, sizeof(szPath));

	BROWSEINFO bi;
	bi.hwndOwner = m_hWnd;
	bi.pidlRoot = NULL;
	bi.pszDisplayName = szPath;
	bi.lpszTitle = "请选择需要图片所在目录，注意，这个要配合信息文件中文件名";
	bi.ulFlags = 0;
	bi.lpfn = NULL;
	bi.lParam = 0;
	bi.iImage = 0;
	//弹出选择目录对话框
	LPITEMIDLIST lp = SHBrowseForFolder(&bi);

	if (lp && SHGetPathFromIDList(lp, szPath))
	{
		str.Format("选择的目录为 %s", szPath);
		//AfxMessageBox(str);
		GetDlgItem(IDC_STATIC_PICPATH)->SetWindowText(szPath);
		m_imgPath.assign(szPath);
		m_imgPath.append("\\");
	}
	else
	{
		AfxMessageBox("无效的目录，请重新选择");
	}
	index = 0;
}
