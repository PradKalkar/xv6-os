//constants used in console.c

#define UP_ARROW 226
#define DOWN_ARROW 227
#define LEFT_ARROW 228
#define RIGHT_ARROW 229

#define BACKSPACE 0x100
#define CRTPORT 0x3d4

#define INPUT_BUF 128
#define MAX_HISTORY 16

#include "types.h"

/*
  this method eareases the current line from screen
*/
void
eraseCurrentLineOnScreen(void);

/*
  this method copies the chars currently on display (and on Input.buf) to oldBuf and save its length on current_history_viewed.lengthOld
*/
void
copyCharsToBeMovedToOldBuffer(void);


/*
  this method earase all the content of the current command on the inputbuf
*/
void
eraseContentOnInputBuffer();

/*
  this method will print the given buf on the screen
*/
void
copyBufferToScreen(char * bufToPrintOnScreen, uint length);

/*
  this method will copy the given buf to Input.buf
  will set the input.e and input.rightmost
  assumes input.r=input.w=input.rightmost=input.e                                                                   
*/
void
copyBufferToInputBuffer(char * bufToSaveInInput, uint length);

/*
  this method copies the current command in the input.buf to the saved history 
  @param length - length of command to be saved                                                                                 //GILAD QUES who should call this??
*/
void
saveCommandInHistory();

/*
  this is the function that gets called by the sys_history and writes the requested command history in the buffer
*/
int getCmdFromHistory(char *buffer, int historyId);