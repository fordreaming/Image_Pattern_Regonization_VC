// Classification.cpp: implementation of the Classification class.
// 2005.1.13��16��02 By Superman 
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
//#include "DSPLIT.h"
#include "Classification.h"
#include "matrix.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Classification::Classification()
{

}

Classification::~Classification()
{

}



/******************************************************************
*   �������ƣ�LeastDistance()
*   �������ͣ�number_no���ṹ��
*   �������ܣ���С���뷨 ,�����������ͱ��
******************************************************************/
number_no Classification::LeastDistance()
{
	double min=10000000000;
	number_no number_no;
	for(int n=0;n<10;n++)
	{
		for(int i=0;i<pattern[n].number;i++)
		{
			if(pipei(pattern[n].feature[i],testsample)<min)
			{
				//ƥ�����Сֵ
				min=pipei(pattern[n].feature[i],testsample);
				number_no.number=n;//��Ʒ���
				number_no.no=i;//��Ʒ���
			}
		}
	}
	return number_no;//������д���ֵ��������
}

/******************************************************************
*   �������ƣ�Fisher_2Classes(int Class0, int Class1)
*   �������ͣ�int 
*   ����˵����Class0,Class1��0��9�е������������
*   �������ܣ�����Fisher������,����Class0��Class1�е�һ��
******************************************************************/
int Classification::Fisher_2Classes(int Class0, int Class1)
{
	double Xmeans[2][25];//����ľ�ֵ
	double S[2][25][25];//��Ʒ������ɢ�Ⱦ���
	double Sw[25][25];//�������ɢ�Ⱦ���
	double Sw_[25][25];//Sw�������
	double W[25];//������w*
	double difXmeans[25];//��ֵ��
	double X[25];//δ֪��Ʒ
	double m0,m1;//����Ʒ��ֵ
	double y0;//��ֵy0
	int i,j,k;

	for(i=0;i<2;i++)
		for(j=0;j<25;j++)
			Xmeans[i][j]=0;
	int num0,num1;		//������Ʒ�ĸ���
	//������Ʒ����
	double mode0[200][25],mode1[200][25];
	//������Ʒ����
	num0=40;//pattern[Class0].number;
	num1=40;//pattern[Class1].number;
	for(i=0;i<num0;i++)
	{
		for(j=0;j<25;j++)
		{
			Xmeans[0][j]+=pattern[Class0].feature[i][j];
			mode0[i][j]=pattern[Class0].feature[i][j];
		}
	}

	for(i=0;i<num1;i++)
	{
		for(j=0;j<25;j++)
		{
			Xmeans[1][j]+=pattern[Class1].feature[i][j];	
			mode1[i][j]=pattern[Class1].feature[i][j];
		}
	}
	//���������Ʒ��ֵ����
	for(i=0;i<25;i++)	
	{
		Xmeans[0][i]/=(double)num0;
		Xmeans[1][i]/=(double)num1;
	}
	//��������Ʒ������ɢ�Ⱦ���
	for(i=0;i<25;i++)
	for(j=0;j<25;j++)
	{
		double s0=0.0,s1=0.0;
		for(k=0;k<num0;k++)
			s0=s0+(mode0[k][i]-Xmeans[0][i])*(mode0[k][j]-Xmeans[0][j]);
		s0=s0/(double)(num0-1);
		S[0][i][j]=s0;//��һ��
		for(k=0;k<num1;k++)
			s1=s1+(mode1[k][i]-Xmeans[1][i])*(mode1[k][j]-Xmeans[1][j]);
		s1=s1/(double)(num1-1);
		S[1][i][j]=s1;//�ڶ���		
	}
	//�������ɢ�Ⱦ���
	for(i=0;i<25;i++)
	for(j=0;j<25;j++)
	{
		Sw[i][j]=S[0][i][j]+S[1][i][j];
	}
	//Sw�������
	for(i=0;i<25;i++)
		for(j=0;j<25;j++)
			Sw_[i][j]=Sw[i][j];	
	double(*p)[25]=Sw_;	
	brinv(*p,25);		//Sw�������Sw_
	//����w*  w*��Sw_��(Xmeans0-Xmeans1)
	for(i=0;i<25;i++)
		difXmeans[i]=Xmeans[0][i]-Xmeans[1][i];
	for(i=0;i<25;i++)
		W[i]=0.0;
	brmul(Sw_,difXmeans,25,W);//�����W*
	
	//������Ʒ��ֵ
	m0=0.0;
	m1=0.0;
	for(i=0;i<num0;i++)
	{
		m0+=brmul(W,mode0[i],25);
	}
	for(i=0;i<num1;i++)
	{
		m1+=brmul(W,mode1[i],25);
	}
	m0/=(double)num0;
	m1/=(double)num1;
	y0=(num0*m0+num1*m1)/(num0+num1);//��ֵy0
	
	//�����������д����X
	for(i=0;i<25;i++)
		X[i]=testsample[i];
	double y;//X��w*�ϵ�ͶӰ��
	y=brmul(W,X,25);
	if (y>=y0) 
		return Class0;
	else
		return Class1;
}

