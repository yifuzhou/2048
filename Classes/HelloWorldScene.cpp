#include "HelloWorldScene.h"
#include"CardSprite.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    auto scene = Scene::create();
   
    auto layer = HelloWorld::create();

    scene->addChild(layer);

    return scene;
}


bool HelloWorld::init()
{
	//////////////////////////////

	if (!Layer::init())
	{
		return false;
	}
	score = 0;

	Size visibleSize = Director::getInstance()->getVisibleSize();
	//Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//加入游戏背景
	auto layerColorBG = cocos2d::LayerColor::create(cocos2d::Color4B(180, 170, 160, 255));
	this->addChild(layerColorBG);

	//在上方加入游戏的分数
	auto labTTFCardNumberName = LabelTTF::create("sorce", "HirakakuProN-W6", 80);
	labTTFCardNumberName->setPosition(Point(visibleSize.width-350, visibleSize.height - 150));
	addChild(labTTFCardNumberName);

	labTTFCardNumber = LabelTTF::create("0", "HirakakuProN-W6", 80);
	labTTFCardNumber->setPosition(Point(visibleSize.width - 150, visibleSize.height - 150));
	addChild(labTTFCardNumber);

	//游戏的手势识别的监听事件，进行绑定
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
	//Director::getInstance()->getEventDispatcher()->
	//	addEventListenerWithSceneGraphPriority(touchListener, this);

	//调用生成卡片的方法
	createCardSprite(visibleSize);

	//调用生成随机数
	autoCreateCardNumber();
	autoCreateCardNumber();

	return true;
}

//创建卡片
void HelloWorld::createCardSprite(cocos2d::Size size)
{//求出单元格的宽度和高度
	int lon = (size.width - 28) / 8;

	//4*4的单元格
	for (int j = 0; j < 4; j++)
	{
		for (int i = 0; i < 4; i++) 
		{
			CardSprite *card = CardSprite::createCardSprite(0, lon, lon, lon*j + 20, lon*i + 20 + size.height / 6);
			addChild(card);

			//添加卡片到二维数组中
			cardArr[j][i] = card;
		}
	}
}

//游戏是否继续下去
void HelloWorld::doCheckGameOver()
{
	bool isGameOver = true;

	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			if (cardArr[x][y]->getNumber() == 0 ||
				(x>0 && (cardArr[x][y]->getNumber() == cardArr[x - 1][y]->getNumber())) ||
				(x<3 && (cardArr[x][y]->getNumber() == cardArr[x + 1][y]->getNumber())) ||
				(y>0 && (cardArr[x][y]->getNumber() == cardArr[x][y - 1]->getNumber()))||
				(y<3 && (cardArr[x][y]->getNumber() == cardArr[x][y + 1]->getNumber()))
				)
			{
				isGameOver = false;
			}
		}
	}
	if (isGameOver)
	{
		Director::getInstance()->replaceScene(TransitionFade::create(1, HelloWorld::createScene()));
	}
}

//自动生成卡片数字
void HelloWorld::autoCreateCardNumber()
{
	int i = CCRANDOM_0_1() * 4;//0~3位置的值
	int j = CCRANDOM_0_1() * 4;

	//判断是否是已经存在的位置
	if (cardArr[i][j]->getNumber() > 0)
	{
		autoCreateCardNumber();
	}
else
{
	cardArr[i][j]->setNumber(CCRANDOM_0_1() * 10 < 1 ? 4:2);//概率是一比九
}


}

