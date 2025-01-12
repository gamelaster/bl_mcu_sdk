#include "bflb_gpio.h"
#include "bflb_mtimer.h"

struct bflb_device_s *gpio;

extern void board_init(void);

void gpio_isr(int irq, void *arg)
{
    static int i = 0;
    bool intstatus = bflb_gpio_get_intstatus(gpio, GPIO_PIN_12);
    if (intstatus) {
        bflb_gpio_int_clear(gpio, GPIO_PIN_12);
        printf("%d\r\n", i++);
    }
}

int main(void)
{
    board_init();

    gpio = bflb_device_get_by_name("gpio");
    printf("gpio interrupt\r\n");

    bflb_gpio_int_init(gpio, GPIO_PIN_12, GPIO_INT_TRIG_MODE_SYNC_FALLING_EDGE);
    bflb_gpio_int_mask(gpio, GPIO_PIN_12, false);

    bflb_irq_attach(gpio->irq_num, gpio_isr, gpio);
    bflb_irq_enable(gpio->irq_num);

    while (1) {
        printf("helloworld\r\n");
        bflb_mtimer_delay_ms(2000);
    }
}
