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
	
private:
	uint64_t remainingDistance;
	LabelTTF* labelDistance;
};

#endif //__HUD_H__