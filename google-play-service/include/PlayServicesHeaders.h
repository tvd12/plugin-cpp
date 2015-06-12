//
//  PlayServicesHeaders.h
//  SupernaturalMemory
//
//  Created by Dung Ta Van on 1/7/15.
//
//

#ifndef SupernaturalMemory_PlayServicesHeaders_h
#define SupernaturalMemory_PlayServicesHeaders_h

#include <string>



#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS

#ifdef __OBJC__
#include <objc/NSObjCRuntime.h>
#endif

#elif CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID

#include <jni.h>

#include <android/log.h>

#include "gpg/android_initialization.h"
#include "gpg/android_support.h"

#endif

#include "logging.h"

#include "gpg/achievement.h"
#include "gpg/achievement_manager.h"
#include "gpg/builder.h"
#include "gpg/debug.h"
#include "gpg/default_callbacks.h"
#include "gpg/game_services.h"
#include "gpg/leaderboard.h"
#include "gpg/leaderboard_manager.h"
#include "gpg/platform_configuration.h"
#include "gpg/player_manager.h"
#include "gpg/score_page.h"
#include "gpg/types.h"

#endif
