/**
 * Marlin 3D Printer Firmware
 * Espressif ESP32 Hibrit Donanım Yapılandırması 
 * (Opto + RC Filtre + I2C + Donanımsal SPI)
 */

#pragma once
#include "env_validate.h"
#define BOARD_INFO_NAME "Espressif ESP32 Hibrit"

//
// Limit Switches (Hepsi bağımsız, kendi pininde!)
//
#define X_MIN_PIN                             32
#define Y_MIN_PIN                             15
#define Z_MIN_PIN                              5

//
// Steppers (E0 motoru 14-23'te, Y_DIR 12'de)
//
#define X_STEP_PIN                            25
#define X_DIR_PIN                             26
#define X_ENABLE_PIN                          33

#define Y_STEP_PIN                            27
#define Y_DIR_PIN                             12  
#define Y_ENABLE_PIN                          33

#define Z_STEP_PIN                            16
#define Z_DIR_PIN                             17
#define Z_ENABLE_PIN                          33

#define E0_STEP_PIN                           14
#define E0_DIR_PIN                            23
#define E0_ENABLE_PIN                         33

//
// Sıcaklık Sensörleri (RC Filtreli Analog Girişler)
//
#define TEMP_0_PIN                            36  
#define TEMP_BED_PIN                          39  

//
// Isıtıcılar & Turbo Fan (İzole Çıkışlar)
//
#define HEATER_0_PIN                          13  
#define HEATER_BED_PIN                         4  
#define FAN_PIN                                2  

//
// SPI Micro SD Kart Pinleri (MÜKEMMEL EŞLEŞME)
//
//
// SPI Micro SD Kart Pinleri (MÜKEMMEL EŞLEŞME)
//
#define SDSS                                   0  // SD Kart Kütüphanesi İçin
#define SS_PIN                                 0  // ESP32 SPI Donanımını Yönlendirmek İçin (BUNU EKLE)
#define MOSI_PIN                              19  // Donanımsal VSPI Pini
#define MISO_PIN                              34  // Sadece giriş pini
#define SCK_PIN                               18  // Donanımsal VSPI Saat Pini
#define SD_DETECT_PIN                         -1
// NOT: I2C LCD Ekran (SDA=21, SCL=22) donanımsal olarak bağlanacaktır.

#define I2C_SDA_PIN                           21
#define I2C_SCL_PIN                           22