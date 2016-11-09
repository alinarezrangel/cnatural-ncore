# NCore - Main Natural Server Program #

Release 0.0.1

NCore listen in a file (a named pipe) for manage the main Natural Server.

The main named pipes (or busses) are:

* `$NATURALPATH/ipc/server/fb`: FrameBuffer (the format is driver-defined).
* `$NATURALPATH/ipc/server/input`*N*: The input device *N*, the *N* is passed
  to the driver as the device fileid.
* `$NATURALPATH/ipc/server/output`*N*: The output device *N*, the *N* is passed
  to the driver as the device fileid.
* `$NATURALPATH/ipc/server/clients/connection`*N*: The client with the PID
  *N*.
* `$NATURALPATH/ipc/server/commander`: The commander device. All commands send
  to this device are executed as NCore internal commands. For example:
  `0 drivers/output/screen/testdriver/bin/driver.so` loads the test driver for
  handle the screen-output.

## C API ##

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ipcapi.h"

int main(int argc, char** argv)
{
	NCoreBool_t isServer = FALSE;
	NCoreIPCConnection_t* connection = NULL;
	char buffer[20];

	memset(buffer, '\0', 19);

	isServer = !strcmp("server", argv[1]);

	NCORE_TRY(ncore_ipc_connection_new(&connection))
	{
		fprintf(stderr, "Error creating the connection: %d\n", ncore_errno);
		exit(EXIT_FAILURE);
	}

	if(isServer)
	{
		NCORE_TRY(ncore_ipc_connection_create(connection, "./example.pipe.fifo"))
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

		NCORE_TRY(ncore_ipc_connection_send_fix(connection, "Hola    ", 4))
		{
			fprintf(stderr, "Error sending the data: %d\n", ncore_errno);
		}

		printf("Data sended, waiting...\n");
		scanf("%s", buffer);
	}
	else
	{
		NCORE_TRY(ncore_ipc_connection_open(connection, "./example.pipe.fifo"))
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
```

## License ##

See the [LICENSE file](LICENSE.txt "NCore LICENSE")
