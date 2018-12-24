#include"DxLib.h"
#include"Singleton.h"
#include"s.h"

const int WIDTH = 800;
const int HEIGHT = 800;

int main() {
	SetGraphMode(WIDTH, HEIGHT, 32);
	ChangeWindowMode(TRUE), DxLib_Init(), SetDrawScreen(DX_SCREEN_BACK);

	sMgr inst(WIDTH, HEIGHT);
	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0) {
		Mouse::Instance()->Update();
		Keyboard::Instance()->Update();
		inst.DO();
	}
	DxLib_End();
	return 0;
}