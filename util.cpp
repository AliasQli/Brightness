#include <iostream>
#include <stdio.h>

#include "include/util.h"

using namespace std;

void error(const string& msg) {
    perror(msg.c_str());
    exit(-1);
}

void log(const string& msg) {
    cout << msg;
}