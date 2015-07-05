#pragma once

class FCommandListener
{
public:
#pragma message("in fcommandlistener")
	FCommandListener(void);
	virtual ~FCommandListener(void){};
	virtual void Command(int command, int extra)=0;
};
