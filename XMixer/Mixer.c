
#define CONTROLS 8

#define GUI_ELEMENTS 4

#define TAB_ELEMENTS 0


#define PLUGIN_UI_URI "https://github.com/brummer10/XMixer_ui"


#include "lv2_plugin.h"

void set_costum_theme(Xputty *main) {
    main->color_scheme->normal = (Colors) {
         /* cairo    / r  / g  / b  / a  /  */
        .fg =       { 0.850, 0.850, 0.850, 1.000},
        .bg =       { 0.100, 0.100, 0.135, 1.000},
        .base =     { 0.000, 0.000, 0.000, 1.000},
        .text =     { 0.900, 0.900, 0.900, 1.000},
        .shadow =   { 0.000, 0.000, 0.000, 0.200},
        .frame =    { 0.000, 0.000, 0.000, 1.000},
        .light =    { 0.100, 0.100, 0.100, 1.000}
    };

    main->color_scheme->prelight = (Colors) {
         /* cairo    / r  / g  / b  / a  /  */
        .fg =       { 1.000, 0.000, 1.000, 1.000},
        .bg =       { 0.250, 0.250, 0.250, 1.000},
        .base =     { 0.300, 0.300, 0.300, 1.000},
        .text =     { 1.000, 1.000, 1.000, 1.000},
        .shadow =   { 0.100, 0.100, 0.100, 0.400},
        .frame =    { 0.300, 0.300, 0.300, 1.000},
        .light =    { 0.300, 0.300, 0.300, 1.000}
    };

    main->color_scheme->selected = (Colors) {
         /* cairo    / r  / g  / b  / a  /  */
        .fg =       { 0.900, 0.900, 0.900, 1.000},
        .bg =       { 0.200, 0.200, 0.200, 1.000},
        .base =     { 0.500, 0.180, 0.180, 1.000},
        .text =     { 1.000, 1.000, 1.000, 1.000},
        .shadow =   { 0.800, 0.180, 0.180, 0.200},
        .frame =    { 0.500, 0.180, 0.180, 1.000},
        .light =    { 0.500, 0.180, 0.180, 1.000}
    };

    main->color_scheme->active = (Colors) {
         /* cairo    / r  / g  / b  / a  /  */
        .fg =       { 0.000, 1.000, 1.000, 1.000},
        .bg =       { 0.000, 0.000, 0.000, 1.000},
        .base =     { 0.180, 0.380, 0.380, 1.000},
        .text =     { 0.750, 0.750, 0.750, 1.000},
        .shadow =   { 0.180, 0.380, 0.380, 0.500},
        .frame =    { 0.180, 0.380, 0.380, 1.000},
        .light =    { 0.180, 0.380, 0.380, 1.000}
    };

    main->color_scheme->insensitive = (Colors) {
         /* cairo    / r  / g  / b  / a  /  */
        .fg =       { 0.850, 0.850, 0.850, 0.500},
        .bg =       { 0.100, 0.100, 0.100, 0.500},
        .base =     { 0.000, 0.000, 0.000, 0.500},
        .text =     { 0.900, 0.900, 0.900, 0.500},
        .shadow =   { 0.000, 0.000, 0.000, 0.100},
        .frame =    { 0.000, 0.000, 0.000, 0.500},
        .light =    { 0.100, 0.100, 0.100, 0.500}
    };
}

#include "lv2_plugin.cc"


void plugin_value_changed(X11_UI *ui, Widget_t *w, PortIndex index) {
    // do special stuff when needed
}

void plugin_set_window_size(int *w,int *h,const char * plugin_uri) {
    (*w) = 517; //set initial width of main window
    (*h) = 296; //set initial height of main window
}

const char* plugin_set_name() {
    return "XMixer"; //set plugin name to display on UI
}

void plugin_create_controller_widgets(X11_UI *ui, const char * plugin_uri) {
    set_costum_theme(&ui->main);
    ui->elem[0] = add_lv2_frame (ui->elem[0], ui->win, 5, "Chan. 1", ui, 30,  30, 95, 246);
    ui->elem[1] = add_lv2_frame (ui->elem[1], ui->win, 5, "Chan. 2", ui, 150,  30, 95, 247);
    ui->elem[2] = add_lv2_frame (ui->elem[2], ui->win, 5, "Chan. 3", ui, 270,  30, 95, 243);
    ui->elem[3] = add_lv2_frame (ui->elem[3], ui->win, 5, "Chan. 4", ui, 390,  30, 95, 243);
    ui->widget[0] = add_lv2_vslider (ui->widget[0], ui->elem[0], 5, "Gain 1", ui, 20,  30, 40, 198);
    set_adjustment(ui->widget[0]->adj, -2.05, -2.05, -60.0, 6.0, 0.01, CL_LOGSCALE);

    ui->widget[1] = add_lv2_vslider (ui->widget[1], ui->elem[1], 6, "Gain 2", ui, 20,  30, 40, 198);
    set_adjustment(ui->widget[1]->adj, -2.05, -2.05, -60.0, 6.0, 0.01, CL_LOGSCALE);

    ui->widget[2] = add_lv2_vslider (ui->widget[2], ui->elem[2], 7, "Gain 3", ui, 20,  30, 40, 198);
    set_adjustment(ui->widget[2]->adj, -2.05, -2.05, -60.0, 6.0, 0.01, CL_LOGSCALE);

    ui->widget[3] = add_lv2_vslider (ui->widget[3], ui->elem[3], 8, "Gain 4", ui, 20,  30, 40, 198);
    set_adjustment(ui->widget[3]->adj, -2.05, -2.05, -60.0, 6.0, 0.01, CL_LOGSCALE);

    ui->widget[4] = add_lv2_vmeter (ui->widget[4], ui->elem[0], 9, "VMeter 1", ui, 60,  30, 15, 180);
    set_adjustment(ui->widget[4]->adj, -70.000, -70.000, -70.000, 6.000, 0.001, CL_METER);

    ui->widget[5] = add_lv2_vmeter (ui->widget[5], ui->elem[1], 10, "VMeter 2", ui, 60,  30, 15, 180);
    set_adjustment(ui->widget[5]->adj, -70.000, -70.000, -70.000, 6.000, 0.001, CL_METER);

    ui->widget[6] = add_lv2_vmeter (ui->widget[6], ui->elem[2], 11, "VMeter 3", ui, 60,  30, 15, 180);
    set_adjustment(ui->widget[6]->adj, -70.000, -70.000, -70.000, 6.000, 0.001, CL_METER);

    ui->widget[7] = add_lv2_vmeter (ui->widget[7], ui->elem[3], 12, "VMeter 4", ui, 60,  30, 15, 180);
    set_adjustment(ui->widget[7]->adj, -70.000, -70.000, -70.000, 6.000, 0.001, CL_METER);

}

void plugin_cleanup(X11_UI *ui) {
    // clean up used sources when needed
}

void plugin_port_event(LV2UI_Handle handle, uint32_t port_index,
                        uint32_t buffer_size, uint32_t format,
                        const void * buffer) {
    // port value change message from host
    // do special stuff when needed
}

