
// markPictures.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CmarkPicturesApp: 
// �йش����ʵ�֣������ markPictures.cpp
//

class CmarkPicturesApp : public CWinApp
{
public:
	CmarkPicturesApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CmarkPicturesApp theApp;