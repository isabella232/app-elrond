#include "menu.h"
#include "os.h"
#include "utils.h"

// read_uint32_be reads 4 bytes from the buffer and returns an uint32_t with big endian encoding
uint32_t read_uint32_be(uint8_t *buffer) {
  return (buffer[0] << 24) | (buffer[1] << 16) | (buffer[2] << 8) | (buffer[3]);
}

void send_response(uint8_t tx, bool approve) {
    uint16_t response = MSG_OK;

    if (!approve)
        response = ERR_USER_DENIED;
    G_io_apdu_buffer[tx++] = response >> 8;
    G_io_apdu_buffer[tx++] = response & 0xff;
    // Send back the response, do not restart the event loop
    io_exchange(CHANNEL_APDU | IO_RETURN_AFTER_TX, tx);
    // Display back the original UX
    ui_idle();
}

// TODO: refactor this function
void uint32_t_to_char_array(uint32_t const input, char *output) {
  uint32_t const base = 10;
  uint32_t index;
  uint8_t pos = 0;
  for (index = 1; (((index * base) <= input) &&
            (((index * base) / base) == index));
            index *= base);
  for (; index; index /= base) {
            output[pos++] = '0' + ((input / index) % base);
        }
    output[pos] = '\0';
}
