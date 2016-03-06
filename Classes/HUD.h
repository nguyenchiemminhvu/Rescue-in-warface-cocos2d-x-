#ifndef __HUD_H__
#define __HUD_H__

#pragma once
#include "cocos2d.h"

USING_NS_CC;

class HUD : public LayerColor	{
public:
	
	HUD();
	virtual ~HUD();

	static HUD* createHUD();
	void initOption();
	virtual void draw (cocos2d::Renderer * renderer, const cocos2d::Mat4 & transform,
                         bool transformUpdated); 
	virtual void update( float delta );

	uint64_t getRemainingDistance();
	void decreaseDistance();

	uint8_t getRemainingFuel();
	void increaseFuel(uint16_t amount);
	void decreaseFuel();
	
	uint64_t getScore();
	void increaseScrore(uint64_t amount);

	void warning();

private:
	uint64_t remainingDistance;
	uint8_t remainingFuel;
	uint64_t score;
	LabelTTF* labelDistance;
	LabelTTF* labelFuel;
	LabelTTF* labelScore;
	LabelTTF* labelWarning;

	void turnOnWarning();
	void turnOffWarning();
};

#endif //__HUD_H__