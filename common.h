/*
 *
 *
 */

#ifndef __COMMON_H__
#define __COMMON_H__

#include <reg52.h>
#include <intrins.h>
#define uchar unsigned char
#define uint  unsigned int

/*
 * Buttons
 */
#define BT_TIMER 	0x7e
#define BT_SPEED 	0x7d
#define BT_TURN  	0x7b
#define BT_CRST  	0x77
#define BT_ESC   	0xde
#define BT_UP		0xdd
#define BT_DOWN 	0xdb
#define BT_ENT		0xd7
#define BT_START 	0xbe
#define BT_WATER 	0xbd
#define BT_STOP  	0xbb
#define BT_GREASE 	0xb7

#define FUN_NON		0
#define FUN_TIMER	1
#define FUN_SPEED	2
#define FUN_TURN	3

#define GROUP_DEFAULT 0
#define GROUP_1		1
#define GROUP_2		4
#define GROUP_3		7
#define GROUP_4		10
#define GROUP_5		13
#define GROUP_6		16
#define GROUP_7		19
#define GROUP_8		22
#define GROUP_9		25
#define GROUP_10	28

#define LCD_TIMER_LINE	1
#define LCD_SPEED_LINE	2
#define LCD_TURN_LINE	3
#define LCD_COUNT_LINE	4

#endif