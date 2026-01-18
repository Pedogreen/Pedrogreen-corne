#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>
#include <zmk/events/layer_state_changed.h>
#include <zmk/hid.h>

static uint8_t layer_byte;

static void update_layer_byte(const struct zmk_layer_state_changed *ev) {
    layer_byte = 0;
    if (BIT(0) & ev->state) layer_byte |= 0x01; /* BASE */
    if (BIT(1) & ev->state) layer_byte |= 0x02; /* LOWER */
    if (BIT(2) & ev->state) layer_byte |= 0x04; /* RAISE */
    if (BIT(3) & ev->state) layer_byte |= 0x08; /* FUN */

    zmk_hid_report_send(USAGE_PAGE(0xFF00), USAGE_ID(0x01), &layer_byte, sizeof(layer_byte));
    printk("LAYER:%02X\n", layer_byte);
}

ZMK_LISTENER(layer_hid_listener, update_layer_byte);
ZMK_SUBSCRIPTION(layer_hid_listener, zmk_layer_state_changed);
