#include "StageScene.h"
#include "Ball.h"
#include "Confings.h"
#include <math.h>

using namespace cocos2d;

CCScene* Stage::scene()
{
	CCScene * scene = NULL;
	do 
	{
		// 'scene' is an autorelease object
		scene = CCScene::create();
		CC_BREAK_IF(! scene);

		// 'layer' is an autorelease object
		Stage *layer = Stage::create();
		CC_BREAK_IF(! layer);

		// add layer as a child to scene
		scene->addChild(layer);
	} while (0);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool Stage::init()
{
	bool bRet = false;
	do 
	{
		//////////////////////////////////////////////////////////////////////////
		// super init first
		//////////////////////////////////////////////////////////////////////////

		CC_BREAK_IF(! CCLayer::init());

		//////////////////////////////////////////////////////////////////////////
		// add your codes below...
		//////////////////////////////////////////////////////////////////////////
		// Get window size and place the label upper. 
		CCSize size = CCDirector::sharedDirector()->getWinSize();
		CCSprite* pBgSprite;
		// 3. Add add a splash screen, show the cocos2d splash image.
		pBgSprite = CCSprite::create("bg.jpg");
		CC_BREAK_IF(! pBgSprite);

		// Place the sprite on the center of the screen
		pBgSprite->setPosition(ccp(size.width/2, size.height/2));
		// Add the sprite to HelloWorld layer as a child layer.
		this->addChild(pBgSprite, -5);

		//game logo
		CCSprite* pLogoSprite;
		// 3. Add add a splash screen, show the cocos2d splash image.
		pLogoSprite = CCSprite::create("glogo.png");
		CC_BREAK_IF(! pLogoSprite);

		// Place the sprite on the center of the screen
		pLogoSprite->setAnchorPoint(ccp(0.0f, 01.f));
		pLogoSprite->setPosition(ccp(0, size.height));
		// Add the sprite to HelloWorld layer as a child layer.
		this->addChild(pLogoSprite, -4);

		CCSprite* pBottleSprite = CCSprite::create("bottle.png");
		CC_BREAK_IF(! pBottleSprite);
		pBottleSprite->setAnchorPoint(ccp(0.0f, 0.0f));
		// Place the sprite on the center of the screen
		pBottleSprite->setPosition(ccp(0.0f, 0.0f));
		// Add the sprite to HelloWorld layer as a child layer.
		this->addChild(pBottleSprite, 4);

		SetupWorld();

		/*
		sn = ShaderNode::shaderNodeWithVertex("Shaders/example_Flower.vsh", "Shaders/example_Flower.fsh");
		sn->setPosition(ccp(size.width/2, size.height/2));
		addChild(sn, -1);
		*/

		rTexture = CCRenderTexture::create(WIN_WIDTH, WIN_HEIGHT,(CCTexture2DPixelFormat)kTexture2DPixelFormat_RGBA4444);
		gTexture = CCRenderTexture::create(WIN_WIDTH, WIN_HEIGHT,(CCTexture2DPixelFormat)kTexture2DPixelFormat_RGBA4444);
		bTexture = CCRenderTexture::create(WIN_WIDTH, WIN_HEIGHT,(CCTexture2DPixelFormat)kTexture2DPixelFormat_RGBA4444);
		yTexture = CCRenderTexture::create(WIN_WIDTH, WIN_HEIGHT,(CCTexture2DPixelFormat)kTexture2DPixelFormat_RGBA4444);
		if (NULL == rTexture)
		{
			CCLog("create renderTex fail");
			return false;
		}
		mainTexture = CCRenderTexture::create(WIN_WIDTH, WIN_HEIGHT, (CCTexture2DPixelFormat)kTexture2DPixelFormat_RGBA4444);
		
		
		if (NULL == mainTexture)
		{
			CCLog("create mainTexture fail");
			return false;
		}

		
		///
		 //renderTexture.sprite.shaderProgram = [[CCGLProgram alloc] initWithVertexShaderByteArray:ccPositionTextureA8Color_vert
//fragmentShaderByteArray:ccPositionTextureColorAlphaTest_frag];

		 shader = new CCGLProgram();
		 //shader->initWithVertexShaderByteArray(ccPositionTextureA8Color_vert, ccPositionTextureColorAlphaTest_frag);
		 shader->initWithVertexShaderFilename("Shaders/mix.vsh", "Shaders/mix.fsh");
		 rTexture->getSprite()->setShaderProgram(shader);
		 gTexture->getSprite()->setShaderProgram(shader);
		 bTexture->getSprite()->setShaderProgram(shader);
		 yTexture->getSprite()->setShaderProgram(shader);
		 shader->release();
        //[renderTexture.sprite.shaderProgram addAttribute:kCCAttributeNamePosition index:kCCVertexAttrib_Position];
		shader->addAttribute(kCCAttributeNamePosition, kCCVertexAttrib_Position);
        //[renderTexture.sprite.shaderProgram addAttribute:kCCAttributeNameColor index:kCCVertexAttrib_Color];
		shader->addAttribute(kCCAttributeNameColor, kCCVertexAttrib_Color);
        //[renderTexture.sprite.shaderProgram addAttribute:kCCAttributeNameTexCoord index:kCCVertexAttrib_TexCoords];
		shader->addAttribute(kCCAttributeNameTexCoord, kCCVertexAttrib_TexCoords);
		shader->link();
		shader->updateUniforms();

		 alphaValueLocation = glGetUniformLocation(shader->getProgram(), "u_alpha_value");
		 colorValueLocation = glGetUniformLocation(shader->getProgram(), "u_color_value");
		 //m_uMaskLocation    = glGetUniformLocation( shader->getProgram(), "u_mask");
		shader->setUniformLocationWith1f(alphaValueLocation, THROLD);
		shader->use();
		///
		CCGLProgram* pProgram = new CCGLProgram();
        pProgram->initWithVertexShaderFilename("Shaders/mix.vsh", "Shaders/mix2.fsh");
		mainTexture->getSprite()->setShaderProgram(pProgram);
        pProgram->release();

        getShaderProgram()->addAttribute(kCCAttributeNamePosition, kCCVertexAttrib_Position);
        getShaderProgram()->addAttribute(kCCAttributeNameColor, kCCVertexAttrib_Color);
        getShaderProgram()->addAttribute(kCCAttributeNameTexCoord, kCCVertexAttrib_TexCoords);

        getShaderProgram()->link();
        getShaderProgram()->updateUniforms();
		m_uMaskLocation    = glGetUniformLocation( shader->getProgram(), "u_mask");
		m_u2MaskLocation    = glGetUniformLocation( shader->getProgram(), "u_mask2");
		m_u3MaskLocation    = glGetUniformLocation( shader->getProgram(), "u_mask3");
		m_u4MaskLocation    = glGetUniformLocation( shader->getProgram(), "u_mask4");
		///
		//renderTexture->setAnchorPoint(ccp(0.0, -1));
		rTexture->setPosition(ccp(WIN_WIDTH/2.0, WIN_HEIGHT/2.0));
		rTexture->retain();

		gTexture->setPosition(ccp(WIN_WIDTH/2.0, WIN_HEIGHT/2.0));
		gTexture->retain();

		bTexture->setPosition(ccp(WIN_WIDTH/2.0, WIN_HEIGHT/2.0));
		bTexture->retain();

		yTexture->setPosition(ccp(WIN_WIDTH/2.0, WIN_HEIGHT/2.0));
		yTexture->retain();

		//mainTexture->getSprite()->setShaderProgram(shader);
		mainTexture->setAnchorPoint(ccp(0.5,0.5));
		mainTexture->setPosition(ccp(WIN_WIDTH/2, WIN_HEIGHT/2.0));


		

		addChild(mainTexture, -2);
		scheduleUpdate();
		bRet = true;
	} while (0);

	return bRet;
}


void Stage::SetupWorld( void )
{
	CCSize s = CCDirector::sharedDirector()->getWinSize();

	b2Vec2 gravity;
	gravity.Set(-0.0f, -10.0f);
	world = new b2World(gravity);

	// Do we want to let bodies sleep?
	world->SetAllowSleeping(true);

	world->SetContinuousPhysics(true);

	m_debugDraw = new GLESDebugDraw(32.0f);
	world->SetDebugDraw(m_debugDraw);


	uint32 flags = 0;
	flags += b2Draw::e_shapeBit;
	//        flags += b2Draw::e_jointBit;
	//        flags += b2Draw::e_aabbBit;
	//        flags += b2Draw::e_pairBit;
	flags += b2Draw::e_centerOfMassBit;
	m_debugDraw->SetFlags(flags);


	// Define the ground body.
	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0, 0); // bottom-left corner

	// Call the body factory which allocates memory for the ground body
	// from a pool and creates the ground box shape (also from a pool).
	// The body is also added to the world.
	b2Body* groundBody = world->CreateBody(&groundBodyDef);

	// Define the ground box shape.
	b2EdgeShape groundBox;

	vector<b2Vec2> groundEdge;
	groundEdge.push_back(b2Vec2(460.000,957.500));
	groundEdge.push_back(b2Vec2(412.500,871.000));
	groundEdge.push_back(b2Vec2(415.500,721.000));
	groundEdge.push_back(b2Vec2(610.500,257.000));
	groundEdge.push_back(b2Vec2(642.000,960.000 ));
	//groundEdge.push_back(b2Vec2(460.000,957.500));

	for (vector<b2Vec2>::iterator it = groundEdge.begin();
		it != groundEdge.end(); ++it)
	{
		b2Vec2 a = (b2Vec2)*it;
		if(it+1 == groundEdge.end())break;
		b2Vec2 b = (b2Vec2)*(it+1);
		groundBox.Set(b2Vec2(a.x/PTM_RATIO,a.y/PTM_RATIO), b2Vec2(b.x/PTM_RATIO,b.y/PTM_RATIO));
		groundBody->CreateFixture(&groundBox,0);
	}

	groundEdge.clear();
	groundEdge.push_back(b2Vec2(226.500,879.000));
	groundEdge.push_back(b2Vec2(172.000,960.500));
	groundEdge.push_back(b2Vec2(2.000,959.000));
	groundEdge.push_back(b2Vec2(31.500,266.000));
	groundEdge.push_back(b2Vec2(220.500,704.000 ));
	groundEdge.push_back(b2Vec2(226.500,879.000));
	for (vector<b2Vec2>::iterator it = groundEdge.begin();
		it != groundEdge.end(); ++it)
	{
		b2Vec2 a = (b2Vec2)*it;
		if(it+1 == groundEdge.end())break;
		b2Vec2 b = (b2Vec2)*(it+1);
		groundBox.Set(b2Vec2(a.x/PTM_RATIO,a.y/PTM_RATIO), b2Vec2(b.x/PTM_RATIO,b.y/PTM_RATIO));
		groundBody->CreateFixture(&groundBox,0);
	}

	groundEdge.clear();
	groundEdge.push_back(b2Vec2(642.000,960.000));
	groundEdge.push_back(b2Vec2(610.500,257.000));
	groundEdge.push_back(b2Vec2(635.000,-1.000 ));

	for (vector<b2Vec2>::iterator it = groundEdge.begin();
		it != groundEdge.end(); ++it)
	{
		b2Vec2 a = (b2Vec2)*it;
		if(it+1 == groundEdge.end())break;
		b2Vec2 b = (b2Vec2)*(it+1);
		groundBox.Set(b2Vec2(a.x/PTM_RATIO,a.y/PTM_RATIO), b2Vec2(b.x/PTM_RATIO,b.y/PTM_RATIO));
		groundBody->CreateFixture(&groundBox,0);
	}

	groundEdge.clear();
	groundEdge.push_back(b2Vec2(610.500,257.000));
	groundEdge.push_back(b2Vec2(597.500,87.000));
	groundEdge.push_back(b2Vec2(635.000,-1.000 ));
	for (vector<b2Vec2>::iterator it = groundEdge.begin();
			it != groundEdge.end(); ++it)
	{
		b2Vec2 a = (b2Vec2)*it;
		if(it+1 == groundEdge.end())break;
		b2Vec2 b = (b2Vec2)*(it+1);
		groundBox.Set(b2Vec2(a.x/PTM_RATIO,a.y/PTM_RATIO), b2Vec2(b.x/PTM_RATIO,b.y/PTM_RATIO));
		groundBody->CreateFixture(&groundBox,0);
	}

	groundEdge.clear();
	groundEdge.push_back(b2Vec2(597.500,87.000));
	groundEdge.push_back(b2Vec2(516.000,33.500));
	groundEdge.push_back(b2Vec2(635.000,-1.000 ));
	for (vector<b2Vec2>::iterator it = groundEdge.begin();
			it != groundEdge.end(); ++it)
	{
		b2Vec2 a = (b2Vec2)*it;
		if(it+1 == groundEdge.end())break;
		b2Vec2 b = (b2Vec2)*(it+1);
		groundBox.Set(b2Vec2(a.x/PTM_RATIO,a.y/PTM_RATIO), b2Vec2(b.x/PTM_RATIO,b.y/PTM_RATIO));
		groundBody->CreateFixture(&groundBox,0);
	}

	groundEdge.clear();
	groundEdge.push_back(b2Vec2(516.000,33.500));
	groundEdge.push_back(b2Vec2(216.000,21.500));
	groundEdge.push_back(b2Vec2(-1.000,1.000));
	groundEdge.push_back(b2Vec2(635.000,-1.000 ));
	for (vector<b2Vec2>::iterator it = groundEdge.begin();
			it != groundEdge.end(); ++it)
	{
		b2Vec2 a = (b2Vec2)*it;
		if(it+1 == groundEdge.end())break;
		b2Vec2 b = (b2Vec2)*(it+1);
		groundBox.Set(b2Vec2(a.x/PTM_RATIO,a.y/PTM_RATIO), b2Vec2(b.x/PTM_RATIO,b.y/PTM_RATIO));
		groundBody->CreateFixture(&groundBox,0);
	}

	groundEdge.clear();
	groundEdge.push_back(b2Vec2(216.000,21.500));
	groundEdge.push_back(b2Vec2(68.500,54.000));
	groundEdge.push_back(b2Vec2(-1.000,1.000 ));
	for (vector<b2Vec2>::iterator it = groundEdge.begin();
			it != groundEdge.end(); ++it)
	{
		b2Vec2 a = (b2Vec2)*it;
		if(it+1 == groundEdge.end())break;
		b2Vec2 b = (b2Vec2)*(it+1);
		groundBox.Set(b2Vec2(a.x/PTM_RATIO,a.y/PTM_RATIO), b2Vec2(b.x/PTM_RATIO,b.y/PTM_RATIO));
		groundBody->CreateFixture(&groundBox,0);
	}

	groundEdge.clear();
	groundEdge.push_back(b2Vec2(68.500,54.000));
	groundEdge.push_back(b2Vec2(28.500,117.000));
	groundEdge.push_back(b2Vec2(-1.000,1.000 ));
	for (vector<b2Vec2>::iterator it = groundEdge.begin();
			it != groundEdge.end(); ++it)
	{
		b2Vec2 a = (b2Vec2)*it;
		if(it+1 == groundEdge.end())break;
		b2Vec2 b = (b2Vec2)*(it+1);
		groundBox.Set(b2Vec2(a.x/PTM_RATIO,a.y/PTM_RATIO), b2Vec2(b.x/PTM_RATIO,b.y/PTM_RATIO));
		groundBody->CreateFixture(&groundBox,0);
	}

	groundEdge.clear();
	groundEdge.push_back(b2Vec2(28.500,117.000));
	groundEdge.push_back(b2Vec2(31.500,266.000));
	groundEdge.push_back(b2Vec2(2.000,959.000));
	groundEdge.push_back(b2Vec2(-1.000,1.000 ));
	for (vector<b2Vec2>::iterator it = groundEdge.begin();
			it != groundEdge.end(); ++it)
	{
		b2Vec2 a = (b2Vec2)*it;
		if(it+1 == groundEdge.end())break;
		b2Vec2 b = (b2Vec2)*(it+1);
		groundBox.Set(b2Vec2(a.x/PTM_RATIO,a.y/PTM_RATIO), b2Vec2(b.x/PTM_RATIO,b.y/PTM_RATIO));
		groundBody->CreateFixture(&groundBox,0);
	}

	setTouchEnabled(true);

}
int totalBall = TOTAL_BALLS;
void Stage::ccTouchesBegan( cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent )
{
	if(totalBall < 1){
		return;
	};
	CCSetIterator it;
	CCTouch* touch;

	for( it = pTouches->begin(); it != pTouches->end(); it++) 
	{
		touch = (CCTouch*)(*it);

		if(!touch)
			break;

		CCPoint location = touch->locationInView();

		location = CCDirector::sharedDirector()->convertToGL(location);

		/////
		b2BodyDef bodyDef;
		bodyDef.type = b2_dynamicBody;
		CCSize s = CCDirector::sharedDirector()->getWinSize();
		location.x = s.width * 0.6;
		location.y = s.height * 0.85;
		bodyDef.position.Set(location.x/PTM_RATIO, location.y/PTM_RATIO);

		body = world->CreateBody(&bodyDef);

		// Define another box shape for our dynamic body.

		b2CircleShape dynamicCircle;
		float rtmp = BALL_R ;//+ 10 * CCRANDOM_MINUS1_1();
		dynamicCircle.m_radius = rtmp / PTM_RATIO;
		// Define the dynamic body fixture.
		b2FixtureDef fixtureDef;
		fixtureDef.shape = &dynamicCircle;    
		fixtureDef.density = 3.0f;
		fixtureDef.friction = 0.8f;
		fixtureDef.restitution = 0.5f;
		body->CreateFixture(&fixtureDef);
		body->ResetMassData();

		
		float tmp = CCRANDOM_0_1();
		
		Ball* pBall = new Ball();
		pBall->m_r = rtmp;
		pBall->m_pBody = body;
		pBall->pos.x = body->GetPosition().x * PTM_RATIO;
		pBall->pos.y = body->GetPosition().y * PTM_RATIO;
		ball_vec_.push_back(pBall);
		//CCLog("ball info: color=%d, x=%f, y=%f",pBall->m_color, pBall->pos.x, pBall->pos.y );
		totalBall--;


	}
}