/******************************************************************
*   �������ƣ�Fisher()
*   �������ͣ�int 
*   �������ܣ�Fisher������,������д���ֵ����
******************************************************************/
int Classification::Fisher()
{
	int i,j,number,maxval,num[10];
	for(i=0;i<10;i++)
		num[i]=0;
	for(i=0;i<10;i++)
		for(j=0;j<i;j++)
			num[Fisher_2Classes(i,j)]++;
	maxval=num[0];
	number=0;
	for(i=1;i<10;i++)
	{
		if(num[i]>maxval)
		{
			maxval=num[i];
			number=i;
		}
	}
	return number;
}

/******************************************************************
*   �������ƣ�BayesErzhishuju()
*   �������ͣ�int 
*   �������ܣ����ڶ�ֵ���ݵ�Bayes������ ,������д���ֵ����
******************************************************************/
int Classification::BayesErzhishuju()
{
	double Pw[10];//�������P(wj)=Nj/N
	double P[10][25];//Pj(wi)wi:wi�࣬j:��j������
	double PXw[10];//����������P(X|wj)
	double PwX[10];//�������P(wj|X)

	int i,j;

	//���������
	int n[10];//������Ʒ��
	int N=0;//��Ʒ����
	for(i=0;i<10;i++)
	{
		//�����������Ʒ��
		n[i]=pattern[i].number;
		N+=n[i];//��Ʒ����
	}
	for(i=0;i<10;i++)
		Pw[i]=(double)n[i]/(double)N;//�������
	
	//������������
	for(i=0;i<10;i++)
	{
		for(j=0;j<25;j++)
		{
			int numof1=0;//��ֵ������1�ĸ���
			for(int k=0;k<pattern[i].number;k++)
				numof1+=pattern[i].feature[k][j]>0.1?1:0;
			P[i][j]=(double)(numof1+1)/(double)(n[i]+2);
		}
	}

	for(i=0;i<10;i++)
	{
		double p=1;
		for(int j=0;j<25;j++)
		{
			p*=(testsample[j]>0.1)?P[i][j]:1-P[i][j];
		}
		PXw[i]=p;
	}

	//��������
	double PX=0.0,maxP=0.0;
	int number;
	for(i=0;i<10;i++)
	{
		PX+=Pw[i]*PXw[i];
	}

	for(i=0;i<10;i++)
	{
		PwX[i]=Pw[i]*PXw[i]/PX;
		if(PwX[i]>maxP)
		{
			maxP=PwX[i];
			number=i;
		}
	}
	return number;
}

