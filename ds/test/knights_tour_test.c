/*****************************************************************************
* FILE: knights_tour_test.c	           PURPOSE: Test file for Knight's Tour  *
*                                                                            *
* DEVELOPER: Peleg Rosenbaum           TEAM: Green                           *
*                                                                            *
* REVIEWER: Daniel Benedik             STATUS: Approved                      *
******************************************************************************/
#define _POSIX_C_SOURCE 199309L /* For timespec struct and nanosleep */

#include <stdio.h> /* printf, puts */
#include <stdlib.h> /* srand, rand */
#include <time.h> /* timespec, nanosleep */
#include <errno.h> /* errno */

#include "knights_tour.h"

#define RED "\033[31;1m"
#define GREEN "\033[32;1m"
#define YELLOW "\033[33;1m"
#define BLUE "\033[34;1m"
#define CYAN "\033[36;1m"
#define DEFAULT "\x1b[0;0m"

#define PRINT_TEST(a, b, format, line, is_test_failed) \
	if ((a) != (b)) \
	{ \
        *is_test_failed = TRUE; \
		printf("%sFAILED at line %s%d%s! Expected "format", " \
        "not "format".%s\n", RED, YELLOW, line, RED, (a), (b), DEFAULT); \
	}

#define INVALID -1

#define GET_Y(pos) ((pos) / ROW_NUM)
#define GET_X(pos) ((pos) - (GET_Y(pos) * ROW_NUM))
#define FALSE 0
#define TRUE 1

static int g_moves[BOARD_SIZE * ROW_NUM] = {0};

static int CalcNextPos(int pos, int *move);

static void InitLUT();

static size_t GetRandomPos(int lower, int upper);

static void PrintPath(char *path_board);

static int CheckLegalTour(char *path_board, int pos);

static int MiliSleep(long msec);

static void PrintCoolBoard(char **board);

int GetNextPos(char *path_board, int pos);

static int BacktrackingTest(void);

static int WarnsdorffTest(void);

static void CoolTest(void);

int main(void)
{
    int is_fail = FALSE;

    InitLUT();

    CoolTest();

    is_fail |= BacktrackingTest();

    is_fail |= WarnsdorffTest();

    if (!is_fail)
    {
        puts(GREEN"Passed All Tests!"DEFAULT);
    }

    return 0;
}

void CoolTest(void)
{
    char *board[BOARD_SIZE] = {NULL};
    char path_board[BOARD_SIZE] = {0};
    int pos = 0;

    size_t i = 0;

    char *seed = "🌱";
    char *water = "💦";
    char *empty = "  ";

    system("clear");

    pos = GetRandomPos(0, 63);
    KnightsTour(path_board, pos, HEURISTIC, 300);

    for (i = 0; i < BOARD_SIZE; ++i)
    {
        board[i] = empty;
    }

    PrintCoolBoard(board);

    board[pos] = water;

    for (i = 1; i < BOARD_SIZE; ++i)
    {
        PrintCoolBoard(board);
        board[pos] = seed;
        pos = GetNextPos(path_board, pos);
        board[pos] = water;
    }

    PrintCoolBoard(board);
    board[pos] = seed;
    PrintCoolBoard(board);
}

int BacktrackingTest(void)
{
    status_t status = SUCCESS;
    char path_board[BOARD_SIZE] = {0};
    int is_test_failed = FALSE;
    int is_legal_tour = FALSE;
    size_t start_pos = 0;

    status = KnightsTour(path_board, start_pos, BACKTRACKING, 300);
    PRINT_TEST(SUCCESS, status, "%d", __LINE__, &is_test_failed);
    is_legal_tour = CheckLegalTour(path_board, start_pos);
    PRINT_TEST(TRUE, is_legal_tour, "%d", __LINE__, &is_test_failed);

    printf("start_pos: %lu\n", start_pos);
    PrintPath(path_board);

    return is_test_failed;
}

