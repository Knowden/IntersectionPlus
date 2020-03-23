
// UIDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "UI.h"
#include "UIDlg.h"
#include "afxdialogex.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#define ratio (12)

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


// CUIDlg 对话框



CUIDlg::CUIDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_UI_DIALOG, pParent)
	, addComponent(_T(""))
	, m_result(0)
	, m_selected(_T(""))
	, m_input(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CUIDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DRAW, m_drawrect);
	DDX_Control(pDX, IDC_LIST1, m_list);
	DDX_Text(pDX, IDC_RESULT, m_result);
	DDX_Text(pDX, IDC_SELECTED, m_selected);
	DDX_Text(pDX, IDC_INPUT, m_input);
}

BEGIN_MESSAGE_MAP(CUIDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_IMPORT, &CUIDlg::OnBnClickedImport)
	ON_BN_CLICKED(IDC_PAINT, &CUIDlg::OnBnClickedPaint)
	ON_NOTIFY(NM_CLICK, IDC_LIST1, &CUIDlg::OnNMClickList1)
	ON_BN_CLICKED(IDC_DELETE, &CUIDlg::OnBnClickedDelete)
	ON_BN_CLICKED(IDC_ADD, &CUIDlg::OnBnClickedAdd)
END_MESSAGE_MAP()


// CUIDlg 消息处理程序

BOOL CUIDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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
	CRect rect;
	m_list.GetClientRect(&rect);
	m_list.InsertColumn(0, _T("输入的图形"), LVCFMT_CENTER, rect.Width(), 0);
	m_list.InsertColumn(1, _T("序号"), LVCFMT_CENTER, 0, 0);
	line_count = 0;


	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CUIDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CUIDlg::OnPaint()
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
HCURSOR CUIDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

float CUIDlg::calY(float x, float k, float b) 
{
	return k * x + b;
}

void CUIDlg::OnBnClickedImport()
{
	// TODO: 在此添加控件通知处理程序代码
	m_strHistoryPath = "";//文件选择清空
	CFileDialog dlg(TRUE, _T("txt"), NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, _T("文本文件|*.txt||"));
	if (dlg.DoModal() == IDOK)
	{
		m_strHistoryPath = dlg.GetPathName();
		if (m_strHistoryPath == "")
		{
			MessageBox(_T("未选择文件！"));
			return;
		}
	}
	else
	{
		return;
	}
	CStdioFile file;
	CString szLine;
	int i = 0;
	file.Open(m_strHistoryPath, CFile::modeRead);
	file.ReadString(szLine);
	while (file.ReadString(szLine))
	{
		std::string str(CW2A(szLine.GetString()));
		try {
			core.add_component(str);
		}
		catch(std::exception e){
			CString cstr;
			std::string str;
			str = e.what();
			cstr = CA2W(str.c_str());
			MessageBox(cstr);
		}
	}
	//关闭文件
	file.Close();
	//在文本框中显示导入的路径（Debug用）
	//((CEdit*)GetDlgItem(IDC_EDIT))->SetWindowText(m_strHistoryPath);

	getList(m_list);
}

void CUIDlg::getList(CListCtrl &m_list)
{
	std::vector<Line>::iterator line_iter;
	std::vector<Circle>::iterator circle_iter;
	line_list = core.get_all_line();
	circle_list = core.get_all_circle();
	for (line_iter = line_list.begin(); line_iter != line_list.end(); line_iter++) 
	{
		std::string str;
		if (line_iter->k == INT_MAX)
		{
			str = "x=" + std::to_string(line_iter->b);
		}
		else if (line_iter->k == 0)
		{
			str = "y=" + std::to_string(line_iter->b);
		}
		else
		{
			str = "y=" + std::to_string(line_iter->k) + "x+" + std::to_string(line_iter->b);
		}
		CString id;
		id.Format(_T("L%d"), line_iter->id);
		m_list.InsertItem(line_count, CA2W(str.c_str()));
		m_list.SetItemText(line_count++, 1, id);
	}
	for (circle_iter = circle_list.begin(); circle_iter != circle_list.end(); circle_iter++)
	{
		std::string str;
		str = "(x-" + std::to_string(circle_iter->center->x) + ")^2 + (y-" 
			  + std::to_string(circle_iter->center->y) + ")^2 = " + std::to_string(circle_iter->r);
		CString id;
		id.Format(_T("C%d"), circle_iter->id);
		m_list.InsertItem(line_count, CA2W(str.c_str()));
		m_list.SetItemText(line_count++, 1, id);
	}
}


