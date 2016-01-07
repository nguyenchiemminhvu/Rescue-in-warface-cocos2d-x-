#include "IntroductionScene.h"
#include "Defination.h"
#include "GameScene.h"

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

	background = Sprite::create("game_background.png");
	background->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);

	helicopter = Sprite::create("helicopter_transportation.png");
	helicopter->setPosition(origin.x + visibleSize.width + helicopter->getContentSize().width / 2,
							origin.y + visibleSize.height - helicopter->getContentSize().height / 2);

	soldier1 = Sprite::create("soldier.png");
	soldier2 = Sprite::create("soldier.png");
	soldier3 = Sprite::create("soldier.png");
	soldier1->setPosition(origin.x + soldier1->getContentSize().width, GROUND_THICKNESS + soldier1->getContentSize().height * 2);
	soldier2->setPosition(origin.x + soldier1->getContentSize().width * 2, GROUND_THICKNESS + soldier1->getContentSize().height * 2);
	soldier3->setPosition(origin.x + soldier1->getContentSize().width * 3, GROUND_THICKNESS + soldier1->getContentSize().height * 2);

	this->addChild(background);
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

cocos2d::Sequence* IntroductionScene::helicopterComing()
{
	auto moveLeft = MoveBy::create(HELICOPTER_COMING_DURATION, Vec2(-visibleSize.width + helicopter->getContentSize().width, 0));
	auto moveLeftEasing = EaseBackOut::create(moveLeft->clone());

	auto moveDown = MoveBy::create(HELICOPTER_LANDING_DURATION, Vec2(0, -visibleSize.height + GROUND_THICKNESS + helicopter->getContentSize().height / 2));

	auto sequence = cocos2d::Sequence::create(moveLeftEasing, moveDown, NULL);
	return sequence;
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
	cocos2d::Director::getInstance()->replaceScene(CCTransitionFade::create(TRANSITION_TIME, GameScene::createScene()));
}
