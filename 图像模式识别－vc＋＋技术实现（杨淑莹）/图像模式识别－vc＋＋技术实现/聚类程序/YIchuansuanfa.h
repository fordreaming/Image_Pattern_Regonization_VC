// YIchuansuanfa.h: interface for the YIchuansuanfa class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_YICHUANSUANFA_H__5EC8E48F_0B4E_4548_8A5A_F50BCB371440__INCLUDED_)
#define AFX_YICHUANSUANFA_H__5EC8E48F_0B4E_4548_8A5A_F50BCB371440__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Cluster.h"

class YIchuansuanfa : public CCluster
{
public:
	YIchuansuanfa();
	virtual ~YIchuansuanfa();
	int     FunctionMode;
 	int     CHROMLENGTH;
    int     PopSize;
    int     MaxGeneration;
	double  Pc;//�������
	double  Pm;//�������

	struct  individual
	{
		int		chrom[50];
	    double value;
		double fitness;
		int    index;
	};
	int    index;//���Ž���ֵ���С����
	int    generation;
	int    best_index;
	int    worst_index;
	struct individual bestindividual;//���Ÿ���
	struct individual worstindividual;//������
	struct individual currentbest;//��ǰ�����Ÿ���
	struct individual population[80];
	void   GenerationInitialPopulation();
	void   GenerateNextPopulation();//��ֳ��һ����
	void   EvaluatePopulation();//������Ⱥ
	void   CalculateObjectValue();//���������ֵ
	void   CalculateFitnessValue();//������Ӧ��
	void   FindBestAndWorstIndividual();
	void   PerformEvolution();//��ʼ�ݱ�
	void   SelectionOperator();
	void   CrossoverOperator();
	void   MutationOperator();
	void   OutputTextReport();
	void   main();
};

#endif // !defined(AFX_YICHUANSUANFA_H__5EC8E48F_0B4E_4548_8A5A_F50BCB371440__INCLUDED_)
