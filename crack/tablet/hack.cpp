#define _CRT_SECURE_NO_WARNINGS

#include "hack.h"

#include <stdio.h>
#include <stdlib.h>

static size_t filesize (FILE* file) {
	size_t bufpos = ftell(file);

	fseek(file, 0, SEEK_SET);
	size_t start = ftell(file);

	fseek(file, 0, SEEK_END);
	size_t size = ftell(file) - start;

	fseek(file, bufpos, SEEK_SET);

	return size;
}

bool isnothacked (const char* prog, size_t cnt) {
	static const size_t nothacked = 15971370364699986717ll;

	return proghash(prog, cnt) == nothacked;
}

bool ishacked (const char* prog, size_t cnt) {
	static const size_t hacked = 2035824285440957717;
	size_t hash = proghash(prog, cnt);
	printf("%lu  %lu\n", hash, hacked);
	if (hash == hacked) {
		return true;
	}

	return false;
}

size_t proghash (const char* buf, size_t cnt) {
	#define hashstep 179875753

	size_t hash = 0;
	for (size_t i = 0; i < cnt; i++) {
		hash *= hashstep;
		hash += buf[i];
	}

	#undef hashstep
	return hash;
}

size_t uploadprogramm (char** buf, const char* filename) {
	FILE* progfile  = fopen(filename, "rb");

	if (!progfile) {
		return 0;
	}

	size_t progsize = filesize(progfile);
	*buf  = (char*)calloc(progsize, sizeof(char));

	if (!(*buf)) {
		return 0;
	}
	
	size_t progsize_buf = fread(*buf, sizeof(char), progsize, progfile);
	if (progsize_buf > progsize) {
		free(*buf);
		*buf = NULL;
	}
	fclose(progfile);

	return progsize;
}

void makecrack (void) {
	FILE* done = fopen("PSD.COM", "rb");
	FILE* file = fopen("PASSWORD.COM", "wb");

	size_t donesize = filesize(done);
	char* buf = (char*)calloc(donesize, sizeof(char));
	fread(buf, sizeof(char), donesize, done);
	fwrite(buf, sizeof(char), donesize, file);
	free(buf);
	fclose(done);
	fclose(file);
}