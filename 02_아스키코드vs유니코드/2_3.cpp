#include <stdio.h>
#include <string.h>

int main(void) {
	wchar_t str[] = L"ABC";
	int size = sizeof(str); //sizeof()�� �������̱� ������ ������� �迭�� ũ�⸦ ����� ��ȯ�Ѵ�
	//������ ������ �߻��Ѵ�. strlen�Լ��� SBCS��� ���ڿ��� ó���ϱ� ���� �Լ��̱� ����.
	//int len = strlen(str);

	printf("�迭�� ũ�� : %d\n", size);
	//printf("���ڿ� ���� : %d\n", len);

	return 0;
}