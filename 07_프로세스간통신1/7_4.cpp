//���޵� ���� ������ �� ����
#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

int _tmain(int argc, TCHAR* argv[])
{
	//���� ���������� ������ 3���� �ƴ϶�� ������� �ν��� �ϰ� -1�� ��ȯ�ϵ��� �Ǿ� �ִ�.
	//�� ���� ������ ���� ����� -1�� ���� �ʴ´ٴ� ������ �ϰ� �ִ�.
	if (argc != 3)
		return -1;

	//_tmain ȣ�� �� ���޵Ǵ� �� ���� ���� ������ ��´�.
	//�̴� �ڽ� ���μ����� �����ϸ鼭 ���ÿ� �����͸� �����ϴ� ���� ���� ����̴�.
	//�θ� ���μ����� �ڽ� ���μ����� �����ϴ� �������� _tmain�Լ��� ���ڿ��� ������ �� �ִ�.
	DWORD start = _ttoi(argv[1]);
	DWORD end = _ttoi(argv[2]);

	DWORD total = 0;

	for (DWORD i = start;i <= end;i++)
		total += i;

	return total;
}