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
#include "stdio.h"
#include "stdlib.h"
#include "naturalserver/ncore/ipcapi.h"

int main(void)
{
	NCoreServerIPC_t* server;
	NCoreConstString_t str = NCORE_CMD_PING_TO_PONG; // Command #1: PING TO PONG
	NCoreString_t resp = NULL, null_term_str = NULL;
	NCoreSize_t resp_size = 0;

	if(ncore_server_ipc_new(&server, NCORE_IS_CLIENT, NCORE_DEFAULT_SERVER) < 0)
	{
		perror("Error connecting to server");
		exit(EXIT_FAILURE);
	}

	printf("Sending the PING TO PONG command...\n");

	if(ncore_server_ipc_send(server, str, strlen(str)) < 0)
	{
		perror("Error sending the command");
		ncore_server_ipc_destroy(&server);
		exit(EXIT_FAILURE);
	}

	ncore_server_ipc_wait_for_response(server);

	if(ncore_server_ipc_receive(server, &resp, &resp_size) < 0)
	{
		perror("Error receiving the response");
		ncore_server_ipc_destroy(&server);
		exit(EXIT_FAILURE);
	}

	null_term_str = ncore_wrap_string(&resp, &resp_size);
	if(null_term_str == NULL)
	{
		perror("Error allocating the response");
		ncore_server_ipc_destroy(&server);
		exit(EXIT_FAILURE);
	}

	printf("Received %s from the server\n", null_term_str);

	free(null_term_str);
	free(resp);
	ncore_server_ipc_destroy(&server);

	exit(EXIT_SUCCESS);
}
```

## License ##

See the [LICENSE file](LICENSE.txt "NCore LICENSE")
