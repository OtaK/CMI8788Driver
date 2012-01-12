#ifndef CMI8788Driver_CMI8788Registers_h
#define CMI8788Driver_CMI8788Registers_h

/*
 * Xonar D1/DX
 * -----------
 *
 * CMI8788:
 *
 *   I²C <-> CS4398 (addr 1001111) (front)
 *       <-> CS4362A (addr 0011000) (surround, center/LFE, back)
 *
 *   GPI 0 <- external power present (DX only)
 *
 *   GPIO 0 -> enable output to speakers
 *   GPIO 1 -> route output to front panel
 *   GPIO 2 -> M0 of CS5361
 *   GPIO 3 -> M1 of CS5361
 *   GPIO 6 -> ?
 *   GPIO 7 -> ?
 *   GPIO 8 -> route input jack to line-in (0) or mic-in (1)
 *
 * CM9780:
 *
 *   LINE_OUT -> input of ADC
 *
 *   AUX_IN  <- aux
 *   MIC_IN  <- mic
 *   FMIC_IN <- front mic
 *
 *   GPO 0 -> route line-in (0) or AC97 output (1) to CS5361 input
 */

/* register 1 */
#define CS4398_REV_MASK		0x07
#define CS4398_PART_MASK	0xf8
#define CS4398_PART_CS4398	0x70
/* register 2 */
#define CS4398_FM_MASK		0x03
#define CS4398_FM_SINGLE	0x00
#define CS4398_FM_DOUBLE	0x01
#define CS4398_FM_QUAD		0x02
#define CS4398_FM_DSD		0x03
#define CS4398_DEM_MASK		0x0c
#define CS4398_DEM_NONE		0x00
#define CS4398_DEM_44100	0x04
#define CS4398_DEM_48000	0x08
#define CS4398_DEM_32000	0x0c
#define CS4398_DIF_MASK		0x70
#define CS4398_DIF_LJUST	0x00
#define CS4398_DIF_I2S		0x10
#define CS4398_DIF_RJUST_16	0x20
#define CS4398_DIF_RJUST_24	0x30
#define CS4398_DIF_RJUST_20	0x40
#define CS4398_DIF_RJUST_18	0x50
#define CS4398_DSD_SRC		0x80
/* register 3 */
#define CS4398_ATAPI_MASK	0x1f
#define CS4398_ATAPI_B_MUTE	0x00
#define CS4398_ATAPI_B_R	0x01
#define CS4398_ATAPI_B_L	0x02
#define CS4398_ATAPI_B_LR	0x03
#define CS4398_ATAPI_A_MUTE	0x00
#define CS4398_ATAPI_A_R	0x04
#define CS4398_ATAPI_A_L	0x08
#define CS4398_ATAPI_A_LR	0x0c
#define CS4398_ATAPI_MIX_LR_VOL	0x10
#define CS4398_INVERT_B		0x20
#define CS4398_INVERT_A		0x40
#define CS4398_VOL_B_EQ_A	0x80
/* register 4 */
#define CS4398_MUTEP_MASK	0x03
#define CS4398_MUTEP_AUTO	0x00
#define CS4398_MUTEP_LOW	0x02
#define CS4398_MUTEP_HIGH	0x03
#define CS4398_MUTE_B		0x08
#define CS4398_MUTE_A		0x10
#define CS4398_MUTEC_A_EQ_B	0x20
#define CS4398_DAMUTE		0x40
#define CS4398_PAMUTE		0x80
/* register 5 */
#define CS4398_VOL_A_MASK	0xff
/* register 6 */
#define CS4398_VOL_B_MASK	0xff
/* register 7 */
#define CS4398_DIR_DSD		0x01
#define CS4398_FILT_SEL		0x04
#define CS4398_RMP_DN		0x10
#define CS4398_RMP_UP		0x20
#define CS4398_ZERO_CROSS	0x40
#define CS4398_SOFT_RAMP	0x80
/* register 8 */
#define CS4398_MCLKDIV3		0x08
#define CS4398_MCLKDIV2		0x10
#define CS4398_FREEZE		0x20
#define CS4398_CPEN		0x40
#define CS4398_PDN		0x80
/* register 9 */
#define CS4398_DSD_PM_EN	0x01
#define CS4398_DSD_PM_MODE	0x02
#define CS4398_INVALID_DSD	0x04
#define CS4398_STATIC_DSD	0x08


/*
 * Xonar D2/D2X
 * ------------
 *
 * CMI8788:
 *
 *   SPI 0 -> 1st PCM1796 (front)
 *   SPI 1 -> 2nd PCM1796 (surround)
 *   SPI 2 -> 3rd PCM1796 (center/LFE)
 *   SPI 4 -> 4th PCM1796 (back)
 *
 *   GPIO 2 -> M0 of CS5381
 *   GPIO 3 -> M1 of CS5381
 *   GPIO 5 <- external power present (D2X only)
 *   GPIO 7 -> ALT
 *   GPIO 8 -> enable output to speakers
 *
 * CM9780:
 *
 *   LINE_OUT -> input of ADC
 *
 *   AUX_IN   <- aux
 *   VIDEO_IN <- CD
 *   FMIC_IN  <- mic
 *
 *   GPO 0 -> route line-in (0) or AC97 output (1) to CS5381 input
 */

