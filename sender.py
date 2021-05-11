#!/usr/bin/env python3
# http://weifan-tmm.blogspot.kr/2015/07/a-simple-turorial-for-python-c-inter.html
import sysv_ipc
import numpy as np
import struct

BUFF_SIZE = 16

from type_definitions import *

if __name__ == '__main__':
    msg_string = "sample string\0"
    msg_double1 = 1234.56789
    msg_double2 = 9876.12345
    msg_npy = np.arange(BUFF_SIZE, dtype=np.uint8).reshape((2,BUFF_SIZE//2))
    msg_npy_half = np.arange(BUFF_SIZE//2, dtype=np.uint8).reshape((2,BUFF_SIZE//4))
    try:
        mq = sysv_ipc.MessageQueue(1234, sysv_ipc.IPC_CREAT)

        # string transmission
        mq.send(msg_string, True, type=TYPE_STRING)
        print(f"string sent: {msg_string}")

        # Two double transmission
        bytearray1 = struct.pack("d", msg_double1)
        bytearray2 = struct.pack("d", msg_double2)
        mq.send(bytearray1 + bytearray2, True, type=TYPE_TWODOUBLES)
        print(f"two doubles sent: {msg_double1}, {msg_double2}")

        # numpy array transmission
        mq.send(msg_npy.tobytes(order='C'), True, type=TYPE_NUMPY)
        print(f"numpy array sent: {msg_npy}")

        # one double one numpy transmission
        bytearray1 = struct.pack("d", msg_double1)
        mq.send(bytearray1 + msg_npy_half.tobytes(order='C'), True, type=TYPE_DOUBLEANDNUMPY)
        print(f"one double and numpy array sent: {msg_double1}, {msg_npy_half}")


    except sysv_ipc.ExistentialError:
        print("ERROR: message queue creation failed")


