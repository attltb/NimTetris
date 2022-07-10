#include "NimTetrisAIThreadRunner.hpp"
void NimTetrisAIThreadRunner::NimTetrisAIThread(void* pAIThread) {
	AIThread& thread = *((AIThread*)pAIThread);
	thread.isRunning = true;
	thread.pAI->applyAIPlay();
	thread.isRunning = false;
}
void NimTetrisAIThreadRunner::createAIThread(NimTetrisAI* pAI) {
	thread.pAI = pAI;
	thread.pThread = threadManager.newThread(NimTetrisAIThread, &thread);
}
bool NimTetrisAIThreadRunner::isThraeding() {
	return thread.isRunning;
}
void NimTetrisAIThreadRunner::closeThreadHandle() {
	thread.pThread->free();
}