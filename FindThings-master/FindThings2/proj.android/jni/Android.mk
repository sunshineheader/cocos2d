LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

$(call import-add-path,$(LOCAL_PATH)/../../cocos2d)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/external)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/cocos)

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

LOCAL_SRC_FILES := hellocpp/main.cpp \
				   hellocpp/PayProxy.cpp \
				   hellocpp/MoreProxy.cpp \
                   ../../Classes/AppDelegate.cpp \
                   ../../Classes/Audio.cpp \
                   ../../Classes/BottomMenu.cpp \
                   ../../Classes/Chinese.cpp \
                   ../../Classes/GameData.cpp \
                   ../../Classes/GameLayer.cpp \
                   ../../Classes/GameOverLayer.cpp \
                   ../../Classes/GameOverScene.cpp \
                   ../../Classes/GamePauseLayer.cpp \
                   ../../Classes/GameScene.cpp \
                   ../../Classes/GameState.cpp \
                   ../../Classes/GameView.cpp \
                   ../../Classes/ImageInfoUtil.cpp \
                   ../../Classes/Materials.cpp \
                   ../../Classes/StartScene.cpp \
                   ../../Classes/BlinkTitle.cpp \
                   ../../Classes/TaskInfoUtil.cpp \
                   ../../Classes/TaskMenu.cpp \
                   ../../Classes/CallAndroidMethod.cpp \
                   ../../Classes/GamePayHandler.cpp \
                   ../../Classes/SignIn.cpp \
                   ../../Classes/TaskSprite.cpp \
                   ../../Classes/GuideInfoUtil.cpp \
                   ../../Classes/GameParticle.cpp \
                   ../../Classes/PlayerRank.cpp \
                   ../../Classes/PositionInfoUtil.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes

LOCAL_STATIC_LIBRARIES := cocos2dx_static

include $(BUILD_SHARED_LIBRARY)

$(call import-module,.)
