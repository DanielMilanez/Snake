#define WINDOWS_SYSTEM 
// #define LINUX_SYSTEM 

#define WINDOWS 0 
#define LINUX 0

#ifdef WINDOWS_SYSTEM
    #undef WINDOWS
    #define WINDOWS 1
#endif

#ifdef LINUX_SYSTEM
    #undef LINUX 
    #define LINUX 1
#endif

#define K_LEFT   75
#define K_RIGHT  77
#define K_UP     72
#define K_DOWN   80

#define SIZE_GAME       32
#define SIZE_GAME_LINES 16

#define GND   0
#define FRUIT 1
#define PBODY 2
#define PHEAD 3
#define PDEAD 4
#define WALL  5

#define ANSI_RESET   "\x1b[0m"
#define ANSI_RED     "\x1b[31m"
#define ANSI_GREEN   "\x1b[32m"
#define ANSI_YELLOW  "\x1b[33m"
#define ANSI_BLUE    "\x1b[34m"
#define ANSI_MAGENTA "\x1b[35m"
#define ANSI_CYAN    "\x1b[36m"
#define ANSI_WHITE   "\x1b[37m"

#define MIN_SIZE_SNAKE 3
#define MAX_SIZE_SNAKE 515
#define WIN_SCORE (MAX_SIZE_SNAKE - 3)

#define HIDE_CURSOR(void) printf("\033[?25l")
#define MOVE_CURSOR_FROM_START(void) printf("\033[H");