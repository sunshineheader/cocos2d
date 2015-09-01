#include "PlayerRank.h"
PLAYERRANK::PLAYERRANK(){
}
PLAYERRANK* PLAYERRANK::_instance = 0;
PLAYERRANK* PLAYERRANK::getInstance(){
	if(_instance == 0){
		_instance = new PLAYERRANK();
	}
	return _instance;
}

int PLAYERRANK::getRankList(int score){
		if (score == 0) {
			return 68547;
		} else if (score < PLAYERRANK::LEVEL_1) {
			return (int) (62547 - 50000 * (1.0f - (PLAYERRANK::LEVEL_1 - score)*1.0f
					/ (PLAYERRANK::LEVEL_1 - PLAYERRANK::LEVEL_0)));
		} else if (score < PLAYERRANK::LEVEL_2) {
			return (int) (12547 - 8000 * (1 - (PLAYERRANK::LEVEL_2 - score)*1.0f
					/ (PLAYERRANK::LEVEL_2 - PLAYERRANK::LEVEL_1)));
		} else if (score < PLAYERRANK::LEVEL_3) {
			return (int) (4544 - 3000 * (1 - (PLAYERRANK::LEVEL_3 - score)*1.0f
					/ (PLAYERRANK::LEVEL_3 - PLAYERRANK::LEVEL_2)));
		} else if (score < PLAYERRANK::LEVEL_4) {
			return (int) (1343 - 600 * (1 - (PLAYERRANK::LEVEL_4 - score)*1.0f
					/ (PLAYERRANK::LEVEL_4 - PLAYERRANK::LEVEL_3)));
		} else if (score < PLAYERRANK::LEVEL_5) {
			return (int) (710 - 400 * (1 - (PLAYERRANK::LEVEL_5 - score)*1.0f
					/ (PLAYERRANK::LEVEL_5 - PLAYERRANK::LEVEL_4)));
		} else if (score < PLAYERRANK::LEVEL_6) {
			return (int) (303 - 240 * (1 - (PLAYERRANK::LEVEL_6 - score)*1.0f
					/ (PLAYERRANK::LEVEL_6 - PLAYERRANK::LEVEL_5)));
		} else if (score < PLAYERRANK::LEVEL_7) {
			return (int) (51 + 10 * (1 - (PLAYERRANK::LEVEL_7 - score)*1.0f
					/ (PLAYERRANK::LEVEL_7 - PLAYERRANK::LEVEL_6)));
		} else {
			return 1;
		}
}

int PLAYERRANK::getRankPer(int score){
	if (score == 0) {
			return 10;
		} else if (score < PLAYERRANK::LEVEL_1) {
			return (int) (10 + 10.0f * (1 - (PLAYERRANK::LEVEL_1 - score)
					/ (PLAYERRANK::LEVEL_1 - PLAYERRANK::LEVEL_0)));
		} else if (score < PLAYERRANK::LEVEL_2) {
			return (int) (20 + 10.0f * (1 - (PLAYERRANK::LEVEL_2 - score)
					/ (PLAYERRANK::LEVEL_2 - PLAYERRANK::LEVEL_1)));
		} else if (score < PLAYERRANK::LEVEL_3) {
			return (int) (30 + 20.0f * (1 - (PLAYERRANK::LEVEL_3 - score)
					/ (PLAYERRANK::LEVEL_3 - PLAYERRANK::LEVEL_2)));
		} else if (score < PLAYERRANK::LEVEL_4) {
			return (int) (50 + 20.0f * (1 - (PLAYERRANK::LEVEL_4 - score)
					/ (PLAYERRANK::LEVEL_4 - PLAYERRANK::LEVEL_3)));
		} else if (score < PLAYERRANK::LEVEL_5) {
			return (int) (70 + 10.0f * (1 - (PLAYERRANK::LEVEL_5 - score)
					/ (PLAYERRANK::LEVEL_5 - PLAYERRANK::LEVEL_4)));
		} else if (score < PLAYERRANK::LEVEL_6) {
			return (int) (80 + 10.0f * (1 - (PLAYERRANK::LEVEL_6 - score)
					/ (PLAYERRANK::LEVEL_6 - PLAYERRANK::LEVEL_5)));
		} else if (score < PLAYERRANK::LEVEL_7) {
			return (int) (90 + 10.0f * (1 - (PLAYERRANK::LEVEL_7 - score)
					/ (PLAYERRANK::LEVEL_7 - PLAYERRANK::LEVEL_6)));
		} else {
			return 99;
		}
}