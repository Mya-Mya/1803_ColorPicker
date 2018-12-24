#pragma once
#include"s.h"
#include<string>

class Prev;

/*�ǂݍ��މ摜�t�@�C�����w�肵�A�\������
*/
class Work : public bs {
private:
	csMgr *maker;
	Prev *pPrev;
	int Image;
	bool ImageLoad = false;
	double ExtRate;
	int WIDTH, HEIGHT;
public:
	Work(csMgr *in, int Width, int Height);
	void DO() override;
	void ReadImage();
	void GetWindowSize(int Width, int Height);
};

typedef enum {
	PrevMode_Code,
	PrevMode_RGB,
}ePrevMode;

/*�}�E�X�̎w�肷��ꏊ�̐F�𒊏o���`�悷��
*/
class Prev {
private:
	signed int Code;
	int R, G, B;
	int H, S, V;
	int x, y;
	ePrevMode mode=PrevMode_RGB;
	int WIDTH, HEIGHT;
	int FONT;
	std::string Mes;
public:
	Prev(int Width,int Height);
	void DRAW();
	void SetPos(int inx, int iny);
	void SetMode(ePrevMode inmode);
};