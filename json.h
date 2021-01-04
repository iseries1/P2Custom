/**
 * @file json.h
 * @brief Convert Json data to values
 * @author Michael Burmeister
 * @date December 29, 2018
 * @version 1.5
 * 
*/

/**
 * @brief init json converter
 * @param json data
 */
void json_init(char *json) __fromfile("libJSON/json.c");

/**
 * @brief find element
 * @param element full name
 * @return string value
 */
char *json_find(char *element) __fromfile("libJSON/json.c");

/**
 * @brief put string element and value
 * @param item Item name
 * @param value Item value
 */
void json_putStr(char *item, char *value) __fromfile("libJSON/json.c");

/**
 * @brief put integer value
 * @param item Item name
 * @param value decimal value
 */
void json_putDec(char *item, char *value) __fromfile("libJSON/json.c");

/**
 * @brief put array of objects
 * @param item object array or NULL for end
 */
void json_putArray(char* item) __fromfile("libJSON/json.c");

/**
 * @brief put object values
 * @param item object name NULL for end of object
 */
void json_putObject(char* item) __fromfile("libJSON/json.c");

/**
 * @brief put more items
 */
void json_putMore(void) __fromfile("libJSON/json.c");

