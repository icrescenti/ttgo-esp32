#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "lvgl.h"
#include "lvgl_helpers.h"

#define LV_TICK_PERIOD_MS   1

const int MAX = 5;
QueueHandle_t cua;
lv_disp_t * disp;

static void lv_ticks_timer(void *arg) {
    (void) arg;

    lv_tick_inc(LV_TICK_PERIOD_MS);
}

void lvgl_setup(){
    lv_init();
    lvgl_driver_init();


    /*A static or global variable to store the buffers*/
    static lv_disp_draw_buf_t disp_buf;

    /*Static or global buffer(s). The second buffer is optional*/
    static lv_color_t buf_1[240 * 10];
    static lv_color_t buf_2[240 * 10];

    /*Initialize `disp_buf` with the buffer(s). With only one buffer use NULL instead buf_2 */
    lv_disp_draw_buf_init(&disp_buf, buf_1, buf_2, 240*10);



    static lv_disp_drv_t disp_drv;          /*A variable to hold the drivers. Must be static or global.*/
    lv_disp_drv_init(&disp_drv);            /*Basic initialization*/
    disp_drv.draw_buf = &disp_buf;          /*Set an initialized buffer*/
    disp_drv.flush_cb = disp_driver_flush;        /*Set a flush callback to draw to the display*/
    disp_drv.hor_res = 240;                 /*Set the horizontal resolution in pixels*/
    disp_drv.ver_res = 135;                 /*Set the vertical resolution in pixels*/
    disp_drv.full_refresh = 1;
    disp = lv_disp_drv_register(&disp_drv); /*Register the driver and save the created display objects*/


    const esp_timer_create_args_t periodic_timer_args = {
        .callback = &lv_ticks_timer,
        .name = "ticks_to_lvgl"
    };
    esp_timer_handle_t periodic_timer;
    ESP_ERROR_CHECK(esp_timer_create(&periodic_timer_args, &periodic_timer));
    ESP_ERROR_CHECK(esp_timer_start_periodic(periodic_timer, LV_TICK_PERIOD_MS * 1000));


    //lv_theme_t * th = lv_theme_default_init(lv_disp_get_default(), VERD_CLAITEC, GRIS_CLAITEC,true,&lv_font_montserrat_16);
    //lv_disp_set_theme(lv_disp_get_default(),th);
    //lv_timer_create(lvgl_task,-1,)
}

void lv_example_spinner_1(void)
{
    lvgl_setup();
    lv_obj_t * spinner = lv_spinner_create(lv_scr_act(), 1000, 60);
    lv_obj_set_size(spinner, 100, 100);
    lv_obj_center(spinner);
    
    while (1) {
        vTaskDelay(pdMS_TO_TICKS(10));
        lv_timer_handler();
    }
}

void lv_example_image(int xavi)
{
    lvgl_setup();
    
    if (xavi == 1)
    {
        LV_IMG_DECLARE(img_xavi);
        lv_obj_t * img1 = lv_img_create(lv_scr_act());
        lv_img_set_src(img1, &img_xavi);
        lv_obj_align(img1, LV_ALIGN_CENTER, 0, 0);
    }
    else
    {
        LV_IMG_DECLARE(img_penguin);
        lv_obj_t * img1 = lv_img_create(lv_scr_act());
        lv_img_set_src(img1, &img_penguin);
        lv_obj_align(img1, LV_ALIGN_CENTER, 0, -10);
    }
    
    while (1) {
        vTaskDelay(pdMS_TO_TICKS(10));
        lv_timer_handler();
    }
}

void app_main() {
    //xTaskCreate(thread_0, "test0", 2048, NULL, 1, NULL);
    //xTaskCreate(lv_example_spinner_1, "spinner", 4096, NULL, 1, NULL);
    //xTaskCreate(thread_1, "test1", 2048, NULL, 0, NULL);

    xTaskCreate(lv_example_image, "image", 8024, 0, 1, NULL);
}