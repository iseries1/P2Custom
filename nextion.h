/**
 * @file nextion.h
 * @brief Interface to Nextion display
 * @author Michael Burmeister
 * @date December 21, 2017
 * @version 1.0
 * 
*/

/**
 * @brief Open connection to display panel
 * @param rx Receive pin
 * @param tx Transmit pin
 * @param baud serial transmit/receive speed
 * @return open status
 */
int Nextion_open(int rx, int tx, int baud) __fromfile("libnextion/nextion.c");

/**
 * @brief Send Nextion command to panel
 * @param c command string
 */
void Nextion_cmd(char *c);

/**
 * @brief Set Object Property Value
 * @param obj object varable
 * @param prop property to set
 * @param val text value to set property to
 */
void Nextion_setProperty(char *obj, char *prop, char *val);

/**
 * @brief get Nextion display error value
 * @return error
 */
int Nextion_error(void);

/**
 * @brief get Nextion return event number
 * @return 0 - no event
 */
short Nextion_event(void);

/**
 * @brief get Nextion serial number
 * @return character string value
 */
char *Nextion_serialno(void);

/**
 * @brief build color value 565
 * @param blue 0 - 31
 * @param green 0 - 63
 * @param red 0 - 31
 * @return color value
 */
int Nextion_color(short blue, short green, short red);

/**
 * @brief get page number
 * @return page number
 */
int Nextion_page(void);

/**
 * @brief set Nextion Page number
 * @param page number zero based
 */
void Nextion_setpage(int page);

/**
 * @brief clear screen
 * @param color value 565
 */
void Nextion_cls(int color);

/**
 *
 * @brief get numeric value from panel
 * @return integer value
 */
int Nextion_getnumeric(void);

/**
 * @brief get text value from panel
 * @return Character string
 */
char *Nextion_gettext(void);

/**
 * @brief get touch event location
 * @param x pointer to x value
 * @param y pointer to y value
 * @return touch type 0 - press 1 - release
 */
int Nextion_touchxy(short *x, short *y);

/**
 * @brief set text value for text object
 * @param var text object variable
 * @param val text string to set
 */ 
void Nextion_settext(char *var, char *val);

/**
 * @brief set numeric value
 * @param var numeric object to set
 * @param val numeric value to set
 */
void Nextion_setnumeric(char *var, int val);

/**
 * @brief set baud rate for panel
 * @param baud baud rate value
 */
void Nextion_setbaud(int baud);

/**
 * @brief close connection to panel
 */
void Nextion_close(void);

/**
 * @brief put panel to sleep
 * @param t seconds to sleep
 */
void Nextion_setsleep(int t);

/**
 * @brief set brightness level of panel
 * @param b brightness level 0 - 100
 */
void Nextion_setbrightness(int b);

/**
 * @brief get object touch event
 * @param page value
 * @param id object id
 * @return touch value 0 - down, 1 - up
 */
int Nextion_gettouch(short *page, short *id);

/**
 * @brief enable/disable page touch events
 * @param events 0 - disable, 1 - enable
 */
void Nextion_touch(int events);

/**
 * @brief send string to display
 * @param x x coordinate
 * @param y y coordinate
 * @param w width of the defined area
 * @param h height of the defined area
 * @param f font resource number
 * @param pco foreground color value
 * @param bco background color value
 * @param xcen position of text 0-left, 1-center, 2-right
 * @param ycen position of text 0-top, 1-center, 3-bottom
 * @param sta background fill 0-crop, 1-solid, 2-image, 3-none
 * @param text data to display
 */
void Nextion_xstr(short x, short y, short w, short h, char f, int pco, int bco, char xcen, char ycen, char sta, char *text);

/**
 * @brief fill area with a color
 * @param x position
 * @param y position
 * @param width of area
 * @param height of area
 * @param color of area
 */
void Nextion_fill(short x, short y, short width, short height, int color);

/**
 * @brief draw line
 * @param x position
 * @param y position
 * @param x1 position
 * @param y1 position
 * @param color value
 */
void Nextion_line(short x, short y, short x1, short y1, int color);

/**
 * @brief draw circle
 * @param x position
 * @param y position
 * @param radius
 * @param color value
 */
void Nextion_circle(short x, short y, short radius, int color);

/**
 * @brief draw filled circle
 * @param x position
 * @param y position
 * @param radius
 * @param color value
 */
void Nextion_fillcircle(short x, short y, short radius, int color);

/**
 * @brief send click event 0/1 up/down
 * @param item item name to click
 * @param value 0 or 1 for up or down click
 */
void Nextion_click(char *item, char value);

/**
 * @brief set date/time on display
 * @param i unix time value
 */
void Nextion_settime(long i);

/**
 * @brief debug output
 */
void Nextion_debug(void);
