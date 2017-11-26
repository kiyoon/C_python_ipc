#!/usr/bin/env python
# http://weifan-tmm.blogspot.kr/2015/07/a-simple-turorial-for-python-c-inter.html
import sysv_ipc
import numpy as np
import struct

BUFF_SIZE = 16

msg_string = "sample string\0"
msg_double1 = 1234.56789
msg_double2 = 9876.12345
msg_npy = np.arange(BUFF_SIZE, dtype=np.uint8).reshape((2,BUFF_SIZE//2))
msg_npy_half = np.arange(BUFF_SIZE//2, dtype=np.uint8).reshape((2,BUFF_SIZE//4))

try:
    mq = sysv_ipc.MessageQueue(1234, sysv_ipc.IPC_CREAT)

    # string transmission
    mq.send(msg_string, True, type=1)

    # Two double transmission
    bytearray1 = str(struct.pack("d", msg_double1))
    bytearray2 = str(struct.pack("d", msg_double2))
    mq.send(bytearray1 + bytearray2, True, type=1)

    # numpy array transmission
    mq.send(msg_npy.tobytes(order='C'), True, type=1)

    # one double one numpy transmission
    bytearray1 = str(struct.pack("d", msg_double1))
    mq.send(bytearray1 + msg_npy_half.tobytes(order='C'), True, type=1)


except sysv_ipc.ExistentialError:
    print "ERROR: message queue creation failed"


