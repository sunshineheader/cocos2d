#include "GameMap.h"
#include "ZhuGong.h"
#include "WuJiang.h"
#include "WenChen.h"
#include "Platform.h"

#include "GameObjects/SharpBall.h"
#include "GameObjects/ShieldSoldier.h"
#include "GameObjects/SpearSoldier.h"
#include "GameObjects/ScoreItem.h"
#include "GameObjects/PropItem.h"
#include "GameObjects/House.h"
#include "GameObjects/Spiling.h"
#include "GameObjects/FireBall.h"
#include "GameObjects/Block.h"

#include "Props/AutoCollectScoreItems.h"
#include "Props/QuickFlying.h"
#include "Props/JiaSuEffect.h"
#include "Props/InvincibleEffect.h"

#include "Utils/Properties.h"
#include "Utils/TmxMapHelper.h"
#include "Base/RepeatedBackground.h"

#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace cocostudio;
using namespace ui;
using namespace std;


GameMap::GameMap()
: _moveSpeed(0.0f)

, _topTerrainWidth(0.0f)
, _lastDistance(0.0f)
, _lastTerrainRight(0.0f)

, _distanceInPoint(0.0f)
, _pointToMeter(1 / 10.0f)

, _score(0)

, _currentFeverPoints(0)
, _maxFeverPoints(3000)
, _numFever(0)

, _propItem(nullptr)

, _collisionData(nullptr)

, _numDoubleJump(0)
{
}

GameMap::~GameMap()
{
	CC_SAFE_RELEASE_NULL(_collisionData);
}

bool GameMap::init()
{
	Properties config("Data/Config.json");
	_moveSpeed = config.getDoubleForKey("InitalMoveSpeed");
	_backgroundSpeedScale = config.getDoubleForKey("BackgroundSpeedScale");
	_mediumShotSpeedScale = config.getDoubleForKey("MediumShotSpeedScale");
	_closeShotSpeedScale = config.getDoubleForKey("CloseShotSpeedScale");
	// 1 米与像素的比例
	// 2 屏幕中的固定位置

	_background = RepeatedBackground::create("Maps/Grassland/Background.png");
	_mediumShot = RepeatedBackground::create("Maps/Grassland/MediumShot.png");
	_closeShot = RepeatedBackground::create("Maps/Grassland/CloseShot.png");
	_entitiesLayer = Node::create();
	addChild(_background);
	addChild(_mediumShot);
	addChild(_closeShot);
	addChild(_entitiesLayer);

	_collisionData = TMXTiledMap::create("Data/CollisionData.tmx");
	_collisionData->retain();


	auto percent = config.getDoubleForKey("ZhuGongFixedScreenPositionX");
	auto visibleSize = Director::getInstance()->getOpenGLView()->getVisibleSize();
	auto positionX = visibleSize.width * percent;



	_zhugong = ZhuGong::create();
	_zhugong->setGameMap(this);
	_zhugong->setPosition(positionX, 200);
	_zhugong->setLocalZOrder(1000);
	_zhugong->setInitPositionX(positionX);
	_entitiesLayer->addChild(_zhugong);



	_wujiang = WuJiang::create();
    _wujiang->setGameMap(this);
    _wujiang->setPosition(positionX + 200, 300);
    _wujiang->setLocalZOrder(1000);
    _wujiang->setInitPositionX(positionX + 200);
    _entitiesLayer->addChild(_wujiang);

	_wenchen = WenChen::create();
	_wenchen->setInitalPosition(Vec2(positionX - 140, 300));
	_wenchen->setLocalZOrder(1000);
	_entitiesLayer->addChild(_wenchen);

	addTerrain("CsbRes/Terrain/Grassland/Terrain_01.csb");
	addTerrain("CsbRes/Terrain/Grassland/Terrain_02.csb");
	addTerrain("CsbRes/Terrain/Grassland/Terrain_03.csb");

	addTouchListener();
	scheduleUpdate();

	return true;
}

