#include"CardSprite.h"

USING_NS_CC;

CardSprite *CardSprite::createCardSprite(int numbers, int wight, int height, float CardSpriteX, float CardSpriteY)
{//模板类型，必不可少的代码
	CardSprite *enemy = new CardSprite();
	if (enemy && enemy->init())
	{
		enemy->autorelease();
		enemy->enemyInit(numbers, wight, height, CardSpriteX, CardSpriteY);

		return enemy;
	}

	CC_SAFE_DELETE(enemy);
	return NULL;
}


bool CardSprite::init()
{
	if (!Sprite::init ())
	{
		return false;
	}
	return true;
}

void CardSprite::setNumber(int num)
{
	number = num;

	//判断数字的大小来调整字体的大小
	if (number >= 0)
	{
		labTTFCardNumber->setFontSize(100);
	}
	if (number >= 16)
	{
		labTTFCardNumber->setFontSize(90);
	}
	if (number >= 128)
	{
		labTTFCardNumber->setFontSize(60);
	}
	if (number >= 1024)
	{
		labTTFCardNumber->setFontSize(40);
	}

	//判断数字的大小来调整颜色
	if (number == 0)
	{
		layerColorBG->setColor(cocos2d::Color3B(200, 190, 180));
	}
	if (number == 2)
	{
		layerColorBG->setColor(cocos2d::Color3B(240, 230, 220));
	}
	if (number == 4)
	{
		layerColorBG->setColor(cocos2d::Color3B(240, 220, 180));
	}
	if (number == 8)
	{
		layerColorBG->setColor(cocos2d::Color3B(200, 180, 120));
	}
	if (number == 16)
	{
		layerColorBG->setColor(cocos2d::Color3B(240, 140, 90));
	}
	if (number == 32)
	{
		layerColorBG->setColor(cocos2d::Color3B(240, 120, 90));
	}
	if (number == 64)
	{
		layerColorBG->setColor(cocos2d::Color3B(240, 90, 60));
	}
	if (number == 128)
	{
		layerColorBG->setColor(cocos2d::Color3B(240, 90, 60));
	}
	if (number == 256)
	{
		layerColorBG->setColor(cocos2d::Color3B(240, 200, 70));
	}
	if (number == 512)
	{
		layerColorBG->setColor(cocos2d::Color3B(240, 200, 70));
	}
	if (number == 1024)
	{
		layerColorBG->setColor(cocos2d::Color3B(0, 190, 0));
	}
	if (number == 2048)
	{
		layerColorBG->setColor(cocos2d::Color3B(0, 150, 0));
	}
	//更新显示的数字
	if (number > 0)
	{
		labTTFCardNumber->setString(__String::createWithFormat("%i", number)->getCString());
	}
 else
 {
	 labTTFCardNumber->setString("");
 }
}

void CardSprite::enemyInit(int numbers, int wight, int height, float CardSpriteX, float CardSpriteY)
{
	//初始化数字
	number = numbers;

	//加入游戏卡片的背景颜色
	layerColorBG = cocos2d::LayerColor::create(Color4B(200, 190, 180, 255), wight - 15, height - 15);
	layerColorBG->setPosition(Vec2(CardSpriteX, CardSpriteY));

	//判断如果不等于0就显示，否则为空
	if (number > 0)
	{
		//加入中间字体
		labTTFCardNumber = cocos2d::LabelTTF::create(__String::createWithFormat("%i", number)->getCString(), "HirakakuProN-W6", 100);
		labTTFCardNumber->setPosition(Vec2(layerColorBG->getContentSize().width / 2, layerColorBG->getContentSize().height / 2));
		layerColorBG->addChild(labTTFCardNumber);
	}
	else
	{
		//加入中间字体
		labTTFCardNumber = cocos2d::LabelTTF::create("", "HirakakuProN-W6", 100);
		labTTFCardNumber->setPosition(Vec2(layerColorBG->getContentSize().width / 2, layerColorBG->getContentSize().height / 2));
		layerColorBG->addChild(labTTFCardNumber);
	}

	this->addChild(layerColorBG);

}



//获取数字
int CardSprite::getNumber()
{
	return number;
}
