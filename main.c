#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "operations.h"

void print_usage() {
	printf("usage:\n");
	printf("sed_editor <file> <command> [arguments]\n");
	printf("\nCommands:\n");
	printf("replace <old_text> <new_text> - text replacement\n");
	printf("delete <temp> - remove strs including temps\n");
	printf("prepend <text> - add text in the beggining of each str\n");
	printf("append <text> - add text to the end of each str\n");
	printf("\nExamples:\n");
	printf("sed_editor test.txt replace \"old\" \"new\"\n");
	printf("sed_editor test.txt delete \"remove\"\n");
	printf("sed_editor test.txt prepend \"beginning_\"\n");
	printf("sed_editor test.txt append \"_ending\"\n");
}

int main(int argc, char *argv[]) {
	if (argc < 3){
		print_usage();
		return 1;
	}

	const char *filename = argv[1];
	const char *command = argv[2];

	if (strcmp(command, "replace") == 0) {
		if (argc != 5) {
			printf("Error: replace command requires 2 arguments\n");
			printf("Usage: %s <file> replace <old> <new>\n", argv[0]);
			return 1;
		}
		replace_in_file(filename, argv[3], argv[4]);
		printf("replacement complete '%s' to '%s' in file '%s'\n", argv[3], argv[4], filename);
	}
	else if (strcmp(command, "delete") == 0) {
		if (argc != 4) {
			printf("Error: command delete requires 1 argument\n");
			printf("Usage: %s <file> delete <temp>\n", argv[0]);
			return 1;
		}
		delete_lines(filename, argv[3]);
		printf("Strs deleted, including '%s' from the file '%s'\n", argv[3], filename);
	}
	else if (strcmp(command, "prepend") == 0) {
		if (argc != 4) {
			printf("Error: command prepend requires 1 argument\n");
			printf("Usage: %s <file> prepend <text>\n", argv[0]);
			return 1;
		}
		prepend_to_lines(filename, argv[3]);
		printf("Text '%s' added to the beginning of each str in the file '%s'\n", argv[3], filename);
	}
	else if (strcmp(command, "append") == 0) {
		if (argc != 4) {
			printf("Error: command append requires 1 argument\n");
			printf("Usage: %s <file> append <text>\n", argv[0]);
			return 1;
		}
		append_to_lines(filename, argv[3]);
		printf("Text '%s' added to the end of each str in the file '%s'\n", argv[3], filename);
	}
	else {
		printf("Unknown command: %s\n", command);
		print_usage();
		return 1;
	}

	return 0;
}
