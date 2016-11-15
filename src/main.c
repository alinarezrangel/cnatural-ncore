/* ****************************************************
**************************
*** NCore Source Code. See the LICENSE.txt file for
*** more info.
*** **
*** **
*** **
*** **
*** **
**************************
**************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ipcapi.h"

int main(int argc, char** argv)
{
	NCoreBool_t isServer = FALSE;
	NCoreIPCConnection_t* connection = NULL;
	NCoreChar_t buffer[20];

	memset(buffer, '\0', sizeof(NCoreChar_t) * 19);

	isServer = !strcmp("server", argv[1]);

	NCORE_TRY(ncore_ipc_connection_new(&connection))
	{
		fprintf(stderr, "Error creating the connection: %d\n", ncore_errno);
		exit(EXIT_FAILURE);
	}

	if(isServer)
	{
		NCORE_TRY(ncore_ipc_connection_create(connection, NCORE_STR("./example.pipe.fifo")))
		{
			fprintf(stderr, "Error opening the rsc: %d\n", ncore_errno);

			NCORE_TRY(ncore_ipc_connection_destroy(&connection))
			{
				fprintf(stderr, "Error destroying the connection: %d\n", ncore_errno);
			}
			exit(EXIT_FAILURE);
		}

		printf("Enter anything to start to send the data\n");
		scanf("%s", buffer);

		NCORE_TRY(ncore_ipc_connection_send_fix(connection, NCORE_STR("Hola    "), 4))
		{
			fprintf(stderr, "Error sending the data: %d\n", ncore_errno);
		}

		printf("Data sended, waiting...\n");
		scanf("%s", buffer);
	}
	else
	{
		NCORE_TRY(ncore_ipc_connection_open(connection, NCORE_STR("./example.pipe.fifo")))
		{
			fprintf(stderr, "Error opening the rsc: %d\n", ncore_errno);

			NCORE_TRY(ncore_ipc_connection_destroy(&connection))
			{
				fprintf(stderr, "Error destroying the connection: %d\n", ncore_errno);
			}
			exit(EXIT_FAILURE);
		}

		printf("Listening...\n");
		printf("Enter anything to start to receive the data\n");
		scanf("%s", buffer);

		NCORE_TRY(ncore_ipc_connection_receive_fix(connection, buffer, 4))
		{
			fprintf(stderr, "Error receiving the data: %d\n", ncore_errno);
		}

		printf("Data receiver: %s\nEnding\n", buffer);
	}

	NCORE_TRY(ncore_ipc_connection_close(connection))
	{
		fprintf(stderr, "Error closing the connection: %d\n", ncore_errno);
		exit(EXIT_FAILURE);
	}

	NCORE_TRY(ncore_ipc_connection_destroy(&connection))
	{
		fprintf(stderr, "Error destroying the connection: %d\n", ncore_errno);
		exit(EXIT_FAILURE);
	}

	exit(EXIT_SUCCESS);
}
