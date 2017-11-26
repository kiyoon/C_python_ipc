////////////////////////// main_receiver.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define  BUFF_SIZE   16

typedef struct {
	long  data_type;
	//int   data_num;
	unsigned char  data_buff[BUFF_SIZE];
} t_data;

int main( void)
{
	int      msqid;
	t_data   data;
	double   dValue1, dValue2;

	if ( -1 == ( msqid = msgget( (key_t)1234, IPC_CREAT | 0666)))
	{
		perror( "msgget() failed");
		exit( 1);
	}

	printf("Print format: HEX                               - String          - Two doubles\n");
	while( 1 )
	{
		// datatype 0: receive all datatype
		// change datatype to 1 if you want to receive python data
		if ( -1 == msgrcv( msqid, &data, sizeof( t_data) - sizeof( long), 0, 0))
		{
			perror( "msgrcv() failed");
			exit( 1);
		}
		int i;
		for(i = 0; i<BUFF_SIZE; i++)
			printf("%02X ", data.data_buff[i]);
		memcpy(&dValue1, data.data_buff, sizeof(double));
		memcpy(&dValue2, data.data_buff+sizeof(double), sizeof(double));
		printf("- %15s ", data.data_buff);
		printf("- %f, %f\n", dValue1, dValue2);
	}
}
