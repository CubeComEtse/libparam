/*
 * parser.c
 *
 * Created: 2020/04/01 13:09:07
 *  Author: Kolijn
 */ 
 
#include "parser.h"
#include <string.h>


void parse_commands(char * commands) {
    // Split command by comma
    char s[2] = ",";
    char *command;

    command = strtok(commands, s);

    char needle[2] = "=";
    while (command != NULL) {
        // parse spi commands
        if (strstr(command, "spi.") != NULL) {
            parse_spi_commands(command);
        }

        if (strstr(command, "i2c.") != NULL) {
            parse_i2c_commands(command);
        }
        // Get the next token
        command = strtok(commands, s);
    }
}

/**
 * \brief Parse and execute any spi command. Commands should be in the form 
 *        spi.config, or spi.write=0x50
 * 
 * \param command a string starting with "spi", and with a null terminator
 * 
 * \return void
 */
void parse_spi_commands(const char *command)
{
    // Assume command starts with spi., so advance the pointer
    const char *startFrom = &command[4];
    const char *subCommand;

    //Config command
    if (strstr(startFrom, "config") != NULL){
        subCommand = &startFrom[6];
        // If there is nothing following the config string, just echo the current config
        if (subCommand[0] != '.') {
            return;
        }
    }

    if (strstr(startFrom, "read") != NULL) {
    }
}

/**
 * \brief 
 * 
 * \param command
 * 
 * \return void
 */
void parse_i2c_commands(const char *command)
{

}
