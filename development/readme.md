To test Client-Server implementation on BBG:

Client Side: Set IP of BBG (find ip using 'ifconfig') in the source code and compile using 'gcc' flag to be executed on the 'HOST' machine

Server Side: Compile using 'arm-linux-gcc' flag to be executed on the 'TARGET' machine

Makefile: Choose appropriate 'PLATFORM'	