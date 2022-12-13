//#define NOMINMAX
//#include <windows.h>

//extern "C" int __stdcall GetTickCount();
//int __start;
//#define t(name, stuff)\
//	__start = GetTickCount();\
//	stuff;\
//	printf("%s: %d ms\n", name, GetTickCount() - __start);

#ifdef __cplusplus

/*__if_not_exists(LARGE_INTEGER)
{
	struct LARGE_INTEGER { __int64 QuadPart; };
	extern "C" int __stdcall QueryPerformanceCounter(LARGE_INTEGER* count);
	extern "C" int __stdcall QueryPerformanceFrequency(LARGE_INTEGER* freq);
}*/

/*#define ms_(name, stuff)\
	LARGE_INTEGER __begin, __end, __freq;\
	QueryPerformanceCounter(&__begin);\
	stuff;\
	QueryPerformanceCounter(&__end);\
	QueryPerformanceFrequency(&__freq);\
	printf("%s: %Id ms\n", name, (__end.QuadPart - __begin.QuadPart) * 1000 / __freq.QuadPart);

#define mks(name, stuff)\
	LARGE_INTEGER __begin, __end, __freq;\
	QueryPerformanceCounter(&__begin);\
	stuff;\
	QueryPerformanceCounter(&__end);\
	QueryPerformanceFrequency(&__freq);\
	printf("%s: %Id mks\n", name, (__end.QuadPart - __begin.QuadPart) * 1'000'000 / __freq.QuadPart);*/

#include <chrono>
#define ms(name, stuff)\
	__if_not_exists(_begin){ std::chrono::steady_clock::time_point _begin, _end; }\
	_begin = std::chrono::steady_clock::now();\
	stuff;\
	_end = std::chrono::steady_clock::now();\
	printf("%s: %Id ms\n", name, std::chrono::duration_cast<std::chrono::milliseconds>(_end - _begin).count());

//#define ms(name, stuff) stuff



/*__declspec(selectany) __int64 __counter1;

#define t1(stuff)\
	LARGE_INTEGER __begin, __end;\
	QueryPerformanceCounter(&__begin);\
	stuff;\
	QueryPerformanceCounter(&__end);\
	__counter1 += __end.QuadPart - __begin.QuadPart;

#define ms1(name)\
	LARGE_INTEGER __freq;\
	QueryPerformanceFrequency(&__freq);\
	printf("%s: %Id ms\n", name, __counter1 * 1000 / __freq.QuadPart);*/

#endif // __cplusplus
