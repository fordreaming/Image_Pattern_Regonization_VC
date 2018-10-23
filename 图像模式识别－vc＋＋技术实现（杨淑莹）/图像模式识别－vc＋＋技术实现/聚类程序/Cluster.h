// Cluster.h: interface for the CCluster class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CLUSTER_H__E921280B_4D09_4970_813F_8831EAEDF1F4__INCLUDED_)
#define AFX_CLUSTER_H__E921280B_4D09_4970_813F_8831EAEDF1F4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Cdib.h"

const int N=7;

class CCluster : public CDib  
{

public:
struct Pattern //�����ṹ
{ 
	int			index;    //�������
	int			category;   //������ģ���������
	double		feature[N*N];//����ֵ
	double		distance; // ��Ʒ�������ĵľ���
	CPoint		lefttop,rightbottom;//��Ʒ��ͼ���е�λ��
};

struct	Center//�������Ľṹ
{
	int 		index;//���ı��
	double		feature[N*N];//��������ֵ
	int 		patternnum;//�þ������İ�������Ʒ��Ŀ
};



public:
	int			patternnum;//��������
	int 		centernum;//����������Ŀ
	Pattern		*m_pattern;//ָ��������ָ��
	Center		*m_center;//ָ�����ĵ�ָ��
	int			wide, height;//ͼ��Ŀ���
public:
	CCluster();
	virtual ~CCluster();

public:
	void GetFeature();
	void CalFeature(CCluster::Pattern *m_pattern);
	void CalCenter(CCluster::Center *pcenter);
	double GetDistance( CCluster::Pattern  pattern1, CCluster::Pattern  pattern2, const int distype);
	double GetDistance(CCluster::Pattern  pattern,  CCluster::Center   center, const int distype);
	double GetDistance(CCluster::Center  mCenter1,CCluster::Center  mCenter2,int distype);
	double GetDistance(double * dis, int i, int j);
	double GetFuzzyDistance(CCluster::Pattern pattern1,CCluster::Pattern pattern2,int distype);
	void FuzzyCluster();
	void ISODATA();
	void Kjunzhi();
	void Leipingjunjulifa();
	void Zhongxinfa();
	void Zhongjianjulifa();
	void Zuichangjulifa();
	void Zuiduanjulifa();
	void Zuidazuixiaojulifa();

	void Zuilinjinguize();

};

#endif // !defined(AFX_CLUSTER_H__E921280B_4D09_4970_813F_8831EAEDF1F4__INCLUDED_)
