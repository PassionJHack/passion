/*
 * MockLocationListener.cpp
 *
 *  Created on: Sep 17, 2014
 */
#include "MockLocationListener.h"

using namespace Tizen::Base;
using namespace Tizen::Base::Runtime;

MockLocationListener::MockLocationListener()
{
	__count = 3;
	__timer.Construct(*this);
}

MockLocationListener::~MockLocationListener()
{
}

void
MockLocationListener::OnTimerExpired(Timer& timer)
{
	AppLogTag("LocationMonitor", "MockLocationListener::OnTimerExpired");
	__count--;
	if (__count == 0)
	{

	}
	else
	{
		timer.Start(10*1000);
	}

	AppLog("LocationMonitor", "LocationMonitor: Current count: %d\n", __count);
}


void
MockLocationListener::StartApp()
{
	AppLogTag("LocationMonitor", "MockLocationListener::StartApp");
	__timer.Start(10*1000);
}