//加入手势识别的事件
bool HelloWorld::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event)
{
	auto touchPO = touch->getLocation();

	firstX = touchPO.x;
	firstY = touchPO.y;

	return true;

}
void HelloWorld::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
	Point touchPO = touch->getLocation();
	endX = firstX - touchPO.x;
	endY = firstY - touchPO.y;

	if (abs(endX) > abs(endY))
	{//左右
		if (endX + 5 > 0)
		{//左边
			if (doLeft())
			{
				//调用生成随机数
				autoCreateCardNumber();
				doCheckGameOver();
			}
		}
		else
		{
			if (doRight())
			{
				//调用生成随机数
				autoCreateCardNumber();
				doCheckGameOver();
			}
		}
	}
	else
	{//上下
		if (endY + 5 > 0)
		{
			if (doDown())
			{
				//调用生成随机数
				autoCreateCardNumber();
				doCheckGameOver();
			}
		}
		else
		{
			if (doUp())
			{
				//调用生成随机数
				autoCreateCardNumber();
				doCheckGameOver();
			}
		}
	}
	
}
//上下左右的方法
bool HelloWorld::doLeft()
{
	bool isdo = false;

	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			for (int x1 = x + 1; x1 < 4; x1++)
			{
				if (cardArr[x1][y]->getNumber() >0)
				{
					if (cardArr[x][y]->getNumber() <= 0)
					{
						cardArr[x][y]->setNumber(cardArr[x1][y]->getNumber());
						cardArr[x1][y]->setNumber(0);

						x--;
						isdo = true;
					}
					else if (cardArr[x][y]->getNumber() == cardArr[x1][y]->getNumber())
					{
						cardArr[x][y]->setNumber(cardArr[x][y]->getNumber() * 2);
						cardArr[x1][y]->setNumber(0);

						//设置分数
						score += cardArr[x][y]->getNumber();
						labTTFCardNumber->setString(__String::createWithFormat("%i", score)->getCString());

						isdo = true;
					}
					break;
				}
			}
		}
	}
		


	return isdo;
}
bool HelloWorld::doRight()
{
	bool isdo = false;

	for (int y = 0; y < 4; y++)
	{
		for (int x = 3; x >= 0; x--)
		{
			for (int x1 = x - 1; x1 >=0; x1--)
			{
				if (cardArr[x1][y]->getNumber() >0)
				{
					if (cardArr[x][y]->getNumber() <= 0)
					{
						cardArr[x][y]->setNumber(cardArr[x1][y]->getNumber());
						cardArr[x1][y]->setNumber(0);

						x++;
						isdo = true;
					}
					else if (cardArr[x][y]->getNumber() == cardArr[x1][y]->getNumber())
					{
						cardArr[x][y]->setNumber(cardArr[x][y]->getNumber() * 2);
						cardArr[x1][y]->setNumber(0);

						//设置分数
						score += cardArr[x][y]->getNumber();
						labTTFCardNumber->setString(__String::createWithFormat("%i", score)->getCString());

						isdo = true;
					}
					break;
				}
			}
		}
	}



	return isdo;
}
bool HelloWorld::doUp()
{
	bool isdo = false;

	for (int x = 0; x < 4; x++)
	{
		for (int y = 3; y >= 0; y--)
		{
			for (int y1 = y - 1; y1 >= 0; y1--)
			{
				if (cardArr[x][y1]->getNumber() >0)
				{
					if (cardArr[x][y]->getNumber() <= 0)
					{
						cardArr[x][y]->setNumber(cardArr[x][y1]->getNumber());
						cardArr[x][y1]->setNumber(0);

						y++;
						isdo = true;
					}
					else if (cardArr[x][y]->getNumber() == cardArr[x][y1]->getNumber())
					{
						cardArr[x][y]->setNumber(cardArr[x][y]->getNumber() * 2);
						cardArr[x][y1]->setNumber(0);

						//设置分数
						score += cardArr[x][y]->getNumber();
						labTTFCardNumber->setString(__String::createWithFormat("%i", score)->getCString());

						isdo = true;
					}
					break;
				}
			}
		}
	}



	return isdo;
}
bool HelloWorld::doDown()
{
	bool isdo = false;

	for (int x = 0; x < 4; x++)
	{
		for (int y = 0; y < 4; y++)
		{
			for (int y1 = y + 1; y1 < 4; y1++)
			{
				if (cardArr[x][y1]->getNumber() >0)
				{
					if (cardArr[x][y]->getNumber() <= 0)
					{
						cardArr[x][y]->setNumber(cardArr[x][y1]->getNumber());
						cardArr[x][y1]->setNumber(0);

						y--;
						isdo = true;
					}
					else if (cardArr[x][y]->getNumber() == cardArr[x][y1]->getNumber())
					{
						cardArr[x][y]->setNumber(cardArr[x][y]->getNumber() * 2);
						cardArr[x][y1]->setNumber(0);

						//设置分数
						score += cardArr[x][y]->getNumber();
						labTTFCardNumber->setString(__String::createWithFormat("%i", score)->getCString());

						isdo = true;
					}
					break;
				}
			}
		}
	}



	return isdo;
}
    
