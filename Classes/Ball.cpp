#include "Ball.h"

Ball::Ball()
	:pos(vertex2(0.0f, 0.0f))
	,m_color(0)
	,m_status(1.0f)
	,m_pBody(NULL)
{
	float tmp = CCRANDOM_0_1();
	if(tmp >= 0.25) m_color= 1;
	if(tmp >= 0.5) m_color= 2;
	if(tmp >= 0.75) m_color= 3;
	
	//char str[20];
	//sprintf(str, "ball%d.png", m_color);
	ballSprite = CCSprite::create("ballx.png");
	//ballSprite->setScale(1.3f);
	//ballSprite->setAnchorPoint
	//ballSprite->setScaleX(1.1);
	//ballSprite->setScaleY(0.9);
	ballSprite->retain();
	//ballSprite->autorelease();
}

Ball::~Ball()
{
	m_pBody = NULL;
	
}