#ifndef __SPRITE_NODE_H__
#define __SPRITE_NODE_H__
#include "cocos2d.h"

USING_NS_CC;
class SpriteShader : public CCSprite
{
public:
    bool initWithTexture(CCTexture2D* texture, const CCRect&  rect);
    void draw();

    static SpriteShader* create(const char *pszFileName);

    CCPoint blur_;
    GLfloat    sub_[4];

    GLuint    blurLocation;
    GLuint    subLocation;
};

#endif