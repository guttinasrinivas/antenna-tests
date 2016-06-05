#include "RX_Link.h"
#include "SoftwareSerial.h"
#include "Base64.h"
#include "Servo.h"

#ifdef WIFI_LINK_SOFT_SERIAL
SoftwareSerial wifi_link(LINK_RX_PIN, LINK_TX_PIN);
#else /* WIFI_LINK_SOFT_SERIAL */
#define wifi_link Serial
#endif /* WIFI_LINK_SOFT_SERIAL */

uchar link_online = 0;
String enc_data;
char cmd_buf[32];
Servo servo;
int angle = 0;

void setup()
{
	pinMode(LINK_RX_PIN, INPUT);
	digitalWrite(LINK_RX_PIN, LOW);

	pinMode(0, INPUT);
	digitalWrite(0, LOW);

	pinMode(LINK_RESET_PIN, OUTPUT);
	digitalWrite(LINK_RESET_PIN, LOW);

	pinMode(LED_PIN, OUTPUT);
	digitalWrite(LED_PIN, LOW);

	servo.attach(6);
	Serial.begin(19200);
	wifi_link.begin(19200);
	delay(1000);

	Serial.println("Initializing link...");
	if (linkEnable() == 0)
	{
		link_online = 1;
	}

	Serial.println("Link ready.");
}

void loop()
{
	while (link_online == 0)
	{
		Serial.println("Link offline. Reset to start over...");
		delay(1000);
	}

	if (Serial.available())
	{
		wifi_link.write(Serial.read());
	}

	if (wifi_link.available())
	{
		getDataFromLink();
		Serial.print((unsigned char) cmd_buf[0], 16);
		Serial.print(' ');
		Serial.print((unsigned char) cmd_buf[1], 16);
		Serial.print(' ');
		Serial.print((unsigned char) cmd_buf[2], 16);
		Serial.print(' ');
		Serial.println((unsigned char) cmd_buf[3], 16);

		if (cmd_buf[0] == 1)
		{
			analogWrite(RED_LED_PIN, cmd_buf[1]);
			analogWrite(GREEN_LED_PIN, cmd_buf[2]);
			analogWrite(BLUE_LED_PIN, cmd_buf[3]);
		}
	}
}

uchar linkEnable(void)
{
	int dly = 10000;
	digitalWrite(LINK_RESET_PIN, HIGH);

	unsigned int l_val = 0;

	while (dly > 0)
	{
		l_val++;
		if (l_val > 1023) {
			l_val = 0;
		}

		analogWrite(RED_LED_PIN, 0);
		analogWrite(6, (l_val >> 2));
		analogWrite(BLUE_LED_PIN, 0);

		while (wifi_link.available())
		{
			dly = 10000;
			Serial.write(wifi_link.read());
		}
		dly--;
		delay(1);
	}

	return (0);
}

uchar waitWithIndication(int max_delay)
{
	uchar led_blink = 0;

	while ((wifi_link.available() == 0) && (max_delay > 0))
	{
		led_blink++;
		LINK_LED_INDICATOR(led_blink);
		max_delay--;
		delay(1);
	}

	digitalWrite(LED_PIN, 0);

	return ((max_delay > 0) ? 0 : 1);
}

uchar getDataFromLink()
{
	char ch = '\0';
	char enc_buf[4];
	char enc_data[32];
	uchar ii = 0;

	if (wifi_link.available() == 0)
	{
		return 1;
	}

	/* Start with '\n' */
	while (ch != '\n') {
		if (waitWithIndication(1000) != 0) {
			return 1;
		}

		ch = wifi_link.read();
	}

	for (ii = 0; ii < 31; ii++)
	{
		if (waitWithIndication(1000) != 0) {
			return 1;
		}

		ch = wifi_link.read();
		if (ch == '\n') {
			enc_data[ii] = 0;
			break;
		}
		enc_data[ii] = ch;

		delay(1);
	}

	base64_decode(cmd_buf, enc_buf, ii+1);
	Serial.print("Received: ");
	Serial.println(enc_data);

	return (0);
}

void linkReset(void)
{
	digitalWrite(LINK_RESET_PIN, LOW);
	waitWithIndication(1000);
	digitalWrite(LINK_RESET_PIN, HIGH);
	waitWithIndication(10000);

	return;
}

