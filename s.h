#pragma once
/*アプリケーション内に存在するシーンの列挙
*/
typedef enum {
	sHelp,
	sWork,
	sNone
}es;

/*シーンを変更することを保証する
*/
class csMgr {
public:
	virtual void sChange(es in)=0;
};

/*sMgrによってシーンごとに管理されるタスクのスーパークラス
*/
class bs {
private:
	int WIDTH, HEIGHT;
public:
	bs(csMgr *in, int Width, int Height);
	virtual void DO() = 0;
};

/*シーンを管理する
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