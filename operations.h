#ifndef OPERATIONS_H
#define OPERATIONS_H

void replace_in_file(const char *filename, const char *old_str, const char *new_str);
void delete_lines(const char *filename, const char *pattern);
void prepend_to_lines(const char *filename, const char *text);
void append_to_lines(const char *filename, const char *text);

#endif
