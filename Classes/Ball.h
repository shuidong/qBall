#ifndef __BALL_SCENE_H__
#define __BALL_SCENE_H__

#include "cocos2d.h"
#include "Box2D/Box2D.h"

USING_NS_CC;

class Ball
{
public:
	Ball();
	~Ball();
	int m_color;//r=0,g=1,b=2,x=3
	float m_status;//enable=0,disable=1
	float m_r;
	ccVertex2F pos;
	CCSprite* ballSprite;
	b2Body* m_pBody;
};

#endif