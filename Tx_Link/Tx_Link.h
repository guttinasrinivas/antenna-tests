// Only modify this file to include
// - function definitions (prototypes)
// - include files
// - extern variable definitions
// In the appropriate section

#ifndef _Tx_Link_H_
#define _Tx_Link_H_
#include "Arduino.h"

typedef unsigned char uchar;

#define LED_PIN			3
#define RED_LED_PIN     5
#define GREEN_LED_PIN   6
#define BLUE_LED_PIN    9

#define LINK_RESET_PIN	2
#define LINK_TX_PIN		13
#define LINK_RX_PIN		12

#define	WIFI_NO_ECHO	"ATE0"
#define WIFI_SET_MODE   "AT+CWMODE=3"
#define WIFI_AP_CONNECT	"AT+CWJAP=\"Hoan\",\"0452346869\""
#define WIFI_CHECK_IP   "AT+CIFSR"
#define WIFI_SOCK_OPEN  "AT+CIPSTART=\"TCP\",\"192.168.1.100\",23"
#define WIFI_SOCK_TRANSP "AT+CIPMODE=1"
#define WIFI_SOCK_SEND   "AT+CIPSEND"
#define WIFI_SOCK_CLOSE  "AT+CIPCLOSE"


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

#endif /* _Tx_Link_H_ */
