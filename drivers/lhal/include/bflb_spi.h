#ifndef _BFLB_SPI_H
#define _BFLB_SPI_H

#include "bflb_core.h"

#if defined(BL602) || defined(BL702)
#define SPI_FIFO_WORD_NUM_MAX           4
#define SPI_FIFO_WIDTH_VARIABLE_SUPPORT 0
#elif defined(BL606P) || defined(BL808)
#define SPI_FIFO_BYTE_NUM_MAX           32
#define SPI_FIFO_WIDTH_VARIABLE_SUPPORT 1
#elif defined(BL616) || defined(BL628)
#define SPI_FIFO_BYTE_NUM_MAX           16
#define SPI_FIFO_WIDTH_VARIABLE_SUPPORT 1
#elif defined(BL702L)
#define SPI_FIFO_BYTE_NUM_MAX           16
#define SPI_FIFO_WIDTH_VARIABLE_SUPPORT 1
#else
#error "unknown device"
#endif

/** @defgroup SPI_ROLE spi role definition
  * @{
  */
#define SPI_ROLE_MASTER 0
#define SPI_ROLE_SLAVE  1
/**
  * @}
  */

/** @defgroup SPI_MODE spi mode definition
  * @{
  */
#define SPI_MODE0 0 /* CPOL=0 CHPHA=0 */
#define SPI_MODE1 1 /* CPOL=0 CHPHA=1 */
#define SPI_MODE2 2 /* CPOL=1 CHPHA=0 */
#define SPI_MODE3 3 /* CPOL=1 CHPHA=1 */
/**
  * @}
  */

/** @defgroup SPI_DATA_WIDTH spi data width definition
  * @{
  */
#define SPI_DATA_WIDTH_8BIT  1
#define SPI_DATA_WIDTH_16BIT 2
#define SPI_DATA_WIDTH_24BIT 3
#define SPI_DATA_WIDTH_32BIT 4
/**
  * @}
  */

/** @defgroup SPI_BIT_ORDER spi bit order definition
  * @{
  */
#define SPI_BIT_LSB 1
#define SPI_BIT_MSB 0
/**
  * @}
  */

/** @defgroup SPI_BYTE_ORDER spi byte order definition
  * @{
  */
#define SPI_BYTE_LSB 0
#if !defined(BL602) && !defined(BL702)
#define SPI_BYTE_MSB 1
#endif
/**
  * @}
  */

/** @defgroup SPI_CMD spi feature control cmd definition
  * @{
  */
#define SPI_CMD_SET_DATA_WIDTH  (0x01)
#define SPI_CMD_GET_DATA_WIDTH  (0x02)
#define SPI_CMD_CLEAR_TX_FIFO   (0x03)
#define SPI_CMD_CLEAR_RX_FIFO   (0x04)
#define SPI_CMD_SET_CS_INTERVAL (0x05)
/**
  * @}
  */

/**
 * @brief SPI configuration structure
 *
 * @param freq                SPI frequence, should be less than spi_clk/2
 * @param role                SPI role, use @ref SPI_ROLE
 * @param mode                SPI mode, use @ref SPI_MODE
 * @param data_width          SPI data width, use @ref SPI_DATA_WIDTH
 * @param bit_order           SPI bit order, use @ref SPI_BIT_ORDER
 * @param byte_order          SPI byte order, use @ref SPI_BYTE_ORDER
 * @param tx_fifo_threshold   SPI tx fifo threshold, should be less than 4
 * @param rx_fifo_threshold   SPI rx fifo threshold, should be less than 4
 */
struct bflb_spi_config_s {
    uint32_t freq;
    uint8_t role;
    uint8_t mode;
    uint8_t data_width;
    uint8_t bit_order;
    uint8_t byte_order;
    uint8_t tx_fifo_threshold;
    uint8_t rx_fifo_threshold;
};

#ifdef __cplusplus
extern "C" {
#endif

void bflb_spi_init(struct bflb_device_s *dev, const struct bflb_spi_config_s *config);
void bflb_spi_deinit(struct bflb_device_s *dev);
void bflb_spi_link_txdma(struct bflb_device_s *dev, bool enable);
void bflb_spi_link_rxdma(struct bflb_device_s *dev, bool enable);
uint32_t bflb_spi_poll_send(struct bflb_device_s *dev, uint32_t data);
int bflb_spi_poll_exchange(struct bflb_device_s *dev, const void *txbuffer, void *rxbuffer, size_t nbytes);
bool bflb_spi_isbusy(struct bflb_device_s *dev);
void bflb_spi_txint_mask(struct bflb_device_s *dev, bool mask);
void bflb_spi_rxint_mask(struct bflb_device_s *dev, bool mask);
void bflb_spi_errint_mask(struct bflb_device_s *dev, bool mask);
uint32_t bflb_spi_get_intstatus(struct bflb_device_s *dev);
void bflb_spi_int_clear(struct bflb_device_s *dev, uint32_t int_clear);

int bflb_spi_feature_control(struct bflb_device_s *dev, int cmd, size_t arg);

#ifdef __cplusplus
}
#endif

#endif
