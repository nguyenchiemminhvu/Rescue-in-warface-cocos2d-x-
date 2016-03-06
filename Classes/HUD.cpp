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

uint8_t HUD::getRemainingFuel()
{
	return this->remainingFuel;
}

void HUD::increaseFuel(uint16_t amount)
{
	remainingFuel += amount;
	if (remainingFuel > 20)
		remainingFuel = 20;
}

void HUD::decreaseFuel()
{
	if (remainingFuel > 0)
		remainingFuel--;
}

uint64_t HUD::getScore()
{
	return score;
}

void HUD::increaseScrore(uint64_t amount)
{
	score += amount;
}

void HUD::warning()
{
	auto delay = DelayTime::create(0.5f);
	auto turnOn = CallFunc::create(this, callfunc_selector(HUD::turnOnWarning));
	auto turnOff = CallFunc::create(this, callfunc_selector(HUD::turnOffWarning));

	this->runAction(
		Sequence::create(
							turnOn->clone(), delay->clone(), turnOff->clone(), delay->clone(), 
							turnOn->clone(), delay->clone(), turnOff->clone(), delay->clone(),
							turnOn->clone(), delay->clone(), turnOff->clone(), NULL
						)
				   );
}

void HUD::turnOnWarning()
{
	labelWarning->setVisible(true);
}

void HUD::turnOffWarning()
{
	labelWarning->setVisible(false);
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

	this->remainingDistance = 5;
	this->remainingFuel = 20;
	this->score = 0;

	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();

	/////////////////////////////////////////////////
	// distance
	auto stringDistance = __String::createWithFormat( "Remaining distance: %d", this->remainingDistance );
	labelDistance = LabelTTF::create(stringDistance->getCString(), "fonts/Backslash.ttf", 40);
	labelDistance->setAnchorPoint(Vec2(0, 0));
	labelDistance->setColor( Color3B::WHITE );
	labelDistance->setFontFillColor(Color3B::YELLOW);
	labelDistance->setPosition( origin.x + visibleSize.width - labelDistance->getContentSize().width,
		origin.y + visibleSize.height - labelDistance->getContentSize().height );

	///////////////////////////////////////////////
	// fuel
	__String fuelDescription = "";
	for (int i = 0; i < remainingFuel; i++)
		fuelDescription.append("I");
	auto stringFuel = __String::createWithFormat("Fuel: %s", fuelDescription.getCString());
	labelFuel = LabelTTF::create(stringFuel->getCString(), "fonts/Backslash.ttf", 40);
	labelFuel->setAnchorPoint(Vec2(0, 0));
	labelFuel->setColor(Color3B::WHITE);
	labelFuel->setFontFillColor( (remainingFuel >= 5) ? Color3B::GREEN : Color3B::RED );
	labelFuel->setPosition(labelDistance->getPositionX(), labelDistance->getPositionY() - labelFuel->getContentSize().height);

	//////////////////////////////////////////////
	// score
	auto stringScore = __String::createWithFormat("Score: %ld", score);
	labelScore = LabelTTF::create(stringScore->getCString(), "fonts/Backslash.ttf", 40);
	labelScore->setAnchorPoint(Vec2(0, 1));
	labelScore->setColor(Color3B::WHITE);
	labelScore->setFontFillColor(Color3B::YELLOW);
	labelScore->setPosition(origin.x, origin.y + visibleSize.height);

	//////////////////////////////////////////////
	// warning
	__String warningDescription = "W A R N I N G";
	auto stringWarning = __String::createWithFormat("%s", warningDescription.getCString());
	labelWarning = LabelTTF::create(stringWarning->getCString(), "fonts/Backslash.ttf", 90);
	labelWarning->setAnchorPoint(Vec2(0.5f, 0.5f));
	labelWarning->setColor(Color3B::WHITE);
	labelWarning->setFontFillColor(Color3B::RED);
	labelWarning->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);
	labelWarning->setVisible(false);

	// add all component to gamescene
	this->addChild( labelDistance );
	this->addChild( labelFuel );
	this->addChild( labelScore );
	this->addChild( labelWarning );
	
	this->scheduleUpdate();
}


void HUD::draw(cocos2d::Renderer * renderer, const cocos2d::Mat4 & transform, bool transformUpdated)   {
}


void HUD::update( float delta )		{
	/////////////////////////////////////////////////////////////
	// update distance
	auto stringDistance = __String::createWithFormat( "Remaining distance: %d", this->remainingDistance );
	labelDistance->setString( stringDistance->getCString() );

	////////////////////////////////////////////////////////////
	// update fuel
	__String fuelDescription = "";
	for (int i = 0; i < remainingFuel; i++)
		fuelDescription.append("I");
	auto stringFuel = __String::createWithFormat("Fuel: %s", fuelDescription.getCString());
	labelFuel->setFontFillColor((remainingFuel > 5) ? Color3B::GREEN : Color3B::RED);
	labelFuel->setString( stringFuel->getCString() );

	///////////////////////////////////////////////////////////
	// update score
	auto stringScore = __String::createWithFormat( "Score: %ld", this->score );
	labelScore->setString( stringScore->getCString() );
}