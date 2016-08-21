#include <iostream>
#include <sys/stat.h>
using namespace std;

unsigned long get_file_size(const char *filename)
{
    unsigned long size;
    FILE* fp = fopen( filename, "rb");
    if(fp==NULL)
    {
        printf("ERROR: Open file %s failed.\n", filename);
        return 0;
    }
    fseek(fp, SEEK_SET, SEEK_END );
    size=ftell(fp);
    fclose(fp);
    return size;
}

unsigned long get_file_size_2(const char *filename)
{
    struct stat buf;
    if(stat(filename, &buf)<0)
    {
        return 0;
    }
    return (unsigned long)buf.st_size;
}

int main(){
    const char* path = "C++_GetFileSize.cpp";
    cout << "Size of file: " << path << " is \n";
    cout << get_file_size(path) << endl;
    cout << get_file_size_2(path) << endl;
}
