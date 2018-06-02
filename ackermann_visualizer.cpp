/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////  Ackermann Visualizer - A basic tool for visually tracing the recursive call stack in the Ackermann–Péter function  ////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/* MIT License
*
* Copyright (c) 2018, Enioluwa Segun
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*/

#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <stdarg.h>

#define MAX_LINE_LENGTH 1024

static unsigned long counter = 0;
static FILE* stream;

unsigned int ackermann(unsigned int m, unsigned int n, char s[] = (char *)"%s");

unsigned int ackermann(unsigned int m, unsigned int n, char s[])
{
	counter++;
	{
		char * s2 = (char *)malloc(10);
		char * s3 = (char *)malloc(strlen(s) + 32);
		snprintf(s2, 10, "A(%d, %d)", m, n);
		snprintf(s3, strlen(s) + 18, s, s2);
		if (strlen(s3) <= MAX_LINE_LENGTH)
			fprintf(stream,"%s\n", s3);
		else
			fputs("...\n", stream);
		fflush(stream);
	}

	if (m == 0)
		return n + 1;

	if (n == 0)
		return ackermann(m - 1, 1, s);

	char * s4 = (char *)malloc(11);
	char * s5 = (char *)malloc(strlen(s) + 32);
	snprintf(s4, 15, "A(%d, %%s)", m - 1);
	snprintf(s5, strlen(s) + 18, s, s4);

	int n2 = ackermann(m, n - 1, s5);
	return ackermann(m - 1, n2, s);
}

int main(int argc, char* argv[])
{
	if (argc < 3)
	{
		printf("argument_error: Provide two arguments, %d provided\n", argc - 1);
		return 1;
	}

	int m = strtol(argv[1], nullptr, 10);
	int n = strtol(argv[2], nullptr, 10);

	if (m < 0 || n < 0)
	{
		puts("argument_error: Invalid argument. use nonnegative integers\n");
		return 1;
	}
	else if (m > 4)
	{
		puts("argument_error: Exponentiation past tetration: ackermann(m > 4, n > 0) cannot be evaluated in reasonable time with this recursive implementation\n");
		return 1;
	}

	if (argc > 3)
	{
		char * rel = (char *)malloc(strlen("./") + strlen(argv[3]));
		snprintf(rel, strlen("./") + strlen(argv[3]), "%s", "./");
		const char* filename = strcat(rel, argv[3]);
		 stream = fopen(filename, "w+");
		if (!stream)
		{
			printf("file_error: Failed to open file: %s\n", filename);
			return 1;
		}
	}
	else
		stream = stdout;

	clock_t begin = clock();
	fprintf(stream,"Value: %d\n", ackermann(m, n));
	clock_t end = clock();
	double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	fprintf(stream, "Number of calls: %d\n", counter);
	fprintf(stream, "Run time: %f seconds\n", time_spent);
	fflush(stream);
	fclose(stream);
	
	return 0;
}