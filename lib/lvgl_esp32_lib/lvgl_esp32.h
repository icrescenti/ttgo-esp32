#ifndef LVGL_ESP32_H
#define LVGL_ESP32_H
#include "lvgl.h"
#include "lvgl_helpers.h"

#include "img_maps.h"

#define VERD_CLAITEC lv_color_make(0x88,0xb9, 0x40)
#define GRIS_CLAITEC lv_color_make(0x72,0x72,0x71)

enum{
    MAIN_SCREEN,
    SCREEN_2,
    LOGIN_SCREEN,
};


/**
 * ENUMS per les interrupcions de boto
 * estaran dins de la data del boto i es llegiran a les interrupcions
 */
enum{
    LOGOUT_BUTTON_INT,
    SETTINGS_BUTTON_INT,
    MUTE_BUTTON_INT,
    NUMPAD0_INT,
    NUMPAD1_INT,
    NUMPAD2_INT,
    NUMPAD3_INT,
    NUMPAD4_INT,
    NUMPAD5_INT,
    NUMPAD6_INT,
    NUMPAD7_INT,
    NUMPAD8_INT,
    NUMPAD9_INT,
    NUMPAD_CHECK_INT,
    NUMPAD_DELETE_INT,
};
void main_screen_ini(void);

void login_screen_ini();

void test_screen_ini();

void lvgl_setup();

void label_display_tag(uint8_t* p);

void configure_background();

void lvgl_change_user_name(char* text);

void change_screen(int screen_num);

void create_pop_up_loading(const char* message);

void destroy_pop_up_loading();

void login(lv_timer_t * timer);

void init_login(lv_timer_t * timer);

void show_error(lv_timer_t * timer);

void change_screen_safe(lv_timer_t * timer);



#endif