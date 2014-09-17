#ifndef _PROFILE_FRAME_H_
#define _PROFILE_FRAME_H_

#include <FBase.h>
#include <FUi.h>


class ProfileFrame
	: public Tizen::Ui::Controls::Frame
{
public:
	ProfileFrame(void);
	virtual ~ProfileFrame(void);

public:
	virtual result OnInitializing(void);
	virtual result OnTerminating(void);
};

#endif  // _PROFILE_FRAME_H_
