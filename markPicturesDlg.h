
// markPicturesDlg.h : ͷ�ļ�
//

#pragma once
#include "opencv.hpp"

#include <vector>
#include <string>
#include <fstream>
#include <sstream>

struct headInfo
{
	std::string imgName;
	int cnt; // the number of heads
	std::vector<cv::Rect> rects;
};

// CmarkPicturesDlg �Ի���
class CmarkPicturesDlg : public CDialogEx
{
// ����
public:
	CmarkPicturesDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MARKPICTURES_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;
	CRect m_pic_rect;

	std::vector<headInfo> infos;
	//, "E:\\DataContest\\yuncong\\yuncong_data\\");
	std::string m_imgPath = "E:\\DataContest\\yuncong\\yuncong_data\\";

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButtonNext();
	afx_msg void OnBnClickedButtonPrev();
	afx_msg void OnBnClickedButtonFileinfo();
	afx_msg void OnBnClickedButtonPath();
};
