#include <stdio.h>
int main()
{
    int sum = 0;
    for(int a = 0; a < 10; a++)
    {
        sum = sum + a;
        printf("%d\n",sum);
    }
    return 0;
}
