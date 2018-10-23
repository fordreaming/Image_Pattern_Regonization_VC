// BpNet.h: interface for the BpNet class.
// 2005.1.13��16��02 By Superman 
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BPNET_H__3A171E41_1E8B_11D7_BA67_936006E9954B__INCLUDED_)
#define AFX_BPNET_H__3A171E41_1E8B_11D7_BA67_936006E9954B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class BpNet  
{
public:
	double tjpt[4];
	double shuchu[4];
	double m[4];
	double * sim(double *psim);
	void train(double p[200][5],double t[200][4],int samplenum);

	BpNet();

	virtual ~BpNet();

	int inNum;  //��������
	int hideNum;//���������
	int outNum;  //��������

	double x[200]; //��������
	double x1[200];//�������״ֵ̬
	double x2[200];//������״ֵ̬
	double o1[200];//�����㼤��ֵ
	double o2[200];//����㼤��ֵ
	double w[5][10];//�������Ȩֵ
	double w1[10][4];//������Ȩֵ
	double rate_w; //Ȩֵѧϰ�ʣ������-������)
	double rate_w1;//Ȩֵѧϰ�� (������-�����)
	double rate_b1;//�����㷧ֵѧϰ��
	double rate_b2;//����㷧ֵѧϰ��
	double b1[10];//������㷧ֵ
	double b2[4];//�����㷧ֵ
	double pp[200];
	double qq[200];
    double yd[200];//ϣ�����ֵ
	double e;
	double error;//�����������
};

#endif // !defined(AFX_BPNET_H__3A171E41_1E8B_11D7_BA67_936006E9954B__INCLUDED_)
