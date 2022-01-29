#include "stdafx.h"
#include "dark_mode.h"

namespace cui::dark {

bool is_dark_mode_enabled()
{
    return false;
}

void enable_dark_mode_for_app()
{
    enum class PreferredAppMode { System = 1, Forced = 2, Disabled = 3 };

    using SetPreferredAppModeProc = int(__stdcall*)(int);
    using FlushMenuThemesProc = void(__stdcall*)();

    const wil::unique_hmodule uxtheme(THROW_LAST_ERROR_IF_NULL(LoadLibrary(L"uxtheme.dll")));

    const auto set_preferred_app_mode
        = reinterpret_cast<SetPreferredAppModeProc>(GetProcAddress(uxtheme.get(), MAKEINTRESOURCEA(135)));

    set_preferred_app_mode(WI_EnumValue(PreferredAppMode::Forced));
}

void enable_top_level_non_client_dark_mode(HWND wnd)
{
    // Valid in Windows 10 10.0.18985 and newer (effectively 20H1+)
    constexpr DWORD DWMWA_USE_IMMERSIVE_DARK_MODE = 20;
    constexpr BOOL value = TRUE;
    DwmSetWindowAttribute(wnd, DWMWA_USE_IMMERSIVE_DARK_MODE, &value, sizeof(value));
}

namespace {

consteval COLORREF create_grey(const int value)
{
    return RGB(value, value, value);
}

enum class DarkColour : COLORREF {
    DARK_000 = create_grey(32),
    DARK_100 = create_grey(42),
    DARK_190 = create_grey(51),
    DARK_200 = create_grey(56),
    DARK_300 = create_grey(77),
    DARK_400 = create_grey(88),
    DARK_500 = create_grey(98),
    DARK_600 = create_grey(119),
    DARK_900 = create_grey(255),
};

COLORREF get_dark_colour(ColourID colour_id)
{
    switch (colour_id) {
    case ColourID::PanelCaptionBackground:
        return WI_EnumValue(DarkColour::DARK_300);
    case ColourID::StatusBarBackground:
        return WI_EnumValue(DarkColour::DARK_200);
    case ColourID::StatusBarText:
        return WI_EnumValue(DarkColour::DARK_900);
    case ColourID::TabControlBackground:
        return WI_EnumValue(DarkColour::DARK_200);
    case ColourID::TabControlItemBackground:
        return WI_EnumValue(DarkColour::DARK_200);
    case ColourID::TabControlItemText:
        return WI_EnumValue(DarkColour::DARK_900);
    case ColourID::TabControlItemBorder:
        return WI_EnumValue(DarkColour::DARK_000);
    case ColourID::TabControlActiveItemBackground:
        return WI_EnumValue(DarkColour::DARK_500);
    case ColourID::TabControlHotItemBackground:
        return WI_EnumValue(DarkColour::DARK_300);
    case ColourID::TabControlHotActiveItemBackground:
        return WI_EnumValue(DarkColour::DARK_600);
    case ColourID::VolumePopupBackground:
        return WI_EnumValue(DarkColour::DARK_200);
    case ColourID::VolumePopupBorder:
        return WI_EnumValue(DarkColour::DARK_300);
    case ColourID::VolumePopupText:
        return WI_EnumValue(DarkColour::DARK_900);
    default:
        uBugCheck();
    }
}

wil::unique_hbrush get_dark_colour_brush(ColourID colour_id)
{
    return wil::unique_hbrush(CreateSolidBrush(get_dark_colour(colour_id)));
}

int get_light_colour_system_id(ColourID colour_id)
{
    switch (colour_id) {
    case ColourID::PanelCaptionBackground:
        return COLOR_BTNFACE;
    case ColourID::StatusBarText:
        return COLOR_MENUTEXT;
    case ColourID::VolumePopupBackground:
        return COLOR_BTNFACE;
    case ColourID::VolumePopupBorder:
        return COLOR_3DLIGHT;
    case ColourID::VolumePopupText:
        return COLOR_MENUTEXT;
    default:
        uBugCheck();
    }
}

COLORREF get_light_colour(ColourID colour_id)
{
    return GetSysColor(get_light_colour_system_id(colour_id));
}

wil::unique_hbrush get_light_colour_brush(ColourID colour_id)
{
    return wil::unique_hbrush(GetSysColorBrush(get_light_colour_system_id(colour_id)));
}

} // namespace

COLORREF get_colour(ColourID colour_id, bool is_dark)
{
    return is_dark ? get_dark_colour(colour_id) : get_light_colour(colour_id);
}

wil::unique_hbrush get_colour_brush(ColourID colour_id, bool is_dark)
{
    return is_dark ? get_dark_colour_brush(colour_id) : get_light_colour_brush(colour_id);
}

LazyResource<wil::unique_hbrush> get_colour_brush_lazy(ColourID colour_id, bool is_dark)
{
    return {[colour_id, is_dark] { return get_colour_brush(colour_id, is_dark); }};
}

namespace {

COLORREF get_dark_system_colour(int system_colour_id)
{
    // Unfortunately, these are hard-coded as there doesn't seem to be a simple
    // way to get a similar set of dark mode colours from Windows.
    switch (system_colour_id) {
    case COLOR_HIGHLIGHTTEXT:
    case COLOR_MENUTEXT:
    case COLOR_WINDOWTEXT:
        return RGB(255, 255, 255);
    case COLOR_WINDOW:
        return RGB(32, 32, 32);
    case COLOR_HIGHLIGHT:
        return RGB(98, 98, 98);
    case COLOR_BTNTEXT:
        return RGB(255, 255, 255);
    case COLOR_BTNFACE:
        return RGB(51, 51, 51);
    case COLOR_WINDOWFRAME:
        return RGB(119, 119, 119);
    case COLOR_3DDKSHADOW:
        // Standard value: RGB(105, 105, 105)
        return RGB(28, 28, 28);
    case COLOR_3DHILIGHT:
        // Standard value: RGB(255, 255, 255)
        return RGB(100, 100, 100);
    case COLOR_3DLIGHT:
        // Standard value: RGB(227, 227, 227)
        return RGB(42, 42, 42);
    case COLOR_3DSHADOW:
        // Standard value: RGB(160, 160, 160)
        return RGB(100, 100, 100);
    default:
        return RGB(255, 0, 0);
    }
}

} // namespace

COLORREF get_system_colour(int system_colour_id, bool is_dark)
{
    if (is_dark)
        return get_dark_system_colour(system_colour_id);

    return GetSysColor(system_colour_id);
}

wil::unique_hbrush get_system_colour_brush(int system_colour_id, bool is_dark)
{
    if (is_dark)
        return wil::unique_hbrush(CreateSolidBrush(get_system_colour(system_colour_id, true)));

    // HBRUSHes returned by GetSysColorBrush don't need destroying, but doing so does no harm
    // according to the docs
    return wil::unique_hbrush(GetSysColorBrush(system_colour_id));
}

} // namespace cui::dark
