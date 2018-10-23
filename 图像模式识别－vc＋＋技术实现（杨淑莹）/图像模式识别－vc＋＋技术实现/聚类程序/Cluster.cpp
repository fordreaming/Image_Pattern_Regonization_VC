// Cluster.cpp: implementation of the CCluster class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "mode.h"
#include "Cluster.h"

#include "math.h"
#include "DlgInfor.h"
#include "DlgMohu.h"
#include "DlgFuzzyDistance.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

const int MAX=1000;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCluster::CCluster()
{
	centernum=0;
	patternnum=0;
	m_pattern=NULL;
	m_center=NULL;

}

CCluster::~CCluster()
{

}
//***********************************************************//
//��������		GetFeature()
//����			void
//����ֵ		void
//��������		���������ݵ�ͼ���š��ָ��ż���ȡ����ֵ��
//				����ֵ��������m_pattern�С�
//************************************************************//	
void CCluster::GetFeature()
{
	////////////////////���¶�����������whx/////////////////////
	
	BYTE * p_temp;
	int stop;
	int i,j;
	int counter;//��¼�໥��������ͨ����ĸ�����
	int present;//��¼��ǰ���ֵ1,2,...,counter.

	height=GetHeight();//ͼ���
	wide=GetWidth();//ͼ���

	stop=0;
	counter=0;
    p_temp=new BYTE[wide*height];//����һ����ʱ�ڴ���
	memset(p_temp,255,wide*height);//�ð�
	
	//�����ҡ����ϵ��±��
	const int T=5;//TΪ��ֵ��RGBֵС�ڸ���ֵ����Ϊ�Ǻڣ�
	for(i=0; i<wide; i++)//���������ð�
		*(m_pData+(height-1)*wide+i)=255;
	for(j=0;j<height;j++)//���������ð�
		*(m_pData+(height-j-1)*wide)=255;
	for( j=1;j<height-1;j++)	// �ӵ�һ�п�ʼ����
	{
		if(stop==1)//�ж���ͨ���Ƿ�̫��
			break;
		for( i=1;i<wide-1;i++)	// �ӵ�һ�п�ʼ����
		{
			if(counter>255)
			{
				AfxMessageBox("��ͨ����Ŀ̫�࣬�������Ʒ����");
				stop=1;
				return;
			}
			if(*(m_pData+(height-j-1)*wide+i)<T)//����ǰ��Ϊ�ڵ�
			{
				if(*(m_pData+(height-j-1+1)*wide+i+1)<T)//����ǰ������ϵ�Ϊ�ڵ�
				{
					*(p_temp+(height-j-1)*wide+i)=*(p_temp+(height-j-1+1)*wide+i+1);//��ǰ����Ӧ�������ϵ���ͬ
					present=*(p_temp+(height-j-1+1)*wide+i+1);//��¼��ǰ��ı��
					
					if(*(m_pData+(height-j-1)*wide+i-1)<T && *(p_temp+(height-j-1)*wide+i-1)!=present)//��ǰ�����ϵ㶼Ϊ���ұ�Ų�ͬ
					{
						int temp=*(p_temp+(height-j-1)*wide+i-1);//��¼��ǰ��ı��
						if (present>temp)//��ǰ���ż�¼�����еĽ�Сֵ
						{
							present=temp;
							temp=*(p_temp+(height-j-1+1)*wide+i+1);
						}
						counter--;//�ϲ���ǰ�����ϱ�ţ����������һ
						for(int m=1;m<=height-1;m++)
							for(int n=1;n<=wide-1;n++)
							{
								if(*(p_temp+(height-m-1)*wide+n)==temp)//���ϴ��Ÿóɽ�С���
								{	
									*(p_temp+(height-m-1)*wide+n)=present;
								}
								else if (*(p_temp+(height-m-1)*wide+n)>temp)//���ϴ����Ժ�����б�ż�һ���Ա��ֱ�ŵ�������
								{
									*(p_temp+(height-m-1)*wide+n)-=1;
								}
							}
					}//end//��ǰ
					if( *(m_pData+(height-j-1+1)*wide+i-1)<T && *(p_temp+(height-j-1+1)*wide+i-1)!=present)//���������ϵ㶼Ϊ���ұ�Ų�ͬ
					{
						counter--;//�ϲ����Ϻ����ϱ�ţ����������һ
						int temp=*(p_temp+(height-j-1+1)*wide+i-1);//��¼���ϵ��ֵ
						if (present<temp)//��ǰ���ż�¼�����еĽ�Сֵ
						{
							temp=present;
							present=*(p_temp+(height-j-1+1)*wide+i-1);
						}

						for(int m=1;m<=height-1;m++)
							for(int n=1;n<=wide-1;n++)
							{
								if(*(p_temp+(height-m-1)*wide+n)==present)//���ϴ��Ÿóɽ�С���
								{	
									*(p_temp+(height-m-1)*wide+n)=temp;
								}
								else if (*(p_temp+(height-m-1)*wide+n)>present)//���ϴ����Ժ�����б�ż�һ���Ա��ֱ�ŵ�������
								{
									*(p_temp+(height-m-1)*wide+n)-=1;
								}
							}
						present=temp;
					}//end//����
				}
				else if(*(m_pData+(height-j-1+1)*wide+i)<T)//��ǰ��ڣ����ϲ�Ϊ�ڣ�����Ϊ��
				{
					*(p_temp+(height-j-1)*wide+i)=*(p_temp+(height-j-1+1)*wide+i);//��ǰ��ţ����ϱ��
					present=*(p_temp+(height-j-1+1)*wide+i);
				}
				else if(*(m_pData+(height-j-1+1)*wide+i-1)<T)//����
				{
					*(p_temp+(height-j-1)*wide+i)=*(p_temp+(height-j-1+1)*wide+i-1);
					present=*(p_temp+(height-j-1+1)*wide+i-1);
				}
				else if(*(m_pData+(height-j-1)*wide+i-1)<T)//��ǰ
				{
					*(p_temp+(height-j-1)*wide+i)=*(p_temp+(height-j-1)*wide+i-1);
					present=*(p_temp+(height-j-1)*wide+i-1);
				}
				else//�����±��
				{				
					++counter;
					present=counter;
					*(p_temp+(height-j-1)*wide+i)=present;
				}
			}//end if
		}// ��
	}//end ��
 // //////////////////////���϶�����������//////////////////////////
				  
					
 //////////////////////���»�ø�����Ʒ����λ�ü����///////////////////
	patternnum=counter;//��Ʒ����

	if (m_pattern!=NULL)
		delete []m_pattern;
	m_pattern=new Pattern[patternnum];				
						  
	for( i=0;i<patternnum;i++) 
	{
		m_pattern[i].index=i+1;
		m_pattern[i].category=0;
		m_pattern[i].lefttop.x=wide;
		m_pattern[i].lefttop.y=height;
		m_pattern[i].rightbottom.x=0;
		m_pattern[i].rightbottom.y=0;
	}

	for(int t=1;t<=patternnum;t++)//��¼ÿ����Ʒ��������ͨ���򣩵����ϡ����µ�����
	{	
		for(int j=1;j<height-1;j++)//��������ͼ��
			for(int i=1;i<wide-1;i++)
			{
				if(*(p_temp+(height-j-1)*wide+i)==t)
				{
					if (m_pattern[t-1].lefttop.x>i)//get the lefttop point
						m_pattern[t-1].lefttop.x=i;
					if (m_pattern[t-1].lefttop.y>j)
						m_pattern[t-1].lefttop.y=j;
					if (m_pattern[t-1].rightbottom.x<i)//get the rightbottom point
						m_pattern[t-1].rightbottom.x=i;
					if (m_pattern[t-1].rightbottom.y<j)
						m_pattern[t-1].rightbottom.y=j;
				}				
			}
	}
	
	delete []p_temp;
	//////////////////////���»��������Ʒ��������m_pattern��//////////////////////////////
	for ( i=0;i<patternnum;i++)//=patternnum
	{
		CalFeature(&m_pattern[i]);//���ú��������i��ģ���ֵ
	}
	
	//////////////////////���ϻ��������Ʒ��������m_pattern��//////////////////////////////

}
/***********************************************************
*��������		CalFeature(CCluster::Pattern *m_pattern)
*����			CCluster::Pattern *m_pattern
*����ֵ	    	void
*��������		������Ʒm_pattern������ֵ������m_pattern��>feature��
*************************************************************/
void CCluster::CalFeature(CCluster::Pattern *m_pattern)
{
	int w,h,count;
	int i,j;

	w=(int)(m_pattern->rightbottom.x-m_pattern->lefttop.x)/N;//����ֵ��ÿ�������Ŀ�
	h=(int)(m_pattern->rightbottom.y-m_pattern->lefttop.y)/N;//����ֵ��ÿ�������ĸ�

	for ( j=0;j<N;j++)//col
	{
		for ( i=0;i<N;i++)//line
		{
			count=0;//ÿ�������ںڵ�ĸ���
            for(int m= height-m_pattern->rightbottom.y+h*j;m<height-m_pattern->rightbottom.y+h*j+h;m++)//col
				for (int n=m_pattern->lefttop.x+i*w; n<m_pattern->lefttop.x+i*w+w; n++)//line
					if (*(m_pData+m*wide+n)==0)
						count++;
			m_pattern->feature[j*N+i]=(double)count/(double)(w*h);
		}
	}
}

