/*
 * parser.c
 *
 * Created: 2020/04/01 13:09:07
 *  Author: Kolijn
 */

#include "parser.h"
#include "bsp.h"
#include "usart_buffer.h"
#include "obc_controller_rev_A.h"
#include "asf.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "spi_manager.h"


// Local variables
static USART_data_t* telemetryUsartBuffer;
static uint8_t endChar = '\n';

static uint8_t commandBuffer[128];
static uint16_t bufPointer;
static bool hasMessage;

static uint8_t spi_tx_buffer[120];
static uint8_t spi_rx_buffer[120];

/**
 * \brief Initialize all pointers, buffers, etc.
 *
 *
 * \return void
 */
void PARSER_vInit(void)
{
    telemetryUsartBuffer = BSP_psGetTelemetryDriver();
    PARSER_vClearMessage();

    USART_TXBuffer_PutByte(telemetryUsartBuffer, 'a');
    USART_TXBuffer_PutByte(telemetryUsartBuffer, 'b');
    USART_TXBuffer_PutByte(telemetryUsartBuffer, 'c');
}

/**
 * \brief Called in an update loop to check for new characters received
 *
 *
 * \return void
 */
void PARSER_vProcess(void)
{
    if (!USART_RXBuffer_IsEmpty(telemetryUsartBuffer)) {
        commandBuffer[bufPointer] = USART_RXBuffer_GetByte(telemetryUsartBuffer);
        if (commandBuffer[bufPointer] == endChar) {
            hasMessage = true;
        }

        bufPointer += 1;
        // For string handling
        commandBuffer[bufPointer] = 0;
    }
}

/**
 * \brief Checks if there is a message, returning true if there is
 *
 * \return bool
 */
bool PARSER_bHasMessage(void)
{
    return hasMessage;
}

/**
 * \brief Clears the message after it has been processed
 *
 * \param
 *
 * \return void
 */
void PARSER_vClearMessage(void)
{
    commandBuffer[0] = 0;
    bufPointer = 0;
    hasMessage = false;
}

/**
 * \brief Parse and execute any commands in the buffer
 *
 * \return void
 */
void PARSER_vParseCommands(void)
{
    if (!PARSER_bHasMessage()) {
        return;
    }
    // Split command by comma
    char s[2] = ",";
    char *command;

    command = strtok((char*) commandBuffer, s);

    while (command != NULL) {
        // parse spi commands
        if (strstr(command, "spi.") != NULL) {
            PARSER_vParseSPICommand(command);
        }

        if (strstr(command, "i2c.") != NULL) {
            PARSER_vParseI2CCommand(command);
        }
        // Get the next token
        command = strtok(NULL, s);
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
void PARSER_vParseSPICommand(const char *command)
{
    /*
    The parse will string match anything after the first 'spi.' section. If 
    there is an '=' in the command the argument will be found first, because 
    many commands use it.
    */

    // Assume command starts with spi., so advance the pointer
    const char *startFrom = &command[4];
    const char *subCommand;
    
    // Parse everything after the equals sign before the rest, makes the logic easier
    bool hasEquals = false;
    const char *afterEquals = memchr(command, '=', strlen(command));
    if (afterEquals != NULL) {
        hasEquals = true;
        afterEquals+=1;
    }

    //Config command
    if (strstr(startFrom, "config") != NULL) {
        subCommand = &startFrom[6];
        // Nothing after config, just echo the current config
        if (subCommand[0] != '.') {
            
            return;
        }
        // Nasty Pointer arithmetic
        subCommand+=1;

        // Set or get the speed
        if (strstr(subCommand, "speed") == subCommand) {
            if (hasEquals) {
                uint32_t newSpeed = atoi(afterEquals);
                SPI_MANAGER_vSetSpeed(newSpeed);
            }
            else {

            }
        }

        // Set or get the CS pin
        if (strstr(subCommand, "cs") == subCommand) {
            if (hasEquals) {
                uint8_t newPin = atoi(afterEquals);
                SPI_MANAGER_vSetCSLine(newPin);
            }
            else {

            }
        }

        // Set or get the SPI Mode
        if (strstr(subCommand, "mode") == subCommand) {
            if (hasEquals) {
                uint8_t newMode = atoi(afterEquals);
                SPI_MANAGER_vSetMode(newMode);
            }
            else {

            }
        }
    }
    if (strstr(startFrom, "start") != NULL) {
        SPI_MANGER_vSelect();
    }

    if (strstr(startFrom, "read") != NULL) {

    }

    if (strstr(startFrom, "write") != NULL && hasEquals) {
        // There are two ways to send data, either as string, or as space-separated bytes
        if (afterEquals[0] == '"') {
            // Set starting position
            uint16_t start_index = 1;

            //Find ending position
            char* final_quote = strstr(&afterEquals[start_index], "\"");
            if (final_quote == NULL) {
                return;
            }
            
            uint16_t length = final_quote - &afterEquals[start_index];
            memcpy(spi_tx_buffer, &afterEquals[start_index], length);

            SPI_MANAGER_vExchangeBuffers(spi_tx_buffer, spi_rx_buffer, length);
        }
        else {
            //Parse two bytes and a space
        }
        
    }

    if (strstr(startFrom, "stop") != NULL) {
        SPI_MANAGER_vDeselect();
    }
}

/**
 * \brief
 *
 * \param command
 *
 * \return void
 */
void PARSER_vParseI2CCommand(const char *command)
{

}
