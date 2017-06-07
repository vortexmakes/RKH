#ifndef _DRIVER_SLCD_H_
#define _DRIVER_SLCD_H_

  #include "PounceTypes_v2.h"
  #include "MK40DZ10.h"
  #include "Fonts_LCD.h"

  /**
    Global defines
  */
  #define MAX_COLUMNS_PER_CHAR                        4
  #define CHAR_RESET_POSITION                         5
  #define CHAR_MAX_POSITION_VALUE                     34
  #define CHAR_POSITION_INCREMENT                     6
  #define MARQUEE_MAX_POSITION_WITHOUT_ARROW          37
  #define MARQUEE_MAX_POSITION_WITH_ARROW             35
  #define MARQUEE_MIN_POSITION_WITHOUT_ARROW          0
  #define MARQUEE_MIN_POSITION_WITH_ARROW             2
  #define MARQUEE_WITH_ARROWS                         1
  #define MARQUEE_WITHOUT_ARROWS                      0

  #define FRONT_PLANE_0_TO_3                          0
  #define FRONT_PLANE_4_TO_7                          4
  #define FRONT_PLANE_8_TO_11                         8
  #define FRONT_PLANE_12_TO_15                        12
  #define FRONT_PLANE_16_TO_19                        16
  #define FRONT_PLANE_20_TO_23                        20
  #define FRONT_PLANE_24_TO_27                        24
  #define FRONT_PLANE_28_TO_31                        28
  #define FRONT_PLANE_32_TO_35                        32
  #define FRONT_PLANE_36_TO_39                        36
  #define FRONT_PLANE_40_TO_43                        40
  #define FRONT_PLANE_44_TO_47                        44

  #define UPPER_LEFT                                  0
  #define MIDDLE_LEFT                                 1
  #define LOWER_LEFT                                  2
  #define UPPER_RIGHT                                 3
  #define MIDDLE_RIGHT                                4
  #define LOWER_RIGHT                                 5

  #define CHARGED                                     2
  #define MID_LEVEL                                   1
  #define LOWER_LEVEL                                 0

  #define ARROWS                                      1
  #define NO_ARROWS                                   0

  /**
    Enumeration for the backplane phases
*/
  typedef enum
  {
    PHASE_A = 0,
    PHASE_B,
    PHASE_C,
    PHASE_D,
    PHASE_E,
    PHASE_F,
    PHASE_G,
    PHASE_H
  }eBackPlanePhases;

  /**
    External Variables
  */
  extern BOOL isMarqueeRestart;

  /**
    Public Function Prototypes
  */
  void _SLCDModule_Init(void);
  BOOL _SLCDModule_PrintScrolling(char *  SourceString);
  void _SLCDModule_TurnOnAllSegments(void);
  void _SLCDModule_TurnOffAllSegments(void);
  void _SLCDModule_SetSegment(U08 X, U08 Y);
  void _SLCDModule_ClearSegment(U08 X, U08 Y);
  void _SLCDModule_PrintString(STRING SourceString, U08 StartPosition);
  BOOL _SLCDModule_PrintMarquee(STRING SourceString, S16 StartPosition, U08 MaxPosition, U08 MinPosition);
  void _SLCDModule_ClearLCD(U08 ArrowsOn);

  void _SLCDModule_PrintUpperArrow(void);
  void _SLCDModule_PrintLowerArrow(void);
  void _SLCDModule_PrintLeftArrow(void);
  void _SLCDModule_PrintRightArrow(void);
  void _SLCDModule_PrintUpperRCArrow(void);
  void _SLCDModule_PrintLowerRCArrow(void);

  void _SLCDModule_EraseUpperArrow(void);
  void _SLCDModule_EraseLowerArrow(void);
  void _SLCDModule_EraseLeftArrow(void);
  void _SLCDModule_EraseRightArrow(void);
  void _SLCDModule_EraseUpperRCArrow(void);
  void _SLCDModule_EraseLowerRCArrow(void);

  void _SLCDMOdule_PrintDotMarquee(S08 StartPosition);
  void _SLCDModule_PrintRCBlocks(U08 Position);
  void _SLCDModule_EraseRCBlocks(U08 Position);
  void _SLCDModule_PrintNumber(U08 Number, U08 Position);

  void _SLCDModule_TurnOnUSBSign(void);
  void _SLCDModule_TurnOnWirelessSign(void);
  void _SLCDModule_TurnOnPounceSign(void);
  void _SLCDModule_TurnOnFreescaleSign(void);
  void _SLCDModule_TurnOnClockSign(void);
  void _SLCDModule_TurnOnJLinkSign(void);
  void _SLCDModule_TurnOnBatteryOutline(void);
  void _SLCDModule_TurnOnBattery(U08 BatteryLevel);

  void _SLCDModule_TurnOffUSBSign(void);
  void _SLCDModule_TurnOffWirelessSign(void);
  void _SLCDModule_TurnOffPounceSign(void);
  void _SLCDModule_TurnOffFreescaleSign(void);
  void _SLCDModule_TurnOffClockSign(void);
  void _SLCDModule_TurnOffJLinkSign(void);
  void _SLCDModule_TurnOffBattery(void);

#endif/*_DRIVER_SLCD_H_*/






