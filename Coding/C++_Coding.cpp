/*
 * @Author: xuezaigds@gmail.com
 * @Last Modified time: 2016-08-20 17:03:23
 */

#include <iostream>

using namespace std;

size_t strlen(const char *str) {
    const char *s;
    for (s = str; *s; ++s) {}
    return s - str;
}
