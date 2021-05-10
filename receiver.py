#!/usr/bin/env python3
# http://weifan-tmm.blogspot.kr/2015/07/a-simple-turorial-for-python-c-inter.html
import sysv_ipc
import numpy as np
import struct

BUFF_SIZE = 16

from type_definitions import *
SIZEOF_FLOAT = 8

try:
    mq = sysv_ipc.MessageQueue(1234, sysv_ipc.IPC_CREAT)

    while True:
        message, mtype = mq.receive()
        print("*** New message received ***")
        print(f"Raw message: {message}")
        if mtype == TYPE_STRING:
            str_message = message.decode()
            print(f"Interpret as string: {str_message}")
        elif mtype == TYPE_TWODOUBLES:
            two_doubles = struct.unpack("dd", message)
            print(f"Interpret as two doubles: {two_doubles}")
        elif mtype == TYPE_NUMPY:
            numpy_message = np.frombuffer(message, dtype=np.int8)
            print(f"Interpret as numpy: {numpy_message}")
        elif mtype == TYPE_DOUBLEANDNUMPY:
            one_double = struct.unpack("d", message[:SIZEOF_FLOAT])[0]
            numpy_message = np.frombuffer(message[SIZEOF_FLOAT:], dtype=np.int8)
            print(f"Interpret as double and numpy: {one_double}, {numpy_message}")

except sysv_ipc.ExistentialError:
    print("ERROR: message queue creation failed")


