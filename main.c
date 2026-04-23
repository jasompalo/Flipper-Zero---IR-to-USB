#include <furi.h>
#include <furi_hal.h>
#include <furi_hal_usb_hid.h>
#include <gui/gui.h>
#include <infrared_worker.h>
#include <input/input.h>

//original idea by @jasompalo
//refactor by @pilot2254

//flipperzero screen res: 128x64px
//FontPrimary: ~12px tall where y is the baseline
//FontSecondary: ~8px tall

typedef struct {
    FuriMessageQueue* event_queue;
    bool running;
    bool signal_received;
    uint32_t last_press_ms;
} AppState;

static void draw_callback(Canvas* canvas, void* ctx) {
    AppState* state = (AppState*)ctx;

    canvas_clear(canvas);

    canvas_set_font(canvas, FontPrimary);
    canvas_draw_str(canvas, 2, 12, "IR to SPACEBAR");

    canvas_set_font(canvas, FontSecondary);
    canvas_draw_str(canvas, 2, 26, "point remote, press any button");
    canvas_draw_str(canvas, 2, 36, "to send SPACEBAR to PC");

    canvas_draw_str(canvas, 2, 52, state->signal_received ? "Signal received!" : "Waiting for IR...");
    canvas_draw_str(canvas, 2, 62, "Hold BACK to exit");
}

static void input_callback(InputEvent* event, void* ctx) {
    AppState* state = (AppState*)ctx;
    furi_message_queue_put(state->event_queue, event, 0);
}

static void ir_received_callback(void* ctx, InfraredWorkerSignal* signal) {
    AppState* state = (AppState*)ctx;

    if(!infrared_worker_signal_is_decoded(signal)) return;

    //flash led
    uint32_t now = furi_get_tick();
    if(now - state->last_press_ms < furi_ms_to_ticks(350)) return;
    state->last_press_ms = now;

    furi_hal_light_set(LightGreen, 255);
    furi_delay_ms(50);
    furi_hal_light_set(LightGreen, 0);

    //send spacebar
    furi_hal_hid_kb_press(HID_KEYBOARD_SPACEBAR);
    furi_delay_ms(80);
    furi_hal_hid_kb_release_all();

    state->signal_received = true;
}

int32_t ir_to_hid_app(void* p) {
    UNUSED(p);

    AppState* state = malloc(sizeof(AppState));
    state->event_queue = furi_message_queue_alloc(8, sizeof(InputEvent));
    state->running = true;
    state->signal_received = false;

    //switch usb to hid mode
    furi_hal_usb_set_config(&usb_hid, NULL);
    furi_delay_ms(200);

    //gui
    ViewPort* view_port = view_port_alloc();
    view_port_draw_callback_set(view_port, draw_callback, state);
    view_port_input_callback_set(view_port, input_callback, state);

    Gui* gui = furi_record_open(RECORD_GUI);
    gui_add_view_port(gui, view_port, GuiLayerFullscreen);

    //ir
    InfraredWorker* worker = infrared_worker_alloc();
    infrared_worker_rx_set_received_signal_callback(worker, ir_received_callback, state);
    infrared_worker_rx_start(worker);

    //main loop
    InputEvent event;
    while(state->running) {
        if(furi_message_queue_get(state->event_queue, &event, 100) == FuriStatusOk) {
            if(event.type == InputTypeLong && event.key == InputKeyBack) {
                state->running = false;
            }
        }

        view_port_update(view_port);
    }

    //cleanup
    infrared_worker_rx_stop(worker);
    infrared_worker_free(worker);

    gui_remove_view_port(gui, view_port);
    view_port_free(view_port);
    furi_record_close(RECORD_GUI);

    furi_message_queue_free(state->event_queue);
    free(state);

    //restore usb
    furi_hal_usb_set_config(&usb_cdc_single, NULL);

    return 0;
}