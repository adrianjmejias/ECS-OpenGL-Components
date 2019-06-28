#pragma once
#include <AntTweakBar/AntTweakBar.h>
#include <vector>

class ITweakable
{
public:
	ITweakable()
	{
	}

	~ITweakable()
	{
	}
	virtual void DebugUI(TwBar*, unsigned int) =0;

private:

};