float m_time = 0.0f;
void Stage::update(float dt)
{
	m_time += dt;
	int velocityIterations = 8;
	int positionIterations = 3;
	//step the world
	world->Step(dt, velocityIterations, positionIterations);
	
	//gen image1
	rTexture->clear(0,0,0,0);
	rTexture->begin();
	for (vector<Ball*>::iterator it = ball_vec_.begin();
					it != ball_vec_.end(); ++it)
	{
		if((*it)->m_color != 0)continue;
		float x=(*it)->m_pBody->GetPosition().x * PTM_RATIO;
		float y=(*it)->m_pBody->GetPosition().y * PTM_RATIO;
		(*it)->ballSprite->setAnchorPoint(ccp(0.5,0.5));
		(*it)->ballSprite->setPosition( ccp(x,y));
		
		(*it)->ballSprite->visit();
	}
	rTexture->end();
	rTexture->getSprite()->setAnchorPoint(ccp(0.5, 0.5));
	rTexture->getSprite()->setPosition(ccp(WIN_WIDTH/2, WIN_HEIGHT/2.0));
	
	////
	gTexture->clear(0,0,0,0);
	gTexture->begin();
	for (vector<Ball*>::iterator it = ball_vec_.begin();
					it != ball_vec_.end(); ++it)
	{
		if((*it)->m_color != 1)continue;
		float x=(*it)->m_pBody->GetPosition().x * PTM_RATIO;
		float y=(*it)->m_pBody->GetPosition().y * PTM_RATIO;
		(*it)->ballSprite->setPosition( ccp(x,y));
		(*it)->ballSprite->visit();
	}
	gTexture->end();
	gTexture->getSprite()->setAnchorPoint(ccp(0.5, 0.5));
	gTexture->getSprite()->setPosition(ccp(WIN_WIDTH/2, WIN_HEIGHT/2.0));
	//shader->setUniformLocationWith1f(colorValueLocation, 1.0);
	
	bTexture->clear(0,0,0,0);
	bTexture->begin();
	
	for (vector<Ball*>::iterator it = ball_vec_.begin();
					it != ball_vec_.end(); ++it)
	{
		if((*it)->m_color != 2)continue;
		float x=(*it)->m_pBody->GetPosition().x * PTM_RATIO;
		float y=(*it)->m_pBody->GetPosition().y * PTM_RATIO;
		(*it)->ballSprite->setPosition( ccp(x,y));
		(*it)->ballSprite->visit();
	}

	bTexture->end();
	bTexture->getSprite()->setAnchorPoint(ccp(0.5, 0.5));
	bTexture->getSprite()->setPosition(ccp(WIN_WIDTH/2, WIN_HEIGHT/2.0));
	
	//shader->setUniformLocationWith1f(colorValueLocation, 2.0);

	/////
	yTexture->clear(0,0,0,0);
	yTexture->begin();
	for (vector<Ball*>::iterator it = ball_vec_.begin();
					it != ball_vec_.end(); ++it)
	{
		if((*it)->m_color != 3)continue;
		float x=(*it)->m_pBody->GetPosition().x * PTM_RATIO;
		float y=(*it)->m_pBody->GetPosition().y * PTM_RATIO;
		(*it)->ballSprite->setPosition( ccp(x,y));
		(*it)->ballSprite->visit();
	}


	yTexture->end();
	yTexture->getSprite()->setAnchorPoint(ccp(0.5, 0.5));
	yTexture->getSprite()->setPosition(ccp(WIN_WIDTH/2, WIN_HEIGHT/2.0));

	mainTexture->clear(0,0,0,0);
	mainTexture->begin();
	/*rTexture->getSprite()->visit();
	shader->setUniformLocationWith1f(colorValueLocation, 0.0);

	gTexture->getSprite()->visit();
	shader->setUniformLocationWith1f(colorValueLocation, 1.0);

	bTexture->getSprite()->visit();
	shader->setUniformLocationWith1f(colorValueLocation, 2.0);

	yTexture->getSprite()->visit();
	shader->setUniformLocationWith1f(colorValueLocation, 3.0);*/
	mainTexture->end();

	glActiveTexture(GL_TEXTURE1);
	glBindTexture( GL_TEXTURE_2D, rTexture->getSprite()->getTexture()->getName() );
	glUniform1i(m_uMaskLocation, 1);

	/*glActiveTexture(GL_TEXTURE2);
    glBindTexture( GL_TEXTURE_2D, gTexture->getSprite()->getTexture()->getName() );
	glUniform1i(m_u2MaskLocation, 2);

	glActiveTexture(GL_TEXTURE3);
    glBindTexture( GL_TEXTURE_2D, bTexture->getSprite()->getTexture()->getName() );
	glUniform1i(m_u3MaskLocation, 3);

	glActiveTexture(GL_TEXTURE4);
	glBindTexture( GL_TEXTURE_2D, yTexture->getSprite()->getTexture()->getName() );
	glUniform1i(m_u4MaskLocation, 4);
*/
	glActiveTexture(GL_TEXTURE0);


	////end
	/////
	
}
void Stage::draw()
{
	//
	// IMPORTANT:
	// This is only for debug purposes
	// It is recommend to disable it
	//
	CCLayer::draw();
	//glEnable(GL_ALPHA_TEST);
    //glAlphaFunc(GL_GREATER, 0.7f);
	ccGLEnableVertexAttribs( kCCVertexAttribFlag_Position );

	kmGLPushMatrix();
	//m_debugDraw->DrawString(5, 15, "bodies/contacts/joints = %d/%d/%d", 0, 88, 88);
	if(box2dDebug)
	world->DrawDebugData();


	kmGLPopMatrix();
}

Stage::~Stage()
{
	rTexture->release();
	gTexture->release();
	bTexture->release();
	yTexture->release();

	//mainTexture->release();
	delete world;
	world = NULL;
}

