#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

UINT CalDistance(UINT a, UINT b) {
	return a - b;
}

int _tmain(void) {
	INT val1 = 10;
	INT val2 = 20;

	_tprintf(_T("Position %d, %d\n"), (UINT)&val1, (UINT)&val2);
	//�� ������ �ּҰ��� ���ڷ� ���޹޾Ƽ� �޸𸮻��� �Ÿ��� ����ؼ� ��ȯ�� �ִ� �Լ��̴�.
	//���� �޸��� �Ÿ��� ����ϱ� ���ؼ� �����Ͱ� ���ϴ� �ּҰ��� ���������� ��ȯ�ؼ� �����ϰ� �ִ�.
	_tprintf(_T("distance : %d\n"), CalDistance((UINT)&val1, (UINT)&val2));

	return 0;
}