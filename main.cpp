#define WIN32_LEAN_AND_MEAN
#define WIN32_EXTRA_LEAN

#define GLX_GLXEXT_LEGACY //Must be declared so that our local glxext.h is picked up, rather than the system one


#include <windows.h>
#include "windowOGL.h"
#include "GameConstants.h"
#include "cWNDManager.h"
#include "cInputMgr.h"
#include "cSoundMgr.h"
#include "cFontMgr.h"
#include "cSprite.h"
#include "asteroidsGame.h"
#include "cRocket.h"
int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR cmdLine,
	int cmdShow)
{

	//Set our window settings
	const int windowWidth = 1024;
	const int windowHeight = 768;
	const int windowBPP = 16;
	bool ok=0;
	int okk=0;

	//This is our window
	static cWNDManager* pgmWNDMgr = cWNDManager::getInstance();

	// This is the input manager
	static cInputMgr* theInputMgr = cInputMgr::getInstance();
	
	// This is the sound manager
	static cSoundMgr* theSoundMgr = cSoundMgr::getInstance();

	// This is the Font manager
	static cFontMgr* theFontMgr = cFontMgr::getInstance();

	//The example OpenGL code
	windowOGL theOGLWnd;

	//Attach our the OpenGL window
	pgmWNDMgr->attachOGLWnd(&theOGLWnd);

	// Attach the keyboard manager
	pgmWNDMgr->attachInputMgr(theInputMgr);

	//Attempt to create the window

	if (!pgmWNDMgr->createWND(windowWidth, windowHeight, windowBPP))
	{
		//If it fails

		MessageBox(NULL, "Unable to create the OpenGL Window", "An error occurred", MB_ICONERROR | MB_OK);
		pgmWNDMgr->destroyWND(); //Reset the display and exit
		return 1;
	}

	if (!theOGLWnd.initOGL(windowWidth, windowHeight)) //Initialize our example
	{
		MessageBox(NULL, "Could not initialize the application", "An error occurred", MB_ICONERROR | MB_OK);
		pgmWNDMgr->destroyWND(); //Reset the display and exit
		return 1;
	}
	
	

	//Clear key buffers
theInputMgr->clearBuffers(theInputMgr->KEYS_DOWN_BUFFER | theInputMgr->KEYS_PRESSED_BUFFER);

	/* initialize random seed: */
	srand((unsigned int)time(NULL));

	// Create vector array of textures
	LPCSTR texturesToUse[] = { "Images\\asteroid1.png", "Images\\asteroid2.png", "Images\\asteroid3.png", "Images\\asteroid4.png", "Images\\bullet.png" };
	for (int tCount = 0; tCount < 5; tCount++)
	{
		theGameTextures.push_back(new cTexture());
		theGameTextures[tCount]->createTexture(texturesToUse[tCount]);
	}

	// load game sounds
	// Load Sound
	LPCSTR gameSounds[3] = { "Space_Coast.wav", "shot007.wav", "explosion2.wav" };

	theSoundMgr->add("Theme", gameSounds[0]);
	theSoundMgr->add("Shot", gameSounds[1]);
	theSoundMgr->add("Explosion", gameSounds[2]);

	// load game fontss
	// Load Fonts
	LPCSTR gameFonts[2] = { "Fonts/lathab.ttf", "Fonts/space age.ttf" };

	//theFontMgr->addFont("SevenSeg", gameFonts[0], 24);
	theFontMgr->addFont("o", gameFonts[0], 50);
	theFontMgr->addFont("Space", gameFonts[1], 50);

	// Create vector array of textures
	

	
	
	//ok = 0;
	
	//sasa = 12;
	cTexture textureBkgd;
	textureBkgd.createTexture("Images\\starscape1024x768.png");
	cBkGround spriteBkgd;
	spriteBkgd.setSpritePos(glm::vec2(0.0f, 0.0f));
	spriteBkgd.setTexture(textureBkgd.getTexture());
	spriteBkgd.setTextureDimensions(textureBkgd.getTWidth(), textureBkgd.getTHeight());



	cTexture rocketTxt;
	rocketTxt.createTexture("Images\\rocketSprite.png");
	cRocket rocketSprite;
	rocketSprite.attachInputMgr(theInputMgr); // Attach the input manager to the sprite
	rocketSprite.setSpritePos(glm::vec2(512.0f, 380.0f));
	rocketSprite.setTexture(rocketTxt.getTexture());
	rocketSprite.setTextureDimensions(rocketTxt.getTWidth(), rocketTxt.getTHeight());
	rocketSprite.setSpriteCentre();
	rocketSprite.setRocketVelocity(glm::vec2(0.0f, 0.0f));
	
	// Attach sound manager to rocket sprite
	rocketSprite.attachSoundMgr(theSoundMgr);
	
	
    //This is the mainloop, we render frames until isRunning returns false
	while (pgmWNDMgr->isWNDRunning() )
	{
		vector<cAsteroid*>::iterator asteroidIterator;
		pgmWNDMgr->processWNDEvents(); //Process any window events

        //We get the time that passed since the last frame
		float elapsedTime = pgmWNDMgr->getElapsedSeconds();
		
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		if (theInputMgr->l_button_down == true)
		{
			//MessageBox(NULL, "1", "fgfdg", MB_ICONERROR | MB_OK);
			ok =!ok;
			
			theInputMgr->l_button_down = false;
		}
		
		spriteBkgd.render();

		rocketSprite.renderfont2();//0
		if (!ok)
		{
		rocketSprite.renderfont();//begin
		okk =0;
		
		}
		else
		{
		
			if (okk < 3)
			{
				okk += 1;
			}
			
			rocketSprite.renderfont3();
		
		}
		if (okk==1)
		{
			rocketSprite.setSpriteTranslation(glm::vec2(0.0f, 0.0f));
			rocketSprite.setSpritePos(glm::vec2(512.0f, 384.0f));
			
		
			for (int astro = 0; astro < 5; astro++)
			{
				//char gfg[12];
				//float a = 0;
				//float b = 0;

				//const char* gg;
				//float dddd = 0;
				theAsteroids.push_back(new cAsteroid);
				theAsteroids[astro]->setSpritePos(glm::vec2(windowWidth / (rand() % 5 + 1), windowHeight / (rand() % 5 + 1)));
				theAsteroids[astro]->setSpriteTranslation(glm::vec2((rand() % 4 + 1), (rand() % 4 + 1)));
				int randAsteroid = rand() % 4;
				theAsteroids[astro]->setTexture(theGameTextures[randAsteroid]->getTexture());
				theAsteroids[astro]->setTextureDimensions(theGameTextures[randAsteroid]->getTWidth(), theGameTextures[randAsteroid]->getTHeight());
				theAsteroids[astro]->setSpriteCentre();
				theAsteroids[astro]->setAsteroidVelocity(glm::vec2(glm::vec2(0.0f, 0.0f)));
				theAsteroids[astro]->setActive(true);
				theAsteroids[astro]->setMdlRadius();
				glm::vec2 pos = theAsteroids[astro]->getSpritePos();
				//a = pos.x;
				//b = pos.y;
				//MessageBox(NULL, "","", MB_ICONERROR | MB_OK);

			}
			//okk =0;
			//ok = 0;
		}
		
		if (ok)
		{
			rocketSprite.update(elapsedTime);


			asteroidIterator = theAsteroids.begin();

			while (asteroidIterator != theAsteroids.end())
			{
				if ((*asteroidIterator)->isActive() == false)
				{
					asteroidIterator = theAsteroids.erase(asteroidIterator);
				}
				else
				{
					(*asteroidIterator)->update(elapsedTime);
					(*asteroidIterator)->render();
					++asteroidIterator;
				}
			}
		}

		rocketSprite.render();
		
		//theFontMgr->getFont("o")->printText("Asteriods", FTPoint(windowHeight / 2, windowWidth / 2, 0.0f));
		
		
		pgmWNDMgr->swapBuffers();
		theInputMgr->clearBuffers(theInputMgr->KEYS_DOWN_BUFFER | theInputMgr->KEYS_PRESSED_BUFFER);
		
	}
	theOGLWnd.shutdown(); //Free any resources
	pgmWNDMgr->destroyWND(); //Destroy the program window
	
    return 0; //Return success
}
