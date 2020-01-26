# Server Application
**Server Application** is a C++ project, a general server that handling client requests as problems,
 and returns a solution for each client.
 Based on empirical experiments, there was found out that **A\* algorithm** is preferable over other search algorithms to search to 
 optimal solution.
## Installation

Download the zip file of the project from the following [link](https://github.com/guyshoham/Milstone2/archive/master.zip).

## Build and Run

* Unzip the zip file.
* Compile the project using the command line:

```bash
g++ -std=c++14 *.cpp -Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic -o app -pthread
```
   
* Run the program by using the command:
 
 ```bash
./app [PORT]
 ```
PORT = port number (e.g 5600).
    
While the program is running, multiple clients can connect and send requests to the server.

Enjoy!