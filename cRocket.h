/*
=================
cRocket.h
- Header file for class definition - SPECIFICATION
- Header file for the Rocket class which is a child of cSprite class
=================
*/
#ifndef _CROCKET_H
#define _CROCKET_H
#include "cSprite.h"
#include "asteroidsGame.h"

class cRocket : public cSprite
{
private:
	glm::vec2 rocketVelocity = glm::vec2(0.0f, 0.0f);
	
public:
	void renderfont();
	void renderfont2();
	void renderfont3();
	void OnDisplay_Font3();
	
	void render();		// Default render function
	void update(float deltaTime);		// Rocket update method
	void setRocketVelocity(glm::vec2 rocketVel);   // Sets the velocity for the rocket
	glm::vec2 getRocketVelocity();				 // Gets the rocket velocity
	float sasa;
	int count = 0;
	int count2 =5;
	BOOL CreateViewGLContext(HDC hDC);
	BOOL SetWindowPixelFormat(HDC hDC);
	void drawString(const char* str); //ÆÁÄ»ÏÔÊ¾×ÖÌå  
	void OnDisplay_Font();
	void cRocket::OnDisplay_Font2();
	void selectFont(int size, int charset, const char* face);
	//void RenderScene();
};
#endif