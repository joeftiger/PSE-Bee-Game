#/****************************************************************************
# Copyright (c) 2013-2014 cocos2d-x.org
# Copyright (c) 2015-2017 Chukong Technologies Inc.
#
# http://www.cocos2d-x.org
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:

# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.

# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.
# ****************************************************************************/

cmake_minimum_required(VERSION 3.6)

set(APP_NAME PSE-Bee-Game)

project(${APP_NAME})

# -----------------------------------------------------------------------------
message("begin custom conf:")
message(STATUS "Cmake version: ${CMAKE_VERSION}")
set(hostname)
cmake_host_system_information(RESULT hostname QUERY HOSTNAME)

# Needed to compile on Linux

if (CMAKE_HOST_SYSTEM_NAME STREQUAL "Linux")
    message(STATUS "Linux - setting flag \"-no-pie\"")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -no-pie")

    if (${CMAKE_VERSION} VERSION_EQUAL "3.11" OR ${CMAKE_VERSION} VERSION_GREATER "3.11")
        # use new OpenGL instead of legacy (laptop/desktop Julius)
        if (hostname STREQUAL "E580")
            cmake_policy(SET CMP0072 NEW)
            message(STATUS "Julius Laptop - setting flag \"CMP0072 NEW\"")
        elseif (hostname STREQUAL "surface")
            cmake_policy(SET CMP0072 NEW)
            message(STATUS "Julius Laptop - setting flag \"CMP0072 NEW\"")
        elseif (hostname STREQUAL "ryzen")
            cmake_policy(SET CMP0072 NEW)
            message(STATUS "Julius Desktop - setting flag \"CMP0072 NEW\"")
        elseif (hostname STREQUAL "mauro-lenovo")
            cmake_policy(SET CMP0072 NEW)
            message(STATUS "Mauro Laptop - setting flag \"CMP0072 NEW\"")
        endif ()
    endif ()
endif ()
message("end custom conf\n")
# -----------------------------------------------------------------------------

set(COCOS2DX_ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cocos2d)
set(CMAKE_MODULE_PATH ${COCOS2DX_ROOT_PATH}/cmake/Modules/)

include(CocosBuildSet)
add_subdirectory(${COCOS2DX_ROOT_PATH}/cocos ${ENGINE_BINARY_PATH}/cocos/core)

# record sources, headers, resources...
set(GAME_SOURCE)
set(GAME_HEADER Classes/HeaderFiles/Restorable.h)

set(GAME_RES_FOLDER
        "${CMAKE_CURRENT_SOURCE_DIR}/Resources"
        )
if (APPLE OR WINDOWS)
    cocos_mark_multi_resources(common_res_files RES_TO "Resources" FOLDERS ${GAME_RES_FOLDER})
endif ()

# add cross-platforms source files and header files 
list(APPEND GAME_SOURCE
        Classes/About/AboutScene.cpp
        Classes/Algorithm/GameAlgorithm.cpp
        Classes/AppDelegate.cpp
        Classes/Atlas/BeeHiveAtlas.cpp
        Classes/Atlas/HoneyExtractorAtlas.cpp
		Classes/Effects/BeeParticles.cpp
        Classes/Game/BeeHive.cpp
        Classes/Game/GameScene.cpp
        Classes/Game/HUDLayer.cpp
        Classes/Game/HoneyExtractor.cpp
        Classes/Game/Player.cpp
		Classes/Game/TileMapLayer.cpp
        Classes/Game/Time.cpp
        Classes/Game/Wallet.cpp
        Classes/Interaction/BeeHivePopup.cpp
        Classes/Interaction/HoneyExtractorPopup.cpp
		Classes/Interaction/HoneyMover.cpp
        Classes/ItemPanel/ItemPanelLayer.cpp
        Classes/ItemPanel/TouchUtil.cpp
        Classes/MainMenu/MainMenuScene.cpp
        Classes/Options/OptionsScene.cpp
        Classes/Options/SaveDeleteConfirmation.cpp
        Classes/Resources/SpriteContainer.cpp
        Classes/Resources/Sprites.cpp
        Classes/Resources/Tiles.cpp
        Classes/SaveLoad/SaveLoad.cpp
        Classes/Settings.cpp
        Classes/Shop/ShopScene.cpp
        Classes/Story/Popup.cpp
        Classes/Story/StoryScene.cpp
        Classes/TileMapObjects/PlaceableSprite.cpp
        Classes/TileMapObjects/PlaceableTile.cpp
        )

