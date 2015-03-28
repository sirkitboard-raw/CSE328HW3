/*
	Author: Richard McKenna
			Stony Brook University
			Computer Science Department

	BugginOutTextGenerator.cpp

	See BugginOutTextGenerator.h for a class description.
*/

#include "buggin_out_VS\stdafx.h"
#include "buggin_out\BugginOut.h"
#include "buggin_out\BugginOutTextGenerator.h"
#include "sssf\game\Game.h"
#include "sssf\graphics\GameGraphics.h"
#include "sssf\text\GameText.h"
#include "sssf\timer\GameTimer.h"
#include "sssf\platforms\Windows\WindowsInput.h"
#include "sssf\platforms\Windows\WindowsTimer.h"
#include "sssf/gui/GameGUI.h"
#include "sssf/gui/ScreenGUI.h"
#include "sssf/gui/OverlayImage.h"

static const wstring	W_MOUSE_COORDS_TEXT = L"Mouse: (";
static const int		W_TEXT_X = 200;
static const int		W_TEXT_Y = 10;
static const wstring	W_BOTS_HEAP_TEXT = L"Monsters Heap Data: [";
static const wstring	W_NUM_BOTS = L"Number Of Bots : ";

void BugginOutTextGenerator::appendMouseCoords(Game *game)
{
	wstringstream wss;
	WindowsInput *input = (WindowsInput*)game->getInput();
	textToGenerate.append(W_MOUSE_COORDS_TEXT);
	wss << input->getMousePoint()->x;
	wss << L", ";
	wss << input->getMousePoint()->y;
	wss << L")";
	wss << L"\n";
	textToGenerate.append(wss.str());
}

void BugginOutTextGenerator::appendLives(Game* game) {
	wstringstream wss;
	int lives = game->getGSM()->getSpriteManager()->getPlayer()->getLives();
	unsigned int imageID = game->getGraphics()->getGUITextureManager()->loadTexture(W_RDM_PATH);
	if (game->getGSM()->isGameInProgress()) {
		ScreenGUI* screen = game->getGUI()->getScreen(GS_GAME_IN_PROGRESS);
		screen->clearOverlayImages();
		int x = 300;
		wss << L"Lives : ";
		for (int i = 0; i < lives; i++) {
			OverlayImage *imageToAdd = new OverlayImage();
			imageToAdd->x = x;
			imageToAdd->y = 2;
			imageToAdd->z = 2;
			imageToAdd->alpha = 200;
			imageToAdd->width = 30;
			imageToAdd->height = 30;
			imageToAdd->imageID = imageID;
			screen->addOverlayImage(imageToAdd);
			x += 80;
		}
		int health = game->getGSM()->getSpriteManager()->getPlayer()->getHealth();
		wss << L"\n";
		wss << L"Health ";
		wss << health;
	}
	livesText.append(wss.str());
	
}


/*
	initText - Provides an example of how to render text to our screen every frame,
	allowing for the text to continually change. This method adds a text object
	to the text manager (GameText), which allows it to be updated each frame. This
	method should be called only once for each object.
*/
void BugginOutTextGenerator::initText(Game *game)
{
	// FIRST UPDATE THE TEXT THIS GENERATOR IS USING
	appendMouseCoords(game);
	appendLives(game);
	appendQuadTreeData(game);
	// AND THEN HAND IT TO THE TEXT MANAGER, SPECIFYING WHERE IT SHOULD BE RENDERED
	GameText *text = game->getText();
	text->addText(&livesText, W_TEXT_X, W_TEXT_Y, game->getGraphics()->getScreenWidth(), game->getGraphics()->getScreenHeight());
	text->addText(&textToGenerate, W_TEXT_X, W_TEXT_Y, game->getGraphics()->getScreenWidth(), game->getGraphics()->getScreenHeight());
	text->addText(&quadText, W_TEXT_X, W_TEXT_Y + 50, game->getGraphics()->getScreenWidth(), game->getGraphics()->getScreenHeight());
}

void BugginOutTextGenerator::appendQuadTreeData(Game* game) {
	QuadTree *quad_tree = game->getGSM()->getSpriteManager()->getBotsTree();
	wstringstream wss;

	wss << W_NUM_BOTS << game->getGSM()->getSpriteManager()->getNumberOfSprites() << L"\n";
	wss << W_BOTS_HEAP_TEXT;

	for (int i = 0; i<20; i++) {
		wss << quad_tree->sizeOfNode(i) << L",";
	}
	wss << quad_tree->sizeOfNode(20) << L"]";

	quadText.append(wss.str());
}

/*
	updateText - updates the text. Note that the text must already have been added
	to the text manager via the initText method. Also not that there should be a
	separate TextGenerator for each line of text we wish to render.
*/
void BugginOutTextGenerator::updateText(Game *game)
{
	// THE TEXT MANAGER (GameText) HAS A POINTER TO OUR TEXT, SO WE CAN
	// SIMPLY CLEAR IT OUT OF OLD CHARACTER DATA AND FILL IT IN WITH
	// WHAT WE WANT.
	textToGenerate.clear();
	livesText.clear();
	quadText.clear();
	appendMouseCoords(game);
	appendLives(game);
	appendQuadTreeData(game);
}