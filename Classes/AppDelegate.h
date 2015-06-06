#ifndef  _APP_DELEGATE_H_
#define  _APP_DELEGATE_H_

#include "Common.h"

class  AppDelegate : private cocos2d::Application {
public:
	AppDelegate();
	virtual ~AppDelegate();
	virtual bool applicationDidFinishLaunching();
	virtual void applicationDidEnterBackground();
	virtual void applicationWillEnterForeground();
};

#endif // _APP_DELEGATE_H_

