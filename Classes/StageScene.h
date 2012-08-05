#ifndef __STAGE_SCENE_H__
#define __STAGE_SCENE_H__


#include "cocos2d.h"

#include "Box2D/Box2D.h"
#include "GLES-Render.h"
#include "SimpleAudioEngine.h"
#include "Ball.h"
#include "ShaderNode.h"

class Stage : public cocos2d::CCLayer
{
public:
	
	
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
	virtual ~Stage();
	virtual void draw();
	void update(float dt);

   // there's no 'id' in cpp, so we recommand to return the exactly class pointer
    static cocos2d::CCScene* scene();
    // implement the "static node()" method manually
    LAYER_CREATE_FUNC(Stage);
	virtual void ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
protected:

	void SetupWorld(void);
	b2World *world;
	b2Body *body;
	
	GLESDebugDraw *m_debugDraw;
	
public:
	ShaderNode *sn;
	
	CCRenderTexture *mainTexture;
	CCRenderTexture *renderTexture;


	vector<Ball*> ball_vec_;
	CCGLProgram *shader;
	int alphaValueLocation;
	int colorValueLocation;

	int m_uMaskLocation;
	CCGLProgram *pProgram;
};
#endif