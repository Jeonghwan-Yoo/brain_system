//DDL용 헤더파일
//이는 헤더파일 중복 포함 시 발생하는 문제를 막기 위한 선언이다.
//첫 번째 포함 시 매크로 CALCULATOR_H__가 정의되고 두 번째 포함 시에는 건너 뛰어 문제가 발생하지 않는다.
#ifndef __CALCULATOR_H__
#define __CALCULATOR_H__

//__cplusplus는 Visual Stdio가 C++컴파일러로 컴파일할 때 기본적으로 정의하는 매크로이다.
//따라서 이 매크로의 정의 유무를 통해 C++컴파일러가 사용되는지, C컴파일러가 사용되는지를 알 수 있다.
#ifdef __cplusplus
extern "C"
{
#endif

//_COMPLING_DLL_CALCULTOR가 정의되면 매크로 LIBSPEC가 export 선언의 역할을 하고
//그렇지 않으면 import 선언의 역할을 하도록 구성.
//이를 기반으로 뒤에 함수가 선언되어 있다.
//따라서 DLL 작성 시에는 매크로 _COMPLING_DLL_CALCULATOR를 정의.
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