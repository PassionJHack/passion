#include "LocationMonitorApp.h"
#include <new>

using namespace Tizen::Base;
using namespace Tizen::Base::Collection;

#ifdef __cplusplus
extern "C"
{
#endif

_EXPORT_ int OspMain(int argc, char* pArgv[]);

//The entry function of Tizen C++ application called by the operating system.
int
OspMain(int argc, char* pArgv[])
{
	result r = E_SUCCESS;

	AppLog("Application started.");
	ArrayList args;
	args.Construct();
	for (int i = 0; i < argc; i++)
	{
		args.Add(*(new (std::nothrow) String(pArgv[i])));
	}

	r = Tizen::App::ServiceApp::Execute(LocationMonitorApp::CreateInstance, &args);
	if (IsFailed(r))
	{
		AppLogException("Application execution failed-[%s].", GetErrorMessage(r));
		r &= 0x0000FFFF;
	}

	args.RemoveAll(true);

	AppLog("Application finished.");

	return static_cast< int >(r);
}
#ifdef __cplusplus
}
#endif
