////////////////////////// main_sender.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define  BUFF_SIZE   1024

typedef struct {
	long  data_type;
	char  data_buff[BUFF_SIZE];
} t_data;

int main( void)
{
	int      msqid;
	t_data   data;

	if ( -1 == ( msqid = msgget( (key_t)1234, IPC_CREAT | 0666)))
	{
		perror( "msgget() failed");
		exit( 1);
	}

	data.data_type = 1;   // data_type:  1, 2, 3
	sprintf( data.data_buff, "string message transmission");

	if ( -1 == msgsnd( msqid, &data, sizeof( t_data) - sizeof( long), 0))
	{
		perror( "msgsnd() failed");
		exit( 1);
	}
}
