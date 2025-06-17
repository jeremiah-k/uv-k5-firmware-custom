#ifndef APP_CHFRSCANNER_H
#define APP_CHFRSCANNER_H

#include <stdbool.h>
#include <stdint.h>

// scan direction, if not equal SCAN_OFF indicates
// that we are in a process of scanning channels/frequencies
extern int8_t            gScanStateDir;
extern bool              gScanKeepResult;
extern bool              gScanPauseMode;

#ifdef ENABLE_SCAN_RANGES
extern uint32_t          gScanRangeStart;
extern uint32_t          gScanRangeStop;
#endif

#ifdef ENABLE_SCANNER_STATE_PERSISTENCE
// Scanner state persistence structure
typedef struct {
    uint8_t  magic;              // Magic number to validate saved state (0xAB)
    int8_t   scanStateDir;       // Scan direction and active flag
    uint8_t  currentScanList;    // Current scan list being used
    uint8_t  nextMrChannel;      // Current channel being scanned
    bool     scanPauseMode;      // Whether scan is paused
    uint8_t  rxVfo;              // Which VFO was being used for scanning
    uint8_t  reserved1;          // Reserved for future use
    uint8_t  reserved2;          // Reserved for future use
} ScannerState_t;

#define SCANNER_STATE_MAGIC 0xAB
#define SCANNER_STATE_EEPROM_ADDR 0x0F20
#endif

void CHFRSCANNER_Found(void);
void CHFRSCANNER_Stop(void);
void CHFRSCANNER_Start(const bool storeBackupSettings, const int8_t scan_direction);
void CHFRSCANNER_ContinueScanning(void);
#ifdef ENABLE_SCANNER_STATE_PERSISTENCE
void CHFRSCANNER_SaveState(void);
void CHFRSCANNER_LoadState(void);
void CHFRSCANNER_ClearState(void);
#endif

#endif