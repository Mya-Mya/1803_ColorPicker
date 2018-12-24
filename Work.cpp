#include "Work.h"
#include"DxLib.h"
#include"Windows.h"
#include"Singleton.h"
#include<string>
using namespace std;

Work::Work(csMgr *in, int Width, int Height):bs(in,Width,Height)
{
	maker = in;
	WIDTH = Width;
	HEIGHT = Height;
	pPrev = new Prev(Width, Height);
}

void Work::DO()
{
	if (!ImageLoad) ReadImage();
	DrawRotaGraph(WIDTH / 2, HEIGHT / 2,ExtRate,0, Image, FALSE);
	pPrev->SetPos(Mouse::Instance()->GetX(), Mouse::Instance()->GetY());
	pPrev->DRAW();

	if (Keyboard::Instance()->Get(KEY_INPUT_D) == 1) ImageLoad = false;
	if (Keyboard::Instance()->Get(KEY_INPUT_C) == 1) pPrev->SetMode(PrevMode_Code);
	if (Keyboard::Instance()->Get(KEY_INPUT_R) == 1) pPrev->SetMode(PrevMode_RGB);
}

void Work::ReadImage()
{
	InitGraph();

	{
		TCHAR szPath[MAX_PATH];
		GetCurrentDirectory(MAX_PATH, szPath);
		TCHAR szFile[MAX_PATH]="";

		OPENFILENAME ofn;
		ZeroMemory(&ofn, sizeof(ofn));
		ofn.lStructSize = sizeof(OPENFILENAME);
		ofn.hwndOwner=GetMainWindowHandle();
		ofn.lpstrInitialDir = szPath;
		ofn.lpstrFile = szFile;
		ofn.nMaxFile = MAX_PATH;
		ofn.lpstrFilter = TEXT("画像ファイル(*.jpg,*.png)\0*.jpg;*.png\0")
							TEXT("すべてのファイル(*.*)\0*.*\0");
		ofn.lpstrTitle = TEXT("読み込む画像を選択");
		ofn.Flags = OFN_FILEMUSTEXIST;

		GetOpenFileName(&ofn);	
		Image=LoadGraph(szFile);
	}//ファイルの選択と読み込み
	
	{
		int PicX, PicY;
		GetGraphSize(Image, &PicX, &PicY);
		ExtRate = (double)WIDTH / (double)PicX;
		if ((double)HEIGHT / (double)PicY < ExtRate) ExtRate = ((double)HEIGHT / (double)PicY);
	}//画像サイズと拡大率計算

	ImageLoad = true;
}

void Work::GetWindowSize(int Width, int Height)
{
	WIDTH = Width;
	HEIGHT = Height;
}

Prev::Prev(int Width, int Height)
{
	WIDTH = Width, HEIGHT = Height;
	FONT = CreateFontToHandle("メイリオ", 20, 4, DX_FONTTYPE_NORMAL);
}

#define Prev_Xdis 100
void Prev::DRAW()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
	
	DrawBox(x-Prev_Xdis, y-90, x , y , GetColor(255, 255, 255), TRUE);
	DrawFormatStringToHandle(x- Prev_Xdis, y-85, GetColor(0, 0, 0), FONT, Mes.c_str());
	
	DrawLine(x - Prev_Xdis, y - 85, x - Prev_Xdis + Prev_Xdis*R / 255, y - 85, GetColor(0,0,0), 2);
	DrawLine(x - Prev_Xdis, y - 55, x - Prev_Xdis + Prev_Xdis*G / 255, y - 55, GetColor(0, 0, 0), 2);
	DrawLine(x - Prev_Xdis, y - 25, x - Prev_Xdis + Prev_Xdis*B / 255, y - 25, GetColor(0, 0, 0), 2);

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

	if (CheckHitKey(KEY_INPUT_SPACE) == 1)
		DrawCircle(x, y, 12, Code, TRUE);
}

void Prev::SetPos(int inx, int iny)
{
	//コード取得
	Code=GetPixel(inx, iny);
	GetColor2(Code, &R, &G, &B);
	//表示する座標取得
	x = inx;
	y = iny;
	if (x - Prev_Xdis <0)x = Prev_Xdis;
	if (y - 90 < 0)y =  90;
	//RGB取得

	//メッセージ生成
	switch(mode){
	case PrevMode_Code:
		Mes =  to_string(Code);
		break;
	case PrevMode_RGB:
		Mes = to_string(R)+"\n"+ to_string(G)+"\n"+ to_string(B);
		break;
	}
}

void Prev::SetMode(ePrevMode inmode)
{
	mode = inmode;
}
