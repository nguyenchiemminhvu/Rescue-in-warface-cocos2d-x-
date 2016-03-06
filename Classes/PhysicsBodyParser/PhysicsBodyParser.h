#ifndef __PHYSICS_BODY_PARSER_H__
#define __PHYSICS_BODY_PARSER_H__

#pragma once

#include <string>
#include "cocos2d.h"
USING_NS_CC;
#include "json/document.h"

class PhysicsBodyParser {

	PhysicsBodyParser() {}
	rapidjson::Document doc;
public:

	static PhysicsBodyParser* getInstance();
	bool parseJsonFile(const std::string& pFile);
	bool parse(unsigned char* buffer, long length);
	void clearCache();
	PhysicsBody* bodyFormJson(Node* pNode, const std::string& name, PhysicsMaterial material);
};

#endif //__PHYSICS_BODY_PARSER_H__