/*
Arduino Ethernet Script Server

Created Mars 4, 2014
Mikael Kindborg, Evothings AB

TCP socket server that accept commands for basic scripting
of the Arduino board.

This example is written for use with an Ethernet shield.

The API consists of the requests listed below.

Requests and responses end with a new line.

*/

// Include files.
#include <SPI.h>
#include <Ethernet.h>
#include <IRLib.h>

IRsend My_Sender;

// Enter a MAC address for your controller below, usually found on a sticker
// on the back of your Ethernet shield.
byte mac[] = { 0x90, 0xA2, 0xDA, 0x0E, 0xD0, 0x93 };

// The IP address will be dependent on your local network.
// If you have IP network info, uncomment the lines starting
// with IPAddress and enter relevant data for your network.
// If you don't know, you probably have dynamically allocated IP adresses, then
// you don't need to do anything, move along.
IPAddress ip(192,168,1,10);
IPAddress gateway(192,168,1,1);
IPAddress subnet(255, 255, 255, 0);

// Create a server listening on the given port.
EthernetServer server(32);

void setup()
{
	// Start serial communication with the given baud rate.
	// NOTE: Remember to set the baud rate in the Serial
	// monitor to the same value.
	Serial.begin(9600);

	// Wait for serial port to connect. Needed for Leonardo only.
	while (!Serial) { ; }

	// Initialize the Ethernet shield.
	// If you entered fixed ipaddress info, gateway, subnet mask,
	// then uncommment the next line.
	Ethernet.begin(mac, ip, gateway, subnet);

	// If it works to get a dynamic IP from a DHCP server, use this
	// code to test if you're getting a dynamic adress. If this
	// does not work, use the above method of specifying an IP-address.
	// dhcp test starts here
	//if (Ethernet.begin(mac) == 0)
	//{
	//	Serial.println("Failed to configure Ethernet using DHCP");
	//	// No point in carrying on, stop here forever.
	//	while(true) ;
	//}
	// dhcp test end


	// Start the server.
	server.begin();

	// Print status.
	printServerStatus();
}

void loop()
{
	// Listen for incoming client requests.
	EthernetClient client = server.available();
	if (!client)
	{
		return;
	}

	Serial.println("Client connected");

	String request = readRequest(&client);
	executeRequest(request);

	// Close the connection.
	//client.stop();

	Serial.println("Client disonnected");
}

// Read the request line,
String readRequest(EthernetClient* client)
{
	String request = "";

	// Loop while the client is connected.
	while (client->connected())
	{
		// Read available bytes.
		while (client->available())
		{
			// Read a byte.
			char c = client->read();

			// Print the value (for debugging).
			Serial.write(c);

			// Exit loop if end of line.
			if ('\n' == c)
			{
				return request;
			}

			// Add byte to request line.
			request += c;
		}
	}
	return request;
}

void executeRequest(String request)
{
	if ( request.equals("nadon") )
	{
    My_Sender.send(NEC, 0xE13EA45B, 32);
		Serial.println("NAD ON");
	}
  else if ( request.equals("nadoff") )
	{
    My_Sender.send(NEC, 0xE13E13EC, 32);
		Serial.println("NAD OFF");
	}
  else if ( request.equals("nadvolup") )
	{
    My_Sender.send(NEC, 0xE13E11EE, 32);
		Serial.println("NAD VOL+");
	}
  else if ( request.equals("nadvoldown") )
	{
    My_Sender.send(NEC, 0xE13E31CE, 32);
		Serial.println("NAD VOL-");
	}
  else if ( request.equals("nadmp") )
	{
    My_Sender.send(NEC, 0xE13E03FC, 32);
		Serial.println("NAD MP");
	}
  else if ( request.equals("nadcd") )
	{
    My_Sender.send(NEC, 0xE13EA15E, 32);
		Serial.println("NAD CD");
	}
  else if ( request.equals("sonyonoff") )
	{
    My_Sender.send(SONY, 0x540C, 15);
		Serial.println("Sony On/Off");
	}
  else if ( request.equals("sonyvolup") )
	{
    My_Sender.send(SONY, 0x240C, 15);
		Serial.println("Sony Vol+");
	}
  else if ( request.equals("sonyvoldown") )
	{
    My_Sender.send(SONY, 0x640C, 15);
		Serial.println("Sony Vol-");
	}
}


void sendResponse(EthernetClient* client, String response)
{
	// Send response to client.
	client->println(response);

	// Debug print.
	Serial.println("sendResponse:");
	Serial.println(response);
}

void printServerStatus()
{
	Serial.print("Server address:");
	Serial.println(Ethernet.localIP());
}
