/**
 * @file blueio.h
 * @brief Driver for Blue Notecard
 * @author Michael Burmeister
 * @version 1.0
 * @date February 8, 2023
 */

/**
 * @brief Initialize Blueio driver
 * @param receive pin
 * @param transmit pin
 * @return unit
 */
int Blueio_Init(int receive, int transmit) __fromfile("libblueio/blueio.c");

/**
 * @brief Send command
 * @param request to send
 */
int Blueio_Request(char *request);

/**
 * @brief Receive data
 * @param buffer to hold data
 * @return number of characters
 */
int Blueio_Receive(char *buffer);

/**
 * @brief Sync with cloud
 */
void Blueio_Sync(void);

/**
 * @brief Status of Notecard
 * @return status 0 - ready, 1 - syncing
 */
int Blueio_Status(void);

/**
 * @brief Notecard version
 * @return version number
 */
int Blueio_Version(void);

/**
 * @brief Add Note
 * @param note json data
 * @param file to use or NULL
 * @return total
 */
int Blueio_Add(char *note, char *file);

/**
 * @brief Add Note with Payload
 * @param payload to add base64
 * @return total
*/
int Blueio_AddPayload(char *payload);

/**
 * @brief Check for note file
 * @return total number of files
 */
int Blueio_Check(void);

/**
 * @brief Get notecard data
 * @param data buffer to hold json data
 * @param remove json data 0 - keep, 1 - remove
 * @return number of bytes return
 */
int Blueio_GetData(char *data, int remove);

/**
 * @brief Set Atten Pin
 * @param mode 1 -> arm, 2 -> sleep, 3 -> disarm
 * @param time
 */
void Blueio_SetAttn(int mode, int time);

/**
 * @brief Get voltage
 * @return voltage
 */
float Blueio_GetVoltage(void);

/**
 * @brief Get temperature
 * @return temp value in celsius
 */
float Blueio_GetTemperature(void);

/**
 * @brief Get current unix time
 * @return unix time
 */
int Blueio_GetTime(void);
