/**
 * @file esp8266.h
 * @brief esp8266 command driver library
 * @author Michael Burmeister
 * @version 1.2
 * @date November 29, 2023
 */

#define HTTP 0xF7
#define WS 0xF6

/**
 * @brief Open connection to ESP8266 unit
 * @param rx receive pin
 * @param tx transmit pin
 * @param baud baud rate of ESP8266 unit
 * 
 */
void esp8266_Open(int rx, int tx, int baud) __fromfile("libesp8266/esp8266.c");

/**
 * @brief Open connection to target
 * @param url target name or address
 * @param port target port number (80)
 * @return handle or error
 */
int esp8266_Connect(char *url, short port);

/**
 * @brief Send request data
 * @param handle return from connection
 * @param request pointer to request data
 * @return status
 */
int esp8266_Send(char handle, char *request);

/**
 * @brief Send HTTP request
 * @param handle return from connection
 * @param request pointer to request data
 * @param opt request options
 * @return status
 */
int esp8266_Http(char handle, char *request, short opt);

/**
 * @brief Set header for http request
 * @param header data
 */
void esp8266_setHeader(char *header);

/**
 * @brief Send binary data request
 * @param handle return from connection
 * @param data pointer to data to send
 * @param size number of characters to send
 * @return status
 */
int esp8266_SendBin(char handle, char *data, int size);

/**
 * @brief Receive requested data
 * @param handle returned from connection
 * @param data pointer to returned data
 * @param size of data
 * @return status
 */
int esp8266_Recv(char handle, char *data, int size);

/**
 * @brief Send UDP Packet
 * @param url remote locator
 * @param port remote port number to connect
 * @return status
 */
int esp8266_UDP(char *url, short port);

/**
 * @brief Close open connection
 * @param handle return from connection
 */
void esp8266_Close(char handle);

/**
 * @brief Join network access point
 * @param sid network access point name
 * @param pwd password for connection
 * @return status
 */
int esp8266_Join(char *sid, char pwd);

/**
 * @brief Set environment value
 * @param env enviroment parameter
 * @param value environment value to set
 * @return status
 */
int esp8266_Set(char *env, char *value);

/**
 * @brief Check environment value
 * @param env
 * @return environment value
 * @details environment values: version, module-name,
 *  wifi-mode, wifi-ssd, station-ipaddr, station-macaddr,
 *  softap-ipaddr, softap-macaddr, cmd-start-char,
 *  cmd-enable, cmd-events, loader-baud-rate, baud-rate,
 *  stop-bits, dbg-baud-rate, dbg-stop-bits, reset-pin,
 *  connected-led-pin, rx-pullup, pin-gpio0...15
 */
char *esp8266_Check(char *env);

/**
 * @brief Poll connection status
 * @param mask of handles to check
 * @return status
 */
int esp8266_Poll(int mask);

/**
 * @brief Set Listen URI
 * @param protocol to listen for (HTTP, WS)
 * @param uri to match
 * @return status
 */
int esp8266_Listen(char *protocol, char *uri);

/**
 * @brief Reply to request
 * @param handle returned by connection
 * @param data return data
 * @return status
 */
int esp8266_Reply(char handle, char *data);

/**
 * @brief Wait for incoming connection
 * @param type character pointer to the return type
 * @return handle
*/
int esp8266_Wait(char *type);

/**
 * @brief Path from connection request
 * @return path pointer to path data
 */
char *esp8266_Path(char handle);

/**
 * @brief Get argument values
 * @param handle of connection
 * @param name of argument
 * @return value
*/
char *esp8266_arg(char handle, char *name);

/**
 * @brief Drop WiFi connection
 * @return status
 */
int esp8266_Drop(void);

/**
 * @brief Special print
 * @param data to print
 * @param size of data
 */
void esp8266_Print(char *data, int size);
