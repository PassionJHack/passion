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


/*
 DbEnumerator* pEnum;
	    DbStatement* pStmt;

	    pStmt = __pProfileDatabase->CreateStatementN(L"SELECT title, "
	    		"year, month, day, hour, minute, "
	    		"year2, month2, day2, hour2, minute,2 "
	    				"latitude, longitude, volume, wifi, memo FROM profile WHERE id = ?");
	    Integer* itemId = static_cast<Integer*>(__pIndexList.GetAt(index));
	    pList->Add(*new (std::nothrow) Integer(index));
	    r = pStmt->BindInt(0, itemId->ToInt());
	    pEnum = __pProfileDatabase->ExecuteStatementN(*pStmt);
	    if (pEnum) {
	        String title;
	        pEnum->MoveNext();
	        r = pEnum->GetStringAt(0, title);
		    pList->Add(*new (std::nothrow) String(title));
		    int intItem;
		    double item;
	        r = pEnum->GetIntAt(1, intItem);	//year
		    pList->Add(*new (std::nothrow) Integer(intItem));
	        r = pEnum->GetIntAt(2, intItem);	//month
		    pList->Add(*new (std::nothrow) Integer(intItem));
	        r = pEnum->GetIntAt(3, intItem);	//day
		    pList->Add(*new (std::nothrow) Integer(intItem));
	        r = pEnum->GetIntAt(4, intItem);	//hour
		    pList->Add(*new (std::nothrow) Integer(intItem));
	        r = pEnum->GetIntAt(5, intItem);	//minute
		    pList->Add(*new (std::nothrow) Integer(intItem));
	        r = pEnum->GetIntAt(6, intItem);	//year2
		    pList->Add(*new (std::nothrow) Integer(intItem));
	        r = pEnum->GetIntAt(7, intItem);	//month2
		    pList->Add(*new (std::nothrow) Integer(intItem));
	        r = pEnum->GetIntAt(8, intItem);	//day2
		    pList->Add(*new (std::nothrow) Integer(intItem));
	        r = pEnum->GetIntAt(9, intItem);	//hour2
		    pList->Add(*new (std::nothrow) Integer(intItem));
	        r = pEnum->GetIntAt(10, intItem);	//minute2
		    pList->Add(*new (std::nothrow) Integer(intItem));
	        r = pEnum->GetDoubleAt(11, item);	//latitude
		    pList->Add(*new (std::nothrow) Double(item));
	        r = pEnum->GetDoubleAt(12, item);	//longitude
		    pList->Add(*new (std::nothrow) Double(item));
	        r = pEnum->GetIntAt(13, intItem);	//volume
		    pList->Add(*new (std::nothrow) Integer(intItem));
	        r = pEnum->GetIntAt(14, intItem);	//wifi
		    pList->Add(*new (std::nothrow) Integer(intItem));
	        r = pEnum->GetStringAt(15, title);	//memo
		    pList->Add(*new (std::nothrow) String(title));
	        delete pEnum;
	    }
	    delete pStmt;

 */
void
MockLocationListener::OnTimerExpired(Timer& timer)
{
	int volume;
	int wifi;

	AppLogTag("LocationMonitor", "MockLocationListener::OnTimerExpired");
	__count--;
	if (__count == 0)
	{

	  device.WifiActivate();

		 device.setVolum(15);
	}
	else
	{

		 AppLog("Device", "%d %d", volume , wifi);

		 device.WifiDeactivate();

		 device.setVolum(0);

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



