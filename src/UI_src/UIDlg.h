
// UIDlg.h: 头文件
//

#pragma once
#include "core.h"

// CUIDlg 对话框
class CUIDlg : public CDialogEx
{
// 构造
public:
	CUIDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_UI_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	// 添加的图形
	CString addComponent;
	//dll相关
	core core;
	std::vector<Line> line_list;
	std::vector<Circle> circle_list;
	//计数列表行数
	int line_count;
	//选中的函数序号
	CString m_id;
public:
	float calY(float x, float k, float b);

	//将所有图形信息输入到列表中
	void getList(CListCtrl &m_list);

	//导入文件路径
	CString m_strHistoryPath;

	CStatic m_drawrect;
	afx_msg void OnBnClickedImport();
	// 列表控件变量
	CListCtrl m_list;
	afx_msg void OnBnClickedPaint();
	// 存放交点个数
	int m_result;
	// 被选中的函数
	CString m_selected;
	afx_msg void OnNMClickList1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBnClickedDelete();
	// 输入的图形字符串
	CString m_input;
	afx_msg void OnBnClickedAdd();
};
