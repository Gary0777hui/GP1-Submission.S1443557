/*
=================
cRocket.cpp
- Header file for class definition - IMPLEMENTATION
=================
*/
#include "cRocket.h"
#include "winuser.h"
#include "cInputMgr.h"
//static cInputMgr* theInputMgr = cInputMgr::getInstance(); bool ok = 1;
BOOL cRocket::SetWindowPixelFormat(HDC hDC)
{
	int PixelFormat;
	PIXELFORMATDESCRIPTOR pixelDesc;

	pixelDesc.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pixelDesc.nVersion = 1;

	pixelDesc.dwFlags = PFD_DRAW_TO_WINDOW |
		PFD_SUPPORT_OPENGL |
		PFD_DOUBLEBUFFER |
		PFD_TYPE_RGBA;

	pixelDesc.iPixelType = PFD_TYPE_RGBA;
	pixelDesc.cColorBits = 32;
	pixelDesc.cRedBits = 0;
	pixelDesc.cRedShift = 0;
	pixelDesc.cGreenBits = 0;
	pixelDesc.cGreenShift = 0;
	pixelDesc.cBlueBits = 0;
	pixelDesc.cBlueShift = 0;
	pixelDesc.cAlphaBits = 0;
	pixelDesc.cAlphaShift = 0;
	pixelDesc.cAccumBits = 0;
	pixelDesc.cAccumRedBits = 0;
	pixelDesc.cAccumGreenBits = 0;
	pixelDesc.cAccumBlueBits = 0;
	pixelDesc.cAccumAlphaBits = 0;
	pixelDesc.cDepthBits = 32;
	pixelDesc.cStencilBits = 1;
	pixelDesc.cAuxBuffers = 0;
	pixelDesc.iLayerType = PFD_MAIN_PLANE;
	pixelDesc.bReserved = 0;
	pixelDesc.dwLayerMask = 0;
	pixelDesc.dwVisibleMask = 0;
	pixelDesc.dwDamageMask = 0;

	PixelFormat = ChoosePixelFormat(hDC, &pixelDesc);
	if (PixelFormat == 0) // Choose default
	{
		PixelFormat = 1;
		if (DescribePixelFormat(hDC, PixelFormat,
			sizeof(PIXELFORMATDESCRIPTOR), &pixelDesc) == 0)
		{
			return FALSE;
		}
	}

	if (SetPixelFormat(hDC, PixelFormat, &pixelDesc) == FALSE)

	{
		return FALSE;
	}

	return TRUE;
}


BOOL cRocket::CreateViewGLContext(HDC hDC)
{
	HGLRC hrenderRC;
	hrenderRC = wglCreateContext(hDC);

	if (hrenderRC == NULL)
		return FALSE;

	if (wglMakeCurrent(hDC, hrenderRC) == FALSE)
		return FALSE;



	return TRUE;
}
void cRocket::selectFont(int size, int charset, const char* face)
{
	HFONT hFont = CreateFontA(size, 0, 0, 0, FW_MEDIUM, 0, 0, 0,
		charset, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, face);
	HFONT hOldFont = (HFONT)SelectObject(wglGetCurrentDC(), hFont);
	DeleteObject(hOldFont);
}
void cRocket::drawString(const char* str)  
{

	static int isFirstCall = 1;
	static GLuint lists;

	if (isFirstCall) {
		isFirstCall = 0;
	
		lists = glGenLists(128);
	 
		wglUseFontBitmaps(wglGetCurrentDC(), 0, 128, lists);
	}

	for (; *str != '\0'; ++str) {
		glCallList(lists + *str);
	}
}
void cRocket::OnDisplay_Font2()
{
	bool h = 0;
	bool h2 = 0;
	int a=0;
	char tt[12];
	char ttt[12];
	const char* aaa;
	const char* bbb;
	int jib;
	selectFont(50, ANSI_CHARSET, "digital-7");
	glColor3f(0.0f, 1.0f, 0.0f);    

	glRasterPos2f(700.0f, 100.0f);  
	sprintf_s(tt, "%d", count);
	aaa=tt;

	drawString(aaa);  

	glRasterPos2f(500.0f, 100.0f);
	sprintf_s(tt, "%d", count2);
	bbb = ttt;

	drawString(bbb);  

	if (count == 5 && count2 ==0 && count==5+count2)
	{
		glRasterPos2f(250.0f, 300.0f);
		drawString("congratiulations,well done!!");
	
	}
	if (count2 <0 || count2 < 0&&count < 5)
	{
		glRasterPos2f(250.0f, 300.0f);
		drawString("Game over!!pls replay!!");
	
	}
	
}

