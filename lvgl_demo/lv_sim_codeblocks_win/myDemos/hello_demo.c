#include "lvgl.h"
#include "demos.h"

static lv_obj_t* scr;
static lv_obj_t* label;

void hello_demo(){
    scr = lv_obj_create(NULL);
    label = lv_label_create(scr);
    lv_label_set_text(label, "hello,boy!");
    lv_obj_center(label);

    lv_scr_load(scr);
}
