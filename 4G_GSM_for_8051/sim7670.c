#include "sim7670.h"

void delay(unsigned int delay_ms) {
  unsigned int count, i;
  for (count = 0; count < delay_ms; count++) {
    for (i = 0; i < 120; i++)
      ;
  }
  delay_ms--;
}
void init_uart() {

  PCON = 0x80;
  TMOD = 0x20;
  SCON = 0x50;
  TH1 = 0xFD;
  TL1 = 0xFD;
  T2CON = 0x34;
  RCAP2H = 0xFF;  //AT+IPR=9600
  RCAP2L = 0xFD;
  TR1 = 1;
}
void Tx_char(char data1) {
  SBUF = data1;
  while (!TI)
    ;
  TI = 0;
}
unsigned char Rx_char1() {
  int x = 0;
  while (!RI) {
    if (x++ >= 100)
      return 0;
  }
  RI = 0;
  return SBUF;
}
char* read_response1() {
  idata char buff[100] = "";
  int i = 0;
  char temp = 0;
  strcpy(buff, "/0");
  while (Rx_char1() != '\n')
    ;
  do {
    temp = Rx_char1();
    if (temp != '\n') {
      if (temp != 0x00)
        buff[i++] = temp;
    } else {
      buff[i++] = '\n';
    }
  } while (temp != 0);
	return buff;
}

void send_string(char* f_ptr) {
  unsigned int a;
  for (a = 0; f_ptr[a] != 0; a++) {
    Tx_char(f_ptr[a]);
  }
}

bit init_gsm() {
  unsigned char  i = 0;
    if(read_response("AT\r\n","OK"))
		{
			while(!read_response("ATe0\r\n","OK"));
			while(!read_response("AT+CLIP=1\r\n","OK"));
			while(!read_response("AT+CMGF=1\r\n","OK"));
//			read_response("AT+CSQ\r\n","OK");
//			read_response("AT+CGREG?\r\n","OK");
			while(!read_response("AT+CNMI=2,2,1,1,1\r\n","OK"));
			while(!read_response("AT+CMGD=1,4\r\n","OK"));
			return 1;
		}
		else 
			return 0;
}
bit send_sms(char* phone_number, char* message) {   
    send_string("AT+CMGF=1\r\n");  // Text mode
    delay(500);
    send_string("AT+CMGS=\"");
	  send_string(phone_number);
	  send_string("\"\r\n");
    delay(100);
    send_string(message);  // Send the actual message
    delay(500);
    Tx_char(0x1A);  // ASCII 26 (Ctrl+Z) signals the end of the message
    delay(200);  // Wait for the message to be sent
	  if(strstr(read_response1(),"OK"))
			return 1;
		else
			return 0;
}
char* read_sms()  {
	idata char* response = "";
	idata char msg[50] = "";
  int i = 0, n = 0;
  send_string("AT+CMGF=1\r\n");
  delay(500);
  send_string("AT+CMGL=\"ALL\"");
  send_string("\r\n");
  response = read_response1();
  if (strncmp(response, "+CMGL", 5) == 0) {
    while (response[i++] != 0x0D)
      ;
    while (response[i++] != 0x0D) {
      msg[n++] = response[i];
    }
    msg[n-1] = '\0';
		send_string("AT+CMGD=1,4\r\n");
    read_response1();
		return msg;
  }
	return NULL;
}
char* config_no() {
	idata char* response = "";
	idata char mob_no[15] = "";
  int i = 0, n = 0;
	strcpy(response, "/0");
  response = read_sms();
	if (strncmp(response, '\0', 1)!=0) {
		while ((response[i] != 13))
    {
      mob_no[n++] += response[i++];
    }
		mob_no[n++] = 0;
		send_sms(mob_no,"This phone configured.");
		return mob_no;
	}
	return NULL;
}
bit read_response(char* at_Cammand,char* response)
{
	idata char* gsm_response = "";
	send_string(at_Cammand);
	gsm_response = read_response1();
	gsm_response = strstr(gsm_response,response);
	if(gsm_response==0)
	{
		return 0;
	}else
	{
		return 1;		
	}	
}
bit network_register()
{
	idata char* gsm_response = "";
	send_string("AT+CGREG?\r\n");
	gsm_response = read_response1();
	gsm_response = strstr(gsm_response,"+CGREG:");
	if(gsm_response!=0)
	{
		if(gsm_response[10] == '1' || gsm_response[10] == '5')
		{
			return 1;
		}
	}
	return 0;
}