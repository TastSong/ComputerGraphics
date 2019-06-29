// Stack_Node.h: interface for the CStack_Node class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_STACK_NODE_H__7B71DCDD_7395_4F11_8358_2079C832E8DE__INCLUDED_)
#define AFX_STACK_NODE_H__7B71DCDD_7395_4F11_8358_2079C832E8DE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CStack_Node  //Ω·µ„¿‡
{
public:
	CStack_Node();
	virtual ~CStack_Node();
	CPoint PixelPoint;
	CStack_Node *next;
};

#endif // !defined(AFX_STACK_NODE_H__7B71DCDD_7395_4F11_8358_2079C832E8DE__INCLUDED_)
