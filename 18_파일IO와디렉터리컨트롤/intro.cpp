/*
01 �⺻���� ���� ó�� �Լ���
Windows���� �����ϴ� ���� ���� �ý��� �Լ����� ANSI���� �����ϴ� �ͺ��� ���� ����� �����Ѵ�.
�̷��� ����� Ȱ���ϱ� ���ؼ��� Windows ��� ���� ����� �Լ��鵵 �˾ƾ� �Ѵ�.
�׷��� �ܼ��� ���Ͽ� �����͸� ���� �д� ���� ���ζ��, ANSI ǥ�� �Լ��� ������ ȣȯ�� ���鿡�� �� ����.

���� ���� & �ݱ�
������ �� ������ ���� �Լ��� Ȱ���Ѵ�.
HANDLE CreateFile (
	LPCTSTR lpFileName, 1)
	DWORD dwDesiredAccess, 2)
	DWORD dwShareMode, 3)
	LPSECURITY_ATTRIBUTES lpSecurityAttributes, 4)
	DWORD dwCreationDisposition, 5)
	DWORD dwFlagsAndAttributes, 6)
	HANDLE hTemplateFile 7)
);
If the function fails, the return value is INVALID_HANDLE_VALUE. 8)
1)lpFileName:������ ���� �̸��� �����Ѵ�.
2)dwDesiredAccess:�б�/���� ��带 �����Ѵ�. or(|)�������� ���� ����.
GENERIC_READ:�б� ��� ����
GENERIC_WRITE:���� ��� ����
3)dwShareMode:���� ��������� �����Ѵ�.
0:�ٸ� ���μ����� ���� ���� �Ұ�. �̹� ����� ������ �ߺ� ���� �Ұ�.
FILE_SHARE_READ:�ٸ� ���μ������� �� ���Ͽ� ���� �б� ���� ����.
FILE_SHARE_WRITE:�ٸ� ���μ������� �� ���Ͽ� ���� ���� ���� ����. �� ���ÿ� ���� ������ �����͸� ���� ������
���ؾ� ��.
4)lpSecurityAttributes:���� �Ӽ��� �����Ѵ�. �ڵ��� �ڽ� ���μ������� ����� ������ �� �������� �����ϱ� ����
�뵵�� ����� �� �ִ�. ����Ʈ ���� �Ӽ��� �����ϰ��� �ϴ� ��� NULL�� �����Ѵ�.
5)dwCreationDisposition:������ �����Ǵ� ����� �����Ѵ�.
CREATE_ALWAYS:�׻� �� ������ �����Ѵ�.
CREATE_NEW:�� ���� ����, ���� �̸��� ������ �����ϸ� ���� ����.
OPEN_ALWAYS:���� ���� ����, ������ ���� ����.
OPEN_EXISTING:���� ���� ����, ������ �Լ� ȣ�� ����.
TRUNCATE_EXISTING:���� ������ ���� ����� ����, ������ �������� ������ ȣ�� ����.
6)dwFlagsAndAttributes:������ Ư�� ������ �����Ѵ�. �� �̻��� Ư�� ������ OR(|)�����ڸ� ���� ������ �� ������,
�⺻�����δ� FILE_ATTRIBUTE_NORMAL�̶�� ���� ����Ѵ�. �̴� Ư���� Ư���� �������� ���� ���� �������� �ǹ��Ѵ�.
�̿ܿ��� ������ �� �ִ� ������ ����.
7)hTemplateFile:������ �����ϴ� ���ϰ� ������ Ư���� ������ �� ������ ���� �� ���Ǵ� ���������̴�.
Windows ME/98/95������ �� �������ڸ� �������� �ʱ� ������ �Ϲ������� NULL�� �����Ѵ�.
8)������ �Լ� ȣ���� �����ϸ�, ������ �ڵ��� ��ȯ�ȴ�.

������ ������ ������ ���������� Closehandle �Լ��� ȣ���ϸ� �ȴ�.
������ ������ ������ Ŀ�� ������Ʈ�� �����ǰ�, �ڵ��� ��ȯ�ȴ�.
CreateFile �Լ��� �ڵ��� ��ȯ�Ѵ�.
�Լ� ȣ���� ���� �����Ǵ� Ŀ�� ������Ʈ���� ���Ͽ� ���� ������ ���� ���ִ�.

���� �б� & ����� ������
���Ͽ� �����͸� ���� ������ ���� �Լ��� ����Ѵ�.
BOOL ReadFile (
	HANDLE hFile, 1)
	LPVOID lpBuffer, 2)
	DWORD nNumberOfBytesToRead, 3)
	LPDWORD lpNumberOfBytesRead, 4)
	LPOVERLAPPED lpOverlapped 5)
);
If the function fails, the return value is 0.
1)hFile:�����͸� ���� ������ �ڵ��� �����Ѵ�.
2)lpBuffer:�о� ���� �����͸� ������ ����(�迭, �޸�)�� �ּ�(������)�� �����Ѵ�.
3)nNumberOfBytesToRead:���Ϸκ��� �а��� �ϴ� �������� ũ�⸦ ����Ʈ ������ �����Ѵ�.
4)lpNubmerOfBytesRead:���� �о� ���� ������ ũ�⸦ ��� ���� ������ �ּҸ� �����Ѵ�.
5)lpOverLapped.

���Ͽ� �����͸� ������ ������ ���� �Լ��� ����Ѵ�.
BOOL WriteFile (
	HANDLE hFile, 1)
	LPCVOID lpBuffer, 2)
	DWORD nNumberOfBytesToWrite, 3)
	LPDWORD lpNumberOfBytesWritten, 4)
	LPOVERLAPPED lpOverlapped 5)
);
If the function fails, the return value is zero.
1)hFile:�����͸� ������ ������ �ڵ��� �����Ѵ�.
2)lpBuffer:�����͸� �����ϰ� �ִ� ����(�迭, �޸�)�� �ּ�(������)�� �����Ѵ�.
3)nNumberOfBytesToWrite:���Ͽ� �����ϰ��� �ϴ� ������ ũ�⸦ ����Ʈ ������ �����Ѵ�.
4)lpNumberOfBytesWritten:���Ͽ� ���� ����� ������ ũ�⸦ ��� ���� ������ �ּҸ� �����Ѵ�.
5)lpOverLapped.

������ ��� �а� ���� �ݴ� ����
18_1.cpp UNICODE_BASE_FILE_IO.cpp
18_2.cpp UNICODE_BASE_FILE_READ.cpp

������ �ð� ���� ������
Windows���� ���� ������ Ȯ���� �����ϴ�.
���� ��¥, ������ ��¥(����������), �׼����� ��¥(����������) ���.
���� ���� ������ ��� ����, �����ϱ� ���ؼ� ���� �Լ��� ����Ѵ�.
BOOL GetFileTime (
	HANDLE hFile, 1)
	LPFILETIME lpCreationTime, 2)
	LPFILETIME lpLastAccessTime, 3)
	LPFILETIME lpLastWriteTime 4)
);
If the function fails, the return value is zero.
1)hFile:�ð� ���� ������ ���� ��� ������ �ڵ��� �����Ѵ�.
2)lpCreationTime:������ ������ �ð��� ��� ���� FILETIME ����ü ������ �ּҰ��� �����Ѵ�. NULL ���޵� ����.
3)lpLastAccessTime:������ ������ ���� �ð��� ��� ���� FILETIME ����ü ������ �ּҰ��� �����Ѵ�. NULL ���޵� ����.
4)lpLastWriteTime:������ ������ ������ ����(���� ���� ����) �ð��� ��� ���� FILETIME ����ü ������ �ּҰ���
�����Ѵ�. NULL ���޵� ����.

�� ��°, �� ��° �׸��� �� ��° �������ڴ� FILETIME ����ü ������ �������ε�, ������ ���� ����Ǿ� �ִ�.
typedef struct _FILETIME {
	DWORD dwLowDateTime;
	DWORD dwHighDateTime;
} FILETIME, *PFILETIME;
FILETIME ����ü�� �ð� ������ ��Ÿ���� 8����Ʈ �ڷ���(DWORD*2)�̴�. �׸��� �� ����ü�� UTC ������� �ð�ǥ��.
GetFileTime �Լ��� UTC ������� �ð� ������ ���� �ش�.

UTC�� Coordinated Universal Time���� ���� �ð��� ������ ����� ���� ���ǵ� �ð�.
�̰��� 1601�� 1�� 1���� �������� 100������ ���� �������� ������ �ð��� ���.
��, ��, �ʴ� �����ϰ� UTC�� [2007, 01, 01]-[1601, 01, 01]�� 100������ ������ ȯ���� ���� UTC��.
���ݵ� �����ǰ� �ְ�, ���е��� �ִ��� ���̱� ���� Atomic Clocks�� ���.
���е��� �߽õǴ� �о߿��� ��κ� UTC ���.
�׸��� �츮�� ���ϴ� Ÿ������ �ð� ������ �����ϴ� �Լ��� �����Ѵ�.
GetFileTime �Լ��� ȣ���� ���� ������ �ð� ������ �����ϰ� �ð� ���� �����Ϸ� ��ȯ�ϴ� ����.
18_3.cpp FileTimeInformation.cpp
FileTimeToSystemTIme �Լ��� ȣ��� ����Ǵ� ���� ���� �����̴�(�ð� ������ ������ UTC����).
����Ǵ� ������ �����ϱ� ���� SYSTEMTIME ����ü�� ���� ���´�
typedef struct _SYSTEMTIME {
	WORD wYear;
	WORD wMonth;
	WORD wDayOfWeek;
	WORD wDay;
	WORD wHour;
	WORD wMinute;
	WORD wSecond;
	WORD wMilliseconds;
} SYSTEMTIME, *PSYSTEMTIME;
������ �ð� ������ ����� �� �� �����ϸ� �׸�ŭ �ð� �Ҹ� ���� �� �ִ�.
SetFileTime �Լ��� �̿��ϸ� ������ �ð� ������ ������ ���� �ִ�.

���� ������ ������
ANSIǥ�� �Լ�������
FILE* fp = fopen("test.dat", "rb");
fseek(fp, 0, SEEK_END);
DWORD sizeOfFile = ftell(fp);
fseek �Լ��� ���� �����͸� ������ �̵���Ų ����, ftell �Լ��� ȣ���� ���� ��ġ ������ ���´�.
���� �����͸� ������ �̵����ױ� ������ ���� ��ġ ������ ������ ũ�Ⱑ �ȴ�.
�ټ� ���ŷӴ�.
Windows �ý��� �Լ��� ���� ũ�⸦ ���� ����ؼ� ��ȯ�ϴ� �Լ��� �����Ѵ�.
DWORD GetFileSize (
	HANDLE hFile, 1)
	LPDWORD lpFileSizeHigh 2)
);
If the function fails and lpFileSizeHigh is non-NULL, the return value is INVALID_FILE_SIZE.
1)hFile:���� �ڵ��� �����Ѵ�. �� �ڵ��� ����Ű�� ������ ũ�� ������ ��� �ȴ�.
2)lpFileSizeHigh:��ȯ Ÿ���� ���� 4����Ʈ DWORD�� ����Ǿ� �ִ�. ���� 4GB �̻��� ���� ũ�⸦ ��ȯ������
��� ���� �Ұ����ϴ�. 4GB�̻� �Ǵ� ������ ũ�⸦ ���� �� ���Ǵ� ���� �� ��° ���������̴�.
�� �������ڸ� ���� ũ�Ⱑ 4GB�� �Ѵ� ������ ���� 4B ������ ���� �� �ִ�.

GetFileSize �Լ��� 4GB �̻��� ���Ͽ� ���� ���� 4B�� ���� 4B�� ���� �ٸ� ��θ� ���� ���� �Ѵ�.
�����ϴٸ� ���� �Լ��� ����� ����� �� �� �ִ�.
BOOL GetFileSizeEx (
	HANDLE HFile, 1)
	PLARGE_INTEGER lpFileSize 2)
);
If the function fails, the return value is zero.
1)hFile:ũ�⸦ ����� �ϴ� ������ �ڵ��� �����Ѵ�.
2)lpFileSize:���� ũ�⸦ �����ϱ� ���� ������ ������(�ּҰ�)�� ���ڷ� �����Ѵ�. PLARGE_INTEGER�� 
LARGE_INTEGER�� ������ Ÿ���̰�, LARGE_INTEGER�� ������ ���� ����Ǿ� �ִ�.
�߿��� ����� 4����Ʈ�� �ƴ� 8����Ʈ �ڷ����̶�� ��.
typedef union _LARGE_INTEGER
{
	struct {
		DWORD LowPart;
		LONG HighPart;
	};
	LONGLONG QuadPart;
} LARGE_INTEGER, *PLARGE_INTEGER;
18_4.cpp GetFileSize.cpp
����ü�� ���� �����غ���, LARGE_INTEGER�� �����ϸ� ������ �� �ִ�.
�� GetFileSizeEx �Լ��� Windows 2000�̳� WindowsXP �̻󿡼��� �����Ǵ� �Լ�.
GetFileSize �Լ��� Ȱ���� ���� ������ ���� ȣȯ���� ������ ���� �ִ�.
DWORD high4ByteFileSize = 0;
LONGLONG fileSize = GetFileSize(hFile, &high4ByteFileSize);
fileSize = fileSize | ((LONGLONG)high4ByteFileSize << 32);
LONGLONGŸ�� ��� LARGE_INTEGER�� ��� ����� ���� �ִ�.

���� Ư��(Attribute) ���� ������
���� Ư�� ������ ������ ������ ������ ���콺 ������ ��ư�� ���� �� �Ӽ��� �����ϸ� �� �� �ִ�.
�̷��� Ư�� ������ ���α׷� �ڵ�󿡼� ���� �� Ȯ���� �����ϴ�.
DWORD GetFilettributes (
	LPCTSTR lpFileName 1)
);
If the function fails, the return value is INVALID_FILE_ATTRIBUTES.
1)lpFileName:Ư�� ������ ����� �ϴ� ������ �ڵ��� �����Ѵ�. ������ Ư�� ������ ��ȯ���� ���ؼ� ��� �ȴ�.

�� �Լ��� ȣ���� ���� DWORD�� ��ȯ���� ���� �� �ִ�.
�� �ȿ� ���� Ư���� ���� �������� ��� ����ִ�.
�ϳ��� ���� ���� ������ ����ִٺ���, ��Ʈ ������ �ǹ̰� �ο��Ǿ� �ִ�.
|  ...|8| | | |4| | | |0|
FILE_ATTRIBUTE_HIDDEN�� ��FILE_ATTRIBUTE_READONLY
�ڷ����� ù ��° ��Ʈ(�����ʿ���)�� 1�� ��쿡 �ش��ϴ� �� 0x00000001�� �б� ���� Ư�� ������ ǥ���ϴµ� ���.
�� ��ȯ���� �ε��� ���� 0��° ��Ʈ�� 1�� �����Ǿ� ������, �� ������ �б� ������ ��.
�� ��° �ε��� ��Ʈ�� 1�� ��쿡 �ش��ϴ� �� 0x00000002�� ���� Ư�� ������ ǥ���ϴµ� ���.
���α׷� ������ ���̼��� ���� �б� ���� Ư���� ���� Ư���� ��ũ�� ����� ������ ���� �ִ�.
#define FILE_ATTRIBUTE_READONLY 0x00000001
#define FILE_ATTRIBUTE_HIDDEN 0x00000002
������ ���� �� �ִ� Ư�� ������ ������ �̰� �ܿ��� 12���� ������ �� �ִ�.

BOOL SetFileAttributes (
	LPCTSTR lpFileName, 1)
	DWORD dwFileAttributes 2)
);
If the funciton fails, the return value is zero.
1)lpFileName:Ư�� ������ �����ϰ��� ������ �ڵ��� �����Ѵ�.
2)dwFileAttributes:������ Ư�� ������ �����Ѵ�.

18_5.cpp Set_Get_FileAttributes.cpp
���� ���� ������ ���� ����, ���� ���� �������ٰ� �б� ����� ���� Ư�� ������ ���� ���� Ư���� �����Ѵ�.
���� ���� Ư�� ��ü�� ���ϴ� ��.
�׸��� ����� ���¸� Ȯ���Ѵ�.
GetFileAttributes�Լ��� SetFileAttributes�Լ��� �Ϲ����� ���� ó�� �Լ��� ���̸� ���δ�.
�װ��� ���� �ڵ��� �ʿ�� ���� �ʴ´ٴ� ��.
��� ��ġ���(�����γ� �����)�� �����ϴ� ������ �̸��� �ʿ�� �Ѵ�.
�̴� ������ ���� ������ ������ ������ �ش�.
��� ������ �̸����ٴ� ������ �ڵ��� Ȱ���ؾ� �ϴ� ��Ȳ�� �ξ� �� ����.

������ Ư��(Attribute) ���� �ڵ�κ��� ������ + a
���ϴ� ���� �ڵ��� �̿��ؼ� ���� ������ ��� ���� ��.
������ �ڵ��� �̿��� ���� ������ ��� ���� ���Ǵ� �Լ��� �ִ�.
BOOL GetFileInformationByHandle (
	HANDLE hFile, 1)
	LPBY_HANDLE_FILE_INFORMATION lpFileInformation 2)
);
If the function fails, the return value is zero.
1)hFile:������ ����� �ϴ� ������ �ڵ��� �����Ѵ�.
2)LPBY_HANDLE_FILE_INFORMATION:����ü BY_HANDLE_FILE_INFORMATION�� ������ Ÿ���̴�.
����� ���޵Ǵ� �ּ��� ������ ���� ������ ä������.

�� �Լ��� ���� ��� ������ ������ Ư�� ������ �ƴ϶� �ð� ������ ������ ũ�� ������ ����� �߰����� ���� �ý���
�����鵵 ���� �� �ִ�.
�׷��� �� �Լ��� ȣ���� GetFileTime�� GetFileSize�Լ��� ȣ���� ����� �� �ִ�.
typedef struct _BY_HANDLE_FILE_INFORMATION
{
	DWORD dwFileAttributes;
	FILETIME ftCreationTime;
	FILETIME ftLastAccessTime;
	FILETIME ftLastWriteTime;
	DWORD dwVolumeSerialNumber;
	DWORD nFileSizeHigh;
	DWORD nFileSizeLow;
	DWORD nNumberOfLinks;
	DWORD nFileIndexHigh;
	DWORD nFileIndexLow;
} BY_HANDLE_FILE_INFORMATION, *BY_HANDLE_FILE_INFORMATION;
18_6.cpp GetFileInformationByHandle.cpp

������ ���(Path) ���� ������
���� ���� ��� �ø��� ������ �ܰ�� ���� �̸��� ���� ���ϰ�� ������ ���� �� �� ����ϴ� �Լ��� �Ұ�.
DWORD GetFullPathName (
	LPCTSTR lpFileName, 1)
	DWORD nBufferLength, 2)
	LPTSTR lpBuffer, 3)
	LPTSTR* lpFilePart 4)
);
If the function fails, the return value is 0.
1)lpFileName:�������(Full Path)�� Ȯ���ϰ��� �ϴ� ���� �̸��� �����Ѵ�.
2)nBufferLength:������θ� ������ ���ۿ� ���� ������ ���ڿ� ���̸� �����Ѵ�. ������ ����Ʈ ���� ũ�Ⱑ �ƴ�
���� ������ ���ڿ��� �����̴�.
3)lpBuffer:������θ� ������ ������ �ּҰ��� �����Ѵ�.
4)lpFilePath:������ΰ� ���ڿ��� ���ۿ� ����� ����, ������ Ư�� ��ġ�� ����Ű�� ������ ���� ����.
������ �� ������(\) ���� ���� �ּҰ��� ����ȴ�.
18_7.cpp GetFullPathName.cpp

���� �������� �̵� - 32��Ʈ ���
ANSI ǥ�� �Լ� fseek�� �ش��ϴ� Windows �ý��� �Լ��� SetFilePointer.
64��Ʈ ȯ����� ����� ��Ȳ����(4GB �̻��� ��뷮 ������ ����� ��Ȳ), �� �Լ��� ����Ϸ��� ������ ���ŷο�
���� ����ؾ߸� �Ѵ�.
DWORD SetFilePointer (
	HANDLE hFile, 1)
	LONG lDistanceToMove, 2)
	PLONG lpDistanceToMoveHigh, 3)
	DWORD dwMoveMethod 4)
);
If the function fails and lpDistanceToMoveHigh is NULL, the return value is INVALID_SET_FILE_POINTER.
1)hFile:���� ������ ��ġ�� �̵���ų ��� ������ �ڵ��� �����Ѵ�.
2)lDistanceToMove:�̵���ų �Ÿ��� �����Ѵ�. ���࿡ 64��Ʈ ������� �����ϸ� ���� 4����Ʈ ������ ǥ���ϰ� �ȴ�.
3)lDistanceToMoveHigh:64��Ʈ ����� ��뷮 ���Ͽ����� �ǹ̸� ���Ѵ�. ���� 4����Ʈ ������ ǥ���ϰ� �ȴ�.
32��Ʈ ��ݿ����� NULL�� �����Ѵ�.
4)dwMoveMethod:���� ������ �̵� �� ������ �Ǵ� ��ġ�� �����Ѵ�. ������ ���� �պκ��� �������� �����ϰ� �� ������
FILE_BEGIN�� ���ڷ� �����Ѵ�. fseek �Լ��� SEEK_SET�� �ش��Ѵ�. ���� �������� ���� ��ġ�� �������� �����ϰ���
�� ������ FILE_CURRENT�� ���ڷ� �����Ѵ�. fseek �Լ��� SEEK_CUR�� �ش��Ѵ�. ������ ���� ������ �κ���
�������� �� ������ FILE_END�� ���ڷ� �����Ѵ�. fseek �Լ��� SEEK_END�� �ش��Ѵ�.

32��Ʈ �ý��ۿ��� 4GB�� ���� �ʴ� ������ �ٷ� ��.
18_8.cpp SetFilePointer_32BIT_VERSION.cpp
������ �ִ� (2^32-2)Bũ���� ���ϱ��� �������� �ϴ�.
SetFilePointer�� �Լ� ȣ�� ���� �� ����� ��ġ�� ���� �����Ͱ��� ��ȯ�Ѵ�.
���� ���� ������ ��ġ �߿��� �Ʒ� 4����Ʈ�� �ش��ϴ� ���� ��ȯ�Ѵ�.
���� �߻��� ��ȯ�Ǵ� �� INVALID_SET_FILE_POINTER�� -1�̰� 32��Ʈ�� ǥ���ϸ� 0xFFFFFFFF, 2^32-1�̴�.
���� ������ ��ġ�� 0�̶�� 0x00000000�� ��ȯ�� ���̰�, 4GB�̰�, ���� �����Ͱ� SetFilePointer �Լ� ȣ����
���ؼ� �� ������ ���� ����Ű�� �Ǿ��ٸ� 2^32-1�� ��ȯ�ȴ�.
�׷��� 2^32-1�� 10������ -1�� �ش��ϱ� ������, INVALID_SET_FILE_POINTER�� ������ ����� ����.
�׷��� �ᱹ ũ�Ⱑ �� 4GB�� ��쿡�� ��뷮 ���Ϸ� �����ϰ� �ٸ� ����� ����.
�׷��� 32��Ʈ ��ݿ��� ���� ������ �ִ� ���� ũ�Ⱑ 2^32-2�� ��.

���� �������� �̵� - 64��Ʈ ���
18_9.cpp SetFilePointer_64BIT_VERSION.cpp
32��Ʈ���(4GB�� �ȳѴ�) �����˻� �ڵ�
if (dwPtr == INVALID_SET_FILE_POINTER) {}
64��Ʈ���(4GB �̻�) �����˻� �ڵ�
if ((dwPtrLow == INVALID_SET_FILE_POINTER) && (GetLastError() != NO_ERROR)) {}
64��Ʈ ��ݿ����� GetLastError�� ���� ���� ������ �߻��ϴ��� Ȯ��.
4GB �̻��� ��뷮 ������ �ٷ�� ������ ������ ��ġ�� 2^32-1�� ��ġ�� ���� �� �ִ�.
�׷��� ���� ������ ��ġ�� 0xFFFFFFFF�� �Ǵµ� INVALID_SET_FILE_POINTER�� �����ϴ�.
�׷��� SetFilePointer �Լ��� ��ȯ������ ������ ���� �߻� ������ Ȯ���� �� ����.
�ݵ�� GetLastError �Լ� ȣ���� ���ؼ� ��ȯ���� �ǹ̸� ��Ȯ�� �ľ��ؾ� �Ѵ�.

02 ���͸� ���� �Լ� �� �׹��� �Լ���
���͸��� ������ �Ҹ�
BOOL CreateDirectory (
	LPCTSTR lpPathName, 1)
	LPSECURITY_ATTRIBUTES lpSecurityAttributes 2)
);
If the function fails, the return value is zero.
1)lpPathName:�����ϰ��� �ϴ� ���͸� �̸��� �����Ѵ�.
2)lpSecurityAttributes:���� �Ӽ��� ������ �� ���ȴ�. ACL�� ����� �ʾ����Ƿ� �⺻������ NULL�� ������
����Ʈ �Ӽ��� ����.
BOOL RemoveDirectory (
	LPCTSTR lpPathName 1)
);
If the function fails, the return value is zero.
1)lpPathName:�Ҹ��ϰ��� �ϴ� ���͸� �̸��� �����Ѵ�.
18_10.cpp CreateDeleteDirectory.cpp
��ũ�θ� 1�� �� ������ ������ �� ������ �Ѵ�.
0���� �����ؼ� �ٽ� �ѹ� ������ �� ������ �Ѵ�.

���� ���͸�, �ý��� ���͸� �׸��� Windows ���͸�
���� ���͸�(Current Directory)
"�ʱ⿡�� ���α׷��� Load�� ���͸��� �����Ǹ�, ���� ���� �����ϴ�."
������ �Ǵ� ���� ���� ���͸��̴�(ǥ�� �˻� ��� �� �ϳ��μ�).

Visual Studio���� �����ϸ� ���� ���͸��� ������Ʈ ������ �����ϴ� ��ġ�� ����.

���� ���͸��� �����ϰų� �����ϴ� �� ���Ǵ� �Լ���.
DWORD GetCurrentDirectory (
	DWORD nBufferLength, 1)
	LPTSTR lpBuffer 2)
);
If the function fails, the return value is zero.
1)nBufferLength:�� ��° ���ڷ� ���޵� ������ ���̸� �����Ѵ�.
2)pBuffer:���� ���͸� ������ ������ ������ �ּҰ��� �����Ѵ�.
BOOL SetCurrentDirectory (
	LPCTSTR lpPathName 1)
);
If the function fails, the return value is zero.
1)lpPathName:�����ϰ��� �ϴ� ���� ���͸� ������ �����Ѵ�.
18_11.cpp CurrentDirectory.cpp

�ý��� ���͸�(System Directory) & Windows ���͸�
�ý��� ���͸��� ���� ���̺귯��(DLL) �� ����̹� ����ó�� Windows �ý��ۿ� �߿��� ���ϵ��� �����ϴ� ��ġ�̰�,
Windows ���͸��� �ʱ�ȭ �� �������ϵ��� �����ϴ� ��ġ�̴�.
��� �ý��� ���͸��� ��� Windows ���͸����� �� ��ġ�� �ƴ� ���� �߿��ϴ�.
�׸��� �̷��� ���͸����� ���� ���͸��� �޸� ������ �Ұ����ϴ�.
������ ���� �� �ֱ� ������ Windows �ü���� Windows ���͸��� �ý��� ���͸� ������ ����.
�ý��� ���͸��� Windows ���͸��� ��ġ ������ Ȯ���ϱ� ���� ���Ǵ� �Լ���.
UINT GetSystemDirectory (
	LPTSTR lpBuffer, 1)
	UINT uSize 2)
);
If the function fails, the return value is zero.
1)lpBuffer:�ý��� ���͸� ������ ������ ������ �ּҰ��� �����Ѵ�.
2)uSize:ù ��° ���ڷ� ���޵� ������ ���̸� �����Ѵ�.
UINT GetWindowsDirectory (
	LPTSTR lpBuffer, 1)
	UINT uSize 2)
);
If the function fails, the return value is zero.
1)lpBuffer:Windows ���͸� ������ ������ ������ �ּҰ��� �����Ѵ�.
2)uSize:ù ��° ���ڷ� ���޵� ������ ���̸� �����Ѵ�.
18_12.cpp System_Windows_Dir.cpp

���͸����� ���� ã��
������ ��ġ ������ ����� �� ��, Ư�� ���͸� ���� �����ϴ� ���� ������ ����� �� �� ����ϴ� �Լ���.
���ڿ��� ������ ��ο� Ư�� ������ �����ϴ��� Ȯ���ϴ� �뵵�� ����� �� �ִ� �Լ�.
���� �̸��� ���ڷ� �ؼ� �ش� ������ ����Ǿ� �ִ� ������� ������ ����� �� ���� ����� ���� �ִ�.(���ѵ� ����)
DWORD SearchPath (
	LPCTSTR lpPath, 1)
	LPCTSTR lpFileName, 2)
	LPCTSTR lpExtension, 3)
	DWORD nBufferLength, 4)
	LPTSTR lpBuffer, 5)
	LPTSTR* lpFilePart 6)
);
If the function fails, the return value is zero.
1)lpPath:��� ��θ� �����Ѵ�. �� ���ڸ� ���� ������ ��ο��� ������ ã�� �ȴ�. ���ڷ� NULL�� ���޵Ǹ�,
ǥ�� �˻� ��� ������ ������ ã�� �ȴ�.
1_���� ���� ���α׷��� Load�� ����(���������� �����ϴ� ���͸�)
2_���� ���͸�
3_�ý��� ���͸�
4_Windows ���͸�
5_���������� ȯ�溯�� PATH�� ��ϵ� ���͸���
2)lpFileName:ã���� �ϴ� ���� �̸�.
3)lpExtension:Ȯ���ڸ� �����ϴ� ���ڷμ� ù ��° ���ڴ� �ݵ�� '.'���� �����ؾ� �Ѵ�.
lpFileName�� Ȯ���ڸ� �����ϰ� �ְų� Ȯ���ڸ� ������ �� �ʿ䰡 ���� ������ NULL�� ����.
4)nBufferLength:������θ��� ������ ������ ���̸� �����Ѵ�.
5)lpBuffer:������θ��� ������ ������ �ּҸ� �����Ѵ�.
6)lpFilePart:�Լ� ȣ�� ����� ��� �Ǵ� ������θ�(lpBuffer�� ������ ���ۿ� ����Ǵ� ������θ�)�� ����������
���� �̸��� �߰��ȴ�. �� �������ڸ� ���� ���� �̸��� ����� ��ġ ����(�����Ͱ�)�� ��� �ȴ�.

ȯ�溯�� PATH�� ��ϵ� ������ [������]->[�ý���]->[���]->[ȯ�溯��]�� �� Ȯ���� �� �ִ�.
Administrator�� ���� ����� ������ Administrator�� �α��� ���� ���� �߰��� �ݿ��Ǵ� �������̴�.

18_13.cpp SearchPath.cpp
���������Ʈ�� �������Ϸμ� �ý��� ���͸��� ����Ǿ� �ִ� CMD.EXE�� �Է��� Ȯ���غ���.

SearchPath���� ������ �Լ��� 3���� �ִµ�, �� �Լ����� �ϳ��� ����� �ϼ��ϱ� ���� �Բ� ���Ǿ�� �Ѵ�.
ù ��°�� �ʿ��� �Լ��� FindFirstFile�̴�.
�� �Լ��� ù ��° �������ڸ� ���� ���޵Ǵ� ���͸��� ���� �̸��� ���� ���յǴ� ������ ã��, ������ ������
�� ��° �������ڰ� ����Ű�� ������ �����Ѵ�.
HANDLE FindFirstFile (
	LPCTSTR lpFileName, 1)
	LPWIN32_FIND_DATA lpFindFileData 2)
);
If the function fails, the return value is INVALID_HANDLE_VALUE.
1)lpFileName:�����̳� ���͸� �̸��� �����Ѵ�. ������ ������ �ٰŷ� ����(Ȥ�� ���͸�) ������ ��� �ȴ�.
2)lpFindFileData:�߰ߵ� �����̳� ���͸� ������ ���� WIN32_FIND_DATA ����ü ������ �ּҰ��� �����Ѵ�.

FindFirstFile �Լ��� ��ȯ Ÿ���� HANDLE�̴�.
�̴� �˻��� ���� �ڵ��̹Ƿ� ������ �������� �� ��� �Ǵ� �ڵ�� �ν��ϸ� �ȵȴ�.
�� �Լ��� ���ؼ��� ���ǿ� �´� ���� �� ���� ù ��° �˻��� ���� ������ ���� �� �ִ�.
���� ���ǿ� �´� �� �ٸ� ���� ������ ��� ���� �߰����� �۾��� FindFirstFile �Լ��� ��ȯ�� �ڵ�� FindNextFile.
BOOL FindNextFile (
	HANDLE hFindFile, 1)
	LPWIN32_FIND_DATA lpFindFileData 2)
);
If the function fails, the return value is zero.
1)hFindFile:FindFirstFile�Լ� ȣ���� ���� ���� �ڵ��� �����Ѵ�. �� �ڵ��� ����Ű�� Ŀ�� ������Ʈ����
ã���� �ϴ� ����(���͸� ����) ������ �˻��� �̷��� ��ġ ������ ��� �ִ�.
���� �� �������ڸ� ���� ���� ������ ã�� �� �ִ�.
2)lpFindFileData:�߰ߵ� �����̳� ���͸��� ������ ���� WIN32_FIND_DATA ����ü ������ �ּҰ��� �����Ѵ�.

FindFirstFile("3RDPARTY���� N�ڷ� �����ϴ� ���͸�")---->Handle---->Kernel Object
----->3RDPARTY���� N�ڷ� �����ϴ� ���͸� NETSCAPE�� ã��.
FindFirstFile �Լ� ȣ���� ���� ������ Ŀ�� ������Ʈ�� ��� �ִ� ������ ���͸� NETSCAPE�� ���� ��.
���� �̾ FindNextFile �Լ��� ȣ���ϸ�, ������ �����ϴ� ���͸��� ���� ������ ä������ �ȴ�.
�� ���Ŀ��� ������ N���� �����ϴ� ���͸��� �ִٸ� FindNextFile �Լ� ȣ���� ���� Ŀ�� ������Ʈ�� �� �ٸ�
���͸� ������ ���� �� �ִ�.

FindFirstFile �Լ��� ��������� Ŀ�� ������Ʈ�� �����Ͽ���.
���� �˻��� ������ ���� �Լ��� �̿��� ���ҽ��� ��ȯ�ؾ� �Ѵ�.
BOOL FindClose (
	HANDLE hFindFile 1)
);
If the function fails, the return value is zero.
1)hFindFile:FindFirstFile �Լ��� ���� ���� �ڵ��� ��ȯ�Ѵ�.

typedef struct _WIN32_FIND_DATA {
	DWORD dwFileAttributes;
	FILETIME ftCreationTime;
	FILETIME ftLastAccessTime;
	FILETime ftLastWriteTime;
	DWORD nFileSizeHigh;
	DWORD nFileSizeLow;
	DWORD dwReserved0;
	DWORD dwReserved1;
	TCHAR cFileName[MAX_PATH];
	TCHAR cAlternateFileName[14];
} WIN32_FIND_DATA, *PWIN32_FIND_DATA;
dwReserved1�� ���ุ �Ǿ����� �� ������ �ʴ� ����̰�, dwReserved0�� dwFileAttributes�� ���� ����
�ǹ� �ִ� ���� ä�����⵵ �Ѵ�.
18_14.cpp ListDirectoryFileList.cpp

�̰͸��� �˰� ���ô�
1. ���� �⺻�� �Ǵ� ������ �������� �Է°� ���
2. 4GB �̻� ��뷮 ���� ó��
64��Ʈ�ý��ۿ���
3. ǥ�� �˻� ���.
Windows �ý����� ������ ã�� �� �� ��θ� �������� �˻��� �Ѵ�.
4. �����ϴ� ����� �˰� ����
��� ����� �����Ǵ��� ���

*/