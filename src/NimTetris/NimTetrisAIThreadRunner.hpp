#ifndef _NimTetrisAIThreadRunnerHeader_
#define _NimTetrisAIThreadRunnerHeader_
#include "NimTetrisAI.hpp"
#include "ThreadManager.hpp"
class NimTetrisAIThreadRunner
{
	struct AIThread {
	public:
		bool isRunning;
		Thread* pThread;
		NimTetrisAI* pAI;

	public:
		AIThread() : isRunning(false), pThread(nullptr) {}
	};

private:
	ThreadManager& threadManager;
	AIThread thread;

public:
	static void NimTetrisAIThread(void* pAI);

public:
	void createAIThread(NimTetrisAI* pAI);
	bool isThraeding();
	void closeThreadHandle();

public:
	NimTetrisAIThreadRunner(ThreadManager& _threadManager) : threadManager(_threadManager) {};
};
#endif