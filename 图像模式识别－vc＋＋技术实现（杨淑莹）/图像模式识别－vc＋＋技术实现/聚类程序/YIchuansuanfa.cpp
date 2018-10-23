// YIchuansuanfa.cpp: implementation of the YIchuansuanfa class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "YIchuansuanfa.h"
#include  <stdio.h>
#include  <stdlib.h>
#include   <math.h>
#define   POPSIZE      500   //��Ⱥ����
#define   MAXIMIZATION 1
#define   MINIMIZATION 2
#define   Cmax         100
#define   Cmin         0
#define   LENGTH1      10//��һ��������Ⱦɫ�峤��
#define   LENGTH2      10//�ڶ���������Ⱦɫ�峤��
    
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

YIchuansuanfa::YIchuansuanfa()
{
    FunctionMode=MAXIMIZATION;
	PopSize=80;
	Pc=0.6;//�������0.6
	Pm=0.05;//�������0.01
	index=1;
}

YIchuansuanfa::~YIchuansuanfa()
{

}
void YIchuansuanfa::  main()
	{
		if (centernum!=0)
		{
			generation=0;
			GenerationInitialPopulation();
			EvaluatePopulation();
			while (generation<MaxGeneration)
			{
				generation++;
				GenerateNextPopulation();
				EvaluatePopulation();
				PerformEvolution();
			}
			for (int i=0;i<patternnum;i++)
			{
				m_pattern[i].category=currentbest.chrom[i];
			}
			
			CString s;
			s.Format("���Ž�����ڵ�%d��",index);
			AfxMessageBox(s);
		}
		else
		{
			AfxMessageBox("��������Ŀ����Ϊ0��");
			return;		
		}
	}
void YIchuansuanfa::GenerationInitialPopulation()
	{
		int  i,j;
		CHROMLENGTH=patternnum;
		for(i=0;i<PopSize;i++)
		{
			for(j=0;j<CHROMLENGTH;j++)//��ʼ��Ⱦɫ��
			{
				population[i].chrom[j]=rand()%centernum+1;
			}
			population[i].chrom[CHROMLENGTH]='\0';
		}

	}
	void YIchuansuanfa::GenerateNextPopulation()
	{
		SelectionOperator();
		CrossoverOperator();
		MutationOperator();
	}
	void YIchuansuanfa::EvaluatePopulation()
	{
		CalculateObjectValue();
		CalculateFitnessValue();
		FindBestAndWorstIndividual();
	}
