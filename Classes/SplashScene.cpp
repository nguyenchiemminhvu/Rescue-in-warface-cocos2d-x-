#include "SplashScene.h"
#include "Defination.h"
#include "MainMenuScene.h"

Scene* SplashScene::createScene()	{
	auto scene = Scene::create();
	auto layer = SplashScene::create();
	scene->addChild(layer);
	return scene;
}

bool SplashScene::init()	{
	if(!Layer::init())	{
		return false;
	}

	this->scheduleOnce(schedule_selector(SplashScene::goToMainMenuScene), SCHEDULE_TRANSITION_TIME);

	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();

	splash = Sprite::create("splashscene.png");
	splash->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);

	this->addChild(splash);

	return true;
}

void SplashScene::goToMainMenuScene(float t)	{
	Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, MainMenuScene::createScene()));
}