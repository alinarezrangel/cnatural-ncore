/* ****************************************************
**************************
*** NCore Source Code. See the LICENSE.txt file for
*** more info.
*** ** Core of the NCore IPC system.

Copyright 2016 Alejandro Linarez Rangel

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
**************************
**************************************************** */

#ifndef _NCORE_IPCAPI_H_
#define _NCORE_IPCAPI_H_

#include "wrap_os/types.h"
#include "wrap_os/named_pipes.h"

#include "error.h"

/**
* @file ipcapi.h
* The main file for the IPC (Inter Process Comunication)
* system and API of Natural.
*/

/**
* @brief The current NCore IPC version.
* The version is a unsigned long int of the form:
* (YYYY)(M)(N)(P)UL, for example: the first version was
* released in the 2016, and it's version is 2016001UL,
* the second release was on the 2017: 2017001UL, and the
* third release in the 2017: 2017002UL.
*/
#define NCORE_IPC_VERSION 2016001UL

NCORE_DECLARATION_BEGIN

typedef unsigned int NCoreIPCConnectionID_t;
typedef unsigned long int NCoreIPCConnectionVersion_t;

/**
* @brief Is a NCore IPC connection.
*
* Is NOT Copyable.
*/
struct NCoreIPCConnection
{
	NCoreOSNamedPipe_t* pipe; /* !PUBLIC! */

	NCoreBool_t isServer; /* !PUBLIC! */
	NCoreIPCConnectionID_t id; /* !PUBLIC! */
	NCoreIPCConnectionVersion_t version; /* !PUBLIC! */
};
typedef struct NCoreIPCConnection NCoreIPCConnection_t;

/**
* @brief Creates a new connection.
* By default, is not connected to the server.
* @param connection Connection to create.
* @return Error (if any)
*/
NCoreError_t ncore_ipc_connection_new(
	NCoreIPCConnection_t** connection
);

/**
* @brief Destroys a connection.
* If the connection is open, returns NCORE_ERROR_OPEN.
* @param connection Connection to be destroyed.
* @return Error (if any)
*/
NCoreError_t ncore_ipc_connection_destroy(
	NCoreIPCConnection_t** connection
);

/**
* @brief Opens a pipe and assigns this connection to this pipe.
* Opens as client.
* @param connection Connection to open.
* @param pipename Name of the pipe to be opened.
* @return Error (if any)
*/
NCoreError_t ncore_ipc_connection_open(
	NCoreIPCConnection_t* connection,
	const NCoreString_t pipename
);

/**
* @brief Creates a pipe and assigns this connection to this pipe.
* Opens as server.
* @param connection Connection to open.
* @param pipename Name of the pipe to be created.
* @return Error (if any)
*/
NCoreError_t ncore_ipc_connection_create(
	NCoreIPCConnection_t* connection,
	const NCoreString_t pipename
);

/**
* @brief Closes this connection
* @param connection Connection to close.
* @return Error (if any)
*/
NCoreError_t ncore_ipc_connection_close(NCoreIPCConnection_t* connection);

/**
* @brief Reads from a connection
* @param connection Connection to open.
* @param buffer Buffer of at least NCORE_IOFCN_READ_BLOCK_SIZE bytes len
* @return Error (if any)
*/
NCoreError_t ncore_ipc_connection_receive(
	NCoreIPCConnection_t* connection,
	NCoreString_t buffer
);

/**
* @brief Reads from a connection
* @param connection Connection to open.
* @param buffer Buffer of at least bflen bytes len
* @param bflen Number of bytes to read
* @return Error (if any)
*/
NCoreError_t ncore_ipc_connection_receive_fix(
	NCoreIPCConnection_t* connection,
	NCoreString_t buffer,
	size_t bflen
);

/**
* @brief Writes from a connection
* @param connection Connection to open.
* @param buffer Buffer of at least NCORE_IOFCN_READ_BLOCK_SIZE bytes len
* @return Error (if any)
*/
NCoreError_t ncore_ipc_connection_send(
	NCoreIPCConnection_t* connection,
	NCoreString_t buffer
);

/**
* @brief Reads from a connection
* @param connection Connection to open.
* @param buffer Buffer of at least bflen bytes len
* @param bflen Number of bytes to read
* @return Error (if any)
*/
NCoreError_t ncore_ipc_connection_send_fix(
	NCoreIPCConnection_t* connection,
	NCoreString_t buffer,
	size_t bflen
);

NCORE_DECLARATION_END

#endif /* ~_NCORE_IPCAPI_H__ */
