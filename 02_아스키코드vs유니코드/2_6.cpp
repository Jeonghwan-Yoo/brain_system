#include <stdio.h>

//wchar_t* argv[]�� �ٲٸ� ������ �߻����� �ʴ� ��ó�� �������� ������ ��°���� ���δ�.
//�ֳ��ϸ� main�̶�� �̸��� �Լ��� ���α׷� ���� ��, ���޵Ǵ� ���ڿ��� MBCS������� �����ϱ� ����.
int main(int argc, char* argv[]) { //char���� ���ڿ� �����ʹ� SBCS���
	int i;
	for (i = 0;i < argc;i++) {
		//������ ����� ����� �Ǵ� ���ڿ��� �����ڵ� ����� �ƴϴ�.
		//fputws(argv[i], stdout);
	}

	return 0;
}