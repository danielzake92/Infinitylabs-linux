/****************************************************************************
* FILE: hash_table_test.c	     PURPOSE: Define Hash Table Data Strucuture
*
* DEVELOPER: Daniel Zaken		 TEAM: Green
*
* REVIEWER:  Yael Koenig  	  	 STATUS: Review
*
****************************************************************************/

#include <stdio.h>			/* printf */
#include <stdlib.h>			/* Hash Table API */
#include <assert.h>        /* assert */
#include <string.h>        /* strcmp */
#include <stdlib.h>		   /* malloc */

#include "hash_table.h"
#include "doubly_linked_list.h"

#define WORD_SIZE sizeof(size_t)
#define MAX_STR 1000
#define DICT_PATH "/usr/share/dict/american-english"	
#define DICT_ROWS 102401
#define DICT_WORD 31

#define ABS(x)  ( ( (x) < 0) ? -(x) : (x) )	

typedef enum {SUCCESS, FAIL, ALLOCATION_ERROR, READ_ERROR, CLOSE_ERROR}status_t;
enum bol {TRUE = 1, FALSE = 0};

/******************************************************************************/
/***                        Color Defines   		                      ***/
/******************************************************************************/
#define DEF     "\033[0m"
#define BLACK   "\033[30m"      /* Black */
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define WHITE   "\033[37m"      /* White */
#define BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */
#define BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */
#define BOLDMAGENTA "\033[1m\033[35m"      /* Bold Magenta */
#define BOLDCYAN    "\033[1m\033[36m"      /* Bold Cyan */
#define BOLDWHITE   "\033[1m\033[37m"      /* Bold White */

static int test_counter_g = 0;
static int success_counter_g = 0;

#define TEST(name, real, expected) \
    do { \
        ++test_counter_g; \
        ((real) == (expected)) ? \
        ++success_counter_g : \
        printf(RED "%s, Failed on line %d, Real: %ld, Expected: %ld\n" DEF, name, __LINE__, (long) (real), (long) (expected)); \
    } while (0)

#define TESTC(name, real, expected) \
    do { \
        ++test_counter_g; \
        ((real) == (expected)) ? \
        ++success_counter_g : \
        printf(RED "%s, Failed on line %d, Real: %c, Expected: %c\n" DEF, name, __LINE__, (char) (real), (char) (expected)); \
    } while (0)

#define PASS (test_counter_g == success_counter_g) ? \
    printf(GREEN "Passed everything!\n\n" DEF) : \
    printf(RED "Failed " BOLDRED "%d/%d" RED" tests.\n\n" DEF, \
           test_counter_g - success_counter_g, test_counter_g)


status_t SpellChecker(void);

size_t StringHash(const void *data, size_t table_size) ;
int IsMatchWord(const void *lhs, const void *rhs);




/************************* Helper Functions *************************/

typedef struct
{
	unsigned int id;
	char grade;
} student_t;



#define TABLE_SIZE 100

static size_t HashFunc(const void *data, size_t table_size)
{
	student_t *student = (student_t *) data;

	return student->id % table_size;
}

static int MatchFunc(const void *one, const void *other)
{
	student_t *student_one = (student_t *) one;
	student_t *student_other = (student_t *) other;

	return (student_one->id == student_other->id);
}

static int ActionLowerGrade(void *data, void *params)
{
	student_t *student = (student_t *) data;

	student->grade += 1;   /* e.g. lowers the grade from A to B */

	(void) params;

	return 0;
}

static int ActionIsFailed(void *data, void *params)
{
	student_t *student = (student_t *) data;

	(void) params;

	return student->grade == 'F';   /* F is failed */
}

static int ActionChangeGrade(void *data, void *params)
{
	student_t *student = (student_t *) data;

	student->grade = *(char *) params;

	return 0;
}


