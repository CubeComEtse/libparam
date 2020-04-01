/*
 * parser.h
 *
 * Created: 2020/04/01 13:09:25
 *  Author: Kolijn
 */ 


#ifndef PARSER_H_
#define PARSER_H_

void parse_commands(char * commands);

void parse_spi_commands(const char *command);
void parse_i2c_commands(const char *command);

#endif /* PARSER_H_ */