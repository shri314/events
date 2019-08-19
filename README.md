# EVENTS

##### instructions for bionic (ubuntu 18)

    sudo apt install g++ g++-8 cmake
    sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-8 300
    sudo update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-8 300
    sudo update-alternatives --install /usr/bin/gcov gcov /usr/bin/gcov-8 300
    sudo apt install libcurl4-openssl-dev

    #g++ --version
    #g++ (Ubuntu 8.3.0-6ubuntu1~18.04.1) 8.3.0

    #cmake --version
    #cmake version 3.10.2

    mkdir build
    cd build
    cmake -DCMAKE_BUILD_TYPE=Debug ..
    make

