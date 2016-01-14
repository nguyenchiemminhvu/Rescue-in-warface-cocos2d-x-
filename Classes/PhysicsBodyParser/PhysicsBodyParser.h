#ifndef __PHYSICS_BODY_PARSER_H__
#define __PHYSICS_BODY_PARSER_H__

#pragma once

#include "cocos2d.h"
#include "json\document.h"

USING_NS_CC;

class PhysicsBodyParser
{
public:
	static PhysicsBodyParser* getInstance();
	bool parseJsonFile(const char *file);
	void parse(const UCHAR *buffer, uint16_t length);
	void clearCache();
	PhysicsBody* createBodyFromJson(Node *node, const char *name, PhysicsMaterial material);

private:
	rapidjson::Document document;

	PhysicsBodyParser();
};

#endif //__PHYSICS_BODY_PARSER_H__