/*********************************************************
*��������		CalCenter(CCluster::Center *pcenter)
*����			CCluster::Center *pcenter
*����ֵ		    void
*��������		��������pcenter������ֵ������������Ʒ�ľ�ֵ��������Ʒ����
************************************************************/	
void CCluster::CalCenter(CCluster::Center *pcenter)
{
	double temp[N*N];//��ʱ�洢���ĵ�����ֵ
	int a=0;//��¼������Ԫ�ظ���
	for (int i=0;i<N*N;i++)//�������
		temp[i]=0;
	for (i=0;i<patternnum;i++)
		if (m_pattern[i].category==pcenter->index)//�ۼ�����������Ʒ
		{
			a++;
			for (int j=0;j<N*N;j++)
				temp[j]+=m_pattern[i].feature[j];
		}
	pcenter->patternnum=a;
	for ( i=0;i<N*N;i++)
			if(a!=0)
			{
				pcenter->feature[i]=(double)(temp[i]/(double)a);//ȡ��ֵ
			}
			else
			{
				pcenter->feature[i]=temp[i];
			}

}

/***********************************************************
*��������		GetDistance( CCluster::Pattern pattern1, CCluster::Pattern  pattern2, const int distype)
*����			CCluster::Pattern pattern1   ��Ʒ1
*				CCluster::Pattern pattern2	 ��Ʒ2
*				const int distype	         ����ģʽ  1��ŷ�Ͼ��룻2���н����Ҿ��룻
*													   3�������Ƕ�ֵʱ�ļн����Ҿ��룻4�����ж�ֵ������Tanimoto���
*����ֵ	    	double
*��������		������Ʒ1����Ʒ2��ľ��룬����ģʽ�ɲ���distype����
*************************************************************/
double CCluster::GetDistance( CCluster::Pattern pattern1, CCluster::Pattern  pattern2, const int distype)
{

	double   result;
	result=0;

	if (distype==1)//ŷ�Ͼ���
	{
		for (int i=0; i<N*N; i++)
			result+=(pattern1.feature[i]-pattern2.feature[i])*(pattern1.feature[i]-pattern2.feature[i]);
		return (double)sqrt(result);
	}
	else if (distype==2)//�н�����
	{
		double	a,b1,b2;
		a=0;
		b1=0;
		b2=0;
		for (int i=0; i<N*N; i++)
		{
			a+=pattern1.feature[i]*pattern2.feature[i];
			b1+=pattern1.feature[i]*pattern1.feature[i];
			b2+=pattern2.feature[i]*pattern2.feature[i];
		}
		if (b2*b1!=0)
		result=a/sqrt(b1*b2);
		else 
		{
			return -1;
		}

		return (1-result);
	}
	else if (distype==3)//��ֵ�н�����
	{
		int *t1,*t2;
		int a,b1,b2;
		 
		a=0;b1=0;b2=0;
		t1=new int [N*N];
		t2=new int [N*N];
		for(int i=0; i<N*N; i++)
		{
			t1[i]=pattern1.feature[i]>0.2? 1:0;
			t2[i]=pattern2.feature[i]>0.2? 1:0;
		}
		
		for ( i=0; i<N*N; i++)
		{
			a+=t1[i]*t2[i];
			b1+=t1[i]*t1[i];
			b2+=t2[i]*t2[i];
		}
		delete	[]t1;
		delete	[]t2;
		if (b2*b1!=0)
		result=(double)(a/sqrt(b1*b2));
		else 
		{
			return -1;
		}

		return (1-result);
	}
	else if (distype==4)//Tanimoto
	{
		int *t1,*t2;
		int a,b1,b2;
		 
		a=0;b1=0;b2=0;
		t1=new int [N*N];
		t2=new int [N*N];
		for(int i=0; i<N*N; i++)
		{
			t1[i]=pattern1.feature[i]>0.2? 1:0;
			t2[i]=pattern2.feature[i]>0.2? 1:0;
		}
		
		for ( i=0; i<N*N; i++)
		{
			a+=t1[i]*t2[i];
			b1+=t1[i]*t1[i];
			b2+=t2[i]*t2[i];
		}
		delete	[]t1;
		delete	[]t2;
		if ((b2*b1-a)!=0)
		result=(double)(a/(b1+b2-a));
		else 
		{
			return -1;
		}
		return (1-result);
	}
	else
		return -1;

}
/***************************************************************
*��������		GetDistance(CCluster::Pattern pattern,  CCluster::Center center, const int distype)
*����			CCluster::Pattern pattern  ��Ʒ
*				CCluster::Center center    ����
*				const int distype	         ����ģʽ  1��ŷ�Ͼ��룻2���н����Ҿ��룻
*													   3�������Ƕ�ֵʱ�ļн����Ҿ��룻
*													   4�����ж�ֵ������Tanimoto���
*����ֵ			double
*��������		������Ʒ�;������ļ�ľ��룬����ģʽ��distype����
************************************************************/
double CCluster::GetDistance(CCluster::Pattern pattern,  CCluster::Center center, const int distype)
{
	double   result;
	result=0;

	if (distype==1)//ŷ�Ͼ���
	{
		for (int i=0; i<N*N; i++)
			result+=(pattern.feature[i]-center.feature[i])*(pattern.feature[i]-center.feature[i]);
		return (double)sqrt(result);
	}
	else if (distype==2)//�н�����
	{
		double	a,b1,b2;
		a=0;
		b1=0;
		b2=0;
		for (int i=0; i<N*N; i++)
		{
			a+=pattern.feature[i]*center.feature[i];
			b1+=pattern.feature[i]*pattern.feature[i];
			b2+=center.feature[i]*center.feature[i];
		}
		if (b2*b1!=0)
		result=a/sqrt(b1*b2);
		else 
		{
			return -1;
		}

		return (1-result);
	}
	else if (distype==3)//��ֵ�н�����
	{
		int *t1,*t2;
		int a,b1,b2;
		 
		a=0;b1=0;b2=0;
		t1=new int [N*N];
		t2=new int [N*N];
		for(int i=0; i<N*N; i++)
		{
			t1[i]=pattern.feature[i]>0.2? 1:0;
			t2[i]=center.feature[i]>0.2? 1:0;
		}
		
		for ( i=0; i<N*N; i++)
		{
			a+=t1[i]*t2[i];
			b1+=t1[i]*t1[i];
			b2+=t2[i]*t2[i];
		}
		delete	[]t1;
		delete	[]t2;
		if (b2*b1!=0)
		result=a/sqrt(b1*b2);
		else 
		{
			return -1;
		}

		return (1-result);
	}
	else if (distype==4)//Tanimoto
	{
		int *t1,*t2;
		int a,b1,b2;
		 
		a=0;b1=0;b2=0;
		t1=new int [N*N];
		t2=new int [N*N];
		for(int i=0; i<N*N; i++)
		{
			t1[i]=pattern.feature[i]>0.2? 1:0;
			t2[i]=center.feature[i]>0.2? 1:0;
		}
		
		for ( i=0; i<N*N; i++)
		{
			a+=t1[i]*t2[i];
			b1+=t1[i]*t1[i];
			b2+=t2[i]*t2[i];
		}
		delete	[]t1;
		delete	[]t2;
		if ((b2*b1-a)!=0)
		result=(double)(a/(b1+b2-a));
		else 
		{
			return -1;
		}
		return (1-result);
	}
	else
		return -1;
}
/*************************************************************
*��������		GetDistance(CCluster::Center mCenter1,CCluster::Center mCenter2,int distype)
*����			CCluster::Center mCenter1   ����1
*				CCluster::Center mCenter2   ����2
*				const int distype	         ����ģʽ   1��ŷ�Ͼ��룻2���н����Ҿ��룻		
*											            3�������Ƕ�ֵʱ�ļн����Ҿ��룻
*														4�����ж�ֵ������Tanimoto���
*����ֵ			double
*��������		���������������ļ�ľ��룬����ģʽ��distype����
*************************************************************/
double CCluster::GetDistance(CCluster::Center mCenter1,CCluster::Center mCenter2,int distype)
{
	double result;
	result=0;

	if (distype==1)//ŷ�Ͼ���
	{
		for ( int m=0;m<N*N;m++)
		result+=(mCenter1.feature[m]-mCenter2.feature[m])*(mCenter1.feature[m]-mCenter2.feature[m]);
		return (double)sqrt(result);
	}
	else if (distype==2)//�н�����
	{
		double	a,b1,b2;
		a=0;
		b1=0;
		b2=0;
		for (int i=0; i<N*N; i++)
		{
			a+=mCenter1.feature[i]*mCenter2.feature[i];
			b1+=mCenter1.feature[i]*mCenter1.feature[i];
			b2+=mCenter2.feature[i]*mCenter2.feature[i];
		}
		if (b2*b1!=0)
		result=a/sqrt(b1*b2);
		else 
		{
			return -1;
		}

		return (1-result);
	}
	else if (distype==3)//��ֵ�н�����
	{
		int *t1,*t2;
		int a,b1,b2;
		 
		a=0;b1=0;b2=0;
		t1=new int [N*N];
		t2=new int [N*N];
		for(int i=0; i<N*N; i++)
		{
			t1[i]=mCenter1.feature[i]>0.2? 1:0;
			t2[i]=mCenter2.feature[i]>0.2? 1:0;
		}
		
		for ( i=0; i<N*N; i++)
		{
			a+=t1[i]*t2[i];
			b1+=t1[i]*t1[i];
			b2+=t2[i]*t2[i];
		}
		delete	[]t1;
		delete	[]t2;
		if (b2*b1!=0)
		result=(double)(a/sqrt(b1*b2));
		else 
		{
			return -1;
		}

		return (1-result);
	}
	else if (distype==4)//Tanimoto
	{
		int *t1,*t2;
		int a,b1,b2;
		 
		a=0;b1=0;b2=0;
		t1=new int [N*N];
		t2=new int [N*N];
		for(int i=0; i<N*N; i++)
		{
			t1[i]=mCenter1.feature[i]>0.2? 1:0;
			t2[i]=mCenter2.feature[i]>0.2? 1:0;
		}
		
		for ( i=0; i<N*N; i++)
		{
			a+=t1[i]*t2[i];
			b1+=t1[i]*t1[i];
			b2+=t2[i]*t2[i];
		}
		delete	[]t1;
		delete	[]t2;
		if ((b2*b1-a)!=0)
		result=(double)(a/(b1+b2-a));
		else 
		{
			return -1;
		}
		return (1-result);
	}
	else
		return -1;	
}

