/*
MS���� C++������ Ȯ���ϴ� ���� �־ ������ �����ϴ� ���� ����.
Ư���� �͵��� ���α׷����� ���Ǹ� ���ؼ� �����Ǵ� �͵��̴�.
GUI���α׷����� �ϴ�, �ý��� ���α׷����� �ϰ� �����ڵ忡 ���� ���ش� �ʼ��̴�.

01 Windows������ �����ڵ�(UNICODE)
���ڼ�(Character Sets)�� ������ Ư��
�ƽ�Ű�ڵ�� �̱����� �����ϰ� �ִ� ǥ���̴�.
���ĺ� ���� 26�����ٰ� Ȯ�� ���ڸ� ������ 256���� ���� �ʾ� 1����Ʈ�ε� ����� ǥ���� �� �ִ�.
�����ڵ�� ���ڸ� ǥ���ϴ� �� �־ �����ϰ� 2����Ʈ�� ����Ѵ�.
�ֳ��ϸ� �������� ��� ���ڿ� �پ��� ������ ��ȣ�� ǥ���ϱ� ����.
���ڼ��̶� ���ڵ��� �������� "��ӵ� ������ ǥ�����"�� �ǹ�.
���ڼ��� ������ ���� �� ���� ���·� ������.

SBCS(Single Byte Character Set)
���ڸ� ǥ���ϴ� �� �־ 1����Ʈ���� ����ϴ� ������� �ƽ�Ű�ڵ尡 ��ǥ��.
MBCS(Multi Byte Character Set)
�پ��� ����Ʈ ���� ����ؼ� ���ڸ� ǥ���ϴ� ���.
�����ڵ�� MBCS�� ������ �ʴ´�.
�ֳ��ϸ� MBCS�� SBCS�� �����ϰ� �ֱ� �����̴�.
�׷��� ��κ��� ���ڵ��� 2����Ʈ�� ó���ϵ�, ��쿡 ���󼭴� 1����Ʈ�� ó���Ѵ�.
�ƽ�Ű�ڵ忡�� �����ϸ� 1����Ʈ�� ó���ϰ�, �ƴϸ� 2����Ʈ�� ó���ϴ� ���.
����� ȿ�������� ���ڸ� ǥ�������� ���α׷��� �����ϴ� �� ������ ���Ǹ� ��￩�� �Ѵ�.
WBCS(Wide Byte Character Set)
�����ڵ尡 �ش��Ѵ�.
��� ���ڸ� 2����Ʈ�� ó���ϴ� ���ڼ��̴�.

MBCS ����� ���ڿ�
2_1.cpp MBCS1.cpp
�迭�� ũ��� ABC(3) + �ѱ�(4) + NULL(1) = 8Bytes
������ 1����Ʈ�� �ѱ��� 2����Ʈ�� ó���ǰ� �ִ�.
�̰��� ���� MBCS�� ������� ����ǰ� ������ �����ش�.
strlen�� ���ڿ��� ���̸� ����Կ� �־ NULL���ڸ� �������� �ʴ´�.
���̴� ABC(3) + �ѱ�(4) = 7Bytes
2_2.cpp MBCS2.cpp
���ڿ� ���̴� 5������, ���ڿ��� �Ҵ�� ũ�Ⱑ 10����Ʈ�� ����� fputc�Լ��� 10�� ȣ���ؾ߸� �Ѵ�.
�̷� �������鵵 ���α׷����� ���ϸ� ��� ���� �ذ��� �����ϴ�.
�̷� �������� �ذ�å�� �� �� �ִ� ���� WBCS����̴�.
WBCS����� ��� ���ڵ��� 2����Ʈ�� ó���Ѵ�.
��� ���ڵ��� ������ ����Ʈ�� ũ��� ó���Ѵٴ� ���� �������� �ذ��ϴ� �Ǹ���.

WBCS ����� ���α׷���
[char�� ����ϴ� wchar_t]
���ڸ� ǥ���ϴµ� ���Ǵ� �ڷ��� char�� ����ؼ� �ڷ��� wchar_t�� ����ؾ� �Ѵ�.
wchar_t�� ������ 2����Ʈ �޸� ������ �Ҵ�ȴ�.
���� �����ڵ带 ������� ���ڸ� ǥ���ϴ� ���� �����ϴ�.
typedef unsigned short wchar_t;
["ABC"�� ����ϴ� L"ABC"]
wchar_t str[] = "ABC";���·� �����ϸ� ������ �߻��Ѵ�.
�迭 str�� �����ڵ� ���ڿ��� ������ �غ� �Ǿ� ������, ������ ���ڿ��� ������ MBCS��� ���ڿ��̱� ����.
whcar_t str[] = L"ABC";���·� �����ؾ� �Ѵ�.
L�� "�̾ �����ϴ� ���ڿ��� �����ڵ� ������� ǥ���϶�"�� �ǹ�.
�� ��쿡�� �ι��ڱ����� 2����Ʈ�� ó���Ǿ� �� 8����Ʈ.
wchar_t�� ANSIǥ�ؿ��� �����ڵ� ������ ���� ������ ǥ�� �ڷ����̴�.
[strlen�� ����ϴ� wcslen]
2_3.cpp MBCS1.cpp �����ڵ� ����
���ڿ� ���� �Լ����� SBCS��� ���ڿ��� ó���ϱ� ���� �Լ�����.
 strlen -> size_t wcslen(const wchar_t* string);
 strcpy -> wchar_t* wcscpy(wchar_t* dest, const wchar_t* src);
strncpy -> wchar_t* wcsncpy(wchar_t* dest, const wchar_t* src, size_t cnt);
 strcat -> wchar_t* wcscat(wchar_t* dest, const wchar_t* src);
strncat -> wchar_t* wcsncat(wchar_t* dest, const wchar_t* src, size_t cnt);
 strcmp -> int wcscmp(const wchar_t* s1, const wchar_t2* s2);
strncmp -> int wcsncmp(const wchar_t* s1, const wchar_t2* s2, size_t cnt);

SBCS�Լ��� WBCS�Լ��� ���������� ���� �� �ǹ̴� ������ �����ϴ�.
�ٸ� WBCS��� �Լ��� �������ڴ� �����ڵ� ��� ���ڿ��̴�.
SBCS�� ��κ� MBCS��� ���ڿ� ó���� ���ؼ��� ��� �����ϴ�.
�ٸ� strlen�Լ��� MBCS���ڿ��� ó���ϴµ� 2_1.cppó�� ������ �ȴ�.
����, size_t�� typedef unsigned int size_t;
2_4.cpp WBCS1.cpp

������ �����ڵ� ������� : ù ��°
Windows2000�̻��� �ü���� �⺻������ �����ڵ带 �����Ѵ�.
�����ڵ带 ������ �Ӹ��ƴ϶�, ���������� ��� ���ڿ��� �����ڵ� ������� ó���Ѵ�.
printf�Լ��� ���ڿ� ó�� �Լ��̹Ƿ�, SBCS�� WBCS �� �ϳ��� ���� �Ǵµ� SBCS��� ���ڿ��� ó���ϴ� �Լ���.
���࿡ Windows2000�̻��� �ü������ ���� ���� �Լ��� ȣ���� �̷����� �ü���� ���޵Ǵ� ���ڿ��� ����������
2����Ʈ �����ڵ� �������� ��ȯ�Ѵ�.
Windows2000�̻��� �ü���� ��� ���ڿ��� �����ڵ� ������� ó���ϱ� ����.
�̴� ���α׷� ���ɿ� �ټ� ������ ��ġ�� ��Ұ� �� �� �ִ�.
�����ڵ� ������� ���α׷��� �ۼ��ϸ�, ���ɿ��� ���� ������ ��ġ�� �ʴ´�.
printf -> int wprintf(const wchar_t* format [, argument]...);
 scanf -> int wscanf(const wchar_t* format [, argument]...);
 fgets -> wchar_t* fgetws(wchar_t* string, int n, FILE* stream);
 fputs -> int fputws(const wchar_t* string, FILE* stream);
2_5.cpp WBCS2.cpp

wprintf, fputws�� ���� �Լ����� ���� �����ڵ� ������� �ѱ��� ����ϰ� �ʹٸ�, ȣ���ϱ� ����
#include "locale.h"
_wsetlocale(LC_ALL, L"korean");
_wsetlocale�Լ��� ���α׷��� ����Ǵ� ���� �� ������ ���� ������ �����ϴ� �� ���Ǵ� �Լ��̴�.

������ �����ڵ� ������� : �� ��°
2_5.cpp�� ������ �����ڵ� ����� �ƴϴ�.
2_6.cpp WBCS3.cpp
c:\>test.exe AAA BBB                       c:\>test.exe AAA BBB
          �� main                                     �� wmain
"test.exe" "AAA" "BBB"                     L"test.exe" L"AAA" L"BBB"
          �� ���� ����                                 �� ���� ����
int main(int argc, char* argv[])           int wmain(int argc, wchar_t* argv[])
�Լ� �̸��� main�̸� ���޵Ǵ� ���ڿ��� MBCS������� �����Ǿ� ���ڷ� ���޵ȴ�.
�Լ� �̸��� wmain�̸� ���α׷� ���� �� ���޵Ǵ� ���ڿ��� �����ڵ� ������� �����Ѵ�.
2_7.cpp WBCS4.cpp

02 MBCS�� WBCS�� ���� ����
WBCS������� �����ϴ� ���� ���ƺ�������, �ý��� ��ΰ� �Ϻ��� �����ڵ� ����� �����ϴ� ���� �ƴϾ
������ �߻��� ������ ����.
���α׷��� �ѹ��� �����ϰ�, ������� MBCS������� ���ư��� ���·ε�, WBCS������� ���ư��� ���·ε�
������ �����ϴٸ� ���� ���������� ���̴�.
�ȱ׷��� ������ �� ���ڿ��� ��� �����ؾ��ϰ� �Լ��鵵 �����ؾߵǴµ� �����ϰ� ���׷� �̾��� ���� �ִ�.

#include <windows.h>
windows.h�� Windows��� ���α׷����� �ϴ� �� �־ �⺻������ �׻� �����ؾ� �ϴ� ��������̴�.
windows.h�� Windows���α׷��ֿ� �ʿ��� �پ��� ������ ��������� ���Ҿ� �����ϱ� ������ �� ������� �ϳ���
����� ��찡 ��κ��̴�.
���ο� �ڷ������� ������� windows.h�� ���ǵǾ� �ִ�.
��Ȯ�ϰԴ� winnt.h�� ���ǵǾ� �ְ�, ������� windef.h�� winnt.h�� �����ϰ�, windows.h�� windef.h�� ����.
windows.h�� ���� Windows�ý��� ���α׷��ֿ� �ʿ��� ��κ��� ���� ����/���������� �����ϰ� �ȴ�.

Windows���� �����ϰ� �ִ� �ڷ���
typedef char CHAR;
typedef wchar_t WCHAR;
���ڿ��� �ּҰ��� ������ �� �ִ� �ڷ���
��ũ�� CONST�� windef.h�� �������� winnt.h�� ���ǵǾ� �ִ�.
#define CONST const
typedef CHAR* LPSTR;
typedef CONST CHAR* LPCSTR;
typedef WCHAR* LPWSTR;
typedef CONST WCHAR* LPCWSTR;
const�� CONST�� ����ϴ� ���� Windows ��Ÿ���� �ڷ��� �̸��� �빮�ڷ� �����Ǵ� �帧�� ���󰡱� ����.
2_8.cpp WinString.cpp
2_8.c

Windows��Ÿ�� �ڷ����� ���� �̾߱�
Windows������ int, char�� ���� �⺻ �ڷ����� Windows��Ÿ���� �̸����� �����ϰ� �ִ�.
�̷� �ڷ����� �����ϴ� ������ ù ������ ������ �����̴�.
typedef�� ������ ������ �ܼ��ϰ� ���ش�.
typedef unsigned int size_t;
�� ������ ����ؼ� �����ϰ�, �ǹ̵� ���� ���ϰ� �ο��� �̸��� ���� ���� �� ����� �� �ִ�.
�� ��°�� Ȯ���� ���̼��̴�.
���� unsigned char���� unsigned int�� �ٲ�� �Ѵٸ� ������ �ٲ��־�� ������
STR_LEN�̶�� �̸��� ��� ����ؼ� ������ ������ ��Ȳ�̶�� ���� ����������.
���Ǹ� �������ְ� �����ϸ� �ٽ� �ϸ� ��� �۾��� �Ϸ�Ǳ� ����.
��, Ȯ�强�� �������� ��.
typedef unsigned char STR_LEN;
typedef unsigned int STR_LEN;
��, ������ ���̼��� Ȯ�强�� ����ؼ� typedef������� ������ �̸��� �ڷ����� �����ϴ� ���� ���� ����
���α׷��� �����̴�.
������Ʈ�� ������ ������ ������ �̸��� �ڷ����� �����ϰ�, �� �̸� Ȱ���Ͽ� ���α׷����� �����ϴ� ���� ����.

MBCS�� WBCS�� ���ÿ� �����ϱ� ���� ��ũ��
Windows������ MBCS�� WBCS�� ���ÿ� �����ϴ� ������ ���α׷� ������ ���ؼ� ��ũ�θ� �����ϰ� �ִ�.
#ifdef UNICODE
	typedef WCHAR TCHAR;
	typedef LPWSTR LPTSTR;
	typedef LPCWSTR LPCTSTR;
#else
	typedef CHAR TCHAR;
	typedef LPSTR LPTSTR;
	typedef LPCSTR LPCTSTR;
#endif
tchar.h��������� �Ϻθ� �����س��� ���ε�, tchar.h�� windows.h�� ���Ե��� �ʴ´�.
���� ������� tchar.h�� �߰��� ���Խ��Ѿ� �Ѵ�.
#ifdef _UNICODE
	#define __T(x) L ## x //##�� �� �յڿ� �� �� ���� �߰����� ��������ִ� ��. ���⼱ x�տ� L�� ���δ�.
#else
	#define __T(x) x
#endif
#define _T(x) __T(x)
#define _TEXT(x) __T(x)
���� ���
TCHAR arr[10];
��ũ�� UNICODE�� ���ǵǸ� WBCS
TCHAR arr[10]; -> WCHAR arr[10]; -> wchar_t arr[10];
��ũ�� UNICODE�� ���ǵ��� ������ MBCS
TCHAR arr[10]; -> CHAR arr[10]; -> char arr[10];
���� ���
_T("HANBIT");
�� ��ũ�δ� �ƹ� ���� ���� ��ó���⿡ ����
__T("HANBIT");
��ũ�� _UNICODE�� ���ǵǸ� WBCS
__T("HANBIT"); -> L"HANBIT"
��ũ�� _UNICODE�� ���ǵ��� ������ MBCS
__T("HANBIT"); -> "HANBIT"
2_9.cpp MBCS_WBCS1.cpp
��ũ�θ� �ּ�ó���ϰ� �������ص� ������ ���ٸ� Visual Studio������ Ȯ���ؾ� �Ѵ�.
������Ʈ�Ӽ����� ����(Alt+p�ι�) C/C++�� Preprocessor���� <edit>�� ������
"Inherited valuse"�� _UNICODE�� UNICODE�� ���ǵǾ� �ִ�.
������Ʈ ���� �� �⺻������ ���ǵ� ��ũ�ε��̴�.
���ڸ� �����Ű���� Inhrit from parent or project defaults�� üũ�� �����ؾ� �ϴµ� ��� �޽����� �޴´�.
��ũ�ΰ� �ߺ� ���ǵǾ��ٴ� ��� �޽����ε� �� ��쿡�� ������ �����ϸ� �ȴ�.
������ ������, ��ó���⿡ ���� ��ó�� ������ ��ġ�� �Ǵµ�, �⺻������ �����ϰ��� �ϴ� ��ũ�θ� ������Ʈ �Ӽ�
���������� ������ �� �ִ�.
MBCS������� �������Ϸ��� ����â���� _UNICODE�� UNICODE�� ������ ������
#undef�����ڸ� ���ؼ� �̹� ���ǵ� _UNICODE�� ��ȿȭ��Ű�� �ȴ�.
#undef _UNICODE
#undef UNICODE

MBCS�� WBCS�� ���ÿ� �����ϱ� ���� �Լ���
2_9.cpp�� ��ũ�� _UNICODE, UNICODE�� ���� ������ ���� WBCS�� MBCS������� �������� �ȴ�.
������ printf�� ��ũ�� ���ǿ� ������� MBCS������� �����ϵȴ�.
�����ڵ� ������� ���ư��� �Ϸ��� wprint�� �ٲ���Ѵ�.
��ũ�ο� �ڽ��� �ִٸ� ����� ���ڿ��� ������ �� �ִ� ��ũ�� _T("string")�� ����Ѵٸ�
#ifdef _UNICODE
	#define _tprintf wprintf
#else
	#define _tprintf printf
#endif
�׷��� _UNICODE�� ���� ������ ���� WBCS�� MBCS������� ������ �� ���̴�.
_tprint(_T("string size : %d\n"), size);
������ �׷��ʿ� ���� �̹� tchar.h�� ����Ǿ� ������ Ȱ���� �� �ִ�.
#ifdef _UNICODE
	#define _tmain wmain
	#define _tcslen wcslen
	#define _tcscat wcscat
	#define _tcscpy wcscpy
	#define _tcsncpy wcsncpy
	#define _tcscmp wcscmp
	#define _tcsncmp wcsncmp
	#define _tprintf wprintf
	#define _tscanf wscanf
	#define _fgetts fgetws
	#define _fputts fputws
#else
	#define _tmain main
	#define _tcslen strlen
	#define _tcscat strcat
	#define _tcscpy strcpy
	#define _tcsncpy strncpy
	#define _tcscmp strcmp
	#define _tcsncmp strncmp
	#define _tprintf printf
	#define _tscanf scanf
	#define _fgetts fgets
	#define _fputts fputs
#endif
2_10.cpp MBCS_WBCS2.cpp

������Ʈ�� �����ϸ�, �⺻������ Pre-compiled��������� ����ϵ��� ������ ������ ������Ʈ�� ������ ���̴�.
Pre-compiled����� ���� ���Ǵ� ������� ������ �̸� ��� �ξ ������ �ӵ��� ����Ű�� ���� ��.
Pre-compiled����� ����ϴ� ���·� ������Ʈ�� �����ϸ� stdafx.h�� stdafx.cpp������ ����� ���µ�,
stdafx.h���� �ȿ����� ������� stdio.h�� tchar.h�� �����ϰ� �ִ�.
���� �� ��������� ���� ���Խ�Ű�� �ʾƵ� �ȴ�.
1)�����ϴ� ����� ��������Ʈ�� �����ϰ� �ַ�� Ž���⿡�� Source Files/Header Files���� ���� Ȯ�� ��
stdafx.h���ϰ� stdafx.cpp������ �߰��Ѵ�.
2)������Ʈ �Ӽ����� C/C++ -> �̸� �����ϵ� ��� �޴����� '�̸� �����ϵ� ��� �����/���' �׸񿡼� ����� ����
3)stdafx.h �� ���ٿ� #pragma once �߰�(�� �ѹ��� ����)
4)stdafx.cpp�� ������ ������Ʈ ��� �ҽ� ���Ͽ� #include "stdafx.h"�߰�
5)������Ʈ ��ü ����
6)���ĺ��ʹ� '�̸� �����ϵ� ��� �����/���' �׸��� ������� ����

�̰͸��� �˰� ���ô�
1. SBCS, MBCS, WBCS�� ����
SBCS�� ���ڸ� ǥ���ϴ� �� 1����Ʈ, MBCS�� ���ڸ� ǥ���ϴ� �� 1����Ʈ Ȥ�� 2����Ʈ, WBCS�� ���ڸ� ǥ���ϴ� 2����Ʈ
����ϴ� ���ڼ��� �ǹ�. �����ڵ�� WBCS�� �ش�.
2. �����ڵ� ��� ���ڿ� ó�� �Լ�
ANSI ǥ�� ���ڿ� ó�� �Լ��� ������ �����ڵ� ����� �����ϰ� �ִ�.
3. UNICODE�� _UNICODE
���� ������ ���� �Լ��� ���� ���°� �޶�����.
�� ��ũ�θ� ������� �����ڵ� ��İ� MBCS����� �������� �����ϵ��� ���α׷��� �ۼ�.
4. �����ڵ� ��İ� MBCS ����� ��� �����ϱ� ���� main�Լ��� ����
MBCS����� �����Ϸ��� main, �����ڵ� ����� �����Ϸ��� wmain, �� ���� ����� ��� �����Ϸ��� _tmain�� ����.

*/