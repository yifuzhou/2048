#pragma once

#include"cocos2d.h"

class CardSprite :public cocos2d::Sprite
{
public:
	//��ʼ����Ϸ��Ƭ�ķ���
	static CardSprite *createCardSprite(int numbers, int wight, int height, float CardSpriteX, float CardSpriteY);
	virtual bool init();
	CREATE_FUNC(CardSprite);

	//��������
	void setNumber(int num);

	//��ȡ����
	int getNumber();

private:
	//��ʾ�ڽ��������
	int number;
	void enemyInit(int numbers, int wight, int height, float CardSpriteX, float CardSpriteY);

	//������ʾ���ֵĿؼ�
	cocos2d::LabelTTF *labTTFCardNumber;

	//��ʾ����
	cocos2d::LayerColor *layerColorBG;

};