/************************************************************
*��������		GetDistance(double *dis, int i, int j)
*����			double *dis    ָ��ģ�����������ָ���СΪ[patternnum*patternnum]
*				int i			����ĵ�i��
*				int j			����ĵ�j��
*����ֵ		    double
*��������		����ģ�����������е�i�е�j�е�ģ����
*************************************************************/
double CCluster::GetDistance(double *dis, int i, int j)
{
	double result;
	result=0;

	for(int t=0;t<patternnum;t++)
	{
		double td=dis[i*patternnum+t]<dis[t*patternnum+j]? dis[i*patternnum+t]:dis[t*patternnum+j];
		if (result<td)
			result=td;
	}
	return result;
}
/************************************************************
*��������		GetFuzzyDistance(CCluster::Pattern pattern1,CCluster::Pattern pattenr2, int distype)
*����			CCluster::Pattern pattern1    ��Ʒ1
*				CCluster::Pattern pattern2    ��Ʒ2
*				int distype					  ���������ʽ��1��ŷ�Ͼ��룻2����������
*															3�����ϵ��
*															4�������С����5������ƽ����; 
*															6,����ƽ����С��
*����ֵ         double
*����			����������Ʒ��ģ�����룬����ģʽ�ɲ���distype����
************************************************************/
double CCluster::GetFuzzyDistance(CCluster::Pattern pattern1,CCluster::Pattern pattern2, int distype)
{
	switch	(distype)
	{
	case 1://ŷ�Ͼ���
		{
				double max=0;
				for (int i=0; i<patternnum-1; i++)
					for (int j=i+1; j<patternnum; j++)
						if (max<GetDistance(m_pattern[i],m_pattern[j],1))
							max=GetDistance(m_pattern[i],m_pattern[j],1);
				return (max-GetDistance(pattern1,pattern2,1))/max;
		}
	case 2://������
		{
			double temp,max;
			max=0;
			for (int i=0; i<patternnum-1; i++)
				for (int j=0; j<patternnum; j++)
				{
					temp=0;
					for (int k=0; k<N*N; k++)
					{
						temp+=m_pattern[i].feature[k]*m_pattern[j].feature[k];
					}
					if (max<temp)
						max=temp;
				}
			temp=0;
			for ( i=0; i<N*N; i++)
			{
				temp+=pattern1.feature[i]*pattern2.feature[i];
			}
			return (temp/max);
		}
	case 3://���ϵ��
		{
			double ap1,ap2;
			ap1=0;ap2=0;
			for (int i=0; i<N*N; i++)
			{
				ap1+=pattern1.feature[i];
				ap2+=pattern2.feature[i];
			}
			ap1/=N; 
			ap1/=N;

			double a,b1,b2;
			a=0;b1=0;b2=0;

			for (i=0; i<N*N; i++)
			{
				a+=(pattern1.feature[i]-ap1)*(pattern2.feature[i]-ap2);
				b1+=(pattern1.feature[i]-ap1)*(pattern1.feature[i]-ap1);
				b2+=(pattern2.feature[i]-ap2)*(pattern2.feature[i]-ap2);
			}
			if (b2*b1!=0)
				return (a/sqrt(b1*b2));
		}
	case 4://�����С��
		{
			double min ,max;
			min=0; max=0;
			for (int i=0; i<N*N; i++)
			{
				min+=pattern1.feature[i]<pattern2.feature[i]? pattern1.feature[i]:pattern2.feature[i];
				max+=pattern1.feature[i]<pattern2.feature[i]? pattern2.feature[i]:pattern1.feature[i];
			}
			if (max!=0)
			return (min/max);
		}
	case 5://����ƽ����
		{
			double min ,max;
			min=0; max=0;
			for (int i=0; i<N*N; i++)
			{
				min+=pattern1.feature[i]<pattern2.feature[i]? pattern1.feature[i]:pattern2.feature[i];
				max+=pattern1.feature[i]+pattern2.feature[i];
			}
			if (max!=0)
			return (2*min/max);	
		}
	case 6://����ƽ����С��
		{
			double min ,max;
			min=0; max=0;
			for (int i=0; i<N*N; i++)
			{
				min+=pattern1.feature[i]<pattern2.feature[i]? pattern1.feature[i]:pattern2.feature[i];
				max+=sqrt(pattern1.feature[i]*pattern2.feature[i]);
			}
			if (max!=0)
			return (min/max);			
		}
	default:
		return -1;
	}
}

/************************************************************
*��������		Zuilinjinguize()
*����			void
*����ֵ		    void
*��������		�������ٽ������ȫ����Ʒ���з���
************************************************************/
void CCluster::Zuilinjinguize()//���ٽ�����
{
	GetFeature();

	double  T;//��ֵ
	int		distype;//����ģʽ��ŷ�ϡ����ҡ�������
	int     i,j;

///////////////�����ֵ�ο�ֵ/////////////////////
	double minous,maxous,mincos,maxcos,minbcos,maxbcos,mintan,maxtan;

	minous=MAX; mincos=MAX; minbcos=MAX; mintan=MAX;
	maxous=0; maxcos=0; maxbcos=0; maxtan=0;

	for (  i=0;i<patternnum-1;i++)//�������־���ģʽ�Ĳο�ֵ
		for ( j=i+1;j<patternnum;j++)
		{
			if (minous>GetDistance(m_pattern[i],m_pattern[j],1))
				minous=GetDistance(m_pattern[i],m_pattern[j],1);
			if (maxous<GetDistance(m_pattern[i],m_pattern[j],1))
				maxous=GetDistance(m_pattern[i],m_pattern[j],1);

			if (mincos>GetDistance(m_pattern[i],m_pattern[j],2))
				mincos=GetDistance(m_pattern[i],m_pattern[j],2);
			if (maxcos<GetDistance(m_pattern[i],m_pattern[j],2))
				maxcos=GetDistance(m_pattern[i],m_pattern[j],2);

			if (minbcos>GetDistance(m_pattern[i],m_pattern[j],3))
				minbcos=GetDistance(m_pattern[i],m_pattern[j],3);
			if (maxbcos<GetDistance(m_pattern[i],m_pattern[j],3))
				maxbcos=GetDistance(m_pattern[i],m_pattern[j],3);
			
			if (mintan>GetDistance(m_pattern[i],m_pattern[j],4))
				mintan=GetDistance(m_pattern[i],m_pattern[j],4);
			if (maxtan<GetDistance(m_pattern[i],m_pattern[j],4))
				maxtan=GetDistance(m_pattern[i],m_pattern[j],4);
		}
	DlgInfor mDlgInfor;
	mDlgInfor.ShowInfor(minous,maxous,mincos,maxcos,minbcos,maxbcos,mintan,maxtan);

////////////////////////������ֵ�;�����ʽ///////////////
	if (mDlgInfor.DoModal()==IDOK)
	{
		T=mDlgInfor.m_T;
		distype=mDlgInfor.m_DisType;
	}
	else return;
	centernum=1;
	m_center=new Center[patternnum];

    //����һ����Ʒ��Ϊ��һ������
	for ( i=0;i<N*N;i++)
		m_center[0].feature[i]=m_pattern[0].feature[i];
	m_center[0].index=1;
	m_center[0].patternnum=1;
	m_pattern[0].category=1;

	for ( i=1;i<patternnum;i++)//������ģ����й���
	{
		double centerdistance=MAX;
		int index=1;
		//�ҵ��������������index����¼��С����centerdistance
		for (int j=0;j<centernum;j++)
		{	
			double dis= GetDistance(m_pattern[i],m_center[j],distype);
			if (dis<centerdistance)
			{
				centerdistance=dis;
				index=j;
			}
		}

		if (centerdistance<T)//����С����ֵ����Ʒ�������
		{
			m_pattern[i].category=m_center[index].index;
			CalCenter(&m_center[j]);
		}
		else //�½���������
		{
			centernum++;
			m_pattern[i].category=centernum;
			for (int m=0;m<N*N;m++)
				m_center[centernum-1].feature[m]=m_pattern[i].feature[m];
			m_center[centernum-1].index=centernum;
		}
	}//end of all pattern
	delete []m_center;
}


