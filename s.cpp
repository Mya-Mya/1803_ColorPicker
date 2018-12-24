#include "s.h"
#include"Help.h"
#include"Work.h"
#include"DxLib.h"

bs::bs(csMgr *in, int Width, int Height)
{
}



sMgr::sMgr(int Width, int Height)
{
	WIDTH = Width;
	HEIGHT = Height;
	inst = (bs*)new Work(this,Width,Height);
}

void sMgr::DO()
{
	if (next != sNone) {
		delete inst;
		switch (next) {
			case sHelp:
				inst = (bs*) new Help(this,WIDTH,HEIGHT);
				break;
			case sWork:
				inst = (bs*)new Work(this,WIDTH,HEIGHT);
				break;
		}
		next = sNone;
	}
	inst->DO();
}

void sMgr::sChange(es in)
{
	next = in;
}


