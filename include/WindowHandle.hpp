#ifndef _WindowHandleHeader_
#define _WindowHandleHeader_
#include <memory>
#include <string>
class WindowHandle_ {
public:
	virtual void msgCustom(int kind, void* params) = 0;
	virtual void msgError(std::string msgText) = 0;
	virtual void exit() = 0;

public:
	virtual ~WindowHandle_() {};
};
class WindowHandle {
	std::shared_ptr<WindowHandle_> pHandle;

public:
	void msgCustom(int kind, void* params) {
		return pHandle->msgCustom(kind, params);
	}
	void msgError(std::string msgText) {
		return pHandle->msgError(msgText);
	}
	void exit() {
		return pHandle->exit();
	}

public:
	WindowHandle(std::shared_ptr<WindowHandle_> _pHandle) : pHandle(_pHandle) {}
};
#endif