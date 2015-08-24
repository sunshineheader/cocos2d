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
hellocpp/PayProxy.cpp \
hellocpp/MoreGameProxy.cpp \
				../../Classes/AppDelegate.cpp \
				../../Classes/HelloWorldScene.cpp \
				../../Classes/BlockParticle.cpp  \
				../../Classes/ChineseWorld.cpp \
				../../Classes/GameAudio.cpp \
				../../Classes/GameBlocks.cpp \
				../../Classes/GameCountLabel.cpp \
				../../Classes/GameData.cpp \
				../../Classes/GameLayerScene.cpp \
				../../Classes/GameOverLabel.cpp \
				../../Classes/GameOverScenecpp.cpp \
				../../Classes/GameStartScene.cpp \
				../../Classes/PlayerRank.cpp \
				../../Classes/PayForGame.cpp \
				../../Classes/MusicInfoUtil.cpp \
				../../Classes/Payhandler.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes

LOCAL_STATIC_LIBRARIES := cocos2dx_static

include $(BUILD_SHARED_LIBRARY)

$(call import-module,.)
