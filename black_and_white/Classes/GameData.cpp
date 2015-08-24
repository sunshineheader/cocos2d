#include"GameData.h"
#include "cocos2d.h"
using namespace cocos2d;

GameData* GameData::data_instance = nullptr;

GameData::GameData()
{
	initData();
}

GameData::~GameData()
{

}

void GameData::initData()
{
	 currcert_sorce = 0;
}
GameData*GameData::getInstance()
{
	if (data_instance==nullptr)
	{
		data_instance = new GameData();
	}
	return data_instance;
	delete data_instance;
	data_instance = nullptr;
}

int GameData::get_currcert_life()
{
	return UserDefault::getInstance()->getIntegerForKey("currcert_life", 0);
}


void GameData::set_currcert_life(int value){
	UserDefault::getInstance()->setIntegerForKey("currcert_life", value);
}


void GameData::setBestSorce(int value)
{
	UserDefault::getInstance()->setIntegerForKey("best_sorce", value);
}

int GameData::getBestSorce()
{
	return UserDefault::getInstance()->getIntegerForKey("best_sorce", 0);
}


void GameData::set_is_first_login(bool value){
	UserDefault::getInstance()->setIntegerForKey("first_login", value);
}

bool GameData::get_is_first_login(){
	return UserDefault::getInstance()->getIntegerForKey("first_login",true);
}

void GameData::set_error_number(int err){
	UserDefault::getInstance()->setIntegerForKey("error_number", err);

}
int GameData::get_error_number(){
	return UserDefault::getInstance()->getIntegerForKey("error_number", 0);
}


void GameData::set_xiao_guo(bool ishave){
	UserDefault::getInstance()->setIntegerForKey("xiao_guo", ishave);
}
bool GameData::get_xiao_guo(){
	return UserDefault::getInstance()->getIntegerForKey("xiao_guo", false);
}
