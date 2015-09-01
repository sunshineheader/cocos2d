#include "MenuScenePayHandler.h"
#include "GameLayer.h"
#include "GameData.h"
#include "GameGuiLayer.h"

static MenuScenePayHandler* _instance = nullptr;
MenuScenePayHandler* MenuScenePayHandler::getInstance()
{
	if (!_instance)
	{
		_instance = new MenuScenePayHandler();
	}
	return _instance;
}

void  MenuScenePayHandler::dealRewardProp(int propId, int propNum){

}
void  MenuScenePayHandler::dealEventClose(int eventId){

}
void MenuScenePayHandler::dealEventSuccess(int requestId, int propIds[], int propNums[], int count){
	
}

void MenuScenePayHandler::dealEventFail(int eventId){

}

/*
void MenuScenePayHandler::payCallback(int requestId,int resultId){

	//CCLog("Star requestId =%d resultId=%d", requestId, resultId);
	if(resultId == 0){
		GAMEDATA::getInstance()->setPaySuccess(true);
		GAMEDATA::getInstance()->savePaySuccess();
	}
	//request_id = requestId;
	switch (requestId)
	{
	case 1:
		if (resultId == 0){
			GAMEDATA::getInstance()->settipNum(GAMEDATA::getInstance()->gettipNum() + 10);
			GAMEDATA::getInstance()->savetipNum();
			GameGuiLayer::help = true;
		}
		else{

			GameGuiLayer::help = false;
		}
		break;
	case 2:
		if (resultId == 0){
			GAMEDATA::getInstance()->setrefreshNum(GAMEDATA::getInstance()->getrefreshNum() + 10);
			GAMEDATA::getInstance()->saverefreshNum();
			GameGuiLayer::refresh = true;
		}
		else{

			GameGuiLayer::refresh = false;
		}
		break;
	case 3:
		if (resultId == 0){
			GAMEDATA::getInstance()->setaddtimeNum(GAMEDATA::getInstance()->getaddtimeNum() + 10);
			GAMEDATA::getInstance()->saveaddtimeNum();

			GameGuiLayer::addTime = true;
		}
		else{

			GameGuiLayer::addTime = false;
		}
		break;
	case 4:
		if (resultId == 0){
			GAMEDATA::getInstance()->setReviveNum(GAMEDATA::getInstance()->getReviveNum() + 5);
			GAMEDATA::getInstance()->saveReviveNum();

			//GameGuiLayer::addTime = true;
		}
		else{

			//GameGuiLayer::addTime = false;
		}
	
		break;
	case 5:
		if (resultId == 0){
			GAMEDATA::getInstance()->settipNum(GAMEDATA::getInstance()->gettipNum() + 10);
			GAMEDATA::getInstance()->savetipNum();
			GameGuiLayer::help = true;
		}
		else{

			GameGuiLayer::help = false;
		}
		break;
	case 6:
		
		if (resultId == 0){
			GAMEDATA::getInstance()->setrefreshNum(GAMEDATA::getInstance()->getrefreshNum() + 10);
			GAMEDATA::getInstance()->saverefreshNum();
			GameGuiLayer::refresh = true;
		}
		else{

			GameGuiLayer::refresh = false;
		}

		break;
	case 7:
		if (resultId == 0){
			GAMEDATA::getInstance()->setaddtimeNum(GAMEDATA::getInstance()->getaddtimeNum() + 10);
			GAMEDATA::getInstance()->saveaddtimeNum();

			GameGuiLayer::addTime = true;
		}
		else{

			GameGuiLayer::addTime = false;
		}
		break;
	case 8:
		if (resultId == 0){
			GAMEDATA::getInstance()->settipNum(GAMEDATA::getInstance()->gettipNum() + 10);
			GAMEDATA::getInstance()->savetipNum();
			GameGuiLayer::help = true;
		}
		else{
		
			GameGuiLayer::help = false;
		}
	
		break;
	case 9:
		if (resultId == 0){
			GAMEDATA::getInstance()->setrefreshNum(GAMEDATA::getInstance()->getrefreshNum() + 10);
			GAMEDATA::getInstance()->saverefreshNum();
			GameGuiLayer::refresh = true;
		}
		else{
			
			GameGuiLayer::refresh = false;
		}

	

		break;
	case 10:
		if (resultId == 0){
			GAMEDATA::getInstance()->setaddtimeNum(GAMEDATA::getInstance()->getaddtimeNum() + 10);
			GAMEDATA::getInstance()->saveaddtimeNum();
		
			GameGuiLayer::addTime = true;
		}
		else{
		
			GameGuiLayer::addTime = false;
		}
		break;
	case 11:
		if (resultId == 0){
			GAMEDATA::getInstance()->settipNum(GAMEDATA::getInstance()->gettipNum() + 3);
			GAMEDATA::getInstance()->savetipNum();
			GAMEDATA::getInstance()->setrefreshNum(GAMEDATA::getInstance()->getrefreshNum() + 3);
			GAMEDATA::getInstance()->saverefreshNum();
			GAMEDATA::getInstance()->setaddtimeNum(GAMEDATA::getInstance()->getaddtimeNum() + 4);
			GAMEDATA::getInstance()->saveaddtimeNum();
		
			GameGuiLayer::addTime = true;
			GameGuiLayer::help = true;
			GameGuiLayer::refresh = true;
		}
		else{

			GameGuiLayer::addTime = false;
			GameGuiLayer::help = false;
			GameGuiLayer::refresh = false;
		}
		break;
	case 12:
		if (resultId == 0){
			GAMEDATA::getInstance()->settime(GAMEDATA::getInstance()->gettime() + 30);
		}
		else{

		}
	    break;
	case 13:
		if (resultId == 0){
			GAMEDATA::getInstance()->settime(GAMEDATA::getInstance()->gettime() + 45);
		}
		else{

		}
	    break;
	case 14:
		if (resultId == 0){
			GAMEDATA::getInstance()->setReviveNum(GAMEDATA::getInstance()->getReviveNum() -1);
			GAMEDATA::getInstance()->saveReviveNum();

			//GameGuiLayer::addTime = true;
		}
		else{

			//GameGuiLayer::addTime = false;
		}
        break;
	case 15:
		if (resultId == 0){
			GAMEDATA::getInstance()->setReviveNum(GAMEDATA::getInstance()->getReviveNum() -1);
			GAMEDATA::getInstance()->saveReviveNum();

			//GameGuiLayer::addTime = true;
		}
		else{

			//GameGuiLayer::addTime = false;
		}
		break;
	case 16:
		if (resultId == 0){
			GAMEDATA::getInstance()->setReviveNum(GAMEDATA::getInstance()->getReviveNum() -1);
			GAMEDATA::getInstance()->saveReviveNum();

			//GameGuiLayer::addTime = true;
		}
		else{

			//GameGuiLayer::addTime = false;
		}
		break;
	case 17:
		if (resultId == 0){
			GAMEDATA::getInstance()->setReviveNum(GAMEDATA::getInstance()->getReviveNum() -1);
			GAMEDATA::getInstance()->saveReviveNum();

			//GameGuiLayer::addTime = true;
		}
		else{

			//GameGuiLayer::addTime = false;
		}
		break;
	case 18:
		if (resultId == 0){
			GAMEDATA::getInstance()->settime(GAMEDATA::getInstance()->gettime() +10);
		}
		else{
	
		}
		break;
	case 19:
		if (resultId == 0){
			GAMEDATA::getInstance()->settime(GAMEDATA::getInstance()->gettime() + 15);
		}
		else{

		}
		break;
	case 20:
		if (resultId == 0){
			GAMEDATA::getInstance()->settime(GAMEDATA::getInstance()->gettime() + 20);
		}
		else{

		}
		break;
	case 21:
		if (resultId == 0){
			GAMEDATA::getInstance()->settime(GAMEDATA::getInstance()->gettime() + 25);
		}
		else{

		}
		break;

	default:
		break;
	}

	}*/