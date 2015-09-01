LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := libzimon.so
LOCAL_SRC_FILES := prebuilt/libzimon.so
include $(PREBUILT_SHARED_LIBRARY)
LOCAL_SHARED_LIBRARIES :=libzimon

$(call import-add-path,$(LOCAL_PATH)/../../cocos2d)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/external)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/cocos)

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

LOCAL_SRC_FILES := hellocpp/main.cpp \
				   hellocpp/payproxy.cpp \
                   ../../Classes/AppDelegate.cpp \
                   ../../Classes/Audio.cpp \
                   ../../Classes/BackgroundLayer.cpp \
                   ../../Classes/BankRaiseLayer.cpp \
                   ../../Classes/Chinese.cpp \
                   ../../Classes/GAMEDATA.cpp \
                   ../../Classes/GameLayer.cpp \
                   ../../Classes/GameResultLayer.cpp \
                   ../../Classes/GameScene.cpp \
                   ../../Classes/GameResultScene.cpp \
                   ../../Classes/GameStateInfo.cpp \
                   ../../Classes/InfoLayer.cpp \
                   ../../Classes/MenuLayer.cpp \
                   ../../Classes/MenuScene.cpp \
                   ../../Classes/Monster.cpp \
                   ../../Classes/MonsterLayer.cpp \
                   ../../Classes/Player.cpp \
                   ../../Classes/PlayerRank.cpp \
                   ../../Classes/ResultGold.cpp \
                   ../../Classes/TollgateScene.cpp \
                   ../../Classes/VisibleRect.cpp \
                   ../../Classes/QuitLayer.cpp \
                   ../../Classes/GamePauseLayer.cpp \
                   ../../Classes/GameResultInfo.cpp \
                   ../../Classes/PayHandler.cpp \
                   ../../Classes/SignIn.cpp \
                   ../../Classes/CallAndroidMethod.cpp\
                   ../../Classes/PropInfo.cpp\
                   ../../Classes/SignInPrize.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes

LOCAL_STATIC_LIBRARIES := cocos2dx_static

include $(BUILD_SHARED_LIBRARY)

$(call import-module,.)