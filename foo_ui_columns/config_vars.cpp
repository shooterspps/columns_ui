#include "stdafx.h"
#include "menu_items.h"
#include "rebar.h"
#include "columns_v2.h"
#include "common.h"
#include "main_window.h"

namespace settings {
namespace guids {
// {A1333C45-B247-4b84-AFBA-F5DAF50EBF33}
const GUID show_status_pane = {0xa1333c45, 0xb247, 0x4b84, {0xaf, 0xba, 0xf5, 0xda, 0xf5, 0xe, 0xbf, 0x33}};

// {92416F05-BD93-4F50-93BD-5577C37CF14D}
static const GUID custom_splitter_divider_width
    = {0x92416f05, 0xbd93, 0x4f50, {0x93, 0xbd, 0x55, 0x77, 0xc3, 0x7c, 0xf1, 0x4d}};
} // namespace guids

fbh::ConfigObjectBoolFactory<> allow_locked_panel_resizing(
    cui::config_objects::guid_bool_locked_panel_resizing_allowed, true);
fbh::ConfigUint32DpiAware custom_splitter_divider_width(guids::custom_splitter_divider_width, 2);

fbh::ConfigInt32DpiAware playlist_switcher_item_padding(
    GUID{0xc8f7e065, 0xeb66, 0xe282, {0xbd, 0xe3, 0x70, 0xaa, 0xf4, 0x3a, 0x10, 0x97}}, 4),
    playlist_view_item_padding(GUID{0x032abfcb, 0x6cab, 0x25ee, {0x9d, 0xe8, 0x27, 0x89, 0xa9, 0x0a, 0x72, 0x36}}, 4);

cfg_bool show_status_pane(guids::show_status_pane, true);
} // namespace settings

namespace cui::config {

advconfig_branch_factory advconfig_branch_columns_ui(
    "Columns UI", advconfig_branch_columns_ui_id, advconfig_branch::guid_branch_display, 0);

advconfig_branch_factory advconfig_branch_notification_area(
    "Windows notification area", advconfig_branch_notification_area_id, advconfig_branch_columns_ui_id, 0);

static GUID advbool_notification_icon_x_buttons_id{
    0xcee3f8cc, 0x7ca6, 0x4277, {0xaa, 0xd4, 0xce, 0xc7, 0xb9, 0xd0, 0x5a, 0x63}};
advconfig_checkbox_factory advbool_notification_icon_x_buttons(
    "Use back/forward mouse buttons to skip track when over notification area icon",
    advbool_notification_icon_x_buttons_id, advconfig_branch_notification_area_id, 0, false);

static GUID advbool_close_to_notification_icon_id{
    0x41695241, 0x7854, 0x5a5a, {0x4d, 0x69, 0x6b, 0x75, 0x57, 0x52, 0x6c, 0x44}};
advconfig_checkbox_factory advbool_close_to_notification_icon("Close to notification area icon",
    advbool_close_to_notification_icon_id, advconfig_branch_notification_area_id, 0, false);

cfg_bool cfg_playlist_tabs_middle_click(
    {0x3074ea96, 0x22e7, 0x464a, {0x9d, 0xac, 0xec, 0x9, 0xc0, 0xb4, 0x5e, 0x5a}}, true);

} // namespace cui::config

ConfigRebar g_cfg_rebar(GUID{0xd26d3aa5, 0x9157, 0xbf8e, {0xd5, 0x9f, 0x44, 0x86, 0x1c, 0x7a, 0x82, 0xc7}});
ConfigBandCache cfg_band_cache(GUID{0x76e74192, 0x6932, 0x2671, {0x90, 0x12, 0xcf, 0x18, 0xca, 0x02, 0x06, 0xe0}});

