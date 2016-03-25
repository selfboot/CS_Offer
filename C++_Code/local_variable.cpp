# include <iostream>
using namespace std;

char *GetMemory( void )
{
    char p[] = "hello world";
    return p;
}

int main(){
    char *str = NULL;
    str = GetMemory();
    printf( str );
}
