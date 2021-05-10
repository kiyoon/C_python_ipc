////////////////////////// main_sender.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define  BUFF_SIZE   16 

#include "type_definitions.h"

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

	// string transmission
	data.data_type = TYPE_STRING;
	sprintf( data.data_buff, "string from C");
	if ( -1 == msgsnd( msqid, &data, sizeof( t_data) - sizeof( long), 0))
	{
		perror( "msgsnd() failed");
		exit( 1);
	}
	printf("string sent: %s\n", data.data_buff);
		
	// two double transmission
	double msg_double1 = 1234.56789;
	double msg_double2 = 9876.12345;
	data.data_type = TYPE_TWODOUBLES;
	memcpy(data.data_buff, &msg_double1, sizeof(double));
	memcpy(data.data_buff+sizeof(double), &msg_double2, sizeof(double));
	if ( -1 == msgsnd( msqid, &data, sizeof( t_data) - sizeof( long), 0))
	{
		perror( "msgsnd() failed");
		exit( 1);
	}
	printf("Two doubles sent: %f, %f\n", msg_double1, msg_double2);

	// array transmission
	char msg_array[BUFF_SIZE];
	int i;
	for (i = 0; i < BUFF_SIZE; i++)
	{
		msg_array[i] = i;
	}

	data.data_type = TYPE_ARRAY;
	memcpy(data.data_buff, msg_array, BUFF_SIZE);
	if ( -1 == msgsnd( msqid, &data, sizeof( t_data) - sizeof( long), 0))
	{
		perror( "msgsnd() failed");
		exit( 1);
	}
	printf("Array sent: ");
	for (i = 0; i < BUFF_SIZE; i++)
	{
		printf("%d ", msg_array[i]);
	}
	printf("\n");

	// one double and an array transmission
	data.data_type = TYPE_DOUBLEANDARRAY;
	memcpy(data.data_buff, &msg_double1, sizeof(double));
	memcpy(data.data_buff+sizeof(double), msg_array, sizeof(double));
	if ( -1 == msgsnd( msqid, &data, sizeof( t_data) - sizeof( long), 0))
	{
		perror( "msgsnd() failed");
		exit( 1);
	}
	printf("One double and one array sent: %f, ", msg_double1);
	for (i = 0; i < BUFF_SIZE/2; i++)
	{
		printf("%d ", msg_array[i]);
	}
	printf("\n");
}
