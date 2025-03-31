#ifndef STANDARD_INCLUDES_H //this is called a header guard
#define STANDARD_INCLUDES_H

#define GLM_ENABLE_EXPERIMENTAL

#define SDL_MAIN_HANDLED

#define NATIVE_XRES 1920
#define NATIVE_YRES 1080



#include <string>
#include <vector>
#include <iostream>
#include <fstream>

#include <cinttypes>
#include <stdio.h>
#include <thread>
#include <map>
#include <algorithm>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_pixels.h> //This is a way we are going to create surfaces from any text
#include <SDL_mixer.h>

//Project headers
#include "Singleton.h"
#include "BasicStructs.h"

//#ifdef _WIN32 //this means if _WIN32 is defined, we are in Windows and will do whatever is below.
//#include <Windows.h>
//#include <direct.h>
//#define M_ASSERT(_cond, _msg) \
//	if(!(_cond)) { OutputDebugStringA(_msg); std::abort(); } //if _cond is false, run error message.
//#define GetCurrentDir _getcwd
//#else //this is if we are in Linux, Max, Unix, or whatever is not Windows, and include the below.
//#include <unistd.h>
//#define GetCurrentDir getcwd //not a typo, just different variable for different operating system.
//#endif

//Windows specific includes and defines
#ifdef _WIN32
#include <Windows.h>
#include <direct.h>
#define M_ASSERT(_cond, _msg) \
	if (!(_cond)) {OutputDebugStringA(_msg); std::abort(); glfwTerminate(); }
#define GetCurrentDir _getcwd //Get the current working directory
#else //if linux or mac or any other Unix-based OS
#include <unistd.h>
#define GetCurrentDir getcwd //not a typo, just different variable for different operating system.
#endif

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm.hpp>
#include <ext.hpp>

using namespace std;

#endif //STANDARD_INCLUDES_H