/*
 * parser.h
 *
 * Created: 2020/04/01 13:09:25
 *  Author: Kolijn
 */ 


#ifndef PARSER_H_
#define PARSER_H_

#include <stdint.h>
#include <string.h>
#include <stdbool.h>

void PARSER_vInit(void);
void PARSER_vProcess(void);

bool PARSER_bHasMessage(void);
void PARSER_vClearMessage(void);

void PARSER_vParseCommands(void);
void PARSER_vParseSPICommand(const char *command);
void PARSER_vParseI2CCommand(const char *command);
#endif /* PARSER_H_ */