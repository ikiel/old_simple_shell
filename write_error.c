#include "shell.h"

/**
 * write_error - write error message to stderr
 * @args: parameters struct containing info about the command and program
 * @msg: error message to print
 *
 */

void write_error(arg_t *args, char *msg)
{
	char errBuffer[1024] = {0};
	char *writeHead = errBuffer, *bufPtr = errBuffer;

	_strcpy(writeHead, args->argv[0]);
	writeHead = bufPtr + _strlen(bufPtr);
	_strcpy(writeHead, ": ");
	writeHead = bufPtr + _strlen(bufPtr);
	_strcpy(writeHead, get_number(args->lineCount));
	writeHead = bufPtr + _strlen(bufPtr);
	_strcpy(writeHead, ": ");
	writeHead = bufPtr + _strlen(bufPtr);
	_strcpy(writeHead, args->params[0]);
	writeHead = bufPtr + _strlen(bufPtr);
	_strcpy(writeHead, ": ");
	writeHead = bufPtr + _strlen(bufPtr);
	_strcpy(writeHead, msg);
	writeHead = bufPtr + _strlen(bufPtr);

	write(STDERR_FILENO, errBuffer, _strlen(bufPtr));
}
