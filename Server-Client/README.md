
[![forthebadge made-with-python](http://ForTheBadge.com/images/badges/made-with-python.svg)](https://www.python.org/)

 **The intention transfer a text file over network through python program. This file transfer is based on server client model to use socket programming in python3+**

![sample](https://linuxhint.com/wp-content/uploads/2019/11/Capture.png)

## !Here are the steps to execute the program.
* [client.py](client.py)
* [server.py](server.py)

* Step1: Go to B_server system and open a terminal. Short cut to open a terminal is Alt+Ctrl+t.
* Step2: Now go the path where server.py is present.
* Step3: Now run server.py like below
 ```
 **python3 server.py**
 There should not be any errors and you should see below prints
 Server is listing on port : 9898
 Copied file name will be recv.txt at server side
 
 ```
* Step4: Now open terminal at A_client system.
* Step5: Go to the path where client.py and sample.txt are present.
* Step6: Now run client.py like below
 ```
  **python3 client.py <B_server system IP>**
    We have observed that we need to know the IP address of server. We can execute below command to know the IP address of B_server system.
 ```