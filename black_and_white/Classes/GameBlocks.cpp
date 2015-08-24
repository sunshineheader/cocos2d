#include "GameBlocks.h"
#include "GameDefinition.h"
#include "cocos2d.h"

Vector<GameBlocks*>*GameBlocks::gameblocks = nullptr;


bool GameBlocks::init()
{
	if (!Sprite::init())
	{
		return false;
	}

	//Sprite::create();
	auto white_block_cache = Director::getInstance()->getTextureCache()->addImage("white.png");
	auto yellow_block_cache = Director::getInstance()->getTextureCache()->addImage("yellow.png");
	auto black_block_cache = Director::getInstance()->getTextureCache()->addImage("black.png");

	auto white_block = Sprite::createWithTexture(white_block_cache);
	auto yellow_block = Sprite::createWithTexture(yellow_block_cache);
	auto black_block = Sprite::createWithTexture(black_block_cache);

	return true;
}
GameBlocks*GameBlocks::create(int color)
{
	GameBlocks*  block = new GameBlocks();
	if (block && block->initWithFile(block->getImage(color)))
	{
		//block->initWithFile("");
		block->mycolor = color;
		block->autorelease();
		//gameblocks->pushBack(block);
		return block;
	}
	CC_SAFE_DELETE(block);
	return nullptr;
}

void GameBlocks::initMatrix()
{
	for (int j = 0; j < RowNumber; j++)
	{
		for (int i = 0; i < ColNumber; i++)
		{
			//setPosition(i,j);
		}

	}



}

Vector<GameBlocks*>*GameBlocks::getGameBlocks()
{
	if (!gameblocks->empty())
	{
		gameblocks->clear();
	}
	return GameBlocks::gameblocks;
}

std::string GameBlocks::getImage(int color)
{
	switch (color)
	{
	case GameBlocks::Color::BLACK:
		return BLACK_BLOCCK;
		break;
	case GameBlocks::Color::WHITE:
		return WHITE_BLOCCK;
		break;
	case GameBlocks::YELLOW:
		return YELLOW_BLOCCK;
		break;
	default:
		break;
	}



}