/*	long YIchuansuanfa::DecodeChromosome(char *string,int point,int length)
	{
		int i;
		long decimal=0L;
		char *pointer;
		for(i=0,pointer=string+point;i<length;i++,pointer++)
		{
			decimal+=(*pointer-'0')<<(length-1-i);
		}
		return (decimal);
	}*/
	void YIchuansuanfa::CalculateObjectValue()
	{
		if (m_center!=NULL)
			delete []m_center;
		m_center=new Center[patternnum];
		for (int t=0;t<centernum;t++)
		{
			m_center[t].index=t+1;
			m_center[t].patternnum=0;
			for (int m=0;m<N*N;m++)
				m_center[t].feature[m]=0.0;
		}

		double sumdistance;

		for(int i=0;i<PopSize;i++)//����population[i]��value
		{
			for (int t=0;t<centernum;t++)
			{
				m_center[t].patternnum=0;
				for (int m=0;m<N*N;m++)
				m_center[t].feature[m]=0.0;
			}
			for (int j=0;j<centernum;j++)//������
			{
				for(int k=0;k<patternnum;k++)
				{
					if (population[i].chrom[k]==j+1)
					{
						m_center[j].patternnum++;
						for(int n=0;n<N*N;n++ )
							m_center[j].feature[n]+=m_pattern[k].feature[n];
					}
				}
				if (m_center[j].patternnum!=0)
				{
					for(int n=0;n<N*N;n++ )
						m_center[j].feature[n]/=(double)m_center[j].patternnum;
				}
			}

			sumdistance=0.0;	//cal value
			for ( j=0;j<centernum;j++)
			{
				for(int k=0;k<patternnum;k++)
				{
					if (population[i].chrom[k]==j+1)
					{
						sumdistance+=GetDistance(m_pattern[k],m_center[j],1);
					}
				}
			
			}
		
	    	population[i].value=sumdistance	;
		}

	}
	void YIchuansuanfa::CalculateFitnessValue()
	{	
		//����value������С����
		int i,j;
		for(i=0;i<PopSize;i++)
		{
			population[i].index=-1;
		}

		for (i=1;i<=PopSize;i++)
		{
			int index=0;
			for (j=0;j<PopSize;j++)
			{
				if (population[j].index==-1)
				{
					index=j;
					break;
				}
			}
			for(j=0;j<PopSize;j++)
			{
				if(population[j].index==-1 && population[j].value<population[index].value)
					index=j;
			}
			population[index].index=i;
		}
		//������Ӧ��
		for(i=0;i<PopSize;i++)
		{
			double a=0.6;
			population[i].fitness=a*pow((1-a),population[i].index-1);
		}
	

	}
	void YIchuansuanfa::FindBestAndWorstIndividual()
	{
		int i;
		bestindividual=population[0];
		worstindividual=population[0];
		for(i=1;i<PopSize;i++)
		{
			if(population[i].value<bestindividual.value)
			{
				bestindividual=population[i];
				best_index=i;
			}else if(population[i].value>worstindividual.value)
			{
				worstindividual=population[i];
				worst_index=i;
			}
		}
		if(generation==0)
		{
			currentbest=bestindividual;
		}
		else
		{
			if(bestindividual.value<currentbest.value)
			{
				currentbest=bestindividual;
				index=generation;
			}
		}
	}
	void YIchuansuanfa::PerformEvolution()
	{
		if(bestindividual.value<currentbest.value)
		{
			currentbest=population[best_index];
		}else
		{
			population[worst_index]=currentbest;
		}
	}
	void YIchuansuanfa::SelectionOperator()
	{
		int i,index;
		double p,sum=0.0;
		double cfitness[POPSIZE];
		struct individual newpopulation[POPSIZE];
		for(i=0;i<PopSize;i++)
		{
			sum+=population[i].fitness;
		}
		for(i=0;i<PopSize;i++)
		{
			cfitness[i]=population[i].fitness/sum;
		}
		for(i=1;i<PopSize;i++)
		{
			cfitness[i]=cfitness[i-1]+cfitness[i];
		}
		for(i=0;i<PopSize;i++)
		{
			p=rand()%1000/1000.0;
			index=0;
			while(p>cfitness[index])
			{
				index++;
			}
			newpopulation[i]=population[index];
		}
		//ѡ����һ��Ⱥ��
		for(i=0;i<PopSize;i++)
		{
			population[i]=newpopulation[i];
		}
	}
	void YIchuansuanfa::CrossoverOperator()
	{
		int i,j;
		int index[POPSIZE];
		int point=0,temp;
		double p;
		int  ch;
		for(i=0;i<PopSize;i++)
		{
			index[i]=i;
		}
		for(i=0;i<PopSize;i++)
		{
			point=rand()%PopSize-i;
			temp=index[i];
			index[i]=index[point+i];
			index[point+i]=temp;
		}
		//�������
		for(i=0;i<PopSize-1;i+=2)
		{
			p=rand()%1000/1000.0;
			if(p<Pc)
			{
				point=(rand()%CHROMLENGTH-1)+1;
				for(j=point;j<CHROMLENGTH;j++)
				{
					ch=population[index[i]].chrom[j];
					population[index[i]].chrom[j]=population[index[i+1]].chrom[j];
					population[index[i+1]].chrom[j]=ch;
				}
			}
		}
	}
	void YIchuansuanfa::MutationOperator()
	{
		int i,j;
		double p;
		//����
		for(i=0;i<PopSize;i++)
		{
			for(j=0;j<CHROMLENGTH;j++)
			{
				p=rand()%1000/1000.0;
				if(p<Pm)
				{
					population[i].chrom[j]=rand()%centernum+1;
				}
			}
		}
	}
	void YIchuansuanfa::OutputTextReport()
	{

		CString str,s;
		s.Format("%f",currentbest.value);
		str.Insert(str.GetLength(),"present best value: ");
		str.Insert(str.GetLength(),s);


		s.Format("�� %d ��",generation);
        str.Insert(str.GetLength(),"\n");
		str.Insert(str.GetLength(),s);
		str.Insert(str.GetLength(),"\n");

		for (int i=0;i<CHROMLENGTH;i++)
		{
			s.Format("%d",currentbest.chrom[i]);
			str.Insert(str.GetLength(),s);
		}
		AfxMessageBox(str);

	}
