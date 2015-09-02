#include "LevelLayer.h"
#include "GameScene.h"
USING_NS_CC;

  
bool LevelLayer::init()
{  
    if (!Layer::init())
	{
		return false;
	}
	//初始化pageNode和curPageNode的值
	pageNode = 0;
	curPageNode = 0;

	//添加点击事件的监听
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->setSwallowTouches(true);
    touchListener->onTouchBegan = CC_CALLBACK_2(LevelLayer::onTouchBegan, this);
    touchListener->onTouchMoved = CC_CALLBACK_2(LevelLayer::onTouchMoved, this);
    touchListener->onTouchEnded = CC_CALLBACK_2(LevelLayer::onTouchEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
    
	WINDOW_WIDTH = Director::getInstance()->getWinSize().width;  
	WINDOW_HEIGHT = Director::getInstance()->getWinSize().height;
    
	//测试用方法
	Size visibleSzie = Director::getInstance()->getVisibleSize();
	MenuItemImage* gotoGame = MenuItemImage::create("content.png", "content.png", CC_CALLBACK_0(LevelLayer::gotoGame, this));
	auto menu = Menu::create(gotoGame,NULL);
	menu->setPosition(ccp(visibleSzie.width / 2, visibleSzie.height / 2));
	this->addChild(menu);

	//滑动部分
	auto cache_frist = SpriteFrameCache::getInstance()->getSpriteFrameByName("bt_every_task.png");
	auto lock_bg = Sprite::createWithSpriteFrame(cache_frist);
	lock_bg->setPosition(Vec2(visibleSzie / 2));
	addChild(lock_bg);

	auto cache = SpriteFrameCache::getInstance()->getSpriteFrameByName("lock_mask.png");
	auto lock = Sprite::createWithSpriteFrame(cache);
	lock->setPosition(Vec2(visibleSzie/2));
	addChild(lock);


	//游戏返回键
	auto backgame = MenuItemImage::create("gameback.png", "gameback.png",CC_CALLBACK_0(LevelLayer::backgame_callback,this));
	auto backgame_menu = Menu::create(backgame,nullptr);
	backgame_menu->setPosition(Vec2(1050,600));
	addChild(backgame_menu);


	//解锁炮弹
	auto openbuttle = MenuItemImage::create("openbuttle.png", "openbuttle.png", CC_CALLBACK_0(LevelLayer::openbuttle_callback, this));
	auto openbuttle_menu = Menu::create(openbuttle, nullptr);
	openbuttle_menu->setPosition(Vec2(450, 50));
	addChild(openbuttle_menu);


	//解锁场景
	auto openscene = MenuItemImage::create("openscene.png", "openscene.png", CC_CALLBACK_0(LevelLayer::openscene_callback, this));
	auto openscene_menu = Menu::create(openscene, nullptr);
	openscene_menu->setPosition(Vec2(750, 50));
	addChild(openscene_menu);


    return true;
}  

void LevelLayer::gotoGame(){
	Director::getInstance()->replaceScene(TransitionFade::create(1, GameScene::create()));
}

void LevelLayer::backgame_callback()
{ 
	//TooD 返回游戏


}
void LevelLayer::openbuttle_callback()
{
	//TooD 解锁炮弹


}
void LevelLayer::openscene_callback()
{
	//TooD 解锁场景


}

void LevelLayer::goToCurrNode()
{
	this->runAction(MoveTo::create(0.4f, Point::Vec2(-curPageNode * WINDOW_WIDTH, 0)));
}

void LevelLayer::addNode(Node *level)
{
    if (level)
    {
        level->setContentSize(Size::Size(WINDOW_WIDTH, WINDOW_HEIGHT));
        level->setPosition(Point(WINDOW_WIDTH * pageNode, 0));
        this->addChild(level);
        pageNode++;
    }
}

bool LevelLayer::onTouchBegan(Touch *touch, Event  *event)
{
    touchDownPoint = touch->getLocation();
    touchCurPoint = touchDownPoint;
    return true;
}

void LevelLayer::onTouchMoved(Touch *touch, Event  *event)
{
    Point touchPoint = touch->getLocation();
    auto currX = this->getPositionX() + touchPoint.x - touchCurPoint.x;
	Point posPoint = Point::Vec2(currX, getPositionY());
    auto dis= fabsf(touchPoint.x - touchCurPoint.x);
    if (dis >= SHORTEST_SLIDE_LENGTH ) {
        setPosition(posPoint);
    }
    touchCurPoint = touchPoint;
}

void LevelLayer::onTouchEnded(Touch *touch, Event  *event)
{
    touchUpPoint = touch->getLocation();
    auto dis= touchUpPoint.getDistance(touchDownPoint);
    auto sprite1 =Sprite::createWithSpriteFrameName("page_mark1.png");
    auto width = sprite1->getContentSize().width;
    if (dis >= SHORTEST_SLIDE_LENGTH )
    {
        int offset = getPositionX() - curPageNode * (-WINDOW_WIDTH);
        if (offset > width) {
            if (curPageNode > 0) {
                --curPageNode;
               /* Sprite *sprite =  (Sprite *)LevelScene::getInstance()->getChildByTag(888);
                sprite->setPosition(Point(sprite->getPositionX()-width,sprite->getPositionY()));*/
            }
        }
        else if (offset < -width) {
            if (curPageNode < (pageNode - 1)) {
                ++curPageNode;
                //Sprite *sprite =  (Sprite *)LevelScene::getInstance()->getChildByTag(888);
                //sprite->setPosition(Point(sprite->getPositionX()+width,sprite->getPositionY()));
            }
        }
        goToCurrNode();
    }
}
