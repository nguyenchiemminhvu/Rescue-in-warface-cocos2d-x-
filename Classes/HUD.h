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

	uint64_t getScore();
	void increaseScore();
	
private:
	uint64_t score;
	LabelTTF* labelScore;
};

#endif //__HUD_H__