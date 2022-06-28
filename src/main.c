#include <ncurses.h>
#include <malloc.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/mman.h>
#include "buffer.h"

///Inits ncurses with some default settings
void init()
{
    initscr();
    cbreak();
    noecho();

    clear();
    refresh();
}

///PRECONDITION
///     ncurses is initialized (init details do not matter)
///POSTCONDITION
///     ncurses has exited
void loop()
{
    if (size > 0)
    {
        addnstr(buffer, size);
    }
    int ch = getch();
    while (ch != 24) {
        if (ch == 27) {
            b_delf();
        } else if (ch == 127) {
            b_del();
        } else {
            b_add(ch);
        }
        clear();
        mvaddstr(0, 0, buffer);
        refresh();
        ch = getch();
    }
    endwin();
    b_free();
}


//prevents sigint from cutting off the process before I can deallocate everything
void sig_handler(int signum)
{
    endwin();
    b_free();
    exit(1);
}

int main(int argc, char** argv)
{
    if (signal(SIGINT, sig_handler) == SIG_ERR)
    {
        perror("failed to register sigint handler.\n");
        return -1;
    }

    if (argc > 1)
    {
        b_init(argv[1]);
    } else
    {
        b_init(NULL);
    }


    init();
    loop();
    b_free();
	return 0;
}
