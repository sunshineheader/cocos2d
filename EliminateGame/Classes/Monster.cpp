#include "Monster.h"

USING_NS_CC;

#define TOTAL_MONSTER (6)

static const char *monsterNormal[TOTAL_MONSTER] = {
	"item_1.png",
	"item_2.png",
	"item_3.png",
	"item_4.png",
	"item_5.png",
	"item_6.png"
};


float Monster::getContentWidth()
{
	static float itemWidth = 0;
	if (0 == itemWidth) {
		Sprite *sprite = CCSprite::createWithSpriteFrameName(monsterNormal[0]);
		itemWidth = sprite->getContentSize().width;
	}
	return itemWidth;
}

Monster::Monster()
	: m_col(0)
	, m_row(0)
	, m_imgIndex(0)
	, m_isNeedRemove(false)
	, m_ignoreCheck(false)
	, m_displayMode(DISPLAY_MODE_NORMAL)
{
}

Monster *Monster::create(int row, int col)
{
	Monster *monster = new Monster();
	monster->m_row = row;
	monster->m_col = col;
	CCLOG("rand = %d", rand());
	monster->m_imgIndex = rand() % TOTAL_MONSTER;
	monster->initWithSpriteFrameName(monsterNormal[monster->m_imgIndex]);
	monster->autorelease();
	return monster;
}

void Monster::setDisplayMode(DisplayMode mode)
{
	m_displayMode = mode;

	SpriteFrame *frame;
	switch (mode) {
	case DISPLAY_MODE_VERTICAL:
		frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(monsterNormal[m_imgIndex]);
		break;
	case DISPLAY_MODE_HORIZONTAL:
		frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(monsterNormal[m_imgIndex]);
		break;
	default:
		return;
	}
	setDisplayFrame(frame);
}
