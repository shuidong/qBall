#include "SpriteShader.h"

using namespace cocos2d;

SpriteShader* SpriteShader::create(const char *pszFileName)
{
    SpriteShader* pRet = new SpriteShader();
    if (pRet && pRet->initWithFile(pszFileName))
    {
        pRet->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pRet);
    }
    
    return pRet;
}

bool SpriteShader::initWithTexture(CCTexture2D* texture, const CCRect& rect)
{
    if( CCSprite::initWithTexture(texture, rect) ) 
    {
        CCSize s = getTexture()->getContentSizeInPixels();

        blur_ = ccp(1/s.width, 1/s.height);
        sub_[0] = sub_[1] = sub_[2] = sub_[3] = 0;

        GLchar * fragSource = (GLchar*) CCString::createWithContentsOfFile(
            CCFileUtils::sharedFileUtils()->fullPathFromRelativePath("Shaders/example_Blur.fsh"))->getCString();
        CCGLProgram* pProgram = new CCGLProgram();
        pProgram->initWithVertexShaderByteArray(ccPositionTextureColor_vert, fragSource);
        setShaderProgram(pProgram);
        pProgram->release();

        CHECK_GL_ERROR_DEBUG();

        getShaderProgram()->addAttribute(kCCAttributeNamePosition, kCCVertexAttrib_Position);
        getShaderProgram()->addAttribute(kCCAttributeNameColor, kCCVertexAttrib_Color);
        getShaderProgram()->addAttribute(kCCAttributeNameTexCoord, kCCVertexAttrib_TexCoords);

        CHECK_GL_ERROR_DEBUG();

        getShaderProgram()->link();

        CHECK_GL_ERROR_DEBUG();

        getShaderProgram()->updateUniforms();

        CHECK_GL_ERROR_DEBUG();

        subLocation = glGetUniformLocation( getShaderProgram()->getProgram(), "substract");
        blurLocation = glGetUniformLocation( getShaderProgram()->getProgram(), "blurSize");

        CHECK_GL_ERROR_DEBUG();
        return true;
    }

    return false;
}

void SpriteShader::draw()
{
    ccGLEnableVertexAttribs(kCCVertexAttribFlag_PosColorTex );
    ccGLBlendFunc( m_sBlendFunc.src, m_sBlendFunc.dst );

    getShaderProgram()->use();
    getShaderProgram()->setUniformForModelViewProjectionMatrix();
    getShaderProgram()->setUniformLocationWith2f(blurLocation, blur_.x, blur_.y);
    getShaderProgram()->setUniformLocationWith4fv(subLocation, sub_, 1);

    ccGLBindTexture2D(  getTexture()->getName() );

    //
    // Attributes
    //
#define kQuadSize sizeof(m_sQuad.bl)
    long offset = (long)&m_sQuad;

    // vertex
    int diff = offsetof( ccV3F_C4B_T2F, vertices);
    glVertexAttribPointer(kCCVertexAttrib_Position, 3, GL_FLOAT, GL_FALSE, kQuadSize, (void*) (offset + diff));

    // texCoods
    diff = offsetof( ccV3F_C4B_T2F, texCoords);
    glVertexAttribPointer(kCCVertexAttrib_TexCoords, 2, GL_FLOAT, GL_FALSE, kQuadSize, (void*)(offset + diff));

    // color
    diff = offsetof( ccV3F_C4B_T2F, colors);
    glVertexAttribPointer(kCCVertexAttrib_Color, 4, GL_UNSIGNED_BYTE, GL_TRUE, kQuadSize, (void*)(offset + diff));


    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    CC_INCREMENT_GL_DRAWS(1);
}