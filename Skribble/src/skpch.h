#pragma once

#include <iostream>
#include <filesystem>
#include <memory>
#include <utility>
#include <functional>
#include <algorithm>

#include <unordered_map>
#include <unordered_set>
#include <string>
#include <sstream>
#include <array>
#include <vector>

#include "Skribble/Core/Core.h"
#include "Skribble/Core/Debug.h"

#include "Skribble/Debug/Instrumentor.h"

#ifdef  SKRIBBLE_WINDOWS
#include <Windows.h>
#endif