/******************************************************************
*   �������ƣ�BayesLeasterror()
*   �������ͣ�int 
*   �������ܣ���С������ʵ�Bayes������ ,������д���ֵ����
******************************************************************/
int Classification::BayesLeasterror()
{
	double X[25];//������Ʒ
	double Xmeans[25];//��Ʒ�ľ�ֵ
	double S[25][25];//Э�������
	double S_[25][25];//S�������
	double Pw;//�������
	double hx[10];//�б���
	
	int i,j,k,n;
	
	for(n=0;n<10;n++)//ѭ�����0��9
	{
		int num=pattern[n].number;//��Ʒ����
		//����Ʒƽ��ֵ
		for(i=0;i<25;i++)
			Xmeans[i]=0.0;
		for(k=0;k<num;k++)
		{
			for(i=0;i<25;i++)
				Xmeans[i]+=pattern[n].feature[k][i]>0.10?1.0:0.0;
		}
		for(i=0;i<25;i++)
			Xmeans[i]/=(double)num;
		//��Э�������
		double mode[200][25];
		for(i=0;i<num;i++)
			for(j=0;j<25;j++)
				mode[i][j]=pattern[n].feature[i][j]>0.10?1.0:0.0;
		for(i=0;i<25;i++)
		for(j=0;j<25;j++)
		{
			double s=0.0;
			for(k=0;k<num;k++)
				s=s+(mode[k][i]-Xmeans[i])*(mode[k][j]-Xmeans[j]);
			s=s/(double)(num-1);
			S[i][j]=s;
		}
		//���������
		int total=0;
		for(i=0;i<10;i++)
			total+=pattern[i].number;
		Pw=(double)num/(double)total;
		//��S�������
		for(i=0;i<25;i++)
			for(j=0;j<25;j++)
				S_[i][j]=S[i][j];

		double(*p)[25]=S_;

		brinv(*p,25);//S�������
		//��S������ʽ
		double (*pp)[25]=S;
		double DetS;
		DetS=bsdet(*pp,25);//S������ʽ
		//���б���
		for(i=0;i<25;i++)
			X[i]=testsample[i]>0.10?1.0:0.0;
		for(i=0;i<25;i++)
			X[i]-=Xmeans[i];
		double t[25];
		for(i=0;i<25;i++)
			t[i]=0;
		brmul(X,S_,25,t);
		double t1=brmul(t,X,25);
		double t2=log(Pw);
		double t3=log(DetS+1);
		hx[n]=-t1/2+t2-t3/2;
	}

	double maxval=hx[0];
	int number=0;
	//�б��������ֵ
	for(n=1;n<10;n++)
	{
		if(hx[n]>maxval)
		{
			maxval=hx[n];
			number=n;
		}
	}
	return number;
}

/******************************************************************
*   �������ƣ�BayesLeastRisk(double loss[10][10])
*   �������ͣ�double*
*   ����˵����double loss[10][10]����ʧ
*   �������ܣ���С���յ�Bayes������ �����ظ���ķ���ֵ
******************************************************************/
double* Classification::BayesLeastRisk(double loss[10][10])
{
	double X[25];//������Ʒ
	double Xmeans[25];//��Ʒ�ľ�ֵ
	double S[25][25];//Э�������S
	double S_[25][25];//S�������
	double P[10];//�������
	double Pw;//�������
	double hx[10];//�б���
	
	int i,j,k,n;
	
	for(n=0;n<10;n++)//
	{
		int num=pattern[n].number;//��Ʒ����
		//����Ʒ��ֵ
		for(i=0;i<25;i++)
			Xmeans[i]=0.0;
		for(k=0;k<num;k++)
		{
			for(i=0;i<25;i++)
				Xmeans[i]+=pattern[n].feature[k][i]>0.2?1.0:0.0;
		}
		for(i=0;i<25;i++)
			Xmeans[i]/=(double)num;
		//��Э�������
		double mode[200][25];
		for(i=0;i<num;i++)
			for(j=0;j<25;j++)
				mode[i][j]=pattern[n].feature[i][j]>0.2?1.0:0.0;
		for(i=0;i<25;i++)
		for(j=0;j<25;j++)
		{
			double s=0.0;
			for(k=0;k<num;k++)
				s=s+(mode[k][i]-Xmeans[i])*(mode[k][j]-Xmeans[j]);
			s=s/(double)(num-1);
			S[i][j]=s;
		}
		//���������
		int total=0;//��Ʒ����
		for(i=0;i<10;i++)
			total+=pattern[i].number;
		Pw=(double)num/(double)total;
		//��S�������
		for(i=0;i<25;i++)
			for(j=0;j<25;j++)
				S_[i][j]=S[i][j];

		double(*p)[25]=S_;

		brinv(*p,25);//S�������
		//��S������ʽ
		double (*pp)[25]=S;
		double DetS;
		DetS=bsdet(*pp,25);//S������ʽ
		//���б���
		for(i=0;i<25;i++)
			X[i]=testsample[i]>0.2?1.0:0.0;
		for(i=0;i<25;i++)
			X[i]-=Xmeans[i];
		double t[25];
		for(i=0;i<25;i++)
			t[i]=0;
		brmul(X,S_,25,t);
		double t1=brmul(t,X,25);
		double t2=log(Pw);
		double t3=log(DetS+1);
		P[n]=-t1/2+t2-t3/2;
	}
	
	for(n=0;n<10;n++)
	{
		double t=0.0;
		for(i=0;i<10;i++)
			t+=loss[n][i]*P[i];
		hx[n]=t;
	}
	
	return (double*)hx;
}

