#include "ThreadManager_Windows.hpp"
#include "Thread_Windows.hpp"
#include <windows.h>
DWORD WINAPI ThreadProc(_In_ LPVOID lpParameter) {
	const Thread_Windows* threadWin = (const Thread_Windows*)lpParameter;
	threadWin->callback(threadWin->params);
	return 0;
}
Thread* ThreadManager_Windows::newThread(ThreadCallback callback, void* params) {
	Thread_Windows* ret = new Thread_Windows(*this, params, callback);
	ret->handle = CreateThread(NULL, 0, ThreadProc, ret, 0, NULL);
	return ret;
}