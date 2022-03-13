#include <stdio.h>
#include <execinfo.h>

int main() {
	void *buffer[32];
	int nlines = backtrace(buffer, 32);
	char **traces = backtrace_symbols(buffer, nlines);

	for (int i = 0; i < nlines; ++i)
		printf("%s\n", traces[i]);
}
