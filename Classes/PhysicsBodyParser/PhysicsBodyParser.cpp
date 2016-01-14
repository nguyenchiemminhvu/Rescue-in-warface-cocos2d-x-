#include "PhysicsBodyParser.h"



PhysicsBodyParser * PhysicsBodyParser::getInstance()
{
	return nullptr;
}

bool PhysicsBodyParser::parseJsonFile(const char * file)
{
	return false;
}

void PhysicsBodyParser::parse(const UCHAR * buffer, uint16_t length)
{
}

void PhysicsBodyParser::clearCache()
{
}

PhysicsBody * PhysicsBodyParser::createBodyFromJson(Node * node, const char * name, PhysicsMaterial material)
{
	return nullptr;
}

PhysicsBodyParser::PhysicsBodyParser()
{
}