/*
 * MockLocationListener.cpp
 *
 *  Created on: Sep 17, 2014
 */
#include "MockLocationListener.h"

using namespace Tizen::Base;
using namespace Tizen::Base::Runtime;
using namespace Tizen::Io;
using namespace Tizen::App;

MockLocationListener::MockLocationListener()
{
	__count = 2;
	__timer.Construct(*this);


	__pProfileDatabase = new Database();
	//String db = App::GetInstance()->GetAppDataPath() + L"profile.db";

	String dbName(App::GetInstance()->GetAppDataPath() + L"profile.db");
	__pProfileDatabase->Construct(dbName, "a+");



}

MockLocationListener::~MockLocationListener()
{
}

void
MockLocationListener::OnTimerExpired(Timer& timer)
{
	__count--;
	if (__count == 0)
	{

	  device.WifiActivate();

		 device.setVolum(15);
	}
	else
	{
		 device.WifiDeactivate();
		 device.setVolum(0);
		 timer.Start(10*1000);
	}
}


void
MockLocationListener::StartApp()
{
	__timer.Start(10*1000);
}



