#include "HUD.h"


HUD::HUD()	{
}


HUD::~HUD()	{
}


void HUD::increaseScore()	{
	this->score++;
}


uint64_t HUD::getScore()	{
	return this->score;
}


HUD* HUD::createHUD()	{
	HUD* hud = new HUD();
	hud->create();
	hud->init();
	hud->autorelease();
	hud->setColor( Color3B::BLACK );
	hud->setAnchorPoint( Vec2(0, 0) );
	hud->initOption();

	return hud;
}


void HUD::initOption()	{

	this->score = 0;
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();

	auto stringScore = __String::createWithFormat( "Score: %d", this->score );
	labelScore = LabelTTF::create(stringScore->getCString(), "fonts/Marker Felt.ttf", 50);
	labelScore->setColor( Color3B::WHITE );
	labelScore->setPosition( origin.x + labelScore->getContentSize().width,
		origin.y + visibleSize.height - labelScore->getContentSize().height );
	labelScore->setFontFillColor( Color3B::YELLOW );

	this->addChild( labelScore );

	this->scheduleUpdate();
}


void HUD::draw(cocos2d::Renderer * renderer, const cocos2d::Mat4 & transform, bool transformUpdated)   {
}


void HUD::update( float delta )		{
	auto stringScore = __String::createWithFormat( "Score: %d", this->score );
	labelScore->setString( stringScore->getCString() );
}