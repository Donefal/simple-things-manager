# A Simple **Things** Manager

This project is a simple C++ CLI app that used to write *things* down. This project is inspired by [Twos App](https://www.twosapp.com/), and created with the only purpose of learning and experimenting. 

This project used `SQLite3` as its main dependencies to store information as databases. Not only that, I also added a [Bcrypt by hilch](https://github.com/hilch/Bcrypt.cpp) to try out one way of storing password.

## How to Build & Run
I have a little to no experience with building my code properly at this point of time. So, I just tried my best to set this project with CMake, here's what you should do to build and run the project,

```bash
mkdir build
cd build
cmake ..
./thingsm
```

All dependencies are self contained within the project, so the only thing you should need to do is to run the executable in the console. Another thing, there's also `log.txt` in the `./docs` directory that I use to log the proccess of the app. This might help in debugging.

## My intention of this project
This project is my way of learning many new things, which is,
- SQLite and database usage in general,
- CMake build system, and
- Object Oriented Programming.

>  *If you somehow see this repository, and noticed (a lot of) problems on my code or anything I can improve, please kindly tell me if you can. It would be so helpful for me ✌️.*
