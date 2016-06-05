// Do not remove the include below
#include "Tx_Link.h"
#include "SoftwareSerial.h"
#include "Base64.h"

SoftwareSerial wifi_link(LINK_RX_PIN, LINK_TX_PIN);
uchar link_online = 0;
String enc_data;
char cmd_buf[32];
int angle = 0;

//The setup function is called once at startup of the sketch
void setup()
{
// Add your initialization code here
	pinMode(LINK_RX_PIN, INPUT);
	digitalWrite(LINK_RX_PIN, LOW);

	pinMode(LINK_RESET_PIN, OUTPUT);
	digitalWrite(LINK_RESET_PIN, LOW);

	pinMode(LED_PIN, OUTPUT);
	digitalWrite(LED_PIN, LOW);

	Serial.begin(19200);
	wifi_link.begin(9600);
	delay(1000);

	Serial.println("Initializing link...");

	if (initLink() == 0)
	{
		link_online = 1;
	}
}

// The loop function is called in an endless loop
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
		/**********************************************
		 * We have some data over the WiFi link. Now,
		 * let us receive the data and try to parse it.
		 * The data contains four bytes. Print each byte
		 * on the serial out for debug.
		 **********************************************/
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

	if (digitalRead(8) == 0) {
		while (digitalRead(8) == 0);
		Serial.println("Sending command to remote...");
		wifi_link.print("\nAQAA+g==\n");
	}
}

uchar initLink(void)
{
	unsigned int ret = 0;

	linkEnable();

	do
	{
		ret = sendAtCommand(WIFI_NO_ECHO);
		if (ret != 0)
		{
			break;
		}

		ret = sendAtCommand(WIFI_SET_MODE);
		if (ret != 0)
		{
			break;
		}

		ret = sendAtCommand(WIFI_AP_CONNECT);
		if (ret != 0)
		{
			break;
		}

		ret = sendAtCommand(WIFI_CHECK_IP);
		if (ret != 0)
		{
			break;
		}

		ret = sendAtCommand(WIFI_SOCK_OPEN);
		if (ret != 0)
		{
			break;
		}

		ret = sendAtCommand(WIFI_SOCK_TRANSP);
		if (ret != 0)
		{
			break;
		}

		ret = sendAtCommand(WIFI_SOCK_SEND);
		if (ret != 0)
		{
			break;
		}

		wifi_link.print('\n');

	} while (0);

	return (ret);
}

uchar sendAtCommand(const char *cmd)
{
	char ch = '.';

	Serial.print("Sending command: ");
	Serial.println(cmd);

	wifi_link.println(cmd);

	do
	{
		if (waitWithIndication())
		{
			return (1);
		}
		ch = wifi_link.read();
		Serial.write(ch);
	} while ((ch != 'O') && (ch != 'n') && (ch != '>'));

	while (wifi_link.available())
	{
		ch = wifi_link.read();
		Serial.write(ch);
		waitWithIndication();
	}

	return (0);
}

uchar linkEnable(void)
{
	int dly = 2000;
	digitalWrite(LINK_RESET_PIN, HIGH);

	if (waitWithIndication())
	{
		Serial.println("Timeout enabling RF link. Reset to start over...");
		return (1);
	}

	while (dly > 0)
	{
		while (wifi_link.available())
		{
			dly = 2000;
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
	char enc_buf[32];
	enc_data = "";

	while (wifi_link.available())
	{
		enc_data += wifi_link.readString();
		delay(1);
	}

	enc_data.toCharArray(enc_buf, 31);

	base64_decode(cmd_buf, enc_buf, enc_data.length());
	Serial.print("Received: ");
	Serial.println(enc_data);

	return (0);
}

void linkReset(void)
{
	uchar ret;

	delay(1000);
	wifi_link.print("+++");
	delay(1000);

	do
	{
		ret = sendAtCommand(WIFI_SOCK_CLOSE);
		if (ret != 0)
		{
			break;
		}

		ret = sendAtCommand(WIFI_SOCK_OPEN);
		if (ret != 0)
		{
			break;
		}

		ret = sendAtCommand(WIFI_SOCK_TRANSP);
		if (ret != 0)
		{
			break;
		}

		ret = sendAtCommand(WIFI_SOCK_SEND);
		if (ret != 0)
		{
			break;
		}

		wifi_link.print('\n');
	} while(0);

	return;
}

