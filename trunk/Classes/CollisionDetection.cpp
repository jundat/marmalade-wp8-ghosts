//
//  CollisionDetection.cpp
//  Created by Mudit Jaju on 30/08/13.
//
//  SINGLETON class for checking Pixel Based Collision Detection

#include "CollisionDetection.h"

// Singleton Instance set to NULL initially
CollisionDetection* CollisionDetection::instance = NULL;

// Handle to get Singleton Instance
CollisionDetection* CollisionDetection::GetInstance() {
    if (instance == NULL) {
        instance = new CollisionDetection();
    }
    return instance;
}

// Private Constructor being called from within the GetInstance handle
CollisionDetection::CollisionDetection() {
    // Code below to setup shaders for use in Cocos2d-x
    glProgram = new CCGLProgram();
    glProgram->retain();
    glProgram->initWithVertexShaderFilename("SolidVertexShader.vsh", "SolidColorShader.fsh");
    glProgram->addAttribute(kCCAttributeNamePosition, kCCVertexAttrib_Position);
    glProgram->addAttribute(kCCAttributeNameTexCoord, kCCVertexAttrib_TexCoords);
    glProgram->link();
    glProgram->updateUniforms();
    glProgram->use();
 
    uniformColorRed = glGetUniformLocation(glProgram->getProgram(), "u_color_red");
    uniformColorBlue = glGetUniformLocation(glProgram->getProgram(), "u_color_blue");
 
    // A large buffer created and re-used again and again to store glReadPixels data
    //buffer = (ccColor4B *)malloc( sizeof(ccColor4B) * 10000 );
}
 
bool CollisionDetection::areTheSpritesColliding(cocos2d::CCSprite* spr1, cocos2d::CCSprite* spr2, bool isCheckPerPixel, CCRenderTexture* _rt) {
    bool isColliding = false;
 
    // Rectangle of the intersecting area if the sprites are colliding according to Bounding Box collision
    CCRect intersection;
 
    // Bounding box of the Two concerned sprites being saved
    CCRect r1 = spr1->boundingBox();
    CCRect r2 = spr2->boundingBox();
 
    // Look for simple bounding box collision
    if (r1.intersectsRect(r2)) {
        // If we're not checking for pixel perfect collisions, return true
        if (!isCheckPerPixel) {
            return true;
        }

		//////////////////////////////////////////////////////////////////////////
 
        float tempX;
        float tempY;
        float tempWidth;
        float tempHeight;
 
        //OPTIMIZE FURTHER
        //CONSIDER THE CASE WHEN ONE BOUDNING BOX IS COMPLETELY INSIDE ANOTHER BOUNDING BOX!
        if (r1.getMaxX() > r2.getMinX()) {
            tempX = r2.getMinX();
            tempWidth = r1.getMaxX() - r2.getMinX();
        } else {
            tempX = r1.getMinX();
            tempWidth = r2.getMaxX() - r1.getMinX();
        }
 
        if (r2.getMaxY() < r1.getMaxY()) {
            tempY = r1.getMinY();
            tempHeight = r2.getMaxY() - r1.getMinY();
        } else {
            tempY = r2.getMinY();
            tempHeight = r1.getMaxY() - r2.getMinY();
        }
 
        // We make the rectangle for the intersection area
        intersection = CCRectMake(tempX * CC_CONTENT_SCALE_FACTOR(), tempY * CC_CONTENT_SCALE_FACTOR(), tempWidth * CC_CONTENT_SCALE_FACTOR(), tempHeight * CC_CONTENT_SCALE_FACTOR());
 
        unsigned int x = intersection.origin.x;
        unsigned int y = intersection.origin.y;
        unsigned int w = intersection.size.width;
        unsigned int h = intersection.size.height;
 
        // Total pixels whose values we will get using glReadPixels depends on the Height and Width of the intersection area
        unsigned int numPixels = w * h;
 
        // Setting the custom shader to be used
        spr1->setShaderProgram(glProgram);
        spr2->setShaderProgram(glProgram);
        glProgram->use();

		CCLOG("CHECK::: before begin");

        // Clearing the Secondary Draw buffer of all previous values
        _rt->beginWithClear( 0, 0, 0, 0);
		
		CCLOG("CHECK::: after begin");
		//////////////////////////////////////////////////////////////////////////

        // The below two values are being used in the custom shaders to set the value of RED and BLUE colors to be used
        glUniform1i(uniformColorRed, 255);
        glUniform1i(uniformColorBlue, 0);

		CCLOG("CHECK::: after begin 1");

        // The blend function is important we don't want the pixel value of the RED color being over-written by the BLUE color.
       // We want both the colors at a single pixel and hence get a PINK color (so that we have both the RED and BLUE pixels)
		ccBlendFunc b1 = {GL_SRC_ALPHA, GL_ONE};
        spr1->setBlendFunc(b1);
 
        // The visit() function draws the sprite in the _rt draw buffer its a Cocos2d-x function
        spr1->visit();

		CCLOG("CHECK::: after begin 2");

        // Setting the shader program back to the default shader being used by our game        
		spr1->setShaderProgram(CCShaderCache::sharedShaderCache()->programForKey(kCCShader_PositionTextureColor));
        // Setting the default blender function being used by the game
		ccBlendFunc b2 = {CC_BLEND_SRC, CC_BLEND_DST};
        spr1->setBlendFunc(b2);

		CCLOG("CHECK::: after begin 3");

        // Setting new values for the same shader but for our second sprite as this time we want to have an all BLUE sprite
        glUniform1i(uniformColorRed, 0);
        glUniform1i(uniformColorBlue, 255);
		ccBlendFunc b3 = {GL_SRC_ALPHA, GL_ONE};
        spr2->setBlendFunc(b3);

		CCLOG("CHECK::: after begin 4");

        spr2->visit();
 
        spr2->setShaderProgram(CCShaderCache::sharedShaderCache()->programForKey(kCCShader_PositionTextureColor));
		ccBlendFunc b4 = {CC_BLEND_SRC, CC_BLEND_DST};
        spr2->setBlendFunc(b4);

		CCLOG("CHECK::: after begin 5");

		buffer = (ccColor4B *)malloc( sizeof(ccColor4B) * w * h );

        // Get color values of intersection area
        glReadPixels(x, y, w, h, GL_RGBA, GL_UNSIGNED_BYTE, buffer);

		//////////////////////////////////////////////////////////////////////////

		CCLOG("CHECK::: after begin 6");

        _rt->end();

		CCLOG("CHECK::: after begin 7");

//		// Read buffer
        unsigned int step = 1;
        for(unsigned int i=0; i<numPixels; i+=step) {
            ccColor4B color = buffer[i];
            // Here we check if a single pixel has both RED and BLUE pixels
            if (color.r > 0 && color.b > 0) {
                isColliding = true;
                break;
            }
        }

		delete[] buffer;

		CCLOG("CHECK::: after begin 8");

    }

    return isColliding;
}