#include "HUD.h"


HUD::HUD()	{
}


HUD::~HUD()	{
}

uint64_t HUD::getRemainingDistance()
{
	return this->remainingDistance;
}

void HUD::decreaseDistance()
{
	if(remainingDistance > 0)
		remainingDistance--;
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

	this->remainingDistance = 500;
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();

	auto stringDistance = __String::createWithFormat( "Remaining distance: %d", this->remainingDistance );
	labelDistance = LabelTTF::create(stringDistance->getCString(), "fonts/Backslash.ttf", 40);
	labelDistance->setAnchorPoint(Vec2(0, 0));
	labelDistance->setColor( Color3B::WHITE );
	labelDistance->setPosition( origin.x + visibleSize.width - labelDistance->getContentSize().width,
		origin.y + visibleSize.height - labelDistance->getContentSize().height );
	labelDistance->setFontFillColor( Color3B::YELLOW );

	this->addChild( labelDistance );

	this->scheduleUpdate();
}


void HUD::draw(cocos2d::Renderer * renderer, const cocos2d::Mat4 & transform, bool transformUpdated)   {
}


void HUD::update( float delta )		{
	auto stringScore = __String::createWithFormat( "Remaining distance: %d", this->remainingDistance );
	labelDistance->setString( stringScore->getCString() );
}