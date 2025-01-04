#ifndef SIM7670_H
#define SIM7670_H

#include <at89x52.h>
#include <string.h>

// Function Prototypes
void delay(unsigned int delay_ms);
void init_uart();
void Tx_char(char data1);
unsigned char Rx_char1();
char* read_response1();
void send_string(char* f_ptr);
bit init_gsm();
bit send_sms(char* phone_number, char* message);
char* read_sms();
char* config_no();
bit read_response(char* at_Cammand,char* response);
bit network_register();

#endif // SIM7670_H
