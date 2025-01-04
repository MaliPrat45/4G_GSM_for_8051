# 4G_GSM_for_8051
Library for sim7670 4G  GSM module with 8051 microcontroller family

This library demonstrates communication with a SIM7670 GSM module using an AT89x52 microcontroller. The system can send and receive SMS messages, check network registration, and handle incoming and outgoing messages efficiently.

## Overview

The system performs the following tasks:

1. **System Initialization**
2. **Network Registration Check**
3. **Phone Number Configuration**
4. **Sending SMS**
5. **Reading Incoming SMS**
6. **Reading and Handling GSM Responses**
7. **Main Execution Flow**

---

## Function Descriptions

### 1. System Initialization

- **`init_uart()`**  
  Initializes the UART communication interface for serial data transmission between the AT89x52 microcontroller and the GSM module.

- **`init_gsm()`**  
  Sends a series of AT commands to the GSM module to configure it for SMS communication. This includes:
  - Enabling text mode (`AT+CMGF=1`)
  - Enabling caller ID (`AT+CLIP=1`)
  - Setting up SMS storage and deletion options.

### 2. Network Registration Check

- **`network_register()`**  
  Sends the `AT+CGREG?` command to check if the GSM module is successfully registered on the network. It verifies that the module responds with a registration status of either `1` or `5`, ensuring the GSM module is ready to send and receive SMS messages.

### 3. Phone Number Configuration

- **`config_no()`**  
  Reads an incoming SMS to extract the sender's phone number. This number is stored for future communication (e.g., sending replies). The function sends a confirmation message back to the sender to notify that their number has been configured.

### 4. Sending SMS

- **`send_sms(phone_number, message)`**  
  Sends an SMS message to the specified `phone_number` with the provided `message`. The process involves:
  - Setting the GSM module into SMS text mode (`AT+CMGF=1`).
  - Sending the phone number followed by the message content.
  - Terminating the message with the Ctrl+Z character (ASCII 26), signaling the end of the SMS.

### 5. Reading Incoming SMS

- **`read_sms()`**  
  Queries the GSM module for all stored SMS messages using the `AT+CMGL="ALL"` command. It extracts and returns the content of the SMS message as a string. This function is useful for reading messages in the module's inbox.

### 6. Reading and Handling GSM Responses

- **`read_response1()`**  
  Reads and collects the response from the GSM module after an AT command is sent. It stores the response and waits for a newline (`\n`) character, allowing confirmation of actions like sending SMS or network registration.

- **`read_response(at_Command, response)`**  
  Sends a specific AT command and checks if the module's response matches the expected `response` string. This function is used to verify the expected responses for various GSM commands.

### 7. Main Execution Flow

1. **Initialize UART** and **set up the GSM module** by calling `init_uart()` and `init_gsm()`.
2. **Check network registration** using `network_register()` to ensure the GSM module is connected to the network.
3. **Read incoming SMS** to extract and store the sender's phone number with `config_no()`.
4. **Send an SMS** with the message "Hello from GSM Module!" to the stored phone number using the `send_sms()` function.
5. **Read incoming SMS** messages using `read_sms()`, and send an acknowledgment or the received message back to the sender.

---

## Files Included

- `sim7670.h`: Header file that defines function prototypes for interacting with the GSM module.
- `sim7670.c`: Contains the implementation of all the functions described above.
- `main.c`: Contains the main logic to initialize the system, send, and read SMS.

---

## How to Use

1. **Set up the GSM module** by connecting it to the AT89x52 microcontroller via UART.
2. **Load the firmware** onto the microcontroller.
3. Once the system is powered up, the GSM module will initialize, register on the network, and be ready to send/receive SMS.
4. **Send an SMS** from any phone to the GSM module to configure the sender's phone number for future communication.
5. The system will reply with a confirmation message, and any subsequent SMS will be acknowledged or replied back with the received content.

---

## Notes

- Make sure the SIM card used in the GSM module is activated and has enough balance for sending SMS.
- Adjust delays between commands and responses based on your specific hardware configuration for optimal performance.

---