void GameMap::addTouchListener()
{
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [=](Touch *t, Event *e)->bool {
		_zhugong->jump();
		return true;
	};
	listener->onTouchEnded = [=](Touch *t, Event *e) {
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

float s_stateTime = 0;
float s_createTime = 5;

void GameMap::update(float delta)
{
	moveForward(delta);
	checkCreatePropItem(delta);
	checkCollision(delta);
	updateTerrain();
}

void GameMap::addTerrain(const std::string &filename)
{
	auto terrain = CSLoader::createNode(filename);

	if (_terrains.empty()) 
	{
		_topTerrainWidth = terrain->getContentSize().width;
	}

	terrain->setPositionX(_lastTerrainRight);
	_lastTerrainRight += terrain->getContentSize().width;

	_terrains.push_back(terrain);
	_entitiesLayer->addChild(terrain);


	auto sharpBalls = terrain->getChildByName("SharpBalls");
	if (sharpBalls != nullptr)
	{
		auto nodes = sharpBalls->getChildren();
		sharpBalls->removeAllChildren();
		for (auto node : nodes)
		{
			auto ball = SharpBall::create();
			ball->setGameMap(this);
			ball->setPosition(node->getPosition());
			ball->setScale(node->getScale());
			ball->setAnchorPoint(node->getAnchorPoint());
			sharpBalls->addChild(ball);
		}
	}

	auto shieldSoldiers = terrain->getChildByName("ShieldSoldiers");
	if (shieldSoldiers != nullptr)
	{
		auto nodes = shieldSoldiers->getChildren();
		shieldSoldiers->removeAllChildren();
		for (auto node : nodes)
		{
			auto soldier = ShieldSoldier::create();
			soldier->setGameMap(this);
			soldier->setPosition(node->getPosition());
			soldier->setScale(node->getScale());
			soldier->setAnchorPoint(node->getAnchorPoint());
			shieldSoldiers->addChild(soldier);
		}
	}

	auto spearSoldiers = terrain->getChildByName("SpearSoldiers");
	if (spearSoldiers != nullptr)
	{
		auto nodes = spearSoldiers->getChildren();
		spearSoldiers->removeAllChildren();
		for (auto node : nodes)
		{
			auto soldier = SpearSoldier::create();
			soldier->setGameMap(this);
			soldier->setPosition(node->getPosition());
			soldier->setScale(node->getScale());
			soldier->setAnchorPoint(node->getAnchorPoint());
			spearSoldiers->addChild(soldier);
		}
	}

	auto stars = terrain->getChildByName("Stars");
	if (stars != nullptr)
	{
		auto nodes = stars->getChildren();
		stars->removeAllChildren();
		for (auto node : nodes)
		{
			auto item = ScoreItem::create();
			item->setGameMap(this);
			item->setSprite(node);
			item->setScale(node->getScale());
			item->setAnchorPoint(node->getAnchorPoint());
			stars->addChild(item);
		}
	}

	auto houses = terrain->getChildByName("Houses");
	if (houses != nullptr)
	{
		auto nodes = houses->getChildren();
		houses->removeAllChildren();
		for (auto node : nodes)
		{
			auto house = House::create();
			house->setGameMap(this);
			house->setPosition(node->getPosition());
			house->setScale(node->getScale());
			house->setAnchorPoint(node->getAnchorPoint());
			houses->addChild(house);
		}
	}

	auto spilings = terrain->getChildByName("Spilings");
	if (spilings != nullptr)
	{
		auto nodes = spilings->getChildren();
		spilings->removeAllChildren();
		for (auto node : nodes)
		{
			auto spiling = Spiling::create();
			spiling->setGameMap(this);
			spiling->setPosition(node->getPosition());
			spiling->setScale(node->getScale());
			spiling->setAnchorPoint(node->getAnchorPoint());
			spilings->addChild(spiling);
		}
	}

	auto fireBalls = terrain->getChildByName("FireBalls");
	if (fireBalls != nullptr)
	{
		auto nodes = fireBalls->getChildren();
		fireBalls->removeAllChildren();
		for (auto node : nodes)
		{
			auto fireBall = FireBall::create();
			fireBall->setGameMap(this);
			fireBall->setPosition(node->getPosition());
			fireBall->setScale(node->getScale());
			fireBall->setAnchorPoint(node->getAnchorPoint());
			fireBalls->addChild(fireBall);
		}
	}

	auto platforms = terrain->getChildByName("Platforms");
	if (platforms != nullptr)
	{
		auto nodes = platforms->getChildren();
		platforms->removeAllChildren();
		for (auto node : nodes)
		{
			auto platform = Platform::create(node);
			platforms->addChild(platform);

		}
	}

	auto blocks = terrain->getChildByName("Blocks");
	if (blocks != nullptr)
	{
		auto nodes = blocks->getChildren();
		blocks->removeAllChildren();
		for (auto node : nodes)
		{
			auto block = Block::create();
			block->setGameMap(this);
			block->setPosition(node->getPosition());
			block->setScale(node->getScale());
			block->setAnchorPoint(node->getAnchorPoint());
			blocks->addChild(block);
		}
	}
}

void GameMap::updateTerrain()
{
	static const char* TERRAINS[] = {
		"CsbRes/Terrain/Grassland/Terrain_01.csb",
		"CsbRes/Terrain/Grassland/Terrain_02.csb",
		"CsbRes/Terrain/Grassland/Terrain_03.csb",
	};

	static int index = 0;

	if (_distanceInPoint - _lastDistance >= _topTerrainWidth)
	{
		_lastDistance = _distanceInPoint;
		if (!_terrains.empty())
		{
			auto front = _terrains.front();
			front->removeFromParent();
			_terrains.pop_front();
		}
		if (!_terrains.empty())
		{
			_topTerrainWidth = _terrains.front()->getContentSize().width;
		}

		int max = sizeof(TERRAINS) / sizeof(TERRAINS[0]);
		//int index = RandomHelper::random_int(0, max);
		addTerrain(TERRAINS[index % max]);
		index += 1;
	}
}

void GameMap::moveForward(float delta)
{
	auto deltaDistance = _moveSpeed * delta;
	_background->setPositionX(_background->getPositionX() - deltaDistance * _backgroundSpeedScale);
	_mediumShot->setPositionX(_mediumShot->getPositionX() - deltaDistance * _mediumShotSpeedScale);
	_closeShot->setPositionX(_closeShot->getPositionX() - deltaDistance * _closeShotSpeedScale);
	_entitiesLayer->setPositionX(_entitiesLayer->getPositionX() - deltaDistance);
	_distanceInPoint += deltaDistance;

	_wenchen->setPositionX(_wenchen->getPositionX() + deltaDistance);
}

void GameMap::checkCreatePropItem(float delta)
{
	if (_propItem == nullptr)
	{
		s_stateTime += delta;
	}
	else if ((_propItem->getPosition() - _zhugong->getPosition()).length() > 1500)
	{
		_propItem->removeFromParent();
		_propItem->release();
		_propItem = nullptr;
	}

	if (s_stateTime >= s_createTime && _propItem == nullptr)
	{
		s_stateTime = 0;

		_propItem = PropItem::create();
		_propItem->setContentSize(Size(90, 90));
		_propItem->retain();

		Vec2 position;
		position.x = _zhugong->getPositionX() + 900;
		position.y = RandomHelper::random_real(380.0f, 420.0f);
		_propItem->setInitalPosition(position);

		_propItem->setPropType(PropItem::PropType::FeiNiao);

		_propItem->setMoveSpeed(_moveSpeed * 0.75f);

		_entitiesLayer->addChild(_propItem);
	}

	if (_propItem != nullptr)
	{
		Rect zhugongRect = _zhugong->_zhugong->getBoundingBox();
		zhugongRect.origin += _zhugong->getPosition();

		Rect rect;
		auto position = _propItem->getPosition();
		auto size = _propItem->getContentSize();
		auto anchor = _propItem->getAnchorPoint();
		rect.origin.x = position.x - size.width * anchor.x;
		rect.origin.y = position.y - size.height * anchor.y;
		rect.size = size;

		if (zhugongRect.intersectsRect(rect)) {
			addOneCollectedObject(_propItem->getTypeName());

			_propItem->removeFromParent();
			_propItem->takeEffect(this);
			_propItem->release();
			_propItem = nullptr;
		}
	}
}

void GameMap::checkCollision(float delta)
{

}

float GameMap::getDistanceInPoint() const
{
	return _distanceInPoint;
}

float GameMap::getDistanceInMeter() const
{
	return _distanceInPoint * _pointToMeter;
}

const std::list<cocos2d::Node*>& GameMap::getTerrains() const
{
	return _terrains;
}

float GameMap::getEntityLayerPositionX() const
{
	return _entitiesLayer->getPositionX();
}


void GameMap::pauseMove()
{
    pause();
    _zhugong->pause();
    _wujiang->pause();
    _wenchen->pause();
}

void GameMap::resumeMove()
{
    resume();
    _zhugong->resume();
    _wujiang->resume();
    _wenchen->resume();
}

void GameMap::addScore(int value)
{
	_score += value;
	_currentFeverPoints += value;
}

int GameMap::getScore() const
{
    return _score;
}

bool GameMap::isZhuGongDead() const
{
    return _zhugong->isDead();
}

ZhuGong* GameMap::getZhuGong() const
{
	return _zhugong;
}

int GameMap::getNumFever() const
{
	return _numFever;
}

bool GameMap::isInFever() const
{
	return _currentFeverPoints >= _maxFeverPoints;
}

float GameMap::getFeverPointsPercent() const
{
	return (float) _currentFeverPoints / _maxFeverPoints * 100.0f;
}

void GameMap::setMoveSpeed(float speed)
{
	_moveSpeed = speed;
}

float GameMap::getMoveSpeed() const
{
	return _moveSpeed;
}

void GameMap::addNumFever()
{
	if (_currentFeverPoints >= _maxFeverPoints)
	{
		_currentFeverPoints -= _maxFeverPoints;
		_numFever += 1;
	}
}

void GameMap::addAutoCollectEffect(float time)
{
	auto autoCollect = AutoCollectScoreItems::create();
	autoCollect->setZhuGong(_zhugong);
	autoCollect->setGameMap(this);
	autoCollect->setTotalTime(time);
	addChild(autoCollect);
}

void GameMap::addQuickFlying(float time)
{
	auto carrier = Sprite::create("Effects/DragonBoat.png");
	auto quickFlying = QuickFlying::create(this, _zhugong, carrier, time);
	addChild(quickFlying);
}

void GameMap::addChildToEntityLayer(cocos2d::Node *node)
{
	_entitiesLayer->addChild(node);
}

void GameMap::addJiaSuEffect(float time)
{
	auto jiasu = JiaSuEffect::create();
	jiasu->setGameMap(this);
	addChild(jiasu);
}

void GameMap::addFeiXingGuai()
{
	auto fireBall = FireBall::create();
	fireBall->setGameMap(this);
	fireBall->setPosition(Vec2(_zhugong->getPositionX() + 800, 400));
	fireBall->setScale(0.7f);
	_entitiesLayer->addChild(fireBall);
}

void GameMap::addInvincibleEffect(float time)
{
	auto invincible = InvincibleEffect::create();
	invincible->setGameMap(this);
	addChild(invincible);
}

void GameMap::addDustAnimation(cocos2d::Node *node)
{
	ArmatureDataManager::getInstance()->addArmatureFileInfo("Test/Animations.ExportJson");
	auto animations = Armature::create("Animations");
	animations->getAnimation()->play("Dust");
	animations->getAnimation()->setMovementEventCallFunc(
		[=](Armature * armature, MovementEventType type, const string &movementId)
	{
		if (movementId == "Dust" && type == MovementEventType::COMPLETE)
		{
			animations->removeFromParent();
		}
	});

	node->addChild(animations);
}

cocos2d::TMXTiledMap* GameMap::getCollisionData() const
{
	return _collisionData;
}

void GameMap::addOneCollectedObject(const std::string typeName)
{
	auto it = _collectedObjects.find(typeName);
	if (it == _collectedObjects.end())
	{
		_collectedObjects.insert({ typeName, 1 });
	}
	else
	{
		it->second += 1;
	}
}

int GameMap::getNumCollectedObject(const std::string typeName)
{
	auto it = _collectedObjects.find(typeName);
	return it == _collectedObjects.end() ? 0 : it->second;
}

void GameMap::addNumDoubleJump()
{
	_numDoubleJump += 1;
}

int GameMap::getNumDoubleJump() const
{
	return _numDoubleJump;
}

