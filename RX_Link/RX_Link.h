// Only modify this file to include
// - function definitions (prototypes)
// - include files
// - extern variable definitions
// In the appropriate section

#ifndef _RX_Link_H_
#define _RX_Link_H_
#include "Arduino.h"

typedef unsigned char uchar;

#define LED_PIN			3
#define RED_LED_PIN     3
#define GREEN_LED_PIN   5
#define BLUE_LED_PIN    6

#define LINK_RESET_PIN	7
#define LINK_TX_PIN		13
#define LINK_RX_PIN		12


#define LED_DIGITAL_PIN
#ifdef LED_DIGITAL_PIN
#define LINK_LED_INDICATOR(val)	\
if (val > 100) { \
	digitalWrite(LED_PIN, 1); \
} else { \
	digitalWrite(LED_PIN, 0); \
}
#else
#define LINK_LED_INDICATOR(val)	\
	if (val > 0x7f) { \
		analogWrite(LED_PIN, (0));	{ \
    else { \
    	analogWrite(LED_PIN, (val << 1)); \
    }
#endif


uchar initLink(void);
uchar linkEnable(void);
uchar waitWithIndication(int max_delay=10000);
uchar getDataFromLink(void);
uchar sendAtCommand(const char *cmd);

void linkReset(void);

#endif /* _RX_Link_H_ */