/*
 * Xonar HDAV1.3 (Deluxe)
 * ----------------------
 *
 * CMI8788:
 *
 *   I²C <-> PCM1796 (addr 1001100) (front)
 *
 *   GPI 0 <- external power present
 *
 *   GPIO 0 -> enable HDMI (0) or speaker (1) output
 *   GPIO 2 -> M0 of CS5381
 *   GPIO 3 -> M1 of CS5381
 *   GPIO 4 <- daughterboard detection
 *   GPIO 5 <- daughterboard detection
 *   GPIO 6 -> ?
 *   GPIO 7 -> ?
 *   GPIO 8 -> route input jack to line-in (0) or mic-in (1)
 *
 *   UART <-> HDMI controller
 *
 * CM9780:
 *
 *   LINE_OUT -> input of ADC
 *
 *   AUX_IN <- aux
 *   CD_IN  <- CD
 *   MIC_IN <- mic
 *
 *   GPO 0 -> route line-in (0) or AC97 output (1) to CS5381 input
 *
 * no daughterboard
 * ----------------
 *
 *   GPIO 4 <- 1
 *
 * H6 daughterboard
 * ----------------
 *
 *   GPIO 4 <- 0
 *   GPIO 5 <- 0
 *
 *   I²C <-> PCM1796 (addr 1001101) (surround)
 *       <-> PCM1796 (addr 1001110) (center/LFE)
 *       <-> PCM1796 (addr 1001111) (back)
 *
 * unknown daughterboard
 * ---------------------
 *
 *   GPIO 4 <- 0
 *   GPIO 5 <- 1
 *
 *   I²C <-> CS4362A (addr 0011000) (surround, center/LFE, back)
 */

/*
 * Xonar Essence ST (Deluxe)/STX
 * -----------------------------
 *
 * CMI8788:
 *
 *   I²C <-> PCM1792A (addr 1001100)
 *       <-> CS2000 (addr 1001110) (ST only)
 *
 *   ADC1 MCLK -> REF_CLK of CS2000 (ST only)
 *
 *   GPI 0 <- external power present (STX only)
 *
 *   GPIO 0 -> enable output to speakers
 *   GPIO 1 -> route HP to front panel (0) or rear jack (1)
 *   GPIO 2 -> M0 of CS5381
 *   GPIO 3 -> M1 of CS5381
 *   GPIO 4 <- daughterboard detection
 *   GPIO 5 <- daughterboard detection
 *   GPIO 6 -> ?
 *   GPIO 7 -> route output to speaker jacks (0) or HP (1)
 *   GPIO 8 -> route input jack to line-in (0) or mic-in (1)
 *
 * PCM1792A:
 *
 *   SCK <- CLK_OUT of CS2000 (ST only)
 *
 * CM9780:
 *
 *   LINE_OUT -> input of ADC
 *
 *   AUX_IN <- aux
 *   MIC_IN <- mic
 *
 *   GPO 0 -> route line-in (0) or AC97 output (1) to CS5381 input
 *
 * H6 daughterboard
 * ----------------
 *
 * GPIO 4 <- 0
 * GPIO 5 <- 0
 */

/*
 * Xonar Xense
 * -----------
 *
 * CMI8788:
 *
 *   I²C <-> PCM1796 (addr 1001100) (front)
 *       <-> CS4362A (addr 0011000) (surround, center/LFE, back)
 *       <-> CS2000 (addr 1001110)
 *
 *   ADC1 MCLK -> REF_CLK of CS2000
 *
 *   GPI 0 <- external power present
 *
 *   GPIO 0 -> enable output
 *   GPIO 1 -> route HP to front panel (0) or rear jack (1)
 *   GPIO 2 -> M0 of CS5381
 *   GPIO 3 -> M1 of CS5381
 *   GPIO 4 -> enable output
 *   GPIO 5 -> enable output
 *   GPIO 6 -> ?
 *   GPIO 7 -> route output to HP (0) or speaker (1)
 *   GPIO 8 -> route input jack to mic-in (0) or line-in (1)
 *
 * CM9780:
 *
 *   LINE_OUT -> input of ADC
 *
 *   AUX_IN   <- aux
 *   VIDEO_IN <- ?
 *   FMIC_IN  <- mic
 *
 *   GPO 0 -> route line-in (0) or AC97 output (1) to CS5381 input
 *   GPO 1 -> route mic-in from input jack (0) or front panel header (1)
 */


typedef struct CMI8788Registers {
    const static UInt16
    // GPI
    GPI_DATA = 0xA4,
    GPI_INTERRUPT_MASK = 0xA5,
    // GPIO
    GPIO_DATA = 0xA6,
    GPIO_CONTROL = 0xA8,
    GPIO_INTERRUPT_MASK = 0xAA,
    NIL = 0x00;
} CMI8788Registers;

#endif
