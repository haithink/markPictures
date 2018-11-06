
// markPicturesDlg.h : 头文件
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

// CmarkPicturesDlg 对话框
class CmarkPicturesDlg : public CDialogEx
{
// 构造
public:
	CmarkPicturesDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MARKPICTURES_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;
	CRect m_pic_rect;

	std::vector<headInfo> infos;
	//, "E:\\DataContest\\yuncong\\yuncong_data\\");
	std::string m_imgPath = "E:\\DataContest\\yuncong\\yuncong_data\\";

	// 生成的消息映射函数
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
