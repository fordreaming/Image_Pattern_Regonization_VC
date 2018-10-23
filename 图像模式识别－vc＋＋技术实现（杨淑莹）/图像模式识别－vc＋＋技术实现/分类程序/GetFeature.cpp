// GetFeature.cpp: implementation of the GetFeature class.
// 2005.1.13��16��02 By Superman 
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DSPLIT.h"
#include "GetFeature.h"
#include "math.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

GetFeature::GetFeature()
{

}

GetFeature::~GetFeature()
{

}

/***************************************************************
*	�������ƣ�GetPosition()
*   �������ͣ�void 
*   �������ܣ�������д���ֵ�λ�ã���ֵ��bottom,down,right,left
****************************************************************/
void GetFeature::GetPosition()
{
	width=GetWidth();
	height=GetHeight();
	LineBytes=(width*8+31)/32*4;

	int i,j;
	BOOL flag;
	for(j=0;j<height;j++)
	{
		flag=FALSE;
		for(i=0;i<width;i++)
			if(m_pData[j*LineBytes+i]==0)
			{
				flag=TRUE;
				break;
			}
		if(flag)
			break;
	}
	bottom=j;
	for(j=height-1;j>0;j--)
	{
		flag=FALSE;
		for(i=0;i<width;i++)
			if(m_pData[j*LineBytes+i]==0)
			{
				flag=TRUE;
				break;
			}
		if(flag)
			break;
	}
	top=j;
	for(i=0;i<width;i++)
	{
		flag=FALSE;
		for(j=0;j<height;j++)
			if(m_pData[j*LineBytes+i]==0)
			{
				flag=TRUE;
				break;
			}
		if(flag)
			break;
	}
	left=i;
	for(i=width-1;i>0;i--)
	{
		flag=FALSE;
		for(j=0;j<height;j++)
			if(m_pData[j*LineBytes+i]==0)
			{
				flag=TRUE;
				break;
			}
		if(flag)
			break;
	}
	right=i;
}

/***************************************************************
*   �������ƣ�SetFeature()
*   �������ͣ�void 
*   �������ܣ�����д�������������ڱ���testsample��
****************************************************************/
void GetFeature::SetFeature()
{
	int i,j;
	for(j=0;j<5;j++)
	{
		for(i=0;i<5;i++)
		{
			testsample[5*(4-j)+i]=Cal(j,i);//(Cal(j,i)>0.10)?1:0;//
		}
	}	
}

/****************************************************************
*   �������ƣ�Cal(int row, int col)
*   �������ͣ�double 
*   ����˵����int row, int col:��row�У���col������
*   �������ܣ�����ĳһС�����ں�������ռ����,����ĳһС�����ں�������ռ����
****************************************************************/
double GetFeature::Cal(int row, int col)
{
	double w,h,count;
	w=(right-left)/5;
	h=(top-bottom)/5;
	count=0;

	for(int j=bottom+row*h;j<bottom+(row+1)*h;j++)
	for(int i=left+col*w;i<left+(col+1)*w;i++)
	{
		if(m_pData[j*LineBytes+i]==0)
			count++;
	}

	return (double)count/(w*h);
}

/***************************************************************
*   �������ƣ�Savealbe(int cls)
*   �������ͣ�BOOL 
*   ����˵����int cls:���
*   �������ܣ��ж���д���ֿɷ񱣴�Ϊcls����һ����Ʒ
*             ͬһ������Ʒ�������ظ���
****************************************************************/
BOOL GetFeature::Saveable(int cls)
{
	for(int i=0;i<pattern[cls].number;i++)
	{
		BOOL flag=TRUE;
		for(int j=0;j<25;j++)
			flag&=(pattern[cls].feature[i][j]==testsample[j])?TRUE:FALSE;
		if (flag) return FALSE;
	}
	return TRUE;
}

/***************************************************************
*   �������ƣ�Save(int cls)
*   �������ͣ�void 
*   ����˵����int cls:���
*   �������ܣ�����д���ֱ���Ϊcls����һ����Ʒ����������Ʒ�ĵ�һ��
****************************************************************/
void GetFeature::Save(int cls)
{
	for(int i=pattern[cls].number;i>0;i--)
		for(int j=0;j<25;j++)
			pattern[cls].feature[i][j]=pattern[cls].feature[i-1][j];
	for(i=0;i<25;i++)
		pattern[cls].feature[0][i]=testsample[i];
	pattern[cls].number++;	
}