int WarnsdorffTest(void)
{
    int i = 0;
    status_t status = SUCCESS;
    char path_board[BOARD_SIZE] = {0};
    int is_test_failed = FALSE;
    int is_legal_tour = FALSE;

    for (i = 0; i < BOARD_SIZE; ++i)
    {
        status = KnightsTour(path_board, i, HEURISTIC, 300);
        PRINT_TEST(SUCCESS, status, "%d", __LINE__, &is_test_failed);
        is_legal_tour = CheckLegalTour(path_board, i);
        PRINT_TEST(TRUE, is_legal_tour, "%d", __LINE__, &is_test_failed);
    }

    return is_test_failed;
}

static int CheckLegalTour(char *path_board, int pos)
{
    char count = 0;
    int next_pos = 0;
    int i = 0, j = 0;

    count = path_board[pos];
    ++count;
    
    for (i = 1; i < BOARD_SIZE; ++i)
    {
        for (j = 0; ROW_NUM > j && 
        (INVALID != (next_pos = g_moves[(pos * ROW_NUM) + j])); ++j)
        {
            if (count == path_board[next_pos])
            {
                break;
            }
        }

        if (INVALID == next_pos)
        {
            return FALSE;
        }
        pos = next_pos;
        ++count;
    }

    return TRUE;
}

static void PrintPath(char *path_board)
{
    size_t i = 0, j = 0;

    for (i = 0; i < ROW_NUM; ++i)
    {
        for (j = 0; j < ROW_NUM; ++j)
        {
            printf("%d  ", path_board[i * ROW_NUM + j]);
        }
        puts("");
    }
}

static void InitLUT()
{
    int pos = 0, move = 0;
    int valid_idx = 0;
    int pos_after_move = 0;

    int moves[ROW_NUM][2] = {{2, 1}, {2, -1}, {1, 2}, {-1, 2}, 
                            {-2, 1}, {-2, -1}, {1, -2}, {-1, -2}};

    for (pos = 0; pos < BOARD_SIZE; ++pos)
    {
        for (move = 0; move < ROW_NUM; ++move)
        {
            pos_after_move = CalcNextPos(pos, moves[move]);
            if (INVALID != pos_after_move)
            {
                g_moves[(pos * ROW_NUM) + valid_idx++] = pos_after_move;
            }
        }

        if (ROW_NUM > valid_idx)
        {
            g_moves[(pos * ROW_NUM) + valid_idx] = INVALID;
        }

        valid_idx = 0;
    }
}

static int CalcNextPos(int pos, int *move)
{
    int i = 0, j = 0;

    i = (GET_Y(pos) + move[1]);
    j = (GET_X(pos) + move[0]);

    if (0 <= i && 0 <= j && i < ROW_NUM && j < ROW_NUM)
    {
        return (pos + move[0] + move[1] * ROW_NUM);
    }
    else
    {
        return INVALID;
    }
}

static size_t GetRandomPos(int lower, int upper)
{
    srand(time(NULL));
	
	return (size_t)((rand() % (upper - lower + 1)) + lower);
}

static int MiliSleep(long msec)
{
    struct timespec ts;
    int res;

    if (msec < 0)
    {
        errno = EINVAL;
        return -1;
    }

    ts.tv_sec = msec / 1000;
    ts.tv_nsec = msec * 1000000;

    do {
        res = nanosleep(&ts, &ts);
    } while (res && errno == EINTR);

    return res;
}

static void PrintCoolBoard(char **board)
{
    int i = 0, j = 0;
    char *colors[2] = {"\33[0;47m", "\33[0;40m"};

    printf("\033[2;0H");
    for (i = 0; i < ROW_NUM; ++i)
    {
        for (j = 0; j < ROW_NUM; ++j)
        {
            printf("%s%s\33[0m", colors[(j + i) % 2], board[i * ROW_NUM + j]);
        }
        printf("\n");
    }

    MiliSleep(500);
}

int GetNextPos(char *path_board, int pos)
{
    char count = 0;
    int next_pos = 0;
    int i = 0;

    count = path_board[pos];
    ++count;

    for (i = 0; ROW_NUM > i && 
    (INVALID != (next_pos = g_moves[(pos * ROW_NUM) + i])); ++i)
    {
        if (count == path_board[next_pos])
        {
            return next_pos;
        }
    }

    return INVALID;
}