/************************* Tests Functions *************************/
static void TestCreateDestroy(void)
{
	ht_t *ht = HTCreate(HashFunc, MatchFunc, TABLE_SIZE);

	HTDestroy(ht);

	printf(BOLDBLUE "Completed TestCreateDestroy\n" DEF);
}
/*****************************************************************************/
static void Test1(void)
{
	int status = 0;
	char new_grade = 'L';

	ht_t *ht = HTCreate(HashFunc, MatchFunc, TABLE_SIZE);

	student_t key_student = {0, '\0'};
	student_t *student = NULL;

	student_t class[10];
	class[0].id = 257;
	class[0].grade = 'A';
	class[1].id = 32;
	class[1].grade = 'B';
	class[2].id = 111;
	class[2].grade = 'E';
	class[3].id = 104701;
	class[3].grade = 'C';
	class[4].id = 57;
	class[4].grade = 'D';
	class[5].id = 1057;
	class[5].grade = 'X';
	class[6].id = 2057;
	class[6].grade = 'Y';
	class[7].id = 3057;
	class[7].grade = 'F';

	TEST("IsEmpty", HTIsEmpty(ht), 1);
	TEST("Size", HTSize(ht), 0);

	/* insert */

	HTInsert(ht, class+0);

	TEST("IsEmpty", HTIsEmpty(ht), 0);
	TEST("Size", HTSize(ht), 1);

	HTInsert(ht, class+1);

	TEST("IsEmpty", HTIsEmpty(ht), 0);
	TEST("Size", HTSize(ht), 2);

	HTInsert(ht, class+2);

	TEST("IsEmpty", HTIsEmpty(ht), 0);
	TEST("Size", HTSize(ht), 3);

	HTInsert(ht, class+3);

	TEST("IsEmpty", HTIsEmpty(ht), 0);
	TEST("Size", HTSize(ht), 4);

	HTInsert(ht, class+4);

	TEST("IsEmpty", HTIsEmpty(ht), 0);
	TEST("Size", HTSize(ht), 5);

	HTInsert(ht, class+5);

	TEST("IsEmpty", HTIsEmpty(ht), 0);
	TEST("Size", HTSize(ht), 6);

	HTInsert(ht, class+6);

	TEST("IsEmpty", HTIsEmpty(ht), 0);
	TEST("Size", HTSize(ht), 7);

	HTInsert(ht, class+7);

	TEST("IsEmpty", HTIsEmpty(ht), 0);
	TEST("Size", HTSize(ht), 8);

	/* find */

	key_student.id = 1000;
	student = (student_t *) HTFind(ht, &key_student);
	TEST("Find", student, NULL);

	key_student.id = 32;
	student = (student_t *) HTFind(ht, &key_student);
	TEST("Find", student->id, 32);
	TESTC("Find", student->grade, 'B');

	key_student.id = 232;
	student = (student_t *) HTFind(ht, &key_student);
	TEST("Find", student, NULL);

	key_student.id = 104701;
	student = (student_t *) HTFind(ht, &key_student);
	TEST("Find", student->id, 104701);
	TESTC("Find", student->grade, 'C');

	key_student.id = 111;
	student = (student_t *) HTFind(ht, &key_student);
	TEST("Find", student->id, 111);
	TESTC("Find", student->grade, 'E');

	/* remove */

	key_student.id = 111;
	HTRemove(ht, &key_student);

	TEST("Size", HTSize(ht), 7);

	key_student.id = 1057;
	HTRemove(ht, &key_student);

	TEST("Size", HTSize(ht), 6);

	key_student.id = 2057;
	HTRemove(ht, &key_student);

	TEST("Size", HTSize(ht), 5);

	key_student.id = 1057;
	student = (student_t *) HTFind(ht, &key_student);
	TEST("Find", student, NULL);

	key_student.id = 3057;
	student = (student_t *) HTFind(ht, &key_student);
	TEST("Find", student->id, 3057);
	TESTC("Find", student->grade, 'F');

	key_student.id = 257;
	student = (student_t *) HTFind(ht, &key_student);
	TEST("Find", student->id, 257);
	TESTC("Find", student->grade, 'A');

	/* for each */

	/* ActionIsFailed */

	status = HTForEach(ht, ActionIsFailed, NULL);
	TEST("ForEach", status, 1);

	key_student.id = 3057;
	HTRemove(ht, &key_student);

	status = HTForEach(ht, ActionIsFailed, NULL);
	TEST("ForEach", status, 0);
	/* ActionLowerGrade */

	status = HTForEach(ht, ActionLowerGrade, NULL);
	TEST("ForEach", status, 0);
	/* these were in the hash table */
	TESTC("ForEach", class[0].grade, 'B');
	TESTC("ForEach", class[1].grade, 'C');
	TESTC("ForEach", class[3].grade, 'D');
	TESTC("ForEach", class[4].grade, 'E');
	/* these were not in the hash table */
	TESTC("ForEach", class[2].grade, 'E');
	TESTC("ForEach", class[5].grade, 'X');
	TESTC("ForEach", class[6].grade, 'Y');
	TESTC("ForEach", class[7].grade, 'F');

	/* ActionChangeGrade */

	new_grade = 'L';
	status = HTForEach(ht, ActionChangeGrade, &new_grade);
	TEST("ForEach", status, 0);
	/* these were in the hash table */
	TESTC("ForEach", class[0].grade, 'L');
	TESTC("ForEach", class[1].grade, 'L');
	TESTC("ForEach", class[3].grade, 'L');
	TESTC("ForEach", class[4].grade, 'L');
	/* these were not in the hash table */
	TESTC("ForEach", class[2].grade, 'E');
	TESTC("ForEach", class[5].grade, 'X');
	TESTC("ForEach", class[6].grade, 'Y');
	TESTC("ForEach", class[7].grade, 'F');

	HTDestroy(ht);

	printf(BOLDBLUE "Completed Standart Test\n" DEF);
}
/*****************************************************************************/
int FreeFunc(void *data, void *params)
{
	free(data);
	(void)params;
	return 0;
}
/************************* main function *************************/

