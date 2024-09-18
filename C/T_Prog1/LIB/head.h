#ifndef __HEAD_H__
#define __HEAD_H__

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include <gtk/gtk.h>

extern uint16_t scr;
extern uint8_t num1;
extern uint8_t num2;
extern long answ;
extern uint8_t result;
extern char task[16];
extern char strScore[16];

uint8_t file_overwrite(char *fileName, char *fileText);
uint8_t file_read(char *fileName, char *buffer, uint16_t *score);
uint8_t generate_nums(uint8_t *number1, uint8_t *number2, long *answer, char *buffer);
uint8_t update_score_str_from_num(char *buffer, uint16_t *num);
uint8_t update_score_num_from_str(char *buffer, uint16_t *num);

#endif // __HEAD_H__