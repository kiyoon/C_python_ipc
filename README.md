# C_python_ipc

Author: Kiyoon Kim (yoonkr33@gmail.com, https://kiyoon.kim)  

Description: Message Queue based Interprocess Communication (IPC) between Python and C. There are sender and receiver code for each language.  

The senders will send:  
- string
- two doubles
- one array (or numpy)
- one double and one array (or numpy)

And the receivers receive the byte formatted data and unpack.


## Dependencies

- Python >= 3.6
- sysv_ipc (python package)
- numpy (python package)

For Python 2 support, see the older version: [v0.1](https://github.com/kiyoon/C_python_ipc/tree/v0.1)

## Usage

Build C programs

`make`

Run receiver. For example, C receiver:

`./receiver`

In a different terminal, execute sender. For example, Python sender with String, double (float64), numpy formats.

`./sender.py`

Watch what happens on the receiver!

## Example output
### sender.py
```
$ python3 sender.py
string sent: sample string
two doubles sent: 1234.56789, 9876.12345
numpy array sent: [[ 0  1  2  3  4  5  6  7]
 [ 8  9 10 11 12 13 14 15]]
one double and numpy array sent: 1234.56789, [[0 1 2 3]
 [4 5 6 7]]
```

### receiver (C)
```
$ ./receiver
*** New message received ***
Raw data: 73 61 6D 70 6C 65 20 73 74 72 69 6E 67 00 00 00
Interpreted as string:   sample string
*** New message received ***
Raw data: E7 C6 F4 84 45 4A 93 40 58 A8 35 CD 0F 4A C3 40
Interpreted as two doubles: 1234.567890, 9876.123450
*** New message received ***
Raw data: 00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F
Interpreted as array: 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15
*** New message received ***
Raw data: E7 C6 F4 84 45 4A 93 40 00 01 02 03 04 05 06 07
Interpreted as one double and array: 1234.567890, 0 1 2 3 4 5 6 7

```

## References

http://weifan-tmm.blogspot.kr/2015/09/invoke-floating-point-logic-set-option_4.html  

http://forum.falinux.com/zbxe/index.php?document_srl=420147&mid=C_LIB
