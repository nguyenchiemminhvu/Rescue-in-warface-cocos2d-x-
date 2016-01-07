#include "PauseScene.h"
#include "MainMenuScene.h"
#include "GameScene.h"
#include "Defination.h"


Scene* PauseScene::createScene()	{
	auto scene = Scene::create();
	auto layer = PauseScene::create();
	scene->addChild(layer);
	return scene;
}


bool PauseScene::init()	{
	if(!Layer::init())	{
		return false;
	}
	
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();
	
	return true;
}


void PauseScene::goToMainMenuScene(Ref* sender)	{
	auto menuScene = MainMenuScene::createScene();
	Director::getInstance()->popScene();
	Director::getInstance()->replaceScene(menuScene);
}


void PauseScene::resume(Ref* sender)	{
	Director::getInstance()->popScene();
}


void PauseScene::retry(Ref* sender)	{
	auto gameScene = GameScene::createScene();
	Director::getInstance()->popScene();
	Director::getInstance()->replaceScene(TransitionFade::create(1000, gameScene) );
}
