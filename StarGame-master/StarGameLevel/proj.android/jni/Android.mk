LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

$(call import-add-path,$(LOCAL_PATH)/../../cocos2d)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/external)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/cocos)

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

LOCAL_SRC_FILES := hellocpp/main.cpp \
                   hellocpp/PayProxy.cpp \
                   ../../Classes/AppDelegate.cpp \
                   ../../Classes/HelloWorldScene.cpp \
  					../../Classes/MenuLayer.cpp \
  					../../Classes/Chinese.cpp \
  					../../Classes/ComboEffect.cpp \
  					../../Classes/FloatWord.cpp \
  					../../Classes/GameData.cpp \
  					../../Classes/GameLayer.cpp \
  					../../Classes/LevelMsgLayer.cpp \
 	 				../../Classes/GameScene.cpp \
 	 				../../Classes/Star.cpp \
  					../../Classes/StarMatrix.cpp \
  					../../Classes/StarParticle.cpp \
  					../../Classes/TopMenu.cpp\
					../../Classes/Audio.cpp\
					../../Classes/GameOverScene.cpp\
					../../Classes/GameOverLayer.cpp\
					../../Classes/PlayerRank.cpp\
					../../Classes/GamePauseLayer.cpp\
					../../Classes/CallAndroidMethod.cpp\
					../../Classes/MenuScenePayHandler.cpp\
					../../Classes/SignIn.cpp\
					../../Classes/Upgrade.cpp\
					../../Classes/About.cpp\
					../../Classes/BlinkTitle.cpp\
					../../Classes/Gold.cpp\
					../../Classes/OvalActionInterval.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes

LOCAL_STATIC_LIBRARIES := cocos2dx_static

include $(BUILD_SHARED_LIBRARY)

$(call import-module,.)
