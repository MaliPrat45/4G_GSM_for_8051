#include <at89x52.h>
#include "sim7670.h"

idata char* incoming_msg = "";
idata char* mob_number = '\0';


void main() {
  init_uart();  // Initialize UART for communication
  init_gsm();   // Initialize GSM module
  while (!network_register())
    ;
  while (mob_number == 0) {
    mob_number = config_no();  // This will read the phone number from an incoming SMS
  }
  send_sms(mob_number, "Hello from GSM Module!");  // Replace with the actual phone number
  delay(2000);                                     // Delay for 2 seconds
  incoming_msg = read_sms();                       // Read the first SMS in the inbox
  if (incoming_msg != NULL) {
    // Assuming `mob_no` is set from config_no(), you can send an acknowledgment
    send_sms(mob_number, "SMS received: ");
    send_sms(mob_number, incoming_msg);  // Send the incoming message back
  }
  while (1) {
    // Continuously process or wait for more SMS
    delay(1000);                // Wait for 1 second
    incoming_msg = read_sms();  // Read the first SMS in the inbox
    if (incoming_msg != NULL) {
      // Assuming `mob_no` is set from config_no(), you can send an acknowledgment
      send_sms(mob_number, "SMS received: ");
      delay(5000);
      send_sms(mob_number, incoming_msg);  // Send the incoming message back
      delay(50000);
    }
  }
}
