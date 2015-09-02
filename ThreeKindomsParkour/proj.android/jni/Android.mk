LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

$(call import-add-path,$(LOCAL_PATH)/../../cocos2d)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/external)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/cocos)

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../cocos2d

LOCAL_SRC_FILES := hellocpp/main.cpp \
                   ../../Classes/AppDelegate.cpp \
                   ../../Classes/Base/RepeatedBackground.cpp \
                   ../../Classes/Game/GameObjects/Block.cpp \
                   ../../Classes/Game/GameObjects/FireBall.cpp \
                   ../../Classes/Game/GameObjects/GameObject.cpp \
                   ../../Classes/Game/GameObjects/House.cpp \
                   ../../Classes/Game/GameObjects/PropItem.cpp \
                   ../../Classes/Game/GameObjects/ScoreItem.cpp \
                   ../../Classes/Game/GameObjects/SharpBall.cpp \
                   ../../Classes/Game/GameObjects/ShieldSoldier.cpp \
                   ../../Classes/Game/GameObjects/SpearSoldier.cpp \
                   ../../Classes/Game/GameObjects/Spiling.cpp \
                   ../../Classes/Game/Props/AutoCollectScoreItems.cpp \
                   ../../Classes/Game/Props/InvincibleEffect.cpp \
                   ../../Classes/Game/Props/JiaSuEffect.cpp \
                   ../../Classes/Game/Props/QuickFlying.cpp \
                   ../../Classes/Game/Quests/CollectionQuest.cpp \
                   ../../Classes/Game/Quests/EndlessQuest.cpp \
                   ../../Classes/Game/Quests/KillQuest.cpp \
                   ../../Classes/Game/Quests/Quest.cpp \
                   ../../Classes/Game/Quests/RacingQuest.cpp \
                   ../../Classes/Game/GameMap.cpp \
                   ../../Classes/Game/WenChen.cpp \
                   ../../Classes/Game/WuJiang.cpp \
                   ../../Classes/Game/ZhuGong.cpp \
                   ../../Classes/Game/Platform.cpp \
                   ../../Classes/Math/Circle.cpp \
                   ../../Classes/Math/Intersector.cpp \
                   ../../Classes/Math/MathUtils.cpp \
                   ../../Classes/Math/OrientedRect.cpp \
                   ../../Classes/Math/Polygon.cpp \
                   ../../Classes/Math/Segment.cpp \
                   ../../Classes/NodeReaders/SceneGameReader.cpp \
                   ../../Classes/NodeReaders/SceneLevelSelectReader.cpp \
                   ../../Classes/NodeReaders/SceneMainReader.cpp \
                   ../../Classes/Scenes/SceneBase.cpp \
                   ../../Classes/Scenes/SceneCharacterSelect.cpp \
                   ../../Classes/Scenes/SceneGame.cpp \
                   ../../Classes/Scenes/SceneLevelSelect.cpp \
                   ../../Classes/Scenes/SceneLoading.cpp \
                   ../../Classes/Scenes/SceneMain.cpp \
                   ../../Classes/Scenes/ScenePropSelect.cpp \
                   ../../Classes/Scenes/SceneSettlement.cpp \
                   ../../Classes/UI/ScrollController.cpp \
                   ../../Classes/Utils/Properties.cpp \
                   ../../Classes/Utils/SceneHelper.cpp \
                   ../../Classes/Utils/QuestHelper.cpp \
                   ../../Classes/Utils/UserData.cpp \
                   ../../Classes/Utils/TmxMapHelper.cpp \
                   ../../Classes/Utils/RapidJsonHelper.cpp



# _COCOS_HEADER_ANDROID_BEGIN
# _COCOS_HEADER_ANDROID_END

LOCAL_STATIC_LIBRARIES := cocos2dx_static
LOCAL_STATIC_LIBRARIES += cocosdenshion_static
LOCAL_STATIC_LIBRARIES += cocos_extension_static
LOCAL_STATIC_LIBRARIES += cocostudio_static
LOCAL_STATIC_LIBRARIES += cocos_network_static

# _COCOS_LIB_ANDROID_BEGIN
# _COCOS_LIB_ANDROID_END

include $(BUILD_SHARED_LIBRARY)

$(call import-module,.)

# _COCOS_LIB_IMPORT_ANDROID_BEGIN
# _COCOS_LIB_IMPORT_ANDROID_END