/************************************************************
*��������		Zuidazuixiaojulifa()
*����			void
*����ֵ		void
*��������		���������С��������ȫ����Ʒ���з���
************************************************************/
void CCluster::Zuidazuixiaojulifa()
{
	GetFeature();

	int	distype;//�������ʽ��ŷ�ϡ����ҡ�������
	int i,j;

	DlgInfor mDlgInfor;
	mDlgInfor.ShowInfor(1);
	if (mDlgInfor.DoModal()==IDOK)
	{
		distype=mDlgInfor.m_DisType;
	}
	else return;
	
	double maxdistance=0;//��¼�����������룬������ָ���ֵ

	int index=1;//��¼�����һ��������Զ����Ʒ

	m_center=new Center[patternnum];

	for ( i=0;i<N*N;i++)//��һ����������
		m_center[0].feature[i]=m_pattern[0].feature[i];
	m_center[0].index=1;
	m_pattern[0].category=1;

	for( i=1;i<patternnum;i++)//�ڶ�����������
		if (maxdistance<GetDistance(m_pattern[i],m_center[0],distype))
		{
			maxdistance=GetDistance(m_pattern[i],m_center[0],distype);
			index=i;
		}
	for ( i=0;i<N*N;i++)//�ڶ�����������
		m_center[1].feature[i]=m_pattern[index].feature[i];
	
	m_center[1].index=2;
	m_pattern[index].category=2;

	centernum=2;

	for ( i=1;i<patternnum;i++)//������ģ�����
	{
		
		double tdistance=MAX;
		index=0;//��¼��Ʒ�������������
		for ( j=0;j<centernum;j++)//2
			if (tdistance>GetDistance(m_pattern[i],m_center[j],distype))
			{
				tdistance=GetDistance(m_pattern[i],m_center[j],distype);
				index=j;
			}

		if (tdistance>maxdistance/2)//��Ʒ������еľ��������ֵ�������µľ�������
		{
				++centernum;
				for (int m=0;m<N*N;m++)
					m_center[centernum-1].feature[m]=m_pattern[i].feature[m];
				m_center[centernum-1].index=centernum;
				m_pattern[i].category=centernum;
		}
		else//����index����
		{
			m_pattern[i].category=m_center[index].index;
			CalCenter(&m_center[index]);
		}
			
	}
	delete []m_center;

}
/************************************************************
*��������		Zuiduanjulifa()
*����			void
*����ֵ 		void
*��������		������̾��뷨��ȫ����Ʒ���з���
************************************************************/
void CCluster::Zuiduanjulifa()//��̾��뷨
{
	GetFeature();

	double  T;//��ֵ
	int		distype;//�������ʽ��ŷ�ϡ����ҡ�������
	int     i,j;

	double minous,maxous,mincos,maxcos,minbcos,maxbcos,mintan,maxtan;

	minous=MAX; mincos=MAX; minbcos=MAX; mintan=MAX;
	maxous=0; maxcos=0; maxbcos=0; maxtan=0;
	//�������־���ģʽ�Ĳο�ֵ
	for (  i=0;i<patternnum-1;i++)
		for ( j=i+1;j<patternnum;j++)
		{
			if (minous>GetDistance(m_pattern[i],m_pattern[j],1))
				minous=GetDistance(m_pattern[i],m_pattern[j],1);
			if (maxous<GetDistance(m_pattern[i],m_pattern[j],1))
				maxous=GetDistance(m_pattern[i],m_pattern[j],1);

			if (mincos>GetDistance(m_pattern[i],m_pattern[j],2))
				mincos=GetDistance(m_pattern[i],m_pattern[j],2);
			if (maxcos<GetDistance(m_pattern[i],m_pattern[j],2))
				maxcos=GetDistance(m_pattern[i],m_pattern[j],2);

			if (minbcos>GetDistance(m_pattern[i],m_pattern[j],3))
				minbcos=GetDistance(m_pattern[i],m_pattern[j],3);
			if (maxbcos<GetDistance(m_pattern[i],m_pattern[j],3))
				maxbcos=GetDistance(m_pattern[i],m_pattern[j],3);
			
			if (mintan>GetDistance(m_pattern[i],m_pattern[j],4))
				mintan=GetDistance(m_pattern[i],m_pattern[j],4);
			if (maxtan<GetDistance(m_pattern[i],m_pattern[j],4))
				maxtan=GetDistance(m_pattern[i],m_pattern[j],4);
		}
	DlgInfor mDlgInfor;
	mDlgInfor.ShowInfor(minous,maxous,mincos,maxcos,minbcos,maxbcos,mintan,maxtan);

	if (mDlgInfor.DoModal()==IDOK)
	{
		T=mDlgInfor.m_T;
		distype=mDlgInfor.m_DisType;
	}
	else return;

    //��ʼ����������Ʒ����һ�� 
	centernum=patternnum;
	m_center=new Center[centernum];
	for ( i=0;i<patternnum;i++)
	{
		m_pattern[i].category=i+1;

		for (j=0;j<N*N;j++)
			m_center[i].feature[j]=m_pattern[i].feature[j];
		m_center[i].index=i+1;
	}

	while (1)
	{
		int pi,pj;
		double mindis;

		pi=0;
		pj=0;
		mindis=MAX;
		//Ѱ�Ҿ������������pi��pj����¼��С����mindis
		for ( i=0;i<patternnum-1;i++)
			for ( j=i+1;j<patternnum;j++)
				if (m_pattern[i].category!=m_pattern[j].category)
					if (GetDistance(m_pattern[i],m_pattern[j],distype)<mindis)
					{
						mindis=GetDistance(m_pattern[i],m_pattern[j],distype);
						pi=i;
						pj=j;
					};
		if (mindis<=T)//����С����ֵ���ϲ�pi��pj��
		{
			if (pi>pj)//���ϴ���Ź����С���
			{
				int temp=pi;
				pi=pj;
				pj=temp;
			}
			int tcenter=m_pattern[pj].category;
			for ( i=0;i<patternnum;i++)
			{
				if (m_pattern[i].category==tcenter)
					m_pattern[i].category=m_pattern[pi].category;
				if (m_pattern[i].category>tcenter)//������ŵ�������
					m_pattern[i].category--;
			}
		}
		else break;//��С���������ֵ���˳�ѭ��
	}
	delete []m_center;

}
/************************************************************
*��������		Zuichangjulifa()
*����			void
*����ֵ		    void
*��������		��������뷨��ȫ����Ʒ���з���
************************************************************/
void CCluster::Zuichangjulifa()//����뷨
{
	GetFeature();

	double  T;//��ֵ
	int		distype;//�������ʽ��ŷ�ϡ����ҡ�������
	int     i,j;

	double minous,maxous,mincos,maxcos,minbcos,maxbcos,mintan,maxtan;

	minous=MAX; mincos=MAX; minbcos=MAX; mintan=MAX;
	maxous=0; maxcos=0; maxbcos=0; maxtan=0;
	//�������־���ģʽ�Ĳο�ֵ
	for (  i=0;i<patternnum-1;i++)
		for ( j=i+1;j<patternnum;j++)
		{
			if (minous>GetDistance(m_pattern[i],m_pattern[j],1))
				minous=GetDistance(m_pattern[i],m_pattern[j],1);
			if (maxous<GetDistance(m_pattern[i],m_pattern[j],1))
				maxous=GetDistance(m_pattern[i],m_pattern[j],1);

			if (mincos>GetDistance(m_pattern[i],m_pattern[j],2))
				mincos=GetDistance(m_pattern[i],m_pattern[j],2);
			if (maxcos<GetDistance(m_pattern[i],m_pattern[j],2))
				maxcos=GetDistance(m_pattern[i],m_pattern[j],2);

			if (minbcos>GetDistance(m_pattern[i],m_pattern[j],3))
				minbcos=GetDistance(m_pattern[i],m_pattern[j],3);
			if (maxbcos<GetDistance(m_pattern[i],m_pattern[j],3))
				maxbcos=GetDistance(m_pattern[i],m_pattern[j],3);
			
			if (mintan>GetDistance(m_pattern[i],m_pattern[j],4))
				mintan=GetDistance(m_pattern[i],m_pattern[j],4);
			if (maxtan<GetDistance(m_pattern[i],m_pattern[j],4))
				maxtan=GetDistance(m_pattern[i],m_pattern[j],4);
		}
	DlgInfor mDlgInfor;
	mDlgInfor.ShowInfor(minous,maxous,mincos,maxcos,minbcos,maxbcos,mintan,maxtan);

	if (mDlgInfor.DoModal()==IDOK)
	{
		T=mDlgInfor.m_T;
		distype=mDlgInfor.m_DisType;
	}
	else return;

    //��ʼ����������Ʒ����һ��
	for ( i=0;i<patternnum;i++)
	{
		m_pattern[i].category=i+1;
	}
 
	centernum=patternnum;

	while (1)
	{
		int pi,pj;
		double mindis,maxdis;

		pi=0;
		pj=0;
		mindis=MAX;
        //�������������룬�ҳ���������������С��Ϊmindis����¼���pi��pj
		for ( i=1;i<=centernum-1;i++)
			for ( j=i+1;j<=centernum;j++)
			{
   				maxdis=-1;
				for (int m=0;m<patternnum-1;m++)
					for (int n=m+1;n<patternnum;n++)
					{
						if ((m_pattern[m].category==i)&&(m_pattern[n].category==j)||((m_pattern[m].category==j)&&(m_pattern[n].category==i)))
							if (GetDistance(m_pattern[m],m_pattern[n],distype)>maxdis)
							{
								maxdis=GetDistance(m_pattern[m],m_pattern[n],distype);
							}
					}
				if ((maxdis<mindis)&&(maxdis!=-1))
				{
					mindis=maxdis;
					pi=i;
					pj=j;
				}
			}
		if (mindis<T)//����С����ֵ���ϲ�pi��pj��
		{
			int tcenter=pj;
			for ( i=0;i<patternnum;i++)
			{
				if (m_pattern[i].category==tcenter)
					m_pattern[i].category=pi;
				if (m_pattern[i].category>tcenter)//����Ʒ���򣬱�����ŵ�������
					m_pattern[i].category--;
			}
			centernum--;
		}
		else break;//�˳�ѭ��
	}

}
/************************************************************
*��������		Zhongjianjulifa()
*����			void
*����ֵ		    void
*��������		�����м���뷨��ȫ����Ʒ���з���
*************************************************************/
void CCluster::Zhongjianjulifa()
{
	GetFeature();
	
	double	**centerdistance;//��¼������
	double  T;//��ֵ
	int		distype;//�������ʽ��ŷ�ϡ����ҡ�������
	int     i,j;

	double minous,maxous,mincos,maxcos,minbcos,maxbcos,mintan,maxtan;

	minous=MAX; mincos=MAX; minbcos=MAX; mintan=MAX;
	maxous=0; maxcos=0; maxbcos=0; maxtan=0;
	//�������־���ģʽ�Ĳο�ֵ
	for (  i=0;i<patternnum-1;i++)
		for ( j=i+1;j<patternnum;j++)
		{
			if (minous>GetDistance(m_pattern[i],m_pattern[j],1))
				minous=GetDistance(m_pattern[i],m_pattern[j],1);
			if (maxous<GetDistance(m_pattern[i],m_pattern[j],1))
				maxous=GetDistance(m_pattern[i],m_pattern[j],1);

			if (mincos>GetDistance(m_pattern[i],m_pattern[j],2))
				mincos=GetDistance(m_pattern[i],m_pattern[j],2);
			if (maxcos<GetDistance(m_pattern[i],m_pattern[j],2))
				maxcos=GetDistance(m_pattern[i],m_pattern[j],2);

			if (minbcos>GetDistance(m_pattern[i],m_pattern[j],3))
				minbcos=GetDistance(m_pattern[i],m_pattern[j],3);
			if (maxbcos<GetDistance(m_pattern[i],m_pattern[j],3))
				maxbcos=GetDistance(m_pattern[i],m_pattern[j],3);
			
			if (mintan>GetDistance(m_pattern[i],m_pattern[j],4))
				mintan=GetDistance(m_pattern[i],m_pattern[j],4);
			if (maxtan<GetDistance(m_pattern[i],m_pattern[j],4))
				maxtan=GetDistance(m_pattern[i],m_pattern[j],4);
		}
	DlgInfor mDlgInfor;
	mDlgInfor.ShowInfor(minous,maxous,mincos,maxcos,minbcos,maxbcos,mintan,maxtan);

	if (mDlgInfor.DoModal()==IDOK)
	{
		T=mDlgInfor.m_T;
		distype=mDlgInfor.m_DisType;
	}
	else return;

    //��ʼ��
	for ( i=0;i<patternnum;i++)//ÿ����Ʒ�Գ�һ��
	{
		m_pattern[i].category=i+1;
	}

	centerdistance=new double *[patternnum];//�������������飬centerdistance[i][j]��ʾi���j�����
	for ( i=1;i<patternnum;i++)
	{
		centerdistance[i]=new double [patternnum+1];
	}

	for ( i=1;i<patternnum;i++)
		for (int j=i+1;j<=patternnum;j++)
		{
			centerdistance[i][j]=GetDistance(m_pattern[i-1],m_pattern[j-1],distype);
		}

	centernum=patternnum;
	
	while(1)
	{
		double td,**tempdistance;
		int ti,tj;
		td=MAX;
		ti=0;
		tj=0;

		tempdistance= new double *[patternnum];//��ʱ��¼������
		for (i=1;i<patternnum;i++)
		{
			tempdistance[i]=new double[patternnum+1];
		}

		for( i=1;i<centernum;i++)//�ҵ��������������:ti,tj,��¼��С����td;
			for ( j=i+1;j<=centernum;j++)
			{
				if (td>centerdistance[i][j])	
				{
					td=centerdistance[i][j];
					ti=i;tj=j;
				}
			}

		if(td<T)//�ϲ���i,j
		{
			for ( i=0;i<patternnum;i++)
			{
				if (m_pattern[i].category==tj)
					m_pattern[i].category=ti;
				if (m_pattern[i].category>tj)
					m_pattern[i].category--;
			}
			centernum--;

			for (i=1;i<centernum;i++)//���¼���ϲ�����ൽ����������¾���
				for ( j=i+1;j<=centernum;j++)
				{
					if (i<ti)
					{
						if(j==ti)
							tempdistance[i][j]=sqrt (centerdistance[i][ti]*centerdistance[i][ti]/2+centerdistance[i][tj]*centerdistance[i][tj]/2-centerdistance[ti][tj]*centerdistance[ti][tj]/4);
						else if (j>=tj)
							tempdistance[i][j]=centerdistance[i][j+1];
						else
							tempdistance[i][j]=centerdistance[i][j];
					
					}
					else if (i==ti)
					{
						if (j<tj)
							tempdistance[i][j]=sqrt (centerdistance[ti][j]*centerdistance[ti][j]/2+centerdistance[j][tj]*centerdistance[j][tj]/2-centerdistance[ti][tj]*centerdistance[ti][tj]/4);
                        else
							tempdistance[i][j]=sqrt (centerdistance[ti][j+1]*centerdistance[ti][j+1]/2+centerdistance[tj][j+1]*centerdistance[tj][j+1]/2-centerdistance[ti][tj]*centerdistance[ti][tj]/4);
					}
					else if((i>ti)&&(i<tj))
					{
						if(j<tj)
							tempdistance[i][j]=centerdistance[i][j];
						else
							tempdistance[i][j]=centerdistance[i][j+1];
					}
					else //i>=tj
					{
						tempdistance[i][j]=centerdistance[i+1][j+1];
					}
				}
			for (i=1;i<centernum;i++)
				for ( j=i+1;j<=centernum;j++)
				{
					centerdistance[i][j]=tempdistance[i][j];
				}

		}
		else break;
		delete []tempdistance;
	}
	delete []centerdistance;

}
/************************************************************
*��������		Zhongxinfa()
*����			void
*����ֵ  		void
*��������		�������ķ���ȫ����Ʒ���з���
************************************************************/
void CCluster::Zhongxinfa()
{
	GetFeature();
	
	double	**centerdistance;//��¼������
	double  T;//��ֵ
	int		distype;//�������ʽ��ŷ�ϡ����ҡ�������
	int     i,j;
	double minous,maxous,mincos,maxcos,minbcos,maxbcos,mintan,maxtan;

	minous=MAX; mincos=MAX; minbcos=MAX; mintan=MAX;
	maxous=0; maxcos=0; maxbcos=0; maxtan=0;
	//�������־���ģʽ�Ĳο�ֵ
	for (  i=0;i<patternnum-1;i++)
		for ( j=i+1;j<patternnum;j++)
		{
			if (minous>GetDistance(m_pattern[i],m_pattern[j],1))
				minous=GetDistance(m_pattern[i],m_pattern[j],1);
			if (maxous<GetDistance(m_pattern[i],m_pattern[j],1))
				maxous=GetDistance(m_pattern[i],m_pattern[j],1);

			if (mincos>GetDistance(m_pattern[i],m_pattern[j],2))
				mincos=GetDistance(m_pattern[i],m_pattern[j],2);
			if (maxcos<GetDistance(m_pattern[i],m_pattern[j],2))
				maxcos=GetDistance(m_pattern[i],m_pattern[j],2);

			if (minbcos>GetDistance(m_pattern[i],m_pattern[j],3))
				minbcos=GetDistance(m_pattern[i],m_pattern[j],3);
			if (maxbcos<GetDistance(m_pattern[i],m_pattern[j],3))
				maxbcos=GetDistance(m_pattern[i],m_pattern[j],3);
			
			if (mintan>GetDistance(m_pattern[i],m_pattern[j],4))
				mintan=GetDistance(m_pattern[i],m_pattern[j],4);
			if (maxtan<GetDistance(m_pattern[i],m_pattern[j],4))
				maxtan=GetDistance(m_pattern[i],m_pattern[j],4);
		}
	DlgInfor mDlgInfor;
	mDlgInfor.ShowInfor(minous,maxous,mincos,maxcos,minbcos,maxbcos,mintan,maxtan);

	if (mDlgInfor.DoModal()==IDOK)
	{
		T=mDlgInfor.m_T;
		distype=mDlgInfor.m_DisType;
	}
	else return;

    //��ʼ��
	for ( i=0;i<patternnum;i++)//ÿ����Ʒ�Գ�һ��
	{
		m_pattern[i].category=i+1;
	}

	centerdistance=new double *[patternnum];//�������������飬centerdistance[i][j]��ʾi���j�����
	for ( i=1;i<patternnum;i++)
	{
		centerdistance[i]=new double [patternnum+1];
	}

	for ( i=1;i<patternnum;i++)
		for (int j=i+1;j<=patternnum;j++)
		{
			centerdistance[i][j]=GetDistance(m_pattern[i-1],m_pattern[j-1],distype);
		}

	centernum=patternnum;
	
	
    while(1)
	{
		double td,**tempdistance;
		int ti,tj;//������С����
		int numi,numj;//i,j���е�Ԫ�ظ���

		td=MAX;
		ti=0;
		tj=0;
		numi=0;
		numj=0;
		tempdistance= new double *[patternnum];//��ʱ��¼������
		for (i=1;i<patternnum;i++)
		{
			tempdistance[i]=new double[patternnum+1];
		}

		for( i=1;i<centernum;i++)//�ҵ��������������:ti,tj,��¼��С����td;
			for ( j=i+1;j<=centernum;j++)
			{
				if (td>centerdistance[i][j])	
				{
					td=centerdistance[i][j];
					ti=i;tj=j;
				}
			}

		if(td<T)//��С����С����ֵ���ϲ���i,j
		{
			for (int i=0;i<patternnum;i++)
			{
				if (m_pattern[i].category==ti)
					numi++;
				if (m_pattern[i].category==tj)
				{
					m_pattern[i].category=ti;
					numj++;
				}
				if (m_pattern[i].category>tj)
					m_pattern[i].category--;
			}
			centernum--;
			//���¼��������룬������ŵ�������
			for (i=1;i<centernum;i++)
				for (int j=i+1;j<=centernum;j++)
				{
					if (i<ti)
					{
						if(j==ti)
							tempdistance[i][j]=sqrt (centerdistance[i][ti]*centerdistance[i][ti]*numi/(numi+numj)+centerdistance[i][tj]*centerdistance[i][tj]*numj/(numi+numj)-centerdistance[ti][tj]*centerdistance[ti][tj]*numi*numj/(numi+numj));
						else if (j>=tj)
							tempdistance[i][j]=centerdistance[i][j+1];
						else
							tempdistance[i][j]=centerdistance[i][j];
					
					}
					else if (i==ti)
					{
						if (j<tj)
							tempdistance[i][j]=sqrt (centerdistance[ti][j]*centerdistance[ti][j]*numi/(numi+numj)+centerdistance[j][tj]*centerdistance[j][tj]*numj/(numi+numj)-centerdistance[ti][tj]*centerdistance[ti][tj]*numi*numj/(numi+numj));
                        else
							tempdistance[i][j]=sqrt (centerdistance[ti][j+1]*centerdistance[ti][j+1]*numi/(numi+numj)+centerdistance[tj][j+1]*centerdistance[tj][j+1]*numj/(numi+numj)-centerdistance[ti][tj]*centerdistance[ti][tj]*numi*numj/(numi+numj));
					}
					else if((i>ti)&&(i<tj))
					{
						if(j<tj)
							tempdistance[i][j]=centerdistance[i][j];
						else
							tempdistance[i][j]=centerdistance[i][j+1];
					}
					else //i>=tj
					{
						tempdistance[i][j]=centerdistance[i+1][j+1];
					}
				}
			for (i=1;i<centernum;i++)
				for (int j=i+1;j<=centernum;j++)
				{
					centerdistance[i][j]=tempdistance[i][j];
				}

		}//end if(td<T)
		else break;
		delete []tempdistance;
	}
	delete  []centerdistance;
}
/************************************************************
*��������		Leipingjunjulifa()
*����			void
*����ֵ			void
*��������		������ƽ�����뷨����ȫ����Ʒ���з���
************************************************************/
void CCluster::Leipingjunjulifa()
{
	GetFeature();
	
	double	**centerdistance;//��¼������
	double T;//��ֵ
	int		distype;//�������ʽ��ŷ�ϡ����ҡ�������
	double minous,maxous,mincos,maxcos,minbcos,maxbcos,mintan,maxtan;

	minous=MAX; mincos=MAX; minbcos=MAX; mintan=MAX;
	maxous=0; maxcos=0; maxbcos=0; maxtan=0;
	//�������־���ģʽ�Ĳο�ֵ
	for (int  i=0;i<patternnum-1;i++)
		for (int j=i+1;j<patternnum;j++)
		{
			if (minous>GetDistance(m_pattern[i],m_pattern[j],1))
				minous=GetDistance(m_pattern[i],m_pattern[j],1);
			if (maxous<GetDistance(m_pattern[i],m_pattern[j],1))
				maxous=GetDistance(m_pattern[i],m_pattern[j],1);

			if (mincos>GetDistance(m_pattern[i],m_pattern[j],2))
				mincos=GetDistance(m_pattern[i],m_pattern[j],2);
			if (maxcos<GetDistance(m_pattern[i],m_pattern[j],2))
				maxcos=GetDistance(m_pattern[i],m_pattern[j],2);

			if (minbcos>GetDistance(m_pattern[i],m_pattern[j],3))
				minbcos=GetDistance(m_pattern[i],m_pattern[j],3);
			if (maxbcos<GetDistance(m_pattern[i],m_pattern[j],3))
				maxbcos=GetDistance(m_pattern[i],m_pattern[j],3);
			
			if (mintan>GetDistance(m_pattern[i],m_pattern[j],4))
				mintan=GetDistance(m_pattern[i],m_pattern[j],4);
			if (maxtan<GetDistance(m_pattern[i],m_pattern[j],4))
				maxtan=GetDistance(m_pattern[i],m_pattern[j],4);
		}
	DlgInfor mDlgInfor;
	mDlgInfor.ShowInfor(minous,maxous,mincos,maxcos,minbcos,maxbcos,mintan,maxtan);
	if (mDlgInfor.DoModal()==IDOK)
	{
		T=mDlgInfor.m_T;
		distype=mDlgInfor.m_DisType;
	}
	else return;

    //��ʼ��
	for ( i=0;i<patternnum;i++)//ÿ����Ʒ�Գ�һ��
	{
		m_pattern[i].category=i+1;
	}

	centerdistance=new double *[patternnum];//�������������飬centerdistance[i][j]��ʾi���j�����
	for ( i=1;i<patternnum;i++)
	{
		centerdistance[i]=new double [patternnum+1];
	}

	for ( i=1;i<patternnum;i++)
		for (int j=i+1;j<=patternnum;j++)
		{
			centerdistance[i][j]=GetDistance(m_pattern[i-1],m_pattern[j-1],distype);
		}

	centernum=patternnum;

	while(1)
	{
		double td,**tempdistance;
		int ti,tj;//������С����
		int numi,numj;//i,j���е�Ԫ�ظ���
		double dis1,dis2;

	    dis1=0;
		dis2=0;
		td=MAX;
		ti=0;
		tj=0;
		numi=0;
		numj=0;
		tempdistance= new double *[patternnum];//��ʱ��¼������
		for (int i=1;i<patternnum;i++)
		{
			tempdistance[i]=new double[patternnum+1];
		}
		//�Ҿ������������ti,tj����¼��С����td
		for( i=1;i<centernum;i++)
		{
			for (int j=i+1;j<=centernum;j++)
			{
				if (td>centerdistance[i][j])	
				{
					td=centerdistance[i][j];
					ti=i;tj=j;
				}
			}
		}

		if(td<T)//�ϲ���ti,tj
		{
			centernum--;
			//�����������������Ա�����ŵ�������
			for (int i=1;i<centernum;i++)
				for (int j=i+1;j<=centernum;j++)
				{
					if (i<ti)
					{
						if(j==ti)
						{
							numi=0;numj=0;
							dis1=0;dis2=0;
							for (int m=0;m<patternnum;m++)
								if (m_pattern[m].category==i)
								{
									for (int n=0;n<patternnum;n++)
									{
										if (m_pattern[n].category==ti)
										{
											numi++;
											dis1+=GetDistance(m_pattern[m],m_pattern[n],distype)*GetDistance(m_pattern[m],m_pattern[n],distype);
										}
										if(m_pattern[n].category==tj)
										{
											numj++;
											dis2+=GetDistance(m_pattern[m],m_pattern[n],distype)*GetDistance(m_pattern[m],m_pattern[n],distype);
										}
									}
								}
                            tempdistance[i][j]=sqrt((dis1+dis2)/(numi+numj));
						}
						else if (j>=tj)
							tempdistance[i][j]=centerdistance[i][j+1];
						else
							tempdistance[i][j]=centerdistance[i][j];
					
					}
					else if (i==ti)
					{
						if (j<tj)
						{
							numi=0;numj=0;
							dis1=0;dis2=0;
							for (int m=0;m<patternnum;m++)
								if (m_pattern[m].category==j)
								{
									for (int n=0;n<patternnum;n++)
									{
										if (m_pattern[n].category==ti)
										{
											numi++;
											dis1+=GetDistance(m_pattern[m],m_pattern[n],distype)*GetDistance(m_pattern[m],m_pattern[n],distype);
										}
										if(m_pattern[n].category==tj)
										{
											numj++;
											dis2+=GetDistance(m_pattern[m],m_pattern[n],distype)*GetDistance(m_pattern[m],m_pattern[n],distype);
										}
									}
								}
                            tempdistance[i][j]=sqrt((dis1+dis2)/(numi+numj));
						
						}
                        else
						{
							numi=0;numj=0;
							dis1=0;dis2=0;
							for (int m=1;m<=patternnum;m++)
								if (m_pattern[m].category==(j+1))
								{
									for (int n=1;n<=patternnum;n++)
									{
										if (m_pattern[n].category==ti)
										{
											numi++;
											dis1+=GetDistance(m_pattern[m],m_pattern[n],distype)*GetDistance(m_pattern[m],m_pattern[n],distype);
										}
										if(m_pattern[n].category==tj)
										{
											numj++;
											dis2+=GetDistance(m_pattern[m],m_pattern[n],distype)*GetDistance(m_pattern[m],m_pattern[n],distype);
										}
									}
								}
                            tempdistance[i][j]=sqrt((dis1+dis2)/(numi+numj));
						
						}
					}
					else if((i>ti)&&(i<tj))
					{
						if(j<tj)
							tempdistance[i][j]=centerdistance[i][j];
						else
							tempdistance[i][j]=centerdistance[i][j+1];
					}
					else //i>=tj
					{
						tempdistance[i][j]=centerdistance[i+1][j+1];
					}
				}
			for (i=1;i<centernum;i++)
				for (int j=i+1;j<=centernum;j++)
				{
					centerdistance[i][j]=tempdistance[i][j];
				}

			for ( i=0;i<patternnum;i++)
			{
				if (m_pattern[i].category==tj)
					m_pattern[i].category=ti;
				if (m_pattern[i].category>tj)
					m_pattern[i].category--;
			}
			delete []tempdistance;
		}//end if(td<T)
		else break;
	}//end while
	delete []centerdistance;
}
/************************************************************
*��������		Kjunzhi()
*����			void
*����ֵ		    void
*��������		����K��ֵ��ȫ����Ʒ���з���
************************************************************/
void CCluster::Kjunzhi()
{
	GetFeature();

	int		distype;//�������ʽ(ŷ�ϡ�����...)
	int		times;//max loop number
	int		i,j;

	DlgInfor mDlgInfor;
	mDlgInfor.ShowInfor(4);
	if (mDlgInfor.DoModal()==IDOK)
	{
		distype=mDlgInfor.m_DisType;
		times=mDlgInfor.m_Times;
		centernum=mDlgInfor.m_CenterNum;
	}
	else return;

	BOOL change=true;//�˳���־��falseʱ��ʾ��Ʒ��������ٱ仯����ֹ����
	int counter=0;//��¼��ǰ�Ѿ�ѭ���Ĵ���
	double distance;//�������ĵľ���
	distance=MAX;
	
	m_center=new Center[centernum];

	for ( i=0;i<patternnum;i++)
		m_pattern[i].distance=MAX;
	for ( i=0;i<centernum;i++)//��ʼ����ǰcenternum��ģ����Է�Ϊһ��
	{
		m_pattern[i].category=i+1;
		m_pattern[i].distance=0;
		for ( j=0;j<N*N;j++)
			m_center[i].feature[j]=m_pattern[i].feature[j];
		m_center[i].index=i+1;
	}

	while (change && counter<times)
	{
		counter++;
		change=false;
		for( i=0;i<patternnum;i++)//��������Ʒ���¹���
		{
			//�����i��ģʽ�������������ĵ���С���룬
			int index=1;
			distance=MAX;
            
			for (int j=0;j<centernum;j++)
				if (distance>GetDistance(m_pattern[i],m_center[j],distype))
				{
					distance=GetDistance(m_pattern[i],m_center[j],distype);
					index=j;//�ҵ���С����,�ǵ���index���������ĵľ���
				}
			
			//�Ƚ�ԭ���ĺ��������ĺ�
			//��ͬ�����¾��롣
			//��ͬ��1���¾���С������������ģ����¾��룬���¼���ǰ��������������ģʽ
			//2���¾������ԭ���룬������
			//counter����
			if (m_pattern[i].category==m_center[index].index)//����ԭ��
			{
				m_pattern[i].distance=distance;
			}
			else//������ԭ��
			{
				int tpcenter=m_pattern[i].category;//��¼ԭ���
				m_pattern[i].category=m_center[index].index;//��������
				m_pattern[i].distance=distance;
				if(tpcenter!=0)
				{
					for (int k=0;k<centernum;k++)
						if (m_center[k].index==tpcenter)
					CalCenter(&m_center[k]);//����ԭ��������
				}
				CalCenter(&m_center[index]);//��������������
				change=true;
			}
		}
		
	}//end of while 
	delete []m_center;
}
/************************************************************
*��������		ISODATA()
*����			void
*����ֵ		void
*��������		��ISODATA������ȫ����Ʒ���з���
************************************************************/
void CCluster::ISODATA()
{
	GetFeature();
	
	int i,j;
	int      distype;
	int      times;//���������������û�����
	int      precenternum;//��ǰ����
	double   T;//�������ĵ���С���룬С�ڸ���ֵ���ϲ�
	double   equation;//���ڷ�����ֵ
	double   *avedistance;//avedistance[i]:��i+1����ƽ������,i=0,1,...,centernum.
	double   allavedis;//ȫ��ģʽ��������ƽ������

	double minous,maxous,mincos,maxcos,minbcos,maxbcos,mintan,maxtan;

	minous=MAX; mincos=MAX; minbcos=MAX; mintan=MAX;
	maxous=0; maxcos=0; maxbcos=0; maxtan=0;
	//�������־���ģʽ�Ĳο�ֵ
	for (  i=0;i<patternnum-1;i++)
		for ( j=i+1;j<patternnum;j++)
		{
			if (minous>GetDistance(m_pattern[i],m_pattern[j],1))
				minous=GetDistance(m_pattern[i],m_pattern[j],1);
			if (maxous<GetDistance(m_pattern[i],m_pattern[j],1))
				maxous=GetDistance(m_pattern[i],m_pattern[j],1);

			if (mincos>GetDistance(m_pattern[i],m_pattern[j],2))
				mincos=GetDistance(m_pattern[i],m_pattern[j],2);
			if (maxcos<GetDistance(m_pattern[i],m_pattern[j],2))
				maxcos=GetDistance(m_pattern[i],m_pattern[j],2);

			if (minbcos>GetDistance(m_pattern[i],m_pattern[j],3))
				minbcos=GetDistance(m_pattern[i],m_pattern[j],3);
			if (maxbcos<GetDistance(m_pattern[i],m_pattern[j],3))
				maxbcos=GetDistance(m_pattern[i],m_pattern[j],3);
			
			if (mintan>GetDistance(m_pattern[i],m_pattern[j],4))
				mintan=GetDistance(m_pattern[i],m_pattern[j],4);
			if (maxtan<GetDistance(m_pattern[i],m_pattern[j],4))
				maxtan=GetDistance(m_pattern[i],m_pattern[j],4);
		}
	//��������Ʒ�ܷ���
	double cen[N*N],equ[N*N];
	for (i=0; i<N*N; i++)
	{
		cen[i]=0;
		equ[i]=0;
	}
	for (i=0;i<patternnum;i++)//������Ʒ�����ۼ�
		for (j=0;j<N*N;j++)
		    cen[j]+=m_pattern[i].feature[j];
	for (i=0;i<N*N;i++)//��������Ʒ������ֵ
		cen[i]=cen[i]/(double)patternnum;
	for (i=0;i<patternnum;i++)//�ܷ���
		for (j=0;j<N*N;j++)
			equ[j]+=(m_pattern[i].feature[j]-cen[j])*(m_pattern[i].feature[j]-cen[j]);
	for (i=0;i<N*N;i++)//������
		equ[i]=sqrt(equ[i]/(double)patternnum);
	double minequ=MAX;
	double maxequ=0.0;
	//��������е������Сֵ
	for (i=0;i<N*N;i++)
	{
		if (minequ>equ[i])
            minequ=equ[i];
		if (maxequ<equ[i])
			maxequ=equ[i];
	}

	DlgInfor    mDlgInfor;
//������Ի���
	mDlgInfor.ShowInfor(minous,maxous,mincos,maxcos,minbcos,maxbcos,mintan,maxtan,minequ,maxequ);//OUTPUT EQUATIONOUT!!!
	if (mDlgInfor.DoModal()==IDOK)
	{
		distype=mDlgInfor.m_DisType;
		T=mDlgInfor.m_T;
		times=mDlgInfor.m_Times;
		equation=mDlgInfor.m_EquationIn;
		centernum=mDlgInfor.m_CenterNum;
	}
	else return;
    //������Ʒ����һ��
	precenternum=centernum;
	m_center=new Center[precenternum];
	for ( i=0;i<precenternum;i++)
	{
		m_pattern[i].category=i+1;
		for (j=0;j<N*N;j++)
			m_center[i].feature[j]=m_pattern[i].feature[j];
		m_center[i].index=i+1;
		m_center[i].patternnum=1;
	}

	int counter=0;//ѭ������

	avedistance=new double[precenternum];

	while (++counter<times)
	{
		for ( i=0;i<patternnum;i++)//��������Ʒ���¹���
		{
			double td=MAX;
			int index=0;
			for (int j=0;j<precenternum;j++)
				if (td>GetDistance(m_pattern[i],m_center[j],distype))
				{
					td=GetDistance(m_pattern[i],m_center[j],distype);
					index=j;
				}
			m_pattern[i].category=m_center[index].index;
		}
		//����������
		for (i=0;i<precenternum;i++)
			CalCenter(&m_center[i]);
		for (i=0; i<precenternum;i++)
		{
			if (m_center[i].patternnum==0)
			{
				for(j=i; j<precenternum-1; j++)
					m_center[j]=m_center[j+1];
				precenternum--;

			}
		}
		//������������ƽ������
		for (i=0;i<centernum;i++)
			avedistance[i]=0.0;//��ʼ��

		allavedis=0;	//ȫ������ƽ������

		for (i=0;i<precenternum;i++)
		{
			int num=0;//���г�Ա����
			double dis;
			dis=0.0;
			for ( j=0;j<patternnum;j++)
			{
				if (m_pattern[j].category==i+1)
				{
					++num;
					dis+=GetDistance(m_pattern[j],m_pattern[i],distype);
				}
			}
			allavedis+=dis;
			avedistance[i]=(double)(dis/(double)num);
		}

		allavedis/=patternnum;
	 
		if ((precenternum>=2*centernum) || ((counter%2)==0) && (precenternum>(int)(centernum/2+0.5)))//�ϲ�
		{
			//�ҵ����������������
			double td=MAX;
			int ti,tj;
			for( i=0;i<precenternum;i++)
				for ( j=i+1;j<precenternum;j++)
				{
					double tdin;
					tdin=GetDistance(m_center[i],m_center[j],distype);
					if (td<tdin)
					{
						td=tdin;
						ti=i;
						tj=j;
					}
				}
			//�ж��Ƿ�Ҫ�ϲ�
			if(td<T)//�ϲ�
			{
				for ( i=0;i<patternnum;i++)
				{
					if (m_pattern[i].category==m_center[tj].index)
						m_pattern[i].category=m_center[ti].index;
					if (m_pattern[i].category>m_center[tj].index)
						m_pattern[i].category--;
				}
				CalCenter(&m_center[ti]);
				for (i=tj;i<precenternum-1;i++)
				{
					m_center[i]=m_center[i+1];
					m_center[i].index--;
				}
				precenternum--;
			}
		}//end �ϲ�
		else//����
		{
			double **mequation;//��׼��
			int ti,tj;//��¼����׼�����λ��,��ti+1����ĵ�tj+1λ��ti��0,1,...,precenternum-1.
			
			mequation= new double *[precenternum];
			for (i=0;i<precenternum;i++)
			{
				mequation[i]=new double[N*N];
				for (j=0;j<N*N;j++)
					mequation[i][j]=0.0;
			}
			//�����׼��
			for ( i=0;i<precenternum;i++)
			{
				for ( j=0;j<patternnum;j++)
					if (m_pattern[j].category==m_center[i].index)
					{
						for (int k=0;k<N*N;k++)
								mequation[i][k]+=(m_pattern[j].feature[k]-m_center[i].feature[k])*(m_pattern[j].feature[k]-m_center[i].feature[k]);
					}
					for (int k=0;k<N*N;k++)
						mequation[i][k]=sqrt(mequation[i][k]/m_center[i].patternnum);
			}
			//������׼��
			ti=0;
			tj=0;
			for (i=0;i<precenternum;i++)
				for ( j=0;j<N*N;j++)
					if(mequation[i][j]>mequation[ti][tj])
						{
							ti=i;tj=j;
						};
			//�ж��Ƿ�Ҫ����
			if (mequation[ti][tj]>equation)//���ڸ�����ֵ
			{
				if (avedistance[ti]>allavedis )
					//��ƽ�����������ƽ������  ����
				{
					precenternum++;
					Center *tempcenter;
					tempcenter=new Center [precenternum];

					for (i=0;i<precenternum-1;i++)
						tempcenter[i]=m_center[i];
					tempcenter[precenternum-1].index=precenternum;
					for (j=0;j<N*N;j++)
						tempcenter[precenternum-1].feature[j]=m_center[ti].feature[j];
					tempcenter[precenternum-1].feature[tj]-=0.5*mequation[ti][tj];
					tempcenter[ti].feature[tj]+=0.5*mequation[ti][tj];

					delete []m_center;
					m_center=tempcenter;
									
				}
			}
			delete []mequation;
		}//end ����
	}//end while(1)*/
	delete []avedistance;
	delete []m_center;
}

