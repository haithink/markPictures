
// markPicturesDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "markPictures.h"
#include "markPicturesDlg.h"
#include "afxdialogex.h"



using namespace cv;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CmarkPicturesDlg �Ի���



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


// CmarkPicturesDlg ��Ϣ�������

BOOL CmarkPicturesDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	namedWindow("view", WINDOW_AUTOSIZE);
	HWND hWnd = (HWND)cvGetWindowHandle("view");
	HWND hParent = ::GetParent(hWnd);
	::SetParent(hWnd, GetDlgItem(IDC_STATIC_PIC)->m_hWnd);
	::ShowWindow(hParent, SW_HIDE);

	// load the info 
	void loadPicture(std::string infoFile, std::vector<headInfo> & infos);
	loadPicture("E:\\DataContest\\yuncong\\yuncong_data\\Mall_train.txt", infos);
	
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CmarkPicturesDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
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
			//��־λ(1) x y w h
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
// ��һ��

static int index = 0; // the index of current picture

void CmarkPicturesDlg::OnBnClickedButtonNext()
{
		// TODO: �ڴ���ӿؼ�֪ͨ����������
	GetDlgItem(IDC_STATIC_PIC)->GetClientRect(&m_pic_rect);
	// m_pic_rect.Width\

	cv::Mat mat = imread(m_imgPath + infos[index].imgName);
	// ����
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (index > 0)
	{
		index -= 1;
	}
	GetDlgItem(IDC_STATIC_PIC)->GetClientRect(&m_pic_rect);
	// m_pic_rect.Width\

	cv::Mat mat = imread(m_imgPath + infos[index].imgName);
	// ����
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	char szPath[MAX_PATH];     //���ѡ���Ŀ¼·�� 
	CString str;

	ZeroMemory(szPath, sizeof(szPath));

	BROWSEINFO bi;
	bi.hwndOwner = m_hWnd;
	bi.pidlRoot = NULL;
	bi.pszDisplayName = szPath;
	bi.lpszTitle = "��ѡ����ҪͼƬ����Ŀ¼��ע�⣬���Ҫ�����Ϣ�ļ����ļ���";
	bi.ulFlags = 0;
	bi.lpfn = NULL;
	bi.lParam = 0;
	bi.iImage = 0;
	//����ѡ��Ŀ¼�Ի���
	LPITEMIDLIST lp = SHBrowseForFolder(&bi);

	if (lp && SHGetPathFromIDList(lp, szPath))
	{
		str.Format("ѡ���Ŀ¼Ϊ %s", szPath);
		//AfxMessageBox(str);
		GetDlgItem(IDC_STATIC_PICPATH)->SetWindowText(szPath);
		m_imgPath.assign(szPath);
		m_imgPath.append("\\");
	}
	else
	{
		AfxMessageBox("��Ч��Ŀ¼��������ѡ��");
	}
	index = 0;
}
