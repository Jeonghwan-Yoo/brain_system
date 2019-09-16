//SEH�� ���� �帧 �ľ��ϱ�
#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

int _tmain(int argc, TCHAR* argv[])
{
	_tprintf(_T("start point!\n"));

	int* p = NULL;

	__try
	{
		//�Ҵ���� ���� �ּ� NULL�� ���� �����ϰ� �ִ�. �׷��� ���ܻ�Ȳ �߻�
		*p = 100; //���ܹ߻� ����
		//������ ���ܰ� �߻��ϸ�, __except ����� �������͸� �˻��Ѵ�.
		//�˻� ����� ������ ������ �帧�� �����ϰ� �Ǵµ�, EXCEPTION_EXECUTE_HANDLER�� �켱 __except�� ����.
		//��������� ���� ���ܻ�Ȳ�� ������ ó���Ǿ��ٰ� Windows�� �����Ѵ�.
		//���ܻ�Ȳ�� ó���� ����(__except ��� ����), __except ����� ���� �κ��� �����ϰ� �ȴ�.
		_tprintf(_T("value:%d\n"), *p);
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		_tprintf(_T("exception occurred!\n"));
	}

	_tprintf(_T("end point!\n"));
	return 0;
}