/******************************************************************
*   �������ƣ�Jiangcheng()
*   �������ͣ�int 
*   �������ܣ������㷨 ,������д���ֵ����
******************************************************************/
int Classification::Jiangcheng()
{
	double w[10][26];//Ȩֵ
	double d[10];//����������Ȩʸ��
	double x[26];//��1��Ʒ
	double hx[10];//�б���
	bool flag;
	int n,i,j,k;
	int c=0;//��������

	//Ȩֵ��ֵΪ0
	for(n=0;n<10;n++)
		for(i=0;i<26;i++)
			w[n][i]=0;
	do
	{
		flag=true;
		for(n=0;n<10;n++)
		{
			for(i=0;i<40;i++)//for(i=0;i<pattern[n].number;i++)
			{
				//ȡ��֪��Ʒ
				for(j=0;j<25;j++)
					x[j]=pattern[n].feature[i][j];
				x[25]=1;//���һλ��1
				//������Ȩʸ��
				for(j=0;j<10;j++)
					d[j]=0;
				for(j=0;j<10;j++)
					for(k=0;k<26;k++)
						d[j]+=w[j][k]*x[k];
				bool f=true;
				//�ж�d[n]�Ƿ�Ϊ���ֵ
				for(j=0;j<10;j++)
				{
					if(j!=n)
						f&=(d[n]>d[j])?true:false;
				}

				if(f)//��d[n]Ϊ���ֵ
					flag&=true;//ͨ������
				else//����δͨ��������Ҫ����Ȩֵ
				{
					for(j=0;j<10;j++)
					{
						for(k=0;k<26;k++)
						{
							if(j==n)
								w[j][k]+=x[k];
							else if(d[j]>d[n])
								w[j][k]-=x[k];
							else;
						}
					}
					flag&=false;
				}
			}
		}
		if(++c>2000)break;
	}while(!flag);//����Ϊֹ�õ������б���Ȩʸ��

	double num[26];//δ֪��Ʒ
	for(i=0;i<25;i++)
		num[i]=testsample[i];
	num[25]=1;//ĩλ��1
	for(n=0;n<10;n++)//�����б���
	{
		hx[n]=0;
		for(i=0;i<26;i++)
			hx[n]+=w[n][i]*num[i];
	}

	double maxval=hx[0];
	int number=0;
	for(n=1;n<10;n++)//ȡ�б������ֵ
	{
		if(hx[n]>maxval)
		{
			maxval=hx[n];
			number=n;
		}
	}
	return number;
}

/******************************************************************
*   �������ƣ�LMSE()
*   �������ͣ�int 
*   �������ܣ�LMSE�㷨 ,������д���ֵ����
******************************************************************/
int Classification::LMSE()
{
	double w[10][26];//Ȩֵ
	double d[10];//����������Ȩʸ��
	double x[26];//��1��Ʒ
	bool flag;
	int n,i,j,k;

	//Ȩֵ��ֵΪ0
	for(n=0;n<10;n++)
		for(i=0;i<26;i++)
			w[n][i]=0;
	int c=0,cc=1;
	do
	{
		flag=true;
		for(n=0;n<10;n++)
		{
				for(i=0;i<40;i++)//for(i=0;i<pattern[n].number;i++)
			{
				//ȡ��֪��Ʒ
				for(j=0;j<25;j++)
					x[j]=pattern[n].feature[i][j];
				x[25]=1;//ĩλ��1
				//������Ȩʸ��
				for(j=0;j<10;j++)
					d[j]=0;
				for(j=0;j<10;j++)
					for(k=0;k<26;k++)
						d[j]+=w[j][k]*x[k];
				bool f=true;
				//d[n]�Ƿ����ֵ��
				for(j=0;j<10;j++)
				{
					if(j!=n)
						f&=(d[n]>d[j])?true:false;
				}

				if(f)//��d[n]Ϊ���ֵ
					flag&=true;
				else
					flag&=false;

				for(j=0;j<10;j++)//�ı�Ȩֵ��10��
				{
					double rX;
					if(j==n)//�ǵ�ǰ���
						rX=1.0;//r[X(k)]=1
					else
						rX=0.0;//r[X(k)]=0
					
					for(k=0;k<26;k++)
					{
						w[j][k]+=x[k]*(rX-d[j])/cc;
					}
				}
				++cc;
			}
		}
		if(++c>2000)break;
	}while(!flag);//����Ϊֹ�õ������б���Ȩʸ��
	
	double hx[10];
	double num[26];
	//ȡδ֪��Ʒ
	for(i=0;i<25;i++)
		num[i]=testsample[i];
	num[25]=1;//ĩλ��1
	//�����б���
	for(n=0;n<10;n++)
	{
		hx[n]=0;
		for(i=0;i<26;i++)
			hx[n]+=w[n][i]*num[i];
	}
	//�б������ֵ
	double maxval=hx[0];
	int number=0;
	for(n=1;n<10;n++)
	{
		if(hx[n]>maxval)
		{
			maxval=hx[n];
			number=n;
		}
	}
	return number;
}