cfg_int cfg_global(GUID{0xf939e07d, 0x0944, 0x0f40, {0xbf, 0x1f, 0x6d, 0x31, 0xaa, 0x37, 0x10, 0x5f}}, 0),
    cfg_vis(GUID{0x2bb960d2, 0xb1a8, 0x5741, {0x55, 0xb6, 0x13, 0x3f, 0xb1, 0x80, 0x37, 0x88}},
        get_default_colour(colours::COLOUR_BACK)),
    cfg_vis_edge(GUID{0x57cd2544, 0xd765, 0xef88, {0x30, 0xce, 0xd9, 0x9b, 0x47, 0xe4, 0x09, 0x94}}, 0),
    cfg_vis2(GUID{0x421d3d3f, 0x5289, 0xb1e4, {0x9b, 0x91, 0xab, 0x51, 0xd3, 0xad, 0xbc, 0x4d}},
        get_default_colour(colours::COLOUR_TEXT)),
    cfg_lock(GUID{0x93843978, 0xae88, 0x5ba2, {0x3c, 0xa6, 0xbc, 0x00, 0xb0, 0x78, 0x74, 0xa5}}, 0),
    cfg_header(GUID{0x7b92fba5, 0x91a8, 0x479e, {0x3e, 0xb9, 0x0a, 0x26, 0x44, 0x8b, 0xef, 0x1c}}, 1),
    cfg_show_seltime(GUID{0x7e70339b, 0x877f, 0xc4a5, {0x02, 0xbc, 0xee, 0x6e, 0x9d, 0x9d, 0x01, 0xc9}}, 1),
    cfg_header_hottrack(GUID{0xc61d7603, 0xfb21, 0xf362, {0xb9, 0xcd, 0x95, 0x2c, 0x82, 0xf9, 0xe5, 0x8e}}, 1),
    cfg_drop_at_end(GUID{0xd72ab7ee, 0x271c, 0xa72f, {0x69, 0x47, 0xb7, 0x26, 0x2c, 0x38, 0xb1, 0x60}}, 0),
    cfg_global_sort(GUID{0xdf68f654, 0x4c01, 0x9d16, {0x0d, 0xb5, 0xc2, 0x77, 0x95, 0x8d, 0x8f, 0xfa}}, 0),
    cfg_mclick(GUID{0xfab4859d, 0x72ae, 0xd27e, {0xb1, 0x19, 0xd6, 0xfe, 0x88, 0x4b, 0x67, 0x93}}, 0),
    cfg_mclick2(GUID{0x41fbf3da, 0x4026, 0x2505, {0xbd, 0x7a, 0x53, 0x76, 0x73, 0x51, 0x0f, 0x3e}}, 1),
    cfg_plm_rename(GUID{0xc793fce9, 0xa0e8, 0xc235, {0xd4, 0x3b, 0xe4, 0xdd, 0x2c, 0xd0, 0x45, 0xb7}}, 1),
    cfg_balloon(GUID{0x55a67634, 0x1a85, 0xf736, {0x5f, 0xce, 0x00, 0xdf, 0xd4, 0xd9, 0x10, 0x02}}, 0),
    cfg_ellipsis(GUID{0xb6fe16e9, 0x0502, 0x2b66, {0x45, 0xd1, 0xda, 0xfb, 0xfc, 0x37, 0xe0, 0x33}}, 1),
    cfg_frame(GUID{0x992ece57, 0xc20d, 0x167c, {0x34, 0x40, 0x80, 0x5e, 0x08, 0x1f, 0x91, 0x14}}, 0),
    cfg_plistframe(GUID{0xdbfdc16f, 0x8cfa, 0xcc63, {0xa2, 0xec, 0x17, 0xde, 0xa8, 0xc6, 0xdc, 0xa1}}, 0),
    cfg_tooltip(GUID{0x69db592b, 0x8c95, 0x810d, {0xca, 0xb7, 0x9b, 0x61, 0xa1, 0xa4, 0xaa, 0x3a}}, 0),
    cfg_tooltips_clipped(GUID{0x8181afae, 0x404e, 0xa880, {0xe2, 0x46, 0x38, 0x69, 0xbd, 0xc9, 0xd3, 0xef}}, 0),
    cfg_np(GUID{0x2e590774, 0xc50e, 0xbcd0, {0x73, 0xa2, 0x75, 0x2f, 0x70, 0x9b, 0xb1, 0x2e}}, 1),
    cfg_show_systray(GUID{0x19cf6962, 0x3d1e, 0x10b7, {0xcd, 0x91, 0x48, 0x66, 0x8b, 0x72, 0xe8, 0x22}}, 0),
    cfg_minimise_to_tray(GUID{0x4c4bf8f0, 0x1f76, 0x65f4, {0x52, 0xe4, 0x78, 0x01, 0x45, 0x13, 0xf9, 0x79}}, 0),
    cfg_show_vol(GUID{0xa325cde8, 0xc0df, 0x96f4, {0x90, 0xe9, 0x55, 0xbd, 0xe7, 0xd0, 0x32, 0xb9}}, 1),
    cfg_custom_icon(GUID{0xb45bfb84, 0x3ecd, 0xe706, {0x6e, 0x13, 0xa3, 0x2a, 0xd0, 0x2f, 0xac, 0x5f}}, 0),
    cfg_drag_autoswitch(GUID{0x593b498d, 0x4cc7, 0x1ec8, {0xb9, 0x20, 0x3c, 0x95, 0xb2, 0xde, 0x70, 0x8c}}, 0),
    cfg_plist_width(GUID{0x05aba8c0, 0x3460, 0x3c58, {0x20, 0xa0, 0x00, 0x6a, 0x54, 0x23, 0x5c, 0x3a}}, 135),
    cfg_drag_pl(GUID{0x56a9c8d8, 0x51fe, 0xac6f, {0x29, 0xe6, 0x29, 0xb3, 0x58, 0x82, 0xa7, 0x26}}, 1),
    cfg_pl_autohide(GUID{0x70cb66a7, 0xbe89, 0x8589, {0x53, 0x6c, 0x2b, 0x81, 0xdb, 0xa6, 0x72, 0x79}}, 0),
    cfg_sel_dp(GUID{0x3586f434, 0x1896, 0xecaa, {0xee, 0x61, 0x65, 0x61, 0xc1, 0x09, 0xd4, 0xcb}}, 0),
    cfg_replace_drop_underscores(GUID{0x73612560, 0xa7f0, 0x3d30, {0xb3, 0x2b, 0x8d, 0xd7, 0xe6, 0x5f, 0xfa, 0x91}}, 0),
    cfg_tabs_multiline(GUID{0xbb86aba9, 0x8402, 0xb932, {0x7a, 0xfd, 0xf3, 0xc9, 0xd5, 0x40, 0xfe, 0x2e}}, 1),
    cfg_status(GUID{0x79829634, 0x9b73, 0xa8bb, {0x89, 0x39, 0xf1, 0x70, 0xf7, 0x38, 0xe8, 0x5e}}, 0),
    cfg_pgen_tf(GUID{0xdc10bfe5, 0xe91b, 0x513e, {0xb9, 0xcb, 0xc4, 0xef, 0xd9, 0xed, 0xac, 0x25}}, 0),
    cfg_cur_prefs_col(GUID{0x6b77648d, 0x35ec, 0xb125, {0x49, 0xea, 0xa2, 0xe6, 0xd8, 0xa8, 0xed, 0x0c}}, 0),
    // cfg_playlist_sidebar_left_sep(GUID{0x9e812607,0xb455,0xe066,0xfc,0xfb,0x0a,0x2b,0x9c,0xef,0x2f,0x3c},0),
    cfg_playlist_switcher_use_tagz(
        GUID{0x43d94259, 0x4fde, 0x8779, {0x8e, 0xde, 0x18, 0xca, 0xa7, 0x2f, 0xc5, 0x7b}}, 1),
    cfg_sidebar_use_custom_show_delay(
        GUID{0x59e44486, 0x2dcc, 0x1276, {0x83, 0x84, 0xcf, 0xcb, 0xc0, 0x4f, 0xb4, 0x1c}}, 0),
    cfg_sidebar_show_delay(GUID{0xad46e438, 0x269d, 0xe1c8, {0x4a, 0xe0, 0x08, 0x29, 0xb5, 0x5d, 0x2f, 0xc3}}, 0),
    cfg_sidebar_hide_delay(GUID{0xab13b5dc, 0x1baa, 0x937a, {0x85, 0x33, 0x2d, 0x58, 0x35, 0xc8, 0xe7, 0xa8}}, 0),
    cfg_toolbars(GUID{0xfd1f165e, 0xeb6e, 0xbb2d, {0xe0, 0xd7, 0xc5, 0x03, 0xee, 0xf1, 0x6d, 0xd7}}, 1),
    cfg_show_sort_arrows(GUID{0xa9f1111e, 0x68d6, 0xc707, {0xd4, 0xad, 0x09, 0x63, 0x72, 0x0b, 0xe9, 0xfa}}, 1),
    cfg_autoswitch_delay(GUID{0x11645dab, 0xf8a6, 0xdc4e, {0x1d, 0xc0, 0xce, 0x50, 0xb1, 0x27, 0xb5, 0xbb}}, 500),
    // cfg_scar_hidden(GUID{0x59a3a04e,0xfd16,0x2345,0xe3,0x30,0x8b,0x4d,0xb5,0x96,0x77,0x3f},0),
    cfg_alternative_sel(GUID{0xfd0cdf1f, 0x588a, 0x1a2a, {0xdc, 0x70, 0x31, 0x06, 0x79, 0x41, 0x52, 0xe2}}, 0),
    cfg_playlist_middle_action(GUID{0xbda32fa2, 0xfb5a, 0xb715, {0x3f, 0x00, 0xcf, 0xaf, 0x9b, 0x57, 0xcd, 0x2c}}, 0),
    cfg_nohscroll(GUID{0x75ede7f7, 0x8c57, 0x03d9, {0x51, 0xa2, 0xe4, 0xe3, 0xdd, 0x7c, 0x8c, 0x74}}, 1);

