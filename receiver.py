#!/usr/bin/env python
# http://weifan-tmm.blogspot.kr/2015/07/a-simple-turorial-for-python-c-inter.html
import sysv_ipc
import numpy as np
import struct

BUFF_SIZE = 16


try:
    mq = sysv_ipc.MessageQueue(1234, sysv_ipc.IPC_CREAT)

    while True:
        message = mq.receive()
        print message

except sysv_ipc.ExistentialError:
    print "ERROR: message queue creation failed"


