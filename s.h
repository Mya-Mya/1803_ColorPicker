#pragma once
/*�A�v���P�[�V�������ɑ��݂���V�[���̗�
*/
typedef enum {
	sHelp,
	sWork,
	sNone
}es;

/*�V�[����ύX���邱�Ƃ�ۏ؂���
*/
class csMgr {
public:
	virtual void sChange(es in)=0;
};

/*sMgr�ɂ���ăV�[�����ƂɊǗ������^�X�N�̃X�[�p�[�N���X
*/
class bs {
private:
	int WIDTH, HEIGHT;
public:
	bs(csMgr *in, int Width, int Height);
	virtual void DO() = 0;
};

/*�V�[�����Ǘ�����
*/
class sMgr: public csMgr {
private:
	bs *inst;
	es next=sNone;
	int WIDTH, HEIGHT;
public:
	sMgr(int Width, int Height);
	void DO();
	void sChange (es in) override;
};