/******************************************************************
*   �������ƣ�Zengliangjiaozheng()
*   �������ͣ�int 
*   �������ܣ�����У���㷨 ,������д���ֵ����
******************************************************************/
int Classification::Zengliangjiaozheng()
{
	double w[10][26];//Ȩֵ
	double d[10];//����������Ȩʸ��
	double x[26];//��1��Ʒ
	bool flag;
	int n,i,j,k;

	//Ȩֵ��ֵΪ0
	for(n=0;n<10;n++)
		for(i=0;i<26;i++)
			w[n][i]=0;
	int c=0,cc=1;
	do
	{
		flag=true;
		for(n=0;n<10;n++)
		{
			for(i=0;i<10;i++)//	for(i=0;i<pattern[n].number;i++)
			{
				//ȡ��֪��Ʒ
				for(j=0;j<25;j++)
					x[j]=pattern[n].feature[i][j];
				x[25]=1;//ĩλ��1
				//������Ȩʸ��
				for(j=0;j<10;j++)
					d[j]=0;
				for(j=0;j<10;j++)
					for(k=0;k<26;k++)
						d[j]+=w[j][k]*x[k];
				bool f=true;
				//d[n]�Ƿ����ֵ��
				for(j=0;j<10;j++)
				{
					if(j!=n)
						f&=(d[n]>d[j])?true:false;
				}

				if(f)//��d[n]Ϊ���ֵ
					flag&=true;
				else//����
					flag&=false;

				for(j=0;j<10;j++)
				{
					double rX;
					if(j==n)//�ǵ�ǰ���
						rX=1.0;//r[X(k)]=1
					else
						rX=0.0;//r[X(k)]=0

					if(d[j]<rX)//W(k)X(k)<r[X(k)]
					{
						for(k=0;k<26;k++)
							w[j][k]+=x[k]/cc;
					}
					else//W(k)X(k)��r[X(k)]
					{
						for(k=0;k<26;k++)
							w[j][k]-=x[k]/cc;
					}
				}
				++cc;
			}
		}
		if(++c>2000)break;
	}while(!flag);//����Ϊֹ�õ������б���Ȩʸ��
	
	double hx[10];
	double num[26];
	//ȡδ֪��Ʒ
	for(i=0;i<25;i++)
		num[i]=testsample[i];
	num[25]=1;//ĩλ��1
	//���б���
	for(n=0;n<10;n++)
	{
		hx[n]=0;
		for(i=0;i<26;i++)
			hx[n]+=w[n][i]*num[i];
	}
	//�б������ֵ
	double maxval=hx[0];
	int number=0;
	for(n=1;n<10;n++)
	{
		if(hx[n]>maxval)
		{
			maxval=hx[n];
			number=n;
		}
	}
	return number;
}

