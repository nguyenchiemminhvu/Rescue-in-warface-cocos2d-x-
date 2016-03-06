#include "FinishedScene.h"
#include "SimpleAudioEngine.h"

Scene * FinishedScene::createScene()
{
	auto scene = Scene::create();
	auto layer = FinishedScene::create();
	scene->addChild(layer);
	return scene;
}

bool FinishedScene::init()
{
	if (!Layer::init()) {
		return false;
	}

	cocos2d::Director::getInstance()->getOpenGLView()->setCursorVisible(true);

	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();

	initLabel();

	return true;
}

void FinishedScene::initLabel()
{
	label = LabelTTF::create("To be continue...", "font/", 50);
	label->setPosition(Vec2(origin.x + visibleSize.width - label->getContentSize().width,
							origin.y + label->getContentSize().height));

	this->addChild(label);
}
