// NewPixel.h: interface for the CNewPixel class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_NEWPIXEL_H__CC9BA4DE_B83D_4B9E_8DF1_74CF0496B622__INCLUDED_)
#define AFX_NEWPIXEL_H__CC9BA4DE_B83D_4B9E_8DF1_74CF0496B622__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CNewPixel  //新像素类
{
public:
	CNewPixel();
	virtual ~CNewPixel();
	long x;//像素中点x坐标
	long y;//像素中点y坐标	
};

#endif // !defined(AFX_NEWPIXEL_H__CC9BA4DE_B83D_4B9E_8DF1_74CF0496B622__INCLUDED_)
