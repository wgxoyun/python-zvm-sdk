/**
 * IBM (C) Copyright 2017 Apache License Version 2.0
 * http://www.apache.org/licenses/LICENSE-2.0
 */
#include "smSocket.h"
#include "vmapiVirtual.h"
#include "smapiTableParser.h"
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>

#define PARSER_TABLE_NAME     Virtual_Network_LAN_Delete_Layout
#define OUTPUT_STRUCTURE_NAME vmApiVirtualNetworkLanDeleteOutput

/**
 * Virtual_Network_Lan_Delete SMAPI interface
 */
int smVirtual_Network_LAN_Delete(struct _vmApiInternalContext* vmapiContextP, char * userid, int passwordLength, char * password,
        char * targetIdentifier, char * lanName, char * lanOwner, vmApiVirtualNetworkLanDeleteOutput ** outData) {
    const char * const functionName = "Virtual_Network_LAN_Delete";
    tableParserParms parserParms;
    int tempSize;
    char * cursor;
    char * stringCursor;  // Used for outData string area pointer
    int arrayCount;
    int totalStringSize;
    int rc;
    int sockDesc;
    int requestId;

    int inputSize = 4 + 4 + strlen(functionName) + 4 + strlen(userid) + 4
            + passwordLength + 4 + strlen(targetIdentifier) + 4 + strlen(
            lanName) + 4 + strlen(lanOwner);
    char * inputP = 0;
    char * smapiOutputP = 0;
    char line[LINESIZE];
    int i;

    // Build SMAPI input parameter buffer
    if (0 == (inputP = malloc(inputSize))) {
        return MEMORY_ERROR;
    }
    cursor = inputP;
    PUT_INT(inputSize - 4, cursor);

    tempSize = strlen(functionName);
    PUT_INT(tempSize, cursor);
    memcpy(cursor, functionName, tempSize);
    cursor += tempSize;

    tempSize = strlen(userid);  // Userid 1..8 or 0..8 chars
    PUT_INT(tempSize, cursor);
    if (tempSize > 0) {
        memcpy(cursor, userid, tempSize);
        cursor += tempSize;
    }

    tempSize = passwordLength;  // Password 1..200 or 0..200 chars
    PUT_INT(tempSize, cursor);
    if (tempSize > 0) {
        memcpy(cursor, password, tempSize);
        cursor += tempSize;
    }

    tempSize = strlen(targetIdentifier);  // Target identifier 1..8
    PUT_INT(tempSize, cursor);
    memcpy(cursor, targetIdentifier, tempSize);
    cursor += tempSize;

    tempSize = strlen(lanName);  // Lan name 1..8 chars
    PUT_INT(tempSize, cursor);
    memcpy(cursor, lanName, tempSize);
    cursor += tempSize;

    tempSize = strlen(lanOwner);  // Lan owner 1..8 chars
    PUT_INT(tempSize, cursor);
    memcpy(cursor, lanOwner, tempSize);
    cursor += tempSize;

    // This routine will send SMAPI the input, delete the input storage
    // and call the table parser to set the output in outData
    rc = getAndParseSmapiBuffer(vmapiContextP, &inputP, inputSize,
            PARSER_TABLE_NAME,  // Integer table
            TO_STRING(PARSER_TABLE_NAME),  // String name of the table
            (char * *) outData);
    return rc;
}