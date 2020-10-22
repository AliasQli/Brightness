#include <iostream>
#include <stdio.h>

#include "include/util.h"

using namespace std;

void error(const char* msg, int num) {
    perror(msg);
    exit(num);
}

void error(const string& msg, int num) {
    error(msg.c_str(), num);
}

void log(const char* msg) {
    cout << msg;
}

void log(const string& msg) {
    cout << msg;
}