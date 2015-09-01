#include "MenuScenePayHandler.h"
#include "GameLayer.h"
#include "GameData.h"
#include "MenuLayer.h"
#include "SignIn.h"
#include "Gold.h"

static MenuScenePayHandler* _instance = nullptr;
MenuScenePayHandler* MenuScenePayHandler::getInstance()
{
	if (!_instance)
	{
		_instance = new MenuScenePayHandler();
	}
	return _instance;
}

void MenuScenePayHandler::payCallback(int requestId,int resultId){
	if(resultId == 0){
		GAMEDATA::getInstance()->setPaySuccess(true);
		GAMEDATA::getInstance()->savePaySuccess();
	}
	//request_id = requestId;
	switch (requestId)
	{
	case 6:
		if(resultId==0){
			GAMEDATA::getInstance()->setGoldNum(GAMEDATA::getInstance()->getGoldNum()+50000);
			GAMEDATA::getInstance()->saveGoldNum();
			TopMenu::getInstance()->refreshGold();
		}	
		break;
	case 2:
		if(resultId==0){
			GAMEDATA::getInstance()->setAddTimeNum(10+GAMEDATA::getInstance()->getAddTimeNum());
			GAMEDATA::getInstance()->saveAddTimeNum();}
		break;
	case 3:
		if(resultId==0){
			GAMEDATA::getInstance()->setBombNum(10+GAMEDATA::getInstance()->getBombNum());
			GAMEDATA::getInstance()->saveBombNum();}
		break;
	case 4:
		if(resultId==0){
			GAMEDATA::getInstance()->setGoldNum(GAMEDATA::getInstance()->getGoldNum()+50000);
			GAMEDATA::getInstance()->saveGoldNum();
			TopMenu::getInstance()->refreshGold();
			Gold::getInstance()->refreshGold();
		}	
		break;
	case 5:
		if(resultId==0){
			GAMEDATA::getInstance()->setGoldNum(GAMEDATA::getInstance()->getGoldNum()+50000);
			GAMEDATA::getInstance()->saveGoldNum();
			TopMenu::getInstance()->refreshGold();
		}
		break;
	case 9:
		if(resultId==0){
			GAMEDATA::getInstance()->setGoldNum(GAMEDATA::getInstance()->getGoldNum()+60000);
			GAMEDATA::getInstance()->setChuiNum(1);
			GAMEDATA::getInstance()->setBiNum(1);
			GAMEDATA::getInstance()->saveChuiNum();
			GAMEDATA::getInstance()->saveBiNum();
			TopMenu::getInstance()->refreshGold();
			GAMEDATA::getInstance()->setIsBuySuperGift();
			TopMenu::getInstance()->hideMenuGift();
		}
		break;
	case 7:
		if(resultId==0){
			GAMEDATA::getInstance()->setGoldNum(GAMEDATA::getInstance()->getGoldNum()+47000);
			GAMEDATA::getInstance()->saveGoldNum();
			TopMenu::getInstance()->refreshGold();
			GameLayer::needRevive=true;
			GameLayer::gameOver=false;
		}else{
			GameLayer::needRevive=false;
			GameLayer::gameOver=true;
		}
		break;
	case 8:
		if(resultId==0){
			GAMEDATA::getInstance()->setGoldNum(GAMEDATA::getInstance()->getGoldNum()+50000);
			GAMEDATA::getInstance()->saveGoldNum();
			TopMenu::getInstance()->refreshGold();
		}
		break;
	case 10:
		if(resultId==0){
			GAMEDATA::getInstance()->setGoldNum(GAMEDATA::getInstance()->getGoldNum()+50000);
			GAMEDATA::getInstance()->saveGoldNum();
			Gold::getInstance()->refreshGold();
			//去下一关
			GameLayer::goToNextLevel =true;
		}else{
		   //从玩本馆
			GameLayer::isShowRePlay =true;
		}

		break;
	case 11:
		if(resultId==0){
			GAMEDATA::getInstance()->setGoldNum(GAMEDATA::getInstance()->getGoldNum()+60000);
			GAMEDATA::getInstance()->setChuiNum(1);
			GAMEDATA::getInstance()->setBiNum(1);
			GAMEDATA::getInstance()->saveChuiNum();
			GAMEDATA::getInstance()->saveBiNum();
			TopMenu::getInstance()->refreshGold();
			GAMEDATA::getInstance()->setIsBuySuperGift();
			TopMenu::getInstance()->hideMenuGift();
		}
		break;
	case 12:
		if(resultId==0){
			GAMEDATA::getInstance()->setGoldNum(GAMEDATA::getInstance()->getGoldNum()+50000);
			GAMEDATA::getInstance()->saveGoldNum();
			TopMenu::getInstance()->refreshGold();
		}
		break;
	case 13:
		if(resultId==0){
			GAMEDATA::getInstance()->setGoldNum(GAMEDATA::getInstance()->getGoldNum()+50000);
			GAMEDATA::getInstance()->saveGoldNum();
			TopMenu::getInstance()->refreshGold();
		}
		break;
	default:
		break;
	}
}

