#ifndef __SHADER_NODE_H__
#define __SHADER_NODE_H__
#include "cocos2d.h"
#include "Confings.h"
#include "Ball.h"

USING_NS_CC;

class ShaderNode : public CCNode
{
public:
    ShaderNode();
	//ccVertex2F pixel[WIN_HEIGHT*WIN_WIDTH] ;
	
	
    bool initWithVertex(const char *vert, const char *frag);
    void loadShaderVertex(const char *vert, const char *frag);

    virtual void update(float dt);
    virtual void setPosition(const CCPoint &newPosition);
    virtual void draw();

    static ShaderNode* shaderNodeWithVertex(const char *vert, const char *frag);

private:
    ccVertex2F m_center;
	ccVertex2F nima[arraySize];
    //ccVertex2F m_resolution;
    float      m_time;
    GLuint     m_uniformCenter,  m_uniformTime, m_uniformPixel;
	//m_uniformResolution
};

#endif