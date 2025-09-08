//----------------------------------------------------------------------------------------------------
//(C) 2025 YuriYuri (Yuriy Golovin)
//----------------------------------------------------------------------------------------------------
#ifndef _COMMANDS_ST7735S
#define _COMMANDS_ST7735S

// System Function Command List and Description
#define ST7735S_NOP        0x00  // No Operation
#define ST7735S_SWRESET    0x01  // Software Reset 
#define ST7735S_RDDID      0x04  // Read Display ID
#define ST7735S_RDDST      0x09  // Read Display Status 
#define ST7735S_RDDPM      0x0A  // Read Display Power Mode 
#define ST7735S_RDDMADCTL  0x0B  // Read Display MADCTL
#define ST7735S_RDDCOLMOD  0x0C  // Read Display Pixel Format 
#define ST7735S_RDDIM      0x0D  // Read Display Image Mode 
#define ST7735S_RDDSM      0x0E  // Read Display Signal Mode 
#define ST7735S_RDDSDR     0x0F  // Read Display Self-Diagnostic Result 
#define ST7735S_SLPIN      0x10  // Sleep In
#define ST7735S_SLPOUT     0x11  // Sleep Out
#define ST7735S_PTLON      0x12  // Partial Display Mode On
#define ST7735S_NORON      0x13  // Normal Display Mode On 
#define ST7735S_INVOFF     0x20  // Display Inversion Off 
#define ST7735S_INVON      0x21  // Display Inversion On 
#define ST7735S_GAMSET     0x26  // Gamma Set
#define ST7735S_DISPOFF    0x28  // Display Off
#define ST7735S_DISPON     0x29  // Display On 
#define ST7735S_CASET      0x2A  // Column Address Set
#define ST7735S_RASET      0x2B  // Row Address Set 
#define ST7735S_RAMWR      0x2C  // Memory Write 
#define ST7735S_RGBSET     0x2D  // Color Setting for 4K, 65K and 262K
#define ST7735S_RAMRD      0x2E  // Memory Read 
#define ST7735S_PTLAR      0x30  // Partial Area 
#define ST7735S_SCRLAR     0x33  // Scroll Area Set 
#define ST7735S_TEOFF      0x34  // Tearing Effect Line OFF 
#define ST7735S_TEON       0x35  // Tearing Effect Line ON 
#define ST7735S_MADCTL     0x36  // Memory Data Access Control 
#define ST7735S_VSCSAD     0x37  // Vertical Scroll Start Address of RAM 0x37h)
#define ST7735S_IDMOFF     0x38  // Idle Mode Off
#define ST7735S_IDMON      0x39  // Idle Mode On 
#define ST7735S_COLMOD     0x3A  // Interface Pixel Format
#define ST7735S_RDID1      0xDA  // Read ID1 Value
#define ST7735S_RDID2      0xDB  // Read ID2 Value 
#define ST7735S_RDID3      0xDC  // Read ID3 Value 
// Panel Function Command List and Description 
#define ST7735S_FRMCTR1    0xB1  // Frame Rate Control (In normal mode/ Full colors) 
#define ST7735S_FRMCTR2    0xB2  // Frame Rate Control (In Idle mode/ 8-colors) 
#define ST7735S_FRMCTR3    0xB3  // Frame Rate Control (In Partial mode/ full colors) 
#define ST7735S_INVCTR     0xB4  // Display Inversion Control 
#define ST7735S_PWCTR1     0xC0  // Power Control 1 
#define ST7735S_PWCTR2     0xC1  // Power Control 2 
#define ST7735S_PWCTR3     0xC2  // Power Control 3 (in Normal mode/ Full colors) 
#define ST7735S_PWCTR4     0xC3  // Power Control 4 (in Idle mode/ 8-colors) 
#define ST7735S_PWCTR5     0xC4  // Power Control 5 (in Partial mode/ full-colors) 
#define ST7735S_VMCTR1     0xC5  // VCOM Control 1 
#define ST7735S_VMOFCTR    0xC7  // VCOM Offset Control 
#define ST7735S_WRID2      0xD1  // Write ID2 Value 
#define ST7735S_WRID3      0xD2  // Write ID3 Value
#define ST7735S_NVFCTR1    0xD9  // NVM Control Status 
#define ST7735S_NVFCTR2    0xDE  // NVM Read Command
#define ST7735S_NVFCTR3    0xDF  // NVM Write Command 
#define ST7735S_GMCTRP1    0xE0  // Gamma ‘+’ polarity Correction Characteristics Setting
#define ST7735S_GMCTRN1    0xE1  // Gamma ‘-’ polarity Correction Characteristics Setting 
#define ST7735S_GCV        0xFC  // Gate Pump Clock Frequency Variable 

#endif