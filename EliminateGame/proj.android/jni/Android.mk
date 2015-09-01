LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

$(call import-add-path,$(LOCAL_PATH)/../../cocos2d)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/external)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/cocos)

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

LOCAL_SRC_FILES := hellocpp/main.cpp \
                   ../../Classes/AppDelegate.cpp \
                   ../../Classes/Audio.cpp \
                   ../../Classes/CallAndroidMethod.cpp \
                   ../../Classes/GameData.cpp \
                   ../../Classes/GameGuiLayer.cpp \
                   ../../Classes/GameLayer.cpp \
                   ../../Classes/GamePauseLayer.cpp \
                   ../../Classes/GameResultLayer.cpp \
                   ../../Classes/GameResultScene.cpp \
                   ../../Classes/GameScene.cpp \
                   ../../Classes/LobbyScene.cpp \
                   ../../Classes/Monster.cpp \
                   ../../Classes/GameSlioder.cpp \
                   ../../Classes/GameState.cpp \
                   

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes

LOCAL_STATIC_LIBRARIES := cocos2dx_static

include $(BUILD_SHARED_LIBRARY)

$(call import-module,.)