int main(void)
{
	TestCreateDestroy();

	Test1();

	if( SUCCESS == SpellChecker() )
	{
		printf(BLUE"Completed SpellChecker Test\n"DEF);
	}

	PASS;

	return 0;
}
/*****************************************************************************/
status_t SpellChecker(void)
{
	size_t table_size = 135000;
	ht_t *table = HTCreate(StringHash,IsMatchWord ,table_size);
	size_t count = 0;

	FILE *file = NULL;

	char line[DICT_WORD] = "";
	char dict[DICT_ROWS][DICT_WORD] = {'\0'};

	if((file = fopen(DICT_PATH, "r")) == NULL )
	{
		return READ_ERROR;
	}

	while( count < DICT_ROWS )
	{
		fgets(dict[count], DICT_WORD, file);

		HTInsert(table, &(dict[count]));

		++count;
	}

	printf(YELLOW"LOAD FACTOR -> "GREEN"%f\n", HTLoadFactor(table));
	printf(YELLOW"STANDART DEVIATION -> "GREEN"%f\n", HTStandardDeviation(table));
	printf(YELLOW"HTSize -> "GREEN"%lu\n", HTSize(table));

	while( TRUE )
	{
		printf(BLUE"Enter word for spell check (case sensitive) for exit type '-':\n"DEF);
					
		fgets(line, DICT_WORD , stdin);
		if ('-' == *line)
		{
			break;
		}
		if( NULL == HTFind(table, &(line)) )
		{
			printf(RED"Not in the dictionary\n"DEF);
		}
		else
		{
			printf(GREEN"Exists in the dictionary\n");
		}
	}

	if( EOF == fclose(file) )
	{
		return CLOSE_ERROR;
	}

	HTDestroy(table);

	return SUCCESS;
}	
/*****************************************************************************/
size_t StringHash(const void *data, size_t table_size) 
{
	size_t i = 0;
	size_t length = 0;	
	int hash = 0;
	char *key = NULL;

	assert(data);		

	length = strlen((char*)data);

	key = (char*)data;

	while (i != length)
	{
		hash += key[i++];
		hash += hash << 10;
		hash ^= hash >> 6;
	}
	hash += hash << 3;
	hash ^= hash >> 11;
	hash += hash << 15;

	return (((size_t)ABS(hash)) % table_size );
}
/*****************************************************************************/
int IsMatchWord(const void *lhs, const void *rhs)
{
	assert(lhs);
	assert(rhs);
	
	return (! (strcmp((const char *)(lhs), (const char *)rhs) ));
}