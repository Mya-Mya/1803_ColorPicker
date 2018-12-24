#pragma once
#include"s.h"

class Help : public bs {
private:
	csMgr *maker;
public:
	Help(csMgr *in, int Width, int Height);
	void DO() override;
};