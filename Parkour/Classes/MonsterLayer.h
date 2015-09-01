#ifndef MonsterLayer_H
#define MonsterLayer_H
 
#include "cocos2d.h"
#include "Player.h"
#include "InfoLayer.h"
USING_NS_CC;
 
class Monster;
class MonsterLayer : public Layer 
{
public:
	MonsterLayer();
	~MonsterLayer();
	CREATE_FUNC(MonsterLayer);
	static MonsterLayer* createLayer(Player* player,InfoLayer* infoLayer);
	virtual bool init(); 
    void logic(float dt);
	void pause();
	void resume();
	bool isCanSlide();
	bool isCanJump();
	bool isNeedContiSlide();
	static int playerRowNum;
private:

    void loadMonstersFromTmxConf();


	void loadNextMap(float shifting);

	bool checkCollision(TMXTiledMap* nowmap,TMXTiledMap* nowmap2);


	bool checkSpritesCollision(Node* sprite1,Node* sprite2);


	void magneticGold(Sprite* gold,int index);


	void goldAnim();

	float abs(float num1,float num2);
 

    Vector<Monster*> m_monsterVec;

	Vector<Monster*> deleteMonsterVec;

	Vector<Sprite*> m_eatGold1;

	Vector<Sprite*> m_eatGold2;


	Vector<Sprite*> m_monsterAnim;


	Vector<Sprite*> m_delMonsterAnim;


	Vector<Sprite*> m_goldAnim;


	Vector<Sprite*> m_delGoldAnim;
	
	Action* monsterDiedAction;


	int tag;
 

    float speed;

	float speed2;

	float distance;

	static Player* m_player;

	static InfoLayer* m_infoLayer;
	
	int speed_x;
	int speed_y;

	bool canSlide;
	bool needContiSlide;
	bool canJump;
	float totalOffset;
};
 
#endif
