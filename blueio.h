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
 * @param number of bytes sent
 */
int Blueio_Request(char *request);

/**
 * @brief Receive data
 * @param buffer to hold data
 * @return number of characters
 */
int Blueio_Receive(char *buffer);

/**
 * @brief Check if receive is ready
 * @return ready 0 - not done, 1 - done
 */
int Blueio_Ready(void);

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
 * @return total
 */
int Blueio_Add(char *note);

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
int Blueio_Get(char *data, int remove);

