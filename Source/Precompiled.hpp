#pragma once

//
// Standard
//

#include <cctype>
#include <typeindex>
#include <memory>
#include <numeric>
#include <algorithm>
#include <functional>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <queue>
#include <map>

//
// External
//

// Windows
#ifdef WIN32
    #define WIN32_LEAN_AND_MEAN
    #define NOMINMAX
    #include <windows.h>
#endif

// GLM
#include <glm/glm.hpp>

// GLEW
#include <gl/glew.h>

// GLFW
#include <glfw/glfw3.h>

//
// Project
//

#include "Common/Build.hpp"
#include "Common/Debug.hpp"
#include "Common/Utility.hpp"
#include "Common/NonCopyable.hpp"
#include "Common/ScopeGuard.hpp"
#include "Common/Delegate.hpp"
#include "Common/Receiver.hpp"
#include "Common/Dispatcher.hpp"
#include "Common/Collector.hpp"
#include "Logger/Logger.hpp"
#include "Main.hpp"
