/*
 * @Author: xuezaigds@gmail.com
 * @Last Modified time: 2016-08-20 16:00:39
 */

#include <stdio.h>      // printf
#include <string.h>     // strlen
#include <cstdlib>      // malloc

char* char_memcpy(char * destination, const char *source, int len){
    if(destination==NULL || source==NULL){
        return NULL;
    }
    char *ret = destination;
    if(destination >= source && destination < source+len){
        destination += len-1;
        source += len-1;
        while(len--){
            *destination-- = *source--;
        }
    }
    else{
        while (len--)   *destination++ = *source++;
    }
    return ret;
}

// Can process overlap now.
char* strcpy(char * destination, const char * source ){
    if(destination==NULL || source==NULL){
        return NULL;
    }
    char *des = destination;
    char_memcpy(destination, source, strlen(source)+1);
    return des;
}

int main() {
    // Normal
    char str[]="hello";
    char* dest = (char *)malloc(10);
    strcpy(dest, str);
    printf("%s \n", dest);  // hello

    // Overlap 1
    char s[]="hello";
    strcpy(s+1, s);
    printf("%s \n", s);     // hhello

    char ss[]="hello";
    strcpy(ss+5, ss);
    printf("%s \n", ss);    // hellohello

    // Overlap 2
    char sss[]="hello";
    strcpy(sss, sss+1);
    printf("%s \n", sss);   // ello

}


