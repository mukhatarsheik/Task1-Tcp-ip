# Task1-Tcp-ip
Task related to Tcp/ip server to client communication 
How to compile this two files
step1:compile server and client source code separetely and store their executabale file with a unigue name
step2:after compilation run the two executable files separately in two different terminal side by side
step3:user need to enter the data from from client terminal first and then server will read and echo(send) it back to client
Note:as per the given task there is no any two way communication between the server and the client user need to enter the data at once after that one entry
communication will be lost,then user need to close both the terminal and open two new terminal and compile and run the code as per the step 1 till step 3

verification and error handling for this i had already put error checking condition depending upon the return values of the system call which through message from the program flow to tell us where is the error in the program and during communication at client side i had check the return value of write and read to ensure proper sending and receiving of message is taking place which is also visible in the terminal
