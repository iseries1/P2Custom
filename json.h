/**
 * @file json.h
 * @brief Convert Json data to values
 * @author Michael Burmeister
 * @date December 29, 2018
 * @version 1.6
 * 
*/

/**
 * @brief init json converter/writer
 * @param json data
 */
void json_init(char *json) __fromfile("libJSON/json.c");

/**
 * @brief find element
 * @param element full name
 * @return string value
 */
char *json_find(char *element);

/**
 * @brief put string element and value
 * @param item Item name
 * @param value Item value
 * @return length of json
 */
int json_putStr(char *item, char *value);

/**
 * @brief put integer value
 * @param item Item name
 * @param value decimal value
 * @return length of json
 */
int json_putDec(char *item, char *value);

/**
 * @brief put array of objects (start of array)
 * Provide name of array to start the array and
 * then write each item in the array using that
 * function and then end the array here with no
 * item name
 * @param item object array or NULL for end
 * @return length of json
 */
int json_putArray(char* item);

/**
 * @brief put object values
 * @param item object name NULL for end of object
 * @return length of json
 */
int json_putObject(char* item);

/**
 * @brief put more items in the array
 * @return length of json
 */
int json_putMore(void);

/**
 * @brief put item only no value use NULL to end array
 * @param item value or data
 * @param length of json
 */
int json_putItem(char* item);

/**
 * @brief put boolean value
 * @param item value
 * @param state 0 - false, 1 - true
 * @return length of json
 */
int json_putBool(char* item, int state);
