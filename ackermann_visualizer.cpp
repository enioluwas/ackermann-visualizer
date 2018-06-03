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
#include <string>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <memory>

#define MAX_LINE_LENGTH 1024

static unsigned long counter = 0;
static FILE* stream;

size_t ackermann(size_t m, size_t n, std::string s = "%s");

size_t ackermann(size_t m, size_t n, std::string s)
{
	counter++;
	{
		size_t s2_length = snprintf(nullptr, 0, "A(%zu, %zu)", m, n) + 1;
		std::unique_ptr<char[]> s2(new char[s2_length]);
		snprintf(s2.get(), s2_length, "A(%zu, %zu)", m, n);

		size_t s3_length = snprintf(nullptr, 0, s.c_str(), s2.get()) + 1;
		std::unique_ptr<char[]> s3(new char[s3_length]);
		snprintf(s3.get(), s3_length, s.c_str(), s2.get());

		if (strlen(s3.get()) <= MAX_LINE_LENGTH)
			fprintf(stream, "%s\n", s3.get());
		else
			fputs("...\n", stream);
		fflush(stream);
	}

	if (m == 0)
		return n + 1;

	if (n == 0)
		return ackermann(m - 1, 1, s);

	size_t s4_length = snprintf(nullptr, 0, "A(%lu, %%s)", m - 1) + 1;
	std::unique_ptr<char[]> s4(new char[s4_length]);
	snprintf(s4.get(), s4_length, "A(%lu, %%s)", m - 1);

	size_t s5_length = snprintf(nullptr, 0, s.c_str(), s4.get()) + 1;
	std::unique_ptr<char[]> s5(new char[s5_length]);
	snprintf(s5.get(), s5_length, s.c_str(), s4.get());

	int n2 = ackermann(m, n - 1, std::string(s5.get(), s5.get() + s5_length -1));
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
		std::string filename = "./";
		filename += *argv[3];
		stream = fopen(filename.c_str(), "w+");
		if (!stream)
		{
			printf("file_error: Failed to open file: %s\n", filename.c_str());
			return 1;
		}
	}
	else
		stream = stdout;

	clock_t begin = clock();
	fprintf(stream, "Value: %zu\n", ackermann(m, n));
	clock_t end = clock();
	double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	fprintf(stream, "Number of calls: %lu\n", counter);
	fprintf(stream, "Run time: %f seconds\n", time_spent);
	fflush(stream);
	fclose(stream);

	return 0;
}