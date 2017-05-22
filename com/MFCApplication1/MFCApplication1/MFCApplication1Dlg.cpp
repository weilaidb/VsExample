
// MFCApplication1Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCApplication1.h"
#include "MFCApplication1Dlg.h"
#include "afxdialogex.h"
#include <iostream>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


using namespace std;

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCApplication1Dlg 对话框



CMFCApplication1Dlg::CMFCApplication1Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMFCApplication1Dlg::IDD, pParent)
	, m_EditReceive(_T(""))
	, m_EditSend(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCApplication1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_RES, m_EditReceive);
	DDX_Text(pDX, IDC_SEND, m_EditSend);
	DDX_Control(pDX, IDC_COMBO1, m_Comb1);
	DDX_Control(pDX, IDC_COMBO2, m_Comb2);
	DDX_Control(pDX, IDC_MSCOMM1, m_Mscom);
}

BEGIN_MESSAGE_MAP(CMFCApplication1Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_OPEN, &CMFCApplication1Dlg::OnBnClickedButtonOpen)
	ON_BN_CLICKED(IDC_BUTTON_SEND, &CMFCApplication1Dlg::OnBnClickedButtonSend)
	ON_BN_CLICKED(IDC_BUTTON_CLS, &CMFCApplication1Dlg::OnBnClickedButtonCls)
	ON_BN_CLICKED(IDC_BUTTON_EXIT, &CMFCApplication1Dlg::OnBnClickedButtonExit)
	ON_EN_CHANGE(IDC_SEND, &CMFCApplication1Dlg::OnEnChangeSend)
END_MESSAGE_MAP()


// CMFCApplication1Dlg 消息处理程序

BOOL CMFCApplication1Dlg::OnInitDialog()
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

	// TODO:  在此添加额外的初始化代码
	CString str;
	int i;
	for (i = 0; i<=25; i++)
	{
		str.Format(_T("com %d"), i /*+ 1*/);
		m_Comb1.InsertString(i, str);
	}

	m_Comb1.SetCurSel(0);//预置COM口

	//波特率选择组合框


	CString str1[] = { _T("300"), _T("600"), _T("1200"), _T("2400"), _T("4800"), _T("9600"),
		_T("19200"), _T("38400"), _T("43000"), _T("56000"), _T("57600"), _T("115200"),
		_T("128000"), _T("256000"), _T("230400")};

#define ARRAY_SIZE(A) (unsigned int )(sizeof(A)/sizeof(A[0]))

	for (int i = 0; i<ARRAY_SIZE(str1); i++)
	{
		//int judge_tf = m_Comb2.AddString(str1[i]);
		m_Comb2.InsertString(i, str1[i]);
		//if ((judge_tf == CB_ERR) || (judge_tf == CB_ERRSPACE))
			//MessageBox(_T("build baud error!"));

	}
	m_Comb2.SetCurSel(11);//预置波特率为"115200" 

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMFCApplication1Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMFCApplication1Dlg::OnPaint()
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
		int offset = 0;
		int x = (rect.Width() + offset  - cxIcon + 1) / 2;
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
HCURSOR CMFCApplication1Dlg::OnQueryDragIcon()
{
	
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCApplication1Dlg::OnBnClickedButtonOpen()
{
	CString str, str1, n;//定义字符串
	GetDlgItemText(IDC_BUTTON_OPEN, str);
	CWnd *h1;
	h1 = GetDlgItem(IDC_BUTTON_OPEN);//指向控件的caption

	if (!m_Mscom.get_PortOpen())
	{

		m_Comb2.GetLBText(m_Comb2.GetCurSel(), str1);//取得所选的字符串，并存放在str1里面
		str1 = str1 + ',' + 'n' + ',' + '8' + ',' + '1';//很关键

		m_Mscom.put_CommPort((m_Comb1.GetCurSel()));//选择串口
		m_Mscom.put_InputMode(1);//设置输入方式为二进制
		m_Mscom.put_Settings(str1);//波特率为（）无校验，8位数据位，1个停止位
		m_Mscom.put_InputLen(1024);//设置当前接受去数据长度为1024
		m_Mscom.put_RThreshold(1);//缓冲区一个字符引发事件
		m_Mscom.put_RTSEnable(1);//设置RT允许



		m_Mscom.put_PortOpen(true);//打开串口
		if (m_Mscom.get_PortOpen())
		{
			str = _T("关闭串口");
			UpdateData(true);
			h1->SetWindowText(str);//改变按钮名称为关闭串口
		}
	}
	else
	{
		m_Mscom.put_PortOpen(false);
		if (str != _T("打开串口")) 
		{
			str = _T("打开串口");
			UpdateData(true);
			h1->SetWindowText(str);//改变按钮名称为打开串口

		}
	}
}


void CMFCApplication1Dlg::OnBnClickedButtonSend()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(true);//更新控件数据
	m_Mscom.put_Output(COleVariant(m_EditSend));//把发送编辑框的数据发送出去
}


void CMFCApplication1Dlg::OnBnClickedButtonCls()
{
	// TODO:  在此添加控件通知处理程序代码
	m_EditReceive=_T("");//把接收编辑框发送空格符
	UpdateData(false);//更新数据
}


void CMFCApplication1Dlg::OnBnClickedButtonExit()
{
	// TODO:  在此添加控件通知处理程序代码
	if (m_Mscom.get_PortOpen())
		m_Mscom.put_PortOpen(false);
	CDialogEx::OnCancel();
}

void CMFCApplication1Dlg::OnEnChangeSend()
{
	cout << "input text changed" << endl;
	// TODO:  在此添加控件通知处理程序代码
	//m_EditReceive = _T("");//把接收编辑框发送空格符
	//UpdateData(false);//更新数据
}


BEGIN_EVENTSINK_MAP(CMFCApplication1Dlg, CDialogEx)
	ON_EVENT(CMFCApplication1Dlg, IDC_MSCOMM1, 1, CMFCApplication1Dlg::OnCommMscomm1, VTS_NONE)
END_EVENTSINK_MAP()


void CMFCApplication1Dlg::OnCommMscomm1()
{
	// TODO:  在此处添加消息处理程序代码
	if (m_Mscom.get_CommEvent() == 2)
	{
		char str[1024] = { 0 };
		long k;
		VARIANT InputData = m_Mscom.get_Input(); //读缓冲区
		COleSafeArray fs;
		fs = InputData; //VARIANT型变À量转换为COleSafeArray型变量
		for (k = 0; k<fs.GetOneDimSize(); k++)
			fs.GetElement(&k, str + k); //转换为BYTE型数组



		m_EditReceive += str;      // 接收到编辑框里面
		//SetTimer(1,10,NULL); //延时10ms


		UpdateData(false);
	}

}


