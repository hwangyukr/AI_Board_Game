
// DdangDdaMuckgiDlg.h : 헤더 파일
//

#pragma once
#include "afxwin.h"
#include "CvvImage.h"
#include "highgui.h"
#include "cv.h"
#include "cxcore.h"
#include "ml.h"

#include <vector>
using namespace std;
typedef vector<CPoint> Via;

class Triangle
{
public:
	Triangle(CPoint p1, CPoint p2, CPoint p3)
	{
		pt[0] = p1;
		pt[1] = p2;
		pt[2] = p3;
		owner = -1;
	}
	bool has(CPoint p)
	{
		return (p == pt[0] || p == pt[1] || p == pt[2]);
	}
	CPoint pt[3]; // 삼각형을 이루는 세 점의 좌표
	int owner;	  // 소유자 : 0이면 RED소유, 1이면 BLUE소유
};


class BackupData
{
public:
	int temp_map[7][7];
	Via temp_via[7][7];
	vector <Triangle*> temp_triangle;
	int temp_red_score;
	int temp_blue_score;

	int temp_line[160][4];
	int temp_count;
	bool temp_chk;
};


// CDdangDdaMuckgiDlg 대화 상자
class CDdangDdaMuckgiDlg : public CDialogEx
{
// 생성입니다.
public:
	CDdangDdaMuckgiDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

	CRect view;
	IplImage *m_view;
	CvvImage m_View;

	int map[7][7];
	Via via[7][7];	
	vector <Triangle*> triangle;

	int line[160][4];
	int count;
	CvPoint start_point, end_point;
	bool chk;

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DDANGDDAMUCKGI_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.

// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CStatic m_iView;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	int x_point1;
	int x_point2;
	int y_point1;
	int y_point2;
	int red_score;
	int blue_score;
	bool polygon;
	int rnum;
	afx_msg void OnBnClickedInput();
	CString team_name;
	CString histo;
	afx_msg void OnBnClickedRestart();

private:
	int CheckDotCross(int x1, int y1, int x2, int y2);
	int CheckLineCrossOneToOne(CPoint s1, CPoint e1, CPoint s2, CPoint e2);
	int CheckLineCross(CPoint s1, CPoint e1);
	int CheckSameLineOneToOne(CPoint s1, CPoint e1, CPoint s2, CPoint e2);
	int CheckSameLine(CPoint s1, CPoint e1);
	int AddTriangle(CPoint p1, CPoint p2, int team);
	void DeleteTriangle(Triangle *t);
	bool CheckTriangle(Triangle *p);
	bool CheckTriangle(CPoint p);
	bool CanConnect(int x1, int y1, int x2, int y2);

	int WillBeTriangle(int x1, int y1, int x2, int y2);
	int WillBeTriangleEx(int x1, int y1, int x2, int y2, int a1, int b1, int a2, int b2);
	int AddLine(int x1, int y1, int x2, int y2, bool emsg = true);

	int AI();
	void MonteCarloAI();

	BackupData *CreateBackup();
	void SetFromBackup(BackupData *bd);

public:
//	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMButtonDown(UINT nFlags, CPoint point);
};

