// GetFeature.h: interface for the GetFeature class.
// 2005.1.13��16��02 By Superman 
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GETFEATURE_H__F4AF6FFD_5056_4E03_8774_096D222CD072__INCLUDED_)
#define AFX_GETFEATURE_H__F4AF6FFD_5056_4E03_8774_096D222CD072__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Cdib.h"

struct pattern//pattern�ṹ�壬����ĳ���������(0��9)��������Ʒ����
{
	int number;//����д������Ʒ����
	double feature[200][25];//����Ʒ������ÿ����д���������200����Ʒ��ÿ����Ʒ��25������
};

class GetFeature : public CDib  
{
public:
	pattern pattern[10];//��д������Ʒ������
	double testsample[25];//�������д����
	int width;//��д���ֵĿ�
	int height;//��д���ֵĸ�
	int LineBytes;

	void Save(int cls);//����д�����ֱ��浽cls(0��9)�����
	BOOL Saveable(int cls);//�ж���д�������ܷ񱣴浽cls(0��9)����У���Ϊ���������Ʒ���������ظ�
	double Cal(int row, int col);//����ָ�õ�5��5С�����У���������ռ�ı���
	void SetFeature();//������д���ֵ���������ֵ��testsample
	void GetPosition();//�����д���ֵ�λ��
	GetFeature();
	virtual ~GetFeature();

protected:
	int bottom;//��д���ֵĵײ�
	int top;//��д���ֵĶ���
	int left;//��д���ֵ����
	int right;//��д���ֵ��ұ�
};

#endif // !defined(AFX_GETFEATURE_H__F4AF6FFD_5056_4E03_8774_096D222CD072__INCLUDED_)
