#include <stdio.h>
#include <stdlib.h>
#include <termios.h>

static struct termios oldt;

void restore_terminal_settings(void)
{
	tcsetattr(0,TCSANOW,&oldt);
}

void disable_terminal_return(void)
{
	struct termios newt;

	tcgetattr(0,&oldt);
	newt = oldt;
	newt.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(0,TCSANOW,&newt);

	atexit(restore_terminal_settings);
}

int main()
{
	int ch;
	disable_terminal_return();
	
	printf("press your keyboard\n");
	while(1)
	{
		ch = getchar();
		if(ch == 'q') return 0;
		printf("You pressed %c\n",ch);
	}
	return 0;
}
