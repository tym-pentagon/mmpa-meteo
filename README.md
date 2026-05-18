# MMPa meteo
**MMPa meteo** je víceúčelová meteostanice určená pro analýzu atmosféry, magnetického pole Země a dalších jevů. 
Jedná se o projekt [týmu Pentagon](https://github.com/tym-pentagon). 

## Komunikace
Jednotky mezi sebou komunikují pomocí LoRa. 

### Předávané proměnné
| Index | Typ proměnné |  Název proměnné  |
|-------|--------------|------------------|
| 0-1   | int16_t      | cas.rok          |
| 2     | int8_t       | cas.mesic        |
| 3     | int8_t       | cas.den          |
| 4     | int8_t       | cas.hodiny       |
| 5     | int8_t       | cas.minuty       |
| 6     | int8_t       | cas.sekundy      |
| 7-10	| int32_t      | teplota          |
| 11-14	| uint32_t     | vlhkost          |
| 15-18 | uint32_t     | tlak             |
| 19-60 |              |                  |
| 61    | uint8_t      | crc              |

## Zdroje
 - [Knihovna pro ovládání ILI9486 LCD](https://github.com/RobertoBenjami/stm32_graphics_display_drivers)
 - [Knihovna pro ovládání SSD1306 OLED](https://github.com/afiskon/stm32-ssd1306)
 - [Čtení dat z BME280 přes I²C](https://controllerstech.com/interface-bme280-with-stm32/) - tutoriál
 - [BME280 datasheet](https://www.bosch-sensortec.com/media/boschsensortec/downloads/datasheets/bst-bme280-ds002.pdf)
 - [LoRa datasheet](https://www.mouser.com/pdfDocs/DS_LLCC68_V10-2.pdf)
 - [STM32 SD Card Interface via SPI and FatFS Tutorial (No RTOS)](https://www.youtube.com/watch?v=PBIm8BCnbyQ) - video tutoriál
 - Dimitar Toshkov Zhekov - Terminus Font
 - [Deepseek](https://chat.deepseek.com/) - generování programu pro export fontů
 - [ChatGPT](https://chatgpt.com/) & [GitHub Copilot modely](https://github.com/copilot) (studentská licence) - debugování