void cRocket::OnDisplay_Font()
{
	
	selectFont(150, ANSI_CHARSET, "digital-7"); 
	glColor3f(0.0f, 1.0f, 0.0f);    

	glRasterPos2f(200.0f, 100.0f); 
		drawString("BEGIN");
	
}
void cRocket::OnDisplay_Font3()
{

	selectFont(150, ANSI_CHARSET, "digital-7"); 
	glColor3f(0.0f, 1.0f, 0.0f);  

	glRasterPos2f(200.0f, 100.0f);  
	drawString("REPLAY");

}
void cRocket::renderfont3()
{

	//	if (!ok)
	//{
	glLoadIdentity();
	gluOrtho2D(0.0f, 1.0f, 0.0f, 1.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	OnDisplay_Font3();
	glPopMatrix();

	//}

}
void cRocket::renderfont()
{
	
//	if (!ok)
	//{
		glLoadIdentity();
		gluOrtho2D(0.0f, 1.0f, 0.0f, 1.0f);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		OnDisplay_Font();
		glPopMatrix();

	//}

}
void cRocket::renderfont2()
{
	
		glLoadIdentity();
		gluOrtho2D(0.0f, 1.0f, 0.0f, 1.0f);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		
		OnDisplay_Font2();
		glPopMatrix();
	
}
void cRocket::render()
{
	
	
	glPushMatrix();

	glTranslatef(spritePos2D.x, spritePos2D.y, 0.0f);
	glRotatef(spriteRotation, 0.0f, 0.0f, 1.0f);
	glScalef(spriteScaling.x, spriteScaling.y, 1.0f);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, GLTextureID); // Binding of GLtexture name 

	glBegin(GL_QUADS);
	glColor3f(255.0f, 255.0f, 255.0f);
	glTexCoord2f(spriteTexCoordData[0].x, spriteTexCoordData[0].y);
	glVertex2f(-(textureWidth / 2), -(textureHeight / 2));
	glTexCoord2f(spriteTexCoordData[1].x, spriteTexCoordData[1].y);
	glVertex2f((textureWidth / 2), -(textureHeight / 2));
	glTexCoord2f(spriteTexCoordData[2].x, spriteTexCoordData[2].y);
	glVertex2f((textureWidth / 2), (textureHeight / 2));
	glTexCoord2f(spriteTexCoordData[3].x, spriteTexCoordData[3].y);
	glVertex2f(-(textureWidth / 2), (textureHeight / 2));
	
	glEnd();
	glDisable(GL_TEXTURE_2D);

	glPopMatrix();
	
}
/*
=================================================================
Update the sprite position
=================================================================
*/

