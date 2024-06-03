// header.h : include file for standard system include files,
// or project specific include files
//

#pragma once

#include "targetver.h"
#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files
#include <windows.h>
// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

#include <deque>
#include <strsafe.h>
#include <time.h>


#define MAX_LOADSTRING 100
#define ROAD_COLOR RGB(200,200,200)
#define OUTLINE_COLOR RGB(0,0,0)
#define RED_COLOR RGB(255,0,0)
#define YELLOW_COLOR RGB(200,200,0)
#define GREEN_COLOR RGB(0,255,75)
#define LIGHT_OFF_COLOR RGB(100,100,100)
#define TIMER_LIGHTS 1
#define TIMER_CARS 2
#define TIMER_ADD_CARS 3
#define CAR_LENGTH 40
#define CAR_WIDTH 20
#define ROAD_WIDTH 100