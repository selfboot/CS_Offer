#include "stdio.h"
#include "conio.h"

#include "seqqueue2.h"

main()
{
	char ch1,ch2;
	SeqQueue  Q;
	int f;
	InitQueue (&Q);

	while(TRUE)
	{
		while(TRUE)
		{
			printf("A");

			if(kbhit())
			{
				ch1=getch();
				if(ch1==';'||ch1=='.')
					break;
				f= EnterQueue(&Q,ch1);
				if(f==FALSE)
				{
					printf("full");
					break;
				}
			}

		}
		while (!IsEmpty(&Q))
		{
			DeleteQueue(&Q,&ch2);
			putchar(ch2);
		}
		getch();
		if(ch1=='.') break;
	}
}
