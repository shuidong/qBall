#include "ShaderNode.h"
#include "Confings.h"

#include "cocos2d.h"
#include "Ball.h"
#include "Box2D/Box2D.h"

using namespace cocos2d;
///---------------------------------------
// 
// ShaderNode
// 
///---------------------------------------
float SIZE_X = WIN_WIDTH;
float SIZE_Y = WIN_HEIGHT;

ShaderNode::ShaderNode()
:m_center(vertex2(0.0f, 0.0f))
//,m_resolution(vertex2(0.0f, 0.0f))
//,pixel(vertex2(0.0f, 0.0f))
,m_time(0.0f)
,m_uniformCenter(0)
//,m_uniformResolution(0)
,m_uniformTime(0)
,m_uniformPixel(0)
{
	for(int i =0; i < arraySize; i++)
	{
		nima[i].x = 0.0f;
		nima[i].y = 0.0f;
	}
}

ShaderNode* ShaderNode::shaderNodeWithVertex(const char *vert, const char *frag)
{
    ShaderNode *node = new ShaderNode();
    node->initWithVertex(vert, frag);
    node->autorelease();

    return node;
}

bool ShaderNode::initWithVertex(const char *vert, const char *frag)
{

    loadShaderVertex(vert, frag);

    m_time = 0;
//    m_resolution = vertex2(WIN_WIDTH/SCALE_V, WIN_HEIGHT/SCALE_V);

    scheduleUpdate();

    setContentSize(CCSizeMake(SIZE_X, SIZE_Y));
    setAnchorPoint(ccp(0.5f, 0.5f));

    return true;
}

void ShaderNode::loadShaderVertex(const char *vert, const char *frag)
{
    CCGLProgram *shader = new CCGLProgram();
    shader->initWithVertexShaderFilename(vert, frag);

    shader->addAttribute("aVertex", kCCVertexAttrib_Position);
    shader->link();

    shader->updateUniforms();

    m_uniformCenter = glGetUniformLocation(shader->getProgram(), "center");
   // m_uniformResolution = glGetUniformLocation(shader->getProgram(), "resolution");
	

    m_uniformTime = glGetUniformLocation(shader->getProgram(), "time");
m_uniformPixel =  glGetUniformLocation(shader->getProgram(), "nima");
	
    this->setShaderProgram(shader);

    shader->release();
}

void ShaderNode::update(float dt)
{
    m_time += dt;
	
	memset(&nima, 0, sizeof(ccVertex2F)*arraySize);
	//for (vector<Ball*>::iterator it = ball_vec_.begin();
	//				it != ball_vec_.end(); ++it)
	//{
	//	b2Vec2 center = (*it)->m_pBody->GetPosition();
	//	center.x *= PTM_RATIO;
	//	center.y *= PTM_RATIO;

	//	float r = (*it)->m_r;
	//	int dltr = 1.1 * r;
	//	int xstart = max(0, center.x - dltr);
	//	int ystart = max(0, center.y - dltr);

	//	int xend = min(WIN_WIDTH, center.x + dltr);
	//	int yend = min(WIN_HEIGHT, center.y + dltr);

	//	for(int x = xstart; x < xend; x ++)
	//	{
	//		for(int y = ystart; y < yend; y ++)
	//		{
	//			//if(nima[y * WIN_WIDTH + x].x != 0.0f)break;
	//			if(b2Abs(x - center.x) + b2Abs(y - center.y) < r)
	//			{
	//			//	nima[y * WIN_WIDTH + x].x = 100.0f;
	//			}
	//			//count the E
	//			float etmp = 0.0f;
	//			for (vector<Ball*>::iterator pb = ball_vec_.begin();
	//				pb != ball_vec_.end(); ++pb)
	//			{
	//				float bcx = (*pb)->m_pBody->GetPosition().x;
	//				float bcy = (*pb)->m_pBody->GetPosition().y;
	//				etmp += ((*pb)->m_r * (*pb)->m_r)/( (bcx - x)*(bcx - x) + (bcy - y)*(bcy - y));
	//				if(etmp >= 0.1)break;
	//			}
	//			nima[0].x = etmp;
	//		}

	//	}
	//}
}

void ShaderNode::setPosition(const CCPoint &newPosition)
{
    CCNode::setPosition(newPosition);
    CCPoint position = getPosition();
	m_center = vertex2(position.x * CC_CONTENT_SCALE_FACTOR() / SCALE_V, position.y * CC_CONTENT_SCALE_FACTOR() / SCALE_V);
}

void ShaderNode::draw()
{
    CC_NODE_DRAW_SETUP();

    float w = SIZE_X, h = SIZE_Y;
    GLfloat vertices[12] = {0,0, w,0, w,h, 0,0, 0,h, w,h};

    //
    // Uniforms
    //
    getShaderProgram()->setUniformLocationWith2f(m_uniformCenter, m_center.x, m_center.y);
    //getShaderProgram()->setUniformLocationWith2f(m_uniformResolution, m_resolution.x, m_resolution.y);
	getShaderProgram()->setUniformLocationWith2fv(m_uniformPixel, (GLfloat *)&nima, arraySize);
    // time changes all the time, so it is Ok to call OpenGL directly, and not the "cached" version
    glUniform1f(m_uniformTime, m_time);
	///
	//glUniform1fv(m_uniformPixel,WIN_WIDTH * WIN_HEIGHT,(const float*)&pixel);
	

    ccGLEnableVertexAttribs( kCCVertexAttribFlag_Position );

    glVertexAttribPointer(kCCVertexAttrib_Position, 2, GL_FLOAT, GL_FALSE, 0, vertices);

    glDrawArrays(GL_TRIANGLES, 0, 6);
    
    CC_INCREMENT_GL_DRAWS(1);
}