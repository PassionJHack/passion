/*
 * MockLocationListener.h
 *
 *  Created on: Sep 17, 2014
 */

#ifndef MOCKLOCATIONLISTENER_H_
#define MOCKLOCATIONLISTENER_H_

#include <FBase.h>
#include <FIo.h>
#include <FApp.h>
#include "DeviceControl.h"

class MockLocationListener
	: public Tizen::Base::Runtime::ITimerEventListener
{
public:
	MockLocationListener();
    ~MockLocationListener();

	void OnTimerExpired(Tizen::Base::Runtime::Timer& timer);
	void StartApp();

private:
	int __count;
	Tizen::Base::Runtime::Timer __timer;
	DeviceControl device;
	Tizen::Io::Database *__pProfileDatabase;
};


#endif /* MOCKLOCATIONLISTENER_H_ */
