// tjsAndroidTypes.h
#pragma once

#ifdef __ANDROID__
#include <string>
#include <codecvt>
#include <locale>


typedef char16_t tjs_char;
typedef std::u16string tjs_string;


#define TJS_W(x) u##x


inline std::string tjs_to_utf8(const tjs_string& str) {
    std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t> converter;
    return converter.to_bytes(str);
}

inline tjs_string utf8_to_tjs(const std::string& str) {
    std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t> converter;
    return converter.from_bytes(str);
}

#else
#include "tjsTypes.h"
#include "tjsString.h"
#endif