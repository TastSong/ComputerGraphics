// Rectangle.h: interface for the CRectangle class.
//
//////////////////////////////////////////////////////////////////////

#ifndef _CRECTANGLE_H
#define _CRectangle_H

class CRectangle//���峤������  
{
public:
	CRectangle();
	CRectangle(double,double,double,double,double,double);//�����ι��캯��
	virtual ~CRectangle();
	void DrawRectangle(CDC*);//���Ƴ�����
	void MoveRectangle();//�ƶ�������
	void SetSpeed(double,double);//���ó������ƶ��ٶ�
public:
	double X;//�������ĵ�X����
	double Y;//�������ĵ�Y����
	double SpeedX;//����X�����ƶ��ٶ�
	double SpeedY;//����Y�����ƶ��ٶ�
	double Width;//���ο��
	double Height;//���θ߶�
};

#endif 
