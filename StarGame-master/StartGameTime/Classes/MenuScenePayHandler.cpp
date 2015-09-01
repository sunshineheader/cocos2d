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
		//�������?
		GameLayer::_PauseTime=false;
		if(resultId==0){
			GAMEDATA::getInstance()->setGoldNum(GAMEDATA::getInstance()->getGoldNum()+50000);
			GAMEDATA::getInstance()->saveGoldNum();
			TopMenu::getInstance()->refreshGold();
		}	
		GAMEDATA::getInstance()->setHasShowRegisterPay(true);
		GAMEDATA::getInstance()->saveShowRegisterPay();
		break;
	case 2:
		//��ʱ
		GameLayer::_PauseTime=false;
		if(resultId==0){
			GAMEDATA::getInstance()->setAddTimeNum(10+GAMEDATA::getInstance()->getAddTimeNum());
			GAMEDATA::getInstance()->saveAddTimeNum();
			TopMenu::getInstance()->updatePropsNum();}
		break;
	case 3:
		//ը��
		GameLayer::_PauseTime=false;
		if(resultId==0){
			GAMEDATA::getInstance()->setBombNum(10+GAMEDATA::getInstance()->getBombNum());
			GAMEDATA::getInstance()->saveBombNum();
			TopMenu::getInstance()->updatePropsNum();}
		break;
	case 4:
		//��ͣ����
		if(resultId==0){
			GAMEDATA::getInstance()->setAddTimeNum(5+GAMEDATA::getInstance()->getAddTimeNum());
			GAMEDATA::getInstance()->saveAddTimeNum();
			GAMEDATA::getInstance()->setBombNum(5+GAMEDATA::getInstance()->getBombNum());
			GAMEDATA::getInstance()->saveBombNum();
			TopMenu::getInstance()->updatePropsNum();	
		}	
		break;
	case 5:
		GameLayer::_PauseTime=false;
		if(resultId==0){
			GAMEDATA::getInstance()->setReviveNum(GAMEDATA::getInstance()->getReviveNum()-1);
			GAMEDATA::getInstance()->saveAddTimeNum();
			GameLayer::needRevive=true;
			GameLayer::gameOver=false;
		}else{
			GameLayer::needRevive=false;
			GameLayer::gameOver=true;
		}

		//����
		break;
	case 9:
		GameLayer::_PauseTime=false;
		//��Ѹ���?
		if(resultId==0){
			GAMEDATA::getInstance()->setReviveNum(GAMEDATA::getInstance()->getReviveNum()-1);
			GAMEDATA::getInstance()->saveAddTimeNum();
			GameLayer::needRevive=true;
			GameLayer::gameOver=false;
		}else{
			GameLayer::needRevive=false;
			GameLayer::gameOver=true;
		}
		break;
	case 7:
		if(resultId==0){
			GAMEDATA::getInstance()->setGoldNum(GAMEDATA::getInstance()->getGoldNum()+50000);
			GAMEDATA::getInstance()->saveGoldNum();
			Gold::getInstance()->refreshGold();
		}
		break;
	case 8:
		if(resultId==0){
			GAMEDATA::getInstance()->setGoldNum(GAMEDATA::getInstance()->getGoldNum()+60000);
			GAMEDATA::getInstance()->saveGoldNum();
			Gold::getInstance()->refreshGold();
		}
		break;
	case 10:
		if(resultId==0){
			GAMEDATA::getInstance()->setGoldNum(GAMEDATA::getInstance()->getGoldNum()+50000);
			GAMEDATA::getInstance()->saveGoldNum();
			Gold::getInstance()->refreshGold();
		}
		break;
	case 11:
		if(resultId==0){
			GAMEDATA::getInstance()->setGoldNum(GAMEDATA::getInstance()->getGoldNum()+50000);
			GAMEDATA::getInstance()->saveGoldNum();
			TopMenu::getInstance()->refreshGold();
		}
		break;
	case 12:
		GameLayer::_PauseTime=false;
		if(resultId==0){
			GAMEDATA::getInstance()->setGoldNum(GAMEDATA::getInstance()->getGoldNum()+50000);
			GAMEDATA::getInstance()->saveGoldNum();
			TopMenu::getInstance()->refreshGold();
		}
		break;
	case 13:
		GameLayer::_PauseTime=false;
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