cfg_bool cfg_go_to_tray(GUID{0x4655434b, 0x4655, 0x434b, {0x46, 0x55, 0x43, 0x4b, 0x46, 0x55, 0x43, 0x4b}}, false);

cfg_string cfg_tray_icon_path(GUID{0x4845fc42, 0x5c4c, 0x4e80, {0xa3, 0xae, 0x9b, 0xdc, 0x33, 0x2f, 0x8d, 0x32}}, "");
cfg_string cfg_export(GUID{0x834b613e, 0x2157, 0x5300, {0x78, 0x33, 0x24, 0x0b, 0x7c, 0xda, 0x42, 0x7f}}, "");
cfg_string cfg_import(GUID{0x79587d33, 0x97e4, 0x72cb, {0x92, 0xce, 0x30, 0x7a, 0x2f, 0x0a, 0x34, 0x83}}, "");
cfg_string cfg_custom_buttons_path(
    GUID{0x3d077fbb, 0x47f2, 0x7c15, {0x7a, 0x3d, 0xa1, 0x09, 0x20, 0xa8, 0xd5, 0x85}}, "");
cfg_string cfg_globalstring(GUID{0x355320ea, 0xf39e, 0x0d97, {0xa5, 0x94, 0xe0, 0x40, 0x57, 0x66, 0x51, 0x25}}, "");
ConfigMenuItem cfg_statusdbl(GUID{0x21440b3f, 0x4c1d, 0xb049, {0x46, 0xe1, 0x37, 0xa2, 0x7e, 0xc1, 0xe6, 0x93}},
    cui::main_menu::commands::activate_now_playing_id);
