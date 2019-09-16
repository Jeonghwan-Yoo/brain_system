//DDL�� �������
//�̴� ������� �ߺ� ���� �� �߻��ϴ� ������ ���� ���� �����̴�.
//ù ��° ���� �� ��ũ�� CALCULATOR_H__�� ���ǵǰ� �� ��° ���� �ÿ��� �ǳ� �پ� ������ �߻����� �ʴ´�.
#ifndef __CALCULATOR_H__
#define __CALCULATOR_H__

//__cplusplus�� Visual Stdio�� C++�����Ϸ��� �������� �� �⺻������ �����ϴ� ��ũ���̴�.
//���� �� ��ũ���� ���� ������ ���� C++�����Ϸ��� ���Ǵ���, C�����Ϸ��� ���Ǵ����� �� �� �ִ�.
#ifdef __cplusplus
extern "C"
{
#endif

//_COMPLING_DLL_CALCULTOR�� ���ǵǸ� ��ũ�� LIBSPEC�� export ������ ������ �ϰ�
//�׷��� ������ import ������ ������ �ϵ��� ����.
//�̸� ������� �ڿ� �Լ��� ����Ǿ� �ִ�.
//���� DLL �ۼ� �ÿ��� ��ũ�� _COMPLING_DLL_CALCULATOR�� ����.
#ifdef _COMPLING_DLL_CALCULATOR
	#define LIBSPEC __declspec(dllexport)
#else
	#define LIBSPEC __declspec(dllimport)
#endif

	LIBSPEC int Add(int a, int b);
	LIBSPEC int Min(int a, int b);
	LIBSPEC double Div(double a, double b);
	LIBSPEC double Mul(double a, double b);

#ifdef __cplusplus
}
#endif
#endif