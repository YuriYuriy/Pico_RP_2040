//----------------------------------------------------------------------------------------------------
//(C) 2025 YuriYuri (Yuriy Golovin)
//----------------------------------------------------------------------------------------------------
#ifndef _COMMANDS_ST7789V
#define _COMMANDS_ST7789V

// System Function Command Table 1 
#define ST7789V_NOP        0x00  // No Operation
#define ST7789V_SWRESET    0x01  // Software Reset
#define ST7789V_RDDID      0x04  // Read Display ID 
#define ST7789V_RDDST      0x09  // Read Display Status
#define ST7789V_RDDPM      0x0A  // Read Display Power Mode 
#define ST7789V_RDDMADCTL  0x0B  // Read Display MADCTL 
#define ST7789V_RDDCOLMOD  0x0C  // Read Display Pixel Format 
#define ST7789V_RDDIM      0x0D  // Read Display Image Mode 
#define ST7789V_RDDSM      0x0E  // Read Display Signal Mode 
#define ST7789V_RDDSDR     0x0F  // Read Display Self-Diagnostic Result 
#define ST7789V_SLPIN      0x10  // Sleep in 
#define ST7789V_SLPOUT     0x11  // Sleep Out 
#define ST7789V_PTLON      0x12  // Partial Display Mode On 
#define ST7789V_NORON      0x13  // Normal Display Mode On
#define ST7789V_INVOFF     0x20  // Display Inversion Off
#define ST7789V_INVON      0x21  // Display Inversion On
#define ST7789V_GAMSET     0x26  // Gamma Set
#define ST7789V_DISPOFF    0x28  // Display Off 
#define ST7789V_DISPON     0x29  // Display On
#define ST7789V_CASET      0x2A  // Column Address Set 
#define ST7789V_RASET      0x2B  // Row Address Set 
#define ST7789V_RAMWR      0x2C  // Memory Write 
#define ST7789V_RAMRD      0x2E  // Memory Read 
#define ST7789V_PTLAR      0x30  // Partial Area 
#define ST7789V_VSCRDEF    0x33  // Vertical Scrolling Definition 
#define ST7789V_TEOFF      0x34  // Tearing Effect Line OFF
#define ST7789V_TEON       0x35  // Tearing Effect Line On 
#define ST7789V_MADCTL     0x36  // Memory Data Access Control 
#define ST7789V_VSCSAD     0x37  // Vertical Scroll Start Address of RAM 
#define ST7789V_IDMOFF     0x38  // Idle Mode Off 
#define ST7789V_IDMON      0x39  // Idle mode on 
#define ST7789V_COLMOD     0x3A  // Interface Pixel Format  
//----------------------------------------------------------------------------------------------------
#define ST7789V_WRMEMC     0x3C  // Write Memory Continue 
#define ST7789V_RDMEMC     0x3E  // Read Memory Continue 
#define ST7789V_STE        0x44  // Set Tear Scanline 
#define ST7789V_GSCAN      0x45  // Get Scanline 
#define ST7789V_WRDISBV    0x51  // Write Display Brigtness 
#define ST7789V_RDDISBV    0x52  // Read Display Brigtness Value 
#define ST7789V_WRCTRLD    0x53  // Write CTRL Display 
#define ST7789V_RDCTRLD    0x54  // Read CTRL Value Display 
#define ST7789V_WRCACE     0x55  // Write Content Adaptive Brigtness Control and Color Enancement 
#define ST7789V_RDCABC     0x56  // Read Content Adaptive Brigtness Control 
#define ST7789V_WRCABCMB   0x5E  // Write CABC Minimum Brigtness 
#define ST7789V_RDCABCMB   0x5F  // Read CABC Minimum Brigtness 
#define ST7789V_RDABCSDR   0x68  // Read Automatic Brigtness Control Self-Diagnostic Result
#define ST7789V_RDID1      0xDA  // Read ID1 
#define ST7789V_RDID2      0xDB  // Read ID2 
#define ST7789V_RDID3      0xDC  // Read ID3 
// System Function Command Table 2
#define ST7789V_RAMCTRL    0xB0  // RAM Control  
#define ST7789V_RGBCTRL    0xB1  // RGB Interface Control
#define ST7789V_PORCTRL    0xB2  // Porc Setting 
#define ST7789V_FRCTRL1    0xB3  // Frame Rate Control 1 In partial mode/ idle colors
#define ST7789V_PARCTRL    0xB5  // Partial mode Control
#define ST7789V_GCTRL      0xB7  // Gate Control 
#define ST7789V_GTADJ      0xB8  // Gate On Timing Adjustment 
#define ST7789V_DGMEN      0xBA  // Digital Gamma Enable 
#define ST7789V_VCOMS      0xBB  // VCOMS Setting
#define ST7789V_LCMCTRL    0xC0  // LCM Control
#define ST7789V_DSET       0xC1  // ID Code Setting
#define ST7789V_VDVVREN    0xC2  // VDV and VR Command Enable
#define ST7789V_VRS        0xC3  // VR Set
#define ST7789V_VDVS       0xC4  // VDV Set
#define ST7789V_VCMOFSET   0xC5  // VCOMS Offset Set
#define ST7789V_FRCTRL2    0xC6  // Frame Rate Control in Normal Mode
#define ST7789V_CABCCTRL   0xC7  // CABC Control
#define ST7789V_REGSEL1    0xC8  // Register Value Selection 1
#define ST7789V_REGSEL2    0xCA  // Register Value Selection 2
#define ST7789V_PWMFRSEL   0xCC  // PWM Frequency Selection
#define ST7789V_PWCTRL1    0xD0  // Power Control 1
#define ST7789V_VAPVANEN   0xD2  // Enable VAP/VAN signal output
#define ST7789V_CMD2EN     0xDF  // Command 2 Enable
#define ST7789V_PVGAMCTRL  0xE0  // Positive Voltage Gamma Control
#define ST7789V_NVGAMCTRL  0xE1  // Negative Voltage Gamma Control
#define ST7789V_DGMLUTR    0xE2  // Digital Gamma Look-up Table for Red
#define ST7789V_DGMLUTB    0xE3  // Digital Gamma Look-up Table for Blue
#define ST7789V_GATECTRL   0xE4  // Gate Control
#define ST7789V_SPI2EN     0xE7  // SPI2 Enable
#define ST7789V_PWCTRL2    0xE8  // Power Control 2
#define ST7789V_EQCTRL     0xE9  // Equalize time control
#define ST7789V_PROMCTRL   0xEC  // Program Mode Control
#define ST7789V_PROMEN     0xFA  // Program Mode Enable
#define ST7789V_NVMSET     0xFC  // NVM Setting
#define ST7789V_PROMACT    0xFE  // Program action

#endif