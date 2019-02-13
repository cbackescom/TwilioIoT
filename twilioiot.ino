/*
Basics of the SMS messaging system
*/
#include "uCommand.h"

STARTUP(cellular_credentials_set("wireless.twilio.com", "", "", NULL));

uCommand uCmd;
 
/* Setup our relay */
int relay = D7;
String smsBody;

void setup()
{
pinMode(relay, OUTPUT);
char res;
int atResult;

	//Cellular.off();
	delay(2000);
	Serial.println("Entering sms setup");
	pinMode(B0,OUTPUT);
	digitalWrite(B0, HIGH);	// turn power on
	uCmd.setDebug(false);
	// set up text mode for the sms
	atResult = uCmd.setSMSMode(1);
	if(atResult == RESP_OK){
		Serial.println("Text mode setup was OK");
	}
	else{
		Serial.println("Did not set up text mode");
	}
	delay(1000);

}


void loop()
{
int val,ret,res;
char c,i,str[80];

	while(1){
		// read next available messages
		if(uCmd.checkMessages(10000) == RESP_OK){
			uCmd.smsPtr = uCmd.smsResults;
			for(i=0;i<uCmd.numMessages;i++){
				Serial.printlnf("-sms: %s",uCmd.smsPtr->sms);
				smsBody = uCmd.smsPtr->sms;
				if (smsBody == "open"){
				    digitalWrite(relay, HIGH);
				    delay(1000);
				    digitalWrite(relay, LOW);
				} else if (smsBody == "close"){
				    digitalWrite(relay, HIGH);
				    delay(250);
				    digitalWrite(relay, LOW);
				    delay(250);
				    digitalWrite(relay, HIGH);
				    delay(250);
				    digitalWrite(relay, LOW);
				} 
			}
		}
		
		// delete all the messages
		uCmd.smsPtr = uCmd.smsResults;
		for(i=0;i<uCmd.numMessages;i++){
			if(uCmd.deleteMessage(uCmd.smsPtr->mess,10000) == RESP_OK){
				Serial.println("message deleted successfully");
			}
			else Serial.println("could not delete message");
			uCmd.smsPtr++;
		}
		delay(1000);
	}

}