void cRocket::update(float deltaTime)
{
	

	
	if (m_InputMgr->isKeyDown(VK_RIGHT))
	{
		spriteRotation += 5.0f;
	}
	if (m_InputMgr->isKeyDown(VK_LEFT))
	{
		spriteRotation -= 5.0f;
	}
	if (m_InputMgr->isKeyDown(VK_UP))
	{
		spriteTranslation = (glm::vec2(2.0f, 2.0f));
	}
	if (m_InputMgr->isKeyDown(VK_DOWN))
	{
		spriteTranslation = -(glm::vec2(2.0f, 2.0f));
	}
	if (m_InputMgr->isKeyDown(int('A')))
	{
		spriteScaling += 0.2f;
	}
	if (m_InputMgr->isKeyDown(int('S')))
	{
		spriteScaling -= 0.2f;
	}

	if (m_InputMgr->isKeyDown(VK_SPACE))
	{
		// Add new bullet sprite to the vector array
		theRocketBullets.push_back(new cBullet);
		int numBullets = theRocketBullets.size() - 1;
		theRocketBullets[numBullets]->setSpritePos(glm::vec2(spritePos2D.x , spritePos2D.y));
		theRocketBullets[numBullets]->setSpriteTranslation(glm::vec2(2.0f, 2.0f));
		theRocketBullets[numBullets]->setTexture(theGameTextures[4]->getTexture());
		theRocketBullets[numBullets]->setTextureDimensions(theGameTextures[4]->getTWidth(), theGameTextures[4]->getTHeight());
		theRocketBullets[numBullets]->setSpriteCentre();
		theRocketBullets[numBullets]->setBulletVelocity(glm::vec2(0.0f, 0.0f));
		theRocketBullets[numBullets]->setSpriteRotation(getSpriteRotation());
		theRocketBullets[numBullets]->setActive(true);
		theRocketBullets[numBullets]->setMdlRadius();
		// play the firing sound
		m_SoundMgr->getSnd("Shot")->playAudio(AL_TRUE);
		count2 -= 1;
		if (count2<-1)
		{
	
				
					count2 = 5;
			
		}
	}

	if (spriteRotation > 360)
	{
		spriteRotation -= 360.0f;
	}

	glm::vec2 spriteVelocityAdd = glm::vec2(0.0f, 0.0f);
	spriteVelocityAdd.x = (glm::sin(glm::radians(spriteRotation)));
	spriteVelocityAdd.y = -(glm::cos(glm::radians(spriteRotation)));

	spriteVelocityAdd *= spriteTranslation;

	rocketVelocity += spriteVelocityAdd;

	spritePos2D += rocketVelocity * deltaTime;

	rocketVelocity *= 0.95;

	/*
	==============================================================
	| Check for collisions
	==============================================================
	*/
	for (vector<cBullet*>::iterator bulletIterartor = theRocketBullets.begin(); bulletIterartor != theRocketBullets.end(); ++bulletIterartor)
	{
		
		(*bulletIterartor)->update(deltaTime);
		for (vector<cAsteroid*>::iterator asteroidIterator = theAsteroids.begin(); asteroidIterator != theAsteroids.end(); ++asteroidIterator)
		{
			
			if ((*asteroidIterator)->collidedWith((*asteroidIterator)->getBoundingRect(), (*bulletIterartor)->getBoundingRect()))
			{
				// if a collision set the bullet and asteroid to false
				(*asteroidIterator)->setActive(false);
				(*bulletIterartor)->setActive(false);
				
			}
		}
	}

	vector<cBullet*>::iterator bulletIterartor = theRocketBullets.begin();
	while (bulletIterartor != theRocketBullets.end())
	{
		if ((*bulletIterartor)->isActive() == false)
		{
			bulletIterartor = theRocketBullets.erase(bulletIterartor);
			// play the explosion sound.
			m_SoundMgr->getSnd("Explosion")->playAudio(AL_TRUE);
			count+=1;
			if (count == 5)
			{
				//count = 0;
				m_SoundMgr->getSnd("Theme")->playAudio(AL_TRUE);
				

				if (count=6)
				{
							count =0;
				}
			}
		}
		else
		{
			//(*bulletIterartor)->update(deltaTime);
			(*bulletIterartor)->render();
			++bulletIterartor;
			
		}
	}
}
/*
=================================================================
  Sets the velocity for the rocket
=================================================================
*/
void cRocket::setRocketVelocity(glm::vec2 rocketVel)
{
	rocketVelocity = rocketVel;
}
/*
=================================================================
  Gets the rocket velocity
=================================================================
*/
glm::vec2 cRocket::getRocketVelocity()
{
	return rocketVelocity;
}
