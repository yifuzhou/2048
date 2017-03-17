#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include"CardSprite.h"

class HelloWorld : public cocos2d::Layer
{
public:

    static cocos2d::Scene* createScene();
    virtual bool init(); 
	CREATE_FUNC(HelloWorld);
    
	//��������ʶ����¼�
	virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event);
	virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event);
	//�������ҵķ���
	bool doLeft();
	bool doRight();
	bool doUp();
	bool doDown();
	//�Զ���Ƭ������
	void autoCreateCardNumber();
	//��Ϸ�Ƿ��ܼ���������ȥ
	void doCheckGameOver();
private:
	//�����Ԫ��
	int firstX, firstY, endX, endY;
	//������Ƭ
	void createCardSprite(cocos2d::Size size);
	//����һ����ά����
	CardSprite *cardArr[4][4];
   //������Ϸ�ķ���
	int score;
	//������ʾ���ݵĿؼ�
	cocos2d::LabelTTF *labTTFCardNumber;



};

#endif // __HELLOWORLD_SCENE_H__