/************************************************************
*��������		Mohujulei()
*����			void
*����ֵ		    void
*��������		��ģ�����෽����ȫ����Ʒ���з���
************************************************************/
void CCluster::FuzzyCluster()
{
	GetFeature();//���������Ʒ����

	double	*dis, *tempdis;
	double	dismax;
	int		i,j;
	int		distype;
	dismax=0;

	dis=new double [patternnum*patternnum];//ģ��ϵ������
	tempdis=new double [patternnum*patternnum];
	DlgFuzzyDistance  dfd;
	if (dfd.DoModal()==IDOK)
	{
		distype=dfd.mfuzzydistance;
	}
	else 
		return;
    //�õ���ʼģ������
	for ( i=0; i<patternnum; i++)
		for (j=0; j<patternnum; j++)
	{
		dis[i*patternnum+j]=GetFuzzyDistance(m_pattern[i],m_pattern[j],distype);//distype
	}

   //����ȼ���
	bool flag;
	flag=true;
	while (flag)
	{
		flag=false;
		for ( i=0; i<patternnum; i++)
			for ( j=0; j<patternnum; j++)
				if (i==j)//�Խ���Ϊ1
					tempdis[i*patternnum+j]=1;
				else
					tempdis[i*patternnum+j]=GetDistance(dis,i,j);
		for ( i=0; i<patternnum; i++)
		{
			for ( j=0; j<patternnum; j++)
				if ((tempdis[i*patternnum+j]-dis[i*patternnum+j])*(tempdis[i*patternnum+j]-dis[i*patternnum+j])>0.000001)//(tdis[i][j]!=dis[i][j])
				{
					flag=true;
					break;
				}
			if (flag)
				break;
		}
	
		for ( i=0; i<patternnum*patternnum; i++)
				dis[i]=tempdis[i];
	}
	//���ģ������
	CString ts,sout;
	//��һ�б��1��2����������patternnum��
	sout.Insert(sout.GetLength(),"   \t");
	for (i=1; i<=patternnum; i++)
	{
		ts.Format("%d   \t",i);
		sout.Insert(sout.GetLength(),ts);
	}
	sout.Insert(sout.GetLength(),"\n\n");

	for (i=0; i<patternnum; i++)
	{
		//ÿ�п�ͷ���
		ts.Format("%d   \t",i+1);
		sout.Insert(sout.GetLength(),ts);
		//���ģ��ϵ������
		for(j=0; j<patternnum; j++)
		{
			ts.Format("%0.3f\t",dis[i*patternnum+j]);
			sout.Insert(sout.GetLength(),ts);
			if ((j+1)%patternnum==0)
				sout.Insert(sout.GetLength(),"\n\n\n");

		}
	}
	MessageBox(NULL,sout,"ģ������",MB_OK);

	delete []tempdis;

	double *xishu=new double [patternnum*patternnum];
	for(i=0; i<patternnum*patternnum; i++)
		xishu[i]=-1;

	int pointer=0;
	//��¼ģ��ϵ�������в�ͬ��ϵ��
	for ( i=0; i<patternnum; i++)
		for ( j=i; j<patternnum; j++)
		{
			bool done=false;
			for (int k=0; k<pointer; k++)
			{
				if ((xishu[k]-dis[i*patternnum+j])*(xishu[k]-dis[i*patternnum+j])<0.000001)
				{
					done=true;
					break;
				}
			}
			if (!done)
			{
				xishu[pointer]=dis[i*patternnum+j];
				pointer++;
			}
		}
	
	for(i=0; i<pointer-1; i++)//����ֵ��С��������
		for (j=0; j<pointer-i-1; j++)
		{
			if (xishu[j]>xishu[j+1])
			{
				double	temp=xishu[j];
				xishu[j]=xishu[j+1];
				xishu[j+1]=temp;
			}
		}
	CString s,str;
	for (i=0; i<pointer; i++)
	{
		s.Format("%0.4f  ",xishu[i]);
		str.Insert(str.GetLength(),s);
	}
	delete   []xishu;
	//�û����������ֵ
	double    yz;
	DlgMohu		mohu;
	mohu.m_Mohuxishu=str;
	if (mohu.DoModal()==IDOK)
	{
		yz=mohu.m_Mohuyuzhi;	
	}
	else return;
	
	int *result;
	//������ֵ���������
	result=new int [patternnum*patternnum];
	for (i=0; i<patternnum*patternnum; i++)
		if (dis[i]>=yz)
			result[i]=1;
		else 
			result[i]=0;

		//��������

	//��һ�б��
	sout="";
	sout.Insert(-1,"ÿ����\"1\"��Ӧ����Ϊͬһ��");
	sout.Insert(sout.GetLength(),"\n\n");
	sout.Insert(sout.GetLength(),"   \t");
	for (i=1; i<=patternnum; i++)
	{
		ts.Format("%d   \t",i);
		sout.Insert(sout.GetLength(),ts);
	}
	sout.Insert(sout.GetLength(),"\n\n");
		

	for (i=0; i<patternnum; i++)
	{
		//ÿ�п�ͷ���
		ts.Format("%d   \t",i+1);
		sout.Insert(sout.GetLength(),ts);
		for(j=0; j<patternnum; j++)//����Ϊԭģ��ϵ��
		{
			ts.Format("%0.3f\t",dis[i*patternnum+j]);
			sout.Insert(sout.GetLength(),ts);
			if ((j+1)%patternnum==0)
				sout.Insert(sout.GetLength(),"\n");
		}
		sout.Insert(sout.GetLength(),"   \t");
		for(j=0; j<patternnum; j++)//����Ϊ������ֵ�޸ĺ��ϵ����1����0��
		{
			ts.Format("%d\t",result[i*patternnum+j]);
			sout.Insert(sout.GetLength(),ts);
			if ((j+1)%patternnum==0)
				sout.Insert(sout.GetLength(),"\n\n");
		}
	}
	MessageBox(NULL,sout,"����ǰ��ľ������",MB_OK);

	centernum=0;

	for (i=0; i<patternnum; i++)//������ֵ����
		for (j=i; j<patternnum; j++)
		{
			if (result[i*patternnum+j]==1)
			{
				if (m_pattern[i].category!=0)
					m_pattern[j].category=m_pattern[i].category;
				else if (m_pattern[j].category!=0)
					m_pattern[i].category=m_pattern[j].category;
				else
				{
					centernum++;
					m_pattern[j].category=centernum;
					m_pattern[i].category=centernum;
				}
			}
		}
	delete []dis;
	delete []result;
}




