#pragma once
#include <cstdarg>
static void DebugLog(const wchar_t* str)
{
    OutputDebugString(str);
    OutputDebugString(L"\n");
}
template<typename T>
void DebugParam(const wchar_t* format, const T src...)
{
    wchar_t str[256];
    va_list args;
    va_start(args, format);
    vswprintf(str, 256, format, args);
    OutputDebugString(str);
    OutputDebugString(L"\n");
    va_end(args);
}