void CUIDlg::OnBnClickedPaint()
{
	std::vector<Line>::iterator line_iter;
	std::vector<Circle>::iterator circle_iter;
	//获取画板信息
	CRect rect;
	CWnd* pWin = GetDlgItem(IDC_DRAW);
	pWin->GetClientRect(rect);
	CDC* pDc = pWin->GetDC();
	pDc->Rectangle(rect);
	CBrush myBrush;
	CBrush blueBrush;
	CPen blackPen;
	CPen redPen;
	CPen bluePen;
	myBrush.CreateSolidBrush(RGB(192, 250, 233));
	blueBrush.CreateSolidBrush(RGB(0, 0, 255));
	blackPen.CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
	redPen.CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	bluePen.CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
	//将画板重置
	pDc->FillRect(rect, &myBrush);
	//绘制坐标轴
	pDc->SelectObject(&blackPen);
	pDc->MoveTo(rect.left, rect.bottom / 2);
	pDc->LineTo(rect.right, rect.bottom / 2);
	pDc->MoveTo(rect.right, rect.bottom / 2);
	pDc->LineTo(rect.right - 20, rect.bottom / 2 + 10);
	pDc->MoveTo(rect.right, rect.bottom / 2);
	pDc->LineTo(rect.right - 20, rect.bottom / 2 - 10);
	pDc->MoveTo(rect.right / 2, rect.bottom);
	pDc->LineTo(rect.right / 2, rect.top);
	pDc->MoveTo(rect.right / 2, rect.top);
	pDc->LineTo(rect.right / 2 + 10, rect.top + 20);
	pDc->MoveTo(rect.right / 2, rect.top);
	pDc->LineTo(rect.right / 2 - 10, rect.top + 20);
	int R_MAX = rect.right / 2/ ratio;
	//将原点设为坐标轴心
	pDc->SetViewportOrg(rect.right / 2, rect.bottom / 2);
	// TODO: 在此添加控件通知处理程序代码
	line_list = core.get_all_line();

	pDc->SelectObject(&redPen);
	for (line_iter = line_list.begin(); line_iter != line_list.end(); line_iter++)
	{
		float k = line_iter->k;
		float b = line_iter->b;
		float left_limit = line_iter->leftLimit < -10000 ? -10000 : line_iter->leftLimit;
		float right_limit = line_iter->rightLimit > 10000 ? 10000 : line_iter->rightLimit;
		if (k == INT_MAX)
		{
			if (b > R_MAX)b = 10000;
			pDc->MoveTo(b*ratio, -(int)left_limit*ratio);
			pDc->LineTo(b*ratio, -(int)right_limit*ratio);
		}
		else
		{
			if (right_limit > R_MAX) right_limit = R_MAX;
			pDc->MoveTo((int)left_limit*ratio, -(int)calY(left_limit, k, b)*ratio);
			pDc->LineTo((int)right_limit*ratio, -(int)calY(right_limit, k, b)*ratio);
		}
	}

	for (circle_iter = circle_list.begin(); circle_iter != circle_list.end(); circle_iter++)
	{
		float x = circle_iter->center->x*ratio;
		float y = circle_iter->center->y*ratio;
		float r = circle_iter->r*ratio;
		CPoint pLeftUp((int)(x - r), (int)(-y - r));
		CPoint pRightDown((int)(x + r), (int)(-y + r));
		if (pLeftUp.x > R_MAX*ratio) continue;
		CRect circle(pLeftUp.x, pLeftUp.y, pRightDown.x, pRightDown.y);
		pDc->SelectStockObject(NULL_BRUSH);
		pDc->Ellipse(&circle);
	}

	std::unordered_set<Point> points;
	std::unordered_set<Point>::iterator point_iter;
	try {
		points = core.get_all_intersection(true);
	}
	catch (std::exception e) {
		CString cstr;
		std::string str;
		str = e.what();
		cstr = CA2W(str.c_str());
		MessageBox(cstr);
	}
	pDc->SelectObject(&bluePen);	//蓝笔标点,点实际是一个实心圆
	for (point_iter = points.begin(); point_iter != points.end(); point_iter++)
	{
		float x = point_iter->x * ratio;
		float y = point_iter->y * ratio;
		if (x > R_MAX*ratio) continue;
		CRect point(x - ratio/4, -y - ratio/4, x + ratio/4, -y + ratio/4);
		pDc->FillRect(point, &blueBrush);
	}
	m_result = points.size();
	UpdateData(false);
}


void CUIDlg::OnNMClickList1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;

	NMLISTVIEW* pNMListView = (NMLISTVIEW*)pNMHDR;
	if (pNMListView->iItem != -1)        // 如果iItem不是-1，就说明有列表项被选择
	{
		m_selected = m_list.GetItemText(pNMListView->iItem, 0);
		m_id = m_list.GetItemText(pNMListView->iItem, 1);
		UpdateData(false);
	}
}


void CUIDlg::OnBnClickedDelete()
{
	// TODO: 在此添加控件通知处理程序代码
	CString t;
	CString id;
	int id_int;
	t = m_id.Left(1);
	id = m_id.Right(1);
	if (t == _T("L"))
	{
		id_int = _ttoi(id);
		core.delete_line_component(id_int);
	}
	else if (t == _T("C"))
	{
		id_int = _ttoi(id);
		core.delete_circle_component(id_int);
	}
	else return;
	m_list.DeleteAllItems();
	line_count = 0;
	getList(m_list);
}


void CUIDlg::OnBnClickedAdd()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(true);
	std::string str(CW2A(m_input.GetString()));
	try {
		core.add_component(str);
	}
	catch (std::exception e) {
		CString cstr;
		std::string str;
		str = e.what();
		cstr = CA2W(str.c_str());
		MessageBox(cstr);
	}
	m_list.DeleteAllItems();
	line_count = 0;
	getList(m_list);
}
