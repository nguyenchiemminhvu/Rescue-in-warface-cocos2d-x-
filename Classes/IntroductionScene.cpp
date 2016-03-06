/*
- Project: Rescue in warface
- Author: Nguyen Chiem Minh Vu

- First release: 00:20 07/03/2016
*/

#include "IntroductionScene.h"
#include "Defination.h"
#include "GameScene.h"
#include "FinishedScene.h"
#include "SimpleAudioEngine.h"

Scene * IntroductionScene::createScene()
{
	auto scene = Scene::create();
	auto layer = IntroductionScene::create();

	scene->addChild(layer);
	return scene;
}

bool IntroductionScene::init()
{
	if (!Layer::init()) {
		return false;
	}

	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();

	background = Sprite::create("introduction_ground.png");
	background->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);

	outdoor = Sprite::create("introduction_background.png");
	outdoor->setPosition(origin.x + visibleSize.width / 2, origin.y + GROUND_THICKNESS + outdoor->getContentSize().height / 2);

	buttonSkip = ui::Button::create("button_skip.png", "button_skip_clicked.png");
	buttonSkip->setPosition(Vec2(origin.x + visibleSize.width - buttonSkip->getContentSize().width / 2,
								 origin.y + buttonSkip->getContentSize().height / 2));
	buttonSkip->addTouchEventListener(CC_CALLBACK_2(IntroductionScene::handleButtonSkipClicked, this));

	helicopter = Sprite::create("helicopter_transportation.png");
	helicopter->setPosition(origin.x + visibleSize.width + helicopter->getContentSize().width / 2,
							origin.y + visibleSize.height - helicopter->getContentSize().height);
	helicopter->setFlipX(true);

	soldier1 = Sprite::create("soldier.png");
	soldier2 = Sprite::create("soldier.png");
	soldier3 = Sprite::create("soldier.png");
	soldier1->setPosition(origin.x + soldier1->getContentSize().width, GROUND_THICKNESS + soldier1->getContentSize().height * 2);
	soldier2->setPosition(origin.x + soldier1->getContentSize().width * 2, GROUND_THICKNESS + soldier1->getContentSize().height * 2);
	soldier3->setPosition(origin.x + soldier1->getContentSize().width * 3, GROUND_THICKNESS + soldier1->getContentSize().height * 2);

	this->addChild(background);
	this->addChild(outdoor);
	this->addChild(buttonSkip);
	this->addChild(helicopter);
	this->addChild(soldier1);
	this->addChild(soldier2);
	this->addChild(soldier3);

	auto delayHelicopter = cocos2d::DelayTime::create(SOLDIER_MOVING_DURATION);
	auto sequenceOfHelicopter = cocos2d::Sequence::create(helicopterComing(), delayHelicopter, helicopterLeaving(), NULL);
	helicopter->runAction(sequenceOfHelicopter);

	auto delaySoldiers = DelayTime::create(HELICOPTER_COMING_DURATION + HELICOPTER_LANDING_DURATION);
	auto sequence1 = cocos2d::Sequence::create(delaySoldiers, soldiersMovement(), CallFunc::create(soldier1, callfunc_selector(Sprite::removeFromParent)), NULL);
	auto sequence2 = cocos2d::Sequence::create(delaySoldiers, soldiersMovement(), CallFunc::create(soldier2, callfunc_selector(Sprite::removeFromParent)), NULL);
	auto sequence3 = cocos2d::Sequence::create(delaySoldiers, soldiersMovement(), CallFunc::create(soldier3, callfunc_selector(Sprite::removeFromParent)), NULL);
	soldier1->runAction(sequence1);
	soldier2->runAction(sequence2);
	soldier3->runAction(sequence3);

	float totalTime = HELICOPTER_COMING_DURATION + HELICOPTER_LANDING_DURATION + SOLDIER_MOVING_DURATION + HELICOPTER_LEAVING_DURATION;
	this->scheduleOnce(schedule_selector(IntroductionScene::goToGameScene), totalTime);

	return true;
}

void IntroductionScene::handleButtonSkipClicked(Ref * sender, ui::Widget::TouchEventType type)
{
	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::BEGAN:
		break;
	case cocos2d::ui::Widget::TouchEventType::MOVED:
		break;
	case cocos2d::ui::Widget::TouchEventType::ENDED:
		this->goToGameScene(0);
		break;
	case cocos2d::ui::Widget::TouchEventType::CANCELED:
		break;
	default:
		break;
	}
}

cocos2d::Sequence* IntroductionScene::helicopterComing()
{
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sounds/helicopter_sound.mp3");
	auto moveLeft = MoveBy::create(HELICOPTER_COMING_DURATION, Vec2(-visibleSize.width + helicopter->getContentSize().width, 0));
	auto moveLeftEasing = EaseBackOut::create(moveLeft->clone());

	auto moveDown = MoveBy::create(HELICOPTER_LANDING_DURATION, Vec2(0, -visibleSize.height + GROUND_THICKNESS + helicopter->getContentSize().height));

	auto sequence = cocos2d::Sequence::create(moveLeftEasing, CallFunc::create(this, callfunc_selector(IntroductionScene::FlipHelicopter)), moveDown, NULL);
	return sequence;
}

void IntroductionScene::FlipHelicopter()
{
	helicopter->setFlipX(false);
}

cocos2d::Sequence * IntroductionScene::helicopterLeaving()
{
	auto moveUp = MoveBy::create(HELICOPTER_LEAVING_DURATION - 4, Vec2(0, visibleSize.height / 2));

	auto rotate = RotateBy::create(1, 20);
	auto moveRight = MoveBy::create(HELICOPTER_LEAVING_DURATION - 2, Vec2(visibleSize.width, 0));
	auto spawning = Spawn::create(rotate, moveRight, NULL);

	auto sequence = cocos2d::Sequence::create(moveUp, spawning, NULL);
	return sequence;
}

cocos2d::Sequence * IntroductionScene::soldiersMovement()
{
	auto moveRight = MoveBy::create(SOLDIER_MOVING_DURATION, Vec2(helicopter->getContentSize().width, 0));
	
	auto sequence = cocos2d::Sequence::create(moveRight, NULL);
	return sequence;
}

void IntroductionScene::goToGameScene(float t)
{
	CocosDenshion::SimpleAudioEngine::getInstance()->stopAllEffects();
	cocos2d::Director::getInstance()->replaceScene(CCTransitionFade::create(TRANSITION_TIME, GameScene::createScene()));
}
