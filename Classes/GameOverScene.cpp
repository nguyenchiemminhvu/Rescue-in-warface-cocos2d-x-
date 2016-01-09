#include "GameOverScene.h"
#include "MainMenuScene.h"
#include "GameScene.h"
#include "Defination.h"


Scene* GameOverScene::createScene()	{
	auto scene = Scene::create();
	auto layer = GameOverScene::create();
	scene->addChild(layer);
	return scene;
}


bool GameOverScene::init()	{
	if(!Layer::init())	{
		return false;
	}
	
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();

	/*UserDefault* userScore = UserDefault::getInstance();
	if(score >= userScore->getIntegerForKey( "highscore" ))	{
		userScore->setIntegerForKey( "highscore", score );
	}
	userScore->flush();*/

	return true;
}


void GameOverScene::goToMainMenuScene(Ref* sender)	{
	auto menuScene = MainMenuScene::createScene();
	Director::getInstance()->replaceScene( TransitionFade::create(1000, menuScene) );
}


void GameOverScene::goToGameScene(Ref* sender)	{
	auto gameScene = GameScene::createScene();
	Director::getInstance()->replaceScene(gameScene);
}