/******************************************************************
*   �������ƣ�ifClassified(int Class0,int Class1)
*   �������ͣ�CString
*   ����˵����int Class0,int Class1:Ҫ��֤���������
*   �������ܣ���LMSE������֤����Ŀɷ���,����ÿ�ε�����Ȩֵ
******************************************************************/
CString Classification::ifClassified(int Class0,int Class1)
{
	double X[60][26];//��1��Ʒ����
	double Xsharp[26][60];//X�Ĺ淶�����X#
	double w[26];//Ȩֵ����
	double Xw[60];//X*W
	double b[60];//����
	double e[60];//����
	bool flag;
	int c=1;//��������
	CString str;
	CString s;
	CStdioFile cf;//�ļ�
	int i,j;
	
	//��1��Ʒ�����ǰ30��ȡClass0����Ʒ
	for(i=0;i<30;i++)
	{
		for(j=0;j<25;j++)
		{
			X[i][j]=pattern[Class0].feature[i][j];
		}
		X[i][25]=1;//���һλȡ1
	}
	//��1��Ʒ����ĺ�30��ȡClass1����Ʒ��ȡ����
	for(i=30;i<59;i++)
	{
		for(j=0;j<25;j++)
		{
			X[i][j]=-pattern[Class1].feature[i-30][j];
		}
		X[i][25]=-1;
	}
	//��X�Ĺ淶�����X#
	guifanni(X,Xsharp);
	//b����ֵ��b(1)={1,1,1,...,1}
	for(i=0;i<40;i++)
		b[i]=1;
	do
	{
		s.Format("��%d�ε�����										",c);
		str.Insert(str.GetLength(),s);
		brmul(Xsharp,b,w);//w=x#*b
		brmul(X,w,Xw);//x*w
		flag=true;
		for(i=0;i<40;i++)
		{
			e[i]=Xw[i]-b[i];
			flag&=e[i]<0?true:false;//e�ķ����Ƿ�ȫ����
			s.Format("%d,\t",e[i]);
			str.Insert(str.GetLength(),s);
		}
		if(!flag)//e�ķ�������ȫ��������b
		{
			for(i=0;i<40;i++)
				b[i]+=2*e[i];
		}
		if(++c>300) break;//��������300�Σ��˳���
	}while(!flag);
	//�����ļ���lmse.txt��
	if(cf.Open("lmse.txt",CFile::modeCreate|CFile::modeWrite))
	{
		cf.WriteString(str);
		cf.Close();
	}
	return str;	
}


/******************************************************************
*   �������ƣ�Shihanshu()
*   �������ͣ�int 
*   �������ܣ��ƺ������෨ ,������д���ֵ����
******************************************************************/
int Classification::Shihanshu()
{
	int r[10][2000];//ϵ��
	int x[2000][2];//��Ʒ
	double hx[10];//�б���
	int i,j,k,n,c=0;

	for(k=0;k<10;k++)//ѭ��10��
	{
		for(n=0;n<10;n++)//10�����
		{
			for(i=0;i<20;i++)//ÿ��ȡ20����Ʒ
			{
				if(c==0)
				{
					for(j=0;j<10;j++)
						r[j][0]=1;
				}
				else
				{
					for(j=0;j<10;j++)
					{
						double t=0.0;
						for(int l=0;l<c;l++)
							t+=r[j][l]*K(pattern[n].feature[i],pattern[x[l][0]].feature[x[l][1]]);
						hx[j]=t;
					}
					for(j=0;j<10;j++)
					{
						if(j==n)
						{
							if(hx[j]>0)//������ȷ
								r[n][c]=0;
							else//�������
								r[n][c]=1;
						}
						else
						{
							if(hx[j]<0)//������ȷ
								r[n][c]=0;
							else//�������
								r[n][c]=-1;
						}
					}
				}
				x[c][0]=n;
				x[c][1]=i;	
				c++;
			}
		}
	}

	for(j=0;j<10;j++)
	{
		double t=0.0;
		for(int l=0;l<200;l++)
			t+=r[j][l]*K(testsample,pattern[x[l][0]].feature[x[l][1]]);
		hx[j]=t;
	}
	
	double maxval=hx[0];
	int number=0;
	for(n=1;n<10;n++)
	{
		if(hx[n]>maxval)
		{
			maxval=hx[n];
			number=n;
		}
	}
	return number;	
}

/****************************************************************
*   �������ƣ�K(double X[], double Xk[])
*   �������ͣ�double 
*   ����˵����X[], Xk[]:������Ʒ������
*   �������ܣ�����������Ʒ���ƺ��� ,����������Ʒ���ƺ�������ֵ��
****************************************************************/
double Classification::K(double X[], double Xk[])
{
	double d=0.0;
	for(int i=0;i<25;i++)
		d+=(X[i]-Xk[i])*(X[i]-Xk[i]);
	return exp(-d);
}

/****************************************************************
*   �������ƣ�pipei(double s1[], double s2[])
*   �������ͣ�double 
*   ����˵����double s1[], double s2[]:������Ʒ������
*   �������ܣ�����������Ʒ��ƥ��̶� ,����������Ʒ�ĵ�ƥ��̶ȡ�
****************************************************************/
double Classification::pipei(double s1[], double s2[])
{
	double count=0.0;
	for(int i=0;i<25;i++)
	{
		count+=(s1[i]-s2[i])*(s1[i]-s2[i]);
	}
	return count;
}