cfg_string cfg_pgenstring(GUID{0x07bee8c2, 0xc6f1, 0x9db3, {0x52, 0x55, 0x43, 0x28, 0x1f, 0xb3, 0xf1, 0xe6}},
    "%album%\\$directory(%_path%,2)");

const char* g_default_colour
    = "$if(%_themed%,,$if($and(%isplaying%,$not(%_is_group%)),\r\n"
      "\r\n"
      "$puts(back,$offset_colour(%_back%,$offset_colour($calculate_blend_target(%_back%),ff0000,20),25))\r\n"
      "$puts(back-selected,$offset_colour(%_selected_back%,$offset_colour($calculate_blend_target(%_selected_back%),"
      "ff0000,20),25))\r\n"
      "$puts(back-selected-no-focus,$offset_colour(%_selected_back_no_focus%,$offset_colour($calculate_blend_target(%_"
      "selected_back_no_focus%),ff0000,20),25))\r\n"
      ",\r\n"
      "\r\n"
      "$ifequal($mod($if2(%_display_index%,%list_index%),2),0,\r\n"
      "$puts(back,$offset_colour(%_back%,$calculate_blend_target(%_back%),12))\r\n"
      "$puts(back-selected,%_selected_back%)\r\n"
      "$puts(back-selected-no-focus,%_selected_back_no_focus%)\r\n"
      ",\r\n"
      "$puts(back-selected,$offset_colour(%_selected_back%,$calculate_blend_target(%_selected_back%),7))\r\n"
      "$puts(back-selected-no-focus,$offset_colour(%_selected_back_no_focus%,$calculate_blend_target(%_selected_back_"
      "no_focus%),7))\r\n"
      "$puts(back,%_back%)\r\n"
      ")\r\n"
      "\r\n"
      ")\r\n"
      "$set_style(back,$get(back),$get(back-selected),$get(back-selected-no-focus)))";

