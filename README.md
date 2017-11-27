# C_python_ipc

Author: Kiyoon Kim (yoonkr33@gmail.com, http://kiyoon.kim)  

Description: Message Queue based Interprocess Communication (IPC) between Python and C. There are sender and receiver code for each languages.


## Dependencies

- Python 2.x
- sysv_ipc (python package)


## Usage

Build C programs

`make`

Run receiver. For example, C receiver:

`./receiver`

In a different terminal, execute sender. For example, Python sender with String, double (float64), numpy formats.

`./sender.py`

Watch what happens on the receiver!

## References

http://weifan-tmm.blogspot.kr/2015/09/invoke-floating-point-logic-set-option_4.html  

http://forum.falinux.com/zbxe/index.php?document_srl=420147&mid=C_LIB
