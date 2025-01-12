#include "bflb_gpio.h"

struct bflb_device_s *gpio;

extern void board_init(void);

int main(void)
{
    board_init();

    gpio = bflb_device_get_by_name("gpio");
    printf("gpio output\r\n");
    bflb_gpio_init(gpio, GPIO_PIN_12, GPIO_OUTPUT | GPIO_PULLUP | GPIO_SMT_EN | GPIO_DRV_0);
    bflb_gpio_init(gpio, GPIO_PIN_24, GPIO_INPUT | GPIO_PULLUP | GPIO_SMT_EN | GPIO_DRV_0);

    while (1) {
        bflb_gpio_set(gpio, GPIO_PIN_12);
        printf("%x\r\n", bflb_gpio_read(gpio, GPIO_PIN_24));
        bflb_mtimer_delay_ms(2000);

        bflb_gpio_reset(gpio, GPIO_PIN_12);
        printf("%x\r\n", bflb_gpio_read(gpio, GPIO_PIN_24));
        bflb_mtimer_delay_ms(2000);
    }
}
