#pragma once

#include"cocos2d.h"

class CardSprite :public cocos2d::Sprite
{
public:
	//初始化游戏卡片的方法
	static CardSprite *createCardSprite(int numbers, int wight, int height, float CardSpriteX, float CardSpriteY);
	virtual bool init();
	CREATE_FUNC(CardSprite);

	//设置数字
	void setNumber(int num);

	//获取数字
	int getNumber();

private:
	//显示在界面的数字
	int number;
	void enemyInit(int numbers, int wight, int height, float CardSpriteX, float CardSpriteY);

	//定义显示数字的控件
	cocos2d::LabelTTF *labTTFCardNumber;

	//显示背景
	cocos2d::LayerColor *layerColorBG;

};

