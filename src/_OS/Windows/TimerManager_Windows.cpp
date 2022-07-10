#include "TimerManager_Windows.hpp"
#include "Timer_Windows.hpp"
#include <windows.h>
void TimerManager_Windows::activateManager() {
	timerqueue = CreateTimerQueue();
}
void TimerManager_Windows::terminateManager() {
	DeleteTimerQueue(timerqueue);
}

VOID CALLBACK TimerCallbackWin(PVOID lpParameter, BOOLEAN TimerOrWaitFired) {
	const Timer_Windows* timerWin = (const Timer_Windows*)lpParameter;
	return timerWin->callback(timerWin->params);
}
Timer* TimerManager_Windows::newTimer(TimerCallback callback, void* params, int dueTime, int period) {
	Timer_Windows* ret = new Timer_Windows(*this, params, callback);
	CreateTimerQueueTimer(&ret->handle, timerqueue, TimerCallbackWin, ret, dueTime, period, WT_EXECUTEDEFAULT);
	return ret;
}
void TimerManager_Windows::destroyTimer(Timer_Windows* timer) {
	DeleteTimerQueueTimer(timerqueue, timer->handle, NULL);
	delete timer;
}