list(APPEND GAME_HEADER
        Classes/About/AboutScene.h
        Classes/Algorithm/GameAlgorithm.h
        Classes/AppDelegate.h
        Classes/Atlas/BeeHiveAtlas.h
        Classes/Atlas/HoneyExtractorAtlas.h
		Classes/Effects/BeeParticles.h
        Classes/Game/BeeHive.h
        Classes/Game/GameScene.h
        Classes/Game/HUDLayer.h
        Classes/Game/HoneyExtractor.h
        Classes/Game/Player.h
        Classes/Game/TileMapLayer.h
        Classes/Game/Time.h
        Classes/Game/Wallet.h
        Classes/HeaderFiles/HealthStates.h
        Classes/HeaderFiles/Restorable.h
        Classes/HeaderFiles/Seasons.h
        Classes/HeaderFiles/TimeStruct.h
        Classes/Interaction/BeeHivePopup.h
        Classes/Interaction/HoneyExtractorPopup.h
		Classes/Interaction/HoneyMover.h
        Classes/ItemPanel/ItemPanelLayer.h
        Classes/ItemPanel/TouchUtil.h
        Classes/MainMenu/MainMenuScene.h
        Classes/Observable.h
        Classes/Observer.h
        Classes/Options/OptionsScene.h
        Classes/Options/SaveDeleteConfirmation.h
        Classes/Resources/SpriteContainer.h
        Classes/Resources/Sprites.h
        Classes/Resources/Tiles.h
        Classes/SaveLoad/SaveLoad.h
        Classes/Settings.h
        Classes/Shop/ShopScene.h
        Classes/Story/Popup.h
        Classes/Story/StoryScene.h
        Classes/TileMapObjects/PlaceableSprite.h
        Classes/TileMapObjects/PlaceableTile.h
		)

if (ANDROID)
    # change APP_NAME to the share library name for Android, it's value depend on AndroidManifest.xml
    set(APP_NAME MyGame)
    list(APPEND GAME_SOURCE
            proj.android/app/jni/hellocpp/main.cpp
            )
elseif (LINUX)
    list(APPEND GAME_SOURCE
            proj.linux/main.cpp
            )
elseif (WINDOWS)
    list(APPEND GAME_HEADER
            proj.win32/main.h
            proj.win32/resource.h
            )
    list(APPEND GAME_SOURCE
            proj.win32/main.cpp
            proj.win32/game.rc
            ${common_res_files}
            )
elseif (APPLE)
    if (IOS)
        list(APPEND GAME_HEADER
                proj.ios_mac/ios/AppController.h
                proj.ios_mac/ios/RootViewController.h
                )
        set(APP_UI_RES
                proj.ios_mac/ios/LaunchScreen.storyboard
                proj.ios_mac/ios/LaunchScreenBackground.png
                proj.ios_mac/ios/Images.xcassets
                )
        list(APPEND GAME_SOURCE
                proj.ios_mac/ios/main.m
                proj.ios_mac/ios/AppController.mm
                proj.ios_mac/ios/RootViewController.mm
                proj.ios_mac/ios/Prefix.pch
                ${APP_UI_RES}
                )
    elseif (MACOSX)
        set(APP_UI_RES
                proj.ios_mac/mac/Icon.icns
                proj.ios_mac/mac/Info.plist
                )
        list(APPEND GAME_SOURCE
                proj.ios_mac/mac/main.cpp
                proj.ios_mac/mac/Prefix.pch
                ${APP_UI_RES}
                )
    endif ()
    list(APPEND GAME_SOURCE ${common_res_files})
endif ()

# mark app complie info and libs info
set(all_code_files
        ${GAME_HEADER}
        ${GAME_SOURCE}
           )
if (NOT ANDROID)
    add_executable(${APP_NAME} ${all_code_files})
else ()
    add_library(${APP_NAME} SHARED ${all_code_files})
    add_subdirectory(${COCOS2DX_ROOT_PATH}/cocos/platform/android ${ENGINE_BINARY_PATH}/cocos/platform)
    target_link_libraries(${APP_NAME} -Wl,--whole-archive cpp_android_spec -Wl,--no-whole-archive)
endif ()

target_link_libraries(${APP_NAME} cocos2d)
target_include_directories(${APP_NAME}
        PRIVATE Classes
        PRIVATE ${COCOS2DX_ROOT_PATH}/cocos/audio/include/
        )

# mark app resources
setup_cocos_app_config(${APP_NAME})
if (APPLE)
    set_target_properties(${APP_NAME} PROPERTIES RESOURCE "${APP_UI_RES}")
    if (MACOSX)
        set_target_properties(${APP_NAME} PROPERTIES
                MACOSX_BUNDLE_INFO_PLIST "${CMAKE_CURRENT_SOURCE_DIR}/proj.ios_mac/mac/Info.plist"
                )
    elseif (IOS)
        cocos_pak_xcode(${APP_NAME} INFO_PLIST "iOSBundleInfo.plist.in")
        set_xcode_property(${APP_NAME} ASSETCATALOG_COMPILER_APPICON_NAME "AppIcon")
    endif ()
elseif (WINDOWS)
    cocos_copy_target_dll(${APP_NAME} COPY_TO ${APP_RES_DIR}/..)
endif ()

if (LINUX OR WINDOWS)
    cocos_copy_res(COPY_TO ${APP_RES_DIR} FOLDERS ${GAME_RES_FOLDER})
endif ()