cfg_string cfg_colour(
    GUID{0xa41b3a98, 0x3834, 0x3b7c, {0x58, 0xae, 0x1d, 0x46, 0xb0, 0xf9, 0x4b, 0x0d}}, g_default_colour);

ConfigMenuItem cfg_playlist_double(GUID{0xffc47d9d, 0xb43d, 0x8fad, {0x8f, 0xb3, 0x42, 0x84, 0xbf, 0x9a, 0x22, 0x2a}});
cfg_string cfg_playlist_switcher_tagz(
    GUID{0x13f4b9ae, 0x5db5, 0xb083, {0x15, 0x36, 0x08, 0x4d, 0x55, 0xe3, 0xb5, 0x64}},
    u8"%title%\r\n"
    u8"\r\n"
    u8"$tab()\r\n"
    u8"\r\n"
    u8"$if(%is_playing%,🔉)");

// {F006EC50-7F52-4037-9D48-7447BBF742AA}
static const GUID guid_columns = {0xf006ec50, 0x7f52, 0x4037, {0x9d, 0x48, 0x74, 0x47, 0xbb, 0xf7, 0x42, 0xaa}};

ConfigColumns g_columns(guid_columns, ColumnStreamVersion::streamVersion0);

ConfigWindowPlacement cfg_window_placement_columns(
    GUID{0x8bdb3caa, 0x6544, 0x07a6, {0x89, 0x67, 0xf8, 0x13, 0x3a, 0x80, 0x75, 0xbb}});

static cfg_bool cfg_colours_fonts_imported(
    {0x27dfb9b0, 0x2621, 0x4935, {0xb6, 0x70, 0x2, 0x57, 0x69, 0x45, 0xc0, 0x12}}, true);

ConfigWindowPlacement::ConfigWindowPlacement(const GUID& p_guid)
    : cfg_struct_t<WINDOWPLACEMENT>(p_guid, get_def_window_pos())
{
}

void ConfigWindowPlacement::get_data_raw(stream_writer* out, abort_callback& p_abort)
{
    if (cui::main_window.get_wnd() && remember_window_pos()) {
        WINDOWPLACEMENT wp;
        memset(&wp, 0, sizeof(wp));
        wp.length = sizeof(wp);
        if (GetWindowPlacement(cui::main_window.get_wnd(), &wp))
            *this = wp;
    }
    const WINDOWPLACEMENT& wp = get_value();

    out->write(&wp, sizeof(wp), p_abort);
}
