#pragma once

#include <cstdarg>
#include <cstdio>

void YYInfo(const char* format, ...);
void YYWarning(const char* format, ...);
void YYError(const char* format, ...);