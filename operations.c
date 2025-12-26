#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "operations.h"

#define BUFFER_SIZE 4096

void replace_in_file(const char *filename, const char *old_str, const char *new_str) {
	FILE *file = fopen(filename, "r");
	if (!file) {
		perror("critical openning error");
		return;
	}

	char temp_filename[] = "temp_XXXXXX";
	int fd = mkstemp(temp_filename);
	if (fd == -1) {
		perror("temp error");
		fclose(file);
		return;
	}

	FILE *temp = fdopen(fd, "w");
	if (!temp) {
		perror("couldn't open temp");
		fclose(file);
		close(fd);
		return;
	}

	char *line = NULL;
	size_t line_len = 0;
	ssize_t read;
	int old_len = strlen(old_str);
	int new_len = strlen(new_str);
	
	while ((read = getline(&line, &line_len, file)) != -1) {
		if (old_len == 0) {
			fputs(line, temp);
			continue;
		}                                  //test service check segmentation issues
		
		char *current_pos = line;
		char *found_pos;

		while ((found_pos = strstr(current_pos, old_str)) != NULL) {
			fwrite(current_pos, 1, found_pos - current_pos, temp);
			fwrite(new_str, 1, new_len, temp);
			current_pos = found_pos + old_len;
		}

		fputs(current_pos, temp);
	}

	free(line);
	fclose(file);
	fclose(temp);

	if(rename(temp_filename, filename) != 0) {
		perror("Replacement error");
		remove(temp_filename);
	}
}

void delete_lines(const char *filename, const char *pattern) { //end service
	FILE *file = fopen(filename, "r");
	if (!file) {
		perror("critical opening error");
		return;
	}

	char temp_filename[] = "temp_xxxxxx";
	int fd = mkstemp(temp_filename);
	if (fd == -1) {
		perror("critical temp error");
		fclose(file);
		return;
	}

	FILE *temp = fdopen(fd, "w");
	if (!temp) {
		perror("critical temp error");
		fclose(file);
		close(fd);
		return;
	}

	char *line = NULL;
	size_t line_len = 0;
	ssize_t read;

	while ((read = getline(&line, &line_len, file)) != -1) {
		if (strstr(line, pattern) == NULL) {
			fputs(line, temp);
		}
	}

	free(line);
	fclose(file);
	fclose(temp);

	if (rename(temp_filename, filename) != 0) {
		perror("replacement error");
		remove(temp_filename);
	}
}

void prepend_to_lines(const char *filename, const char *text) {
	FILE *file = fopen(filename, "r");
	if (!file) {
		perror("couldn't open");
		return;
	}

	char temp_filename[] = "temp_XXXXXX";
	int fd = mkstemp(temp_filename);
	if (fd == -1) {
		perror("temp error");
		fclose(file);
		return;
	}

	FILE *temp = fdopen(fd, "w");
	if (!temp) {
		perror("couldn't open temp");
		fclose(file);
		close(fd);
		return;
	}

	char *line = NULL;
	size_t line_len = 0;
	ssize_t read;

	while ((read = getline(&line, &line_len, file)) != -1) {
		fprintf(temp, "%s%s", text, line);
	}

	free(line);
	fclose(file);
	fclose(temp);

	if (rename(temp_filename, filename) != 0) {
		perror("replacement error");
		remove(temp_filename);
	}
}

void append_to_lines(const char *filename, const char *text) {
	FILE *file = fopen(filename, "r");
	if (!file) {
		perror("couldn't open");
		return;
	}

	char temp_filename[] = "temp_XXXXXX";
	int fd = mkstemp(temp_filename);
	if (fd == -1) {
		perror("critical temp error");
		fclose(file);
		return;
	}

	FILE *temp = fdopen(fd, "w");
	if (!temp) {
		perror("couldn't open temp");
		fclose(file);
		close(fd);
		return;
	}

	char *line = NULL;
	size_t line_len = 0;
	ssize_t read;

	while ((read = getline(&line, &line_len, file)) != -1) {
		if (read > 0 && line[read - 1] == '\n') {
			line[read - 1] = '\0';
			fprintf(temp, "%s%s\n", line, text);
		} else {
			fprintf(temp, "%s%s", line, text);
		}
	}

	free(line);
	fclose(file);
	fclose(temp);

	if(rename(temp_filename, filename) != 0) {
		perror("replacement error");
		remove(temp_filename);
	}
}
