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

#include "ipcapi.h"

NCoreError_t ncore_ipc_connection_new(
	NCoreIPCConnection_t** connection
)
{
	*connection = malloc(sizeof(NCoreIPCConnection_t));

	if(*connection == NULL)
		return NCORE_ERROR_BADALLOC;

	(*connection)->pipe = NULL;
	(*connection)->isServer = FALSE;
	(*connection)->id = 0;
	(*connection)->version = NCORE_IPC_VERSION;

	NCORE_TRY(ncore_os_namedpipe_new(&(*connection)->pipe))
	{
		return ncore_errno;
	}

	return NCORE_NO_ERROR;
}

NCoreError_t ncore_ipc_connection_destroy(
	NCoreIPCConnection_t** connection
)
{
	if((*connection)->pipe != NULL)
	{
		NCORE_TRY(ncore_os_namedpipe_destroy(&(*connection)->pipe))
		{
			return ncore_errno;
		}
	}

	free(*connection);
	*connection = NULL;

	return NCORE_NO_ERROR;
}

NCoreError_t ncore_ipc_connection_open(
	NCoreIPCConnection_t* connection,
	const NCoreString_t pipename
)
{
	NCORE_TRY(ncore_os_namedpipe_open(connection->pipe, pipename))
	{
		return ncore_errno;
	}

	connection->isServer = FALSE;

	return NCORE_NO_ERROR;
}

NCoreError_t ncore_ipc_connection_create(
	NCoreIPCConnection_t* connection,
	const NCoreString_t pipename
)
{
	NCORE_TRY(ncore_os_namedpipe_create(connection->pipe, pipename))
	{
		return ncore_errno;
	}

	connection->isServer = TRUE;

	return NCORE_NO_ERROR;
}

NCoreError_t ncore_ipc_connection_close(NCoreIPCConnection_t* connection)
{
	if(connection->isServer)
	{
		NCORE_TRY(ncore_os_namedpipe_release(connection->pipe))
		{
			return ncore_errno;
		}
	}
	else
	{
		NCORE_TRY(ncore_os_namedpipe_close(connection->pipe))
		{
			return ncore_errno;
		}
	}

	return NCORE_NO_ERROR;
}

NCoreError_t ncore_ipc_connection_receive(
	NCoreIPCConnection_t* connection,
	NCoreString_t buffer
)
{
	NCORE_TRY(ncore_os_namedpipe_receive(connection->pipe, buffer))
	{
		return ncore_errno;
	}

	return NCORE_NO_ERROR;
}

NCoreError_t ncore_ipc_connection_receive_fix(
	NCoreIPCConnection_t* connection,
	NCoreString_t buffer,
	size_t bflen
)
{
	NCORE_TRY(ncore_os_namedpipe_receive_fix(connection->pipe, buffer, bflen))
	{
		return ncore_errno;
	}

	return NCORE_NO_ERROR;
}

NCoreError_t ncore_ipc_connection_send(
	NCoreIPCConnection_t* connection,
	NCoreString_t buffer
)
{
	NCORE_TRY(ncore_os_namedpipe_send(connection->pipe, buffer))
	{
		return ncore_errno;
	}

	return NCORE_NO_ERROR;
}

NCoreError_t ncore_ipc_connection_send_fix(
	NCoreIPCConnection_t* connection,
	NCoreString_t buffer,
	size_t bflen
)
{
	NCORE_TRY(ncore_os_namedpipe_send_fix(connection->pipe, buffer, bflen))
	{
		return ncore_errno;
	}

	return NCORE_NO_ERROR;
}
