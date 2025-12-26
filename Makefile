# Переменные
CC = gcc
CFLAGS = -Wall -Wextra -std=gnu11 -D_GNU_SOURCE
TARGET = sed_editor
SOURCES = main.c operations.c
OBJECTS = $(SOURCES:.c=.o)

# Цель по умолчанию
all: $(TARGET)

# Сборка исполняемого файла
$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS)

# Компиляция в .о
$.o: %.c operations.h
	$(CC) $(CFLAGS) -c $< -o $@

# Очистка
clean:
	rm -f $(TARGET) $(OBJECTS) test_txt temp_* 2>/dev/null || true

# Тестрование
test: $(TARGET)
	@echo "=== Testing sed_editor ==="
	
	@echo "Creating test file..."
	@echo "str1\nstr2\ntest str\nstr3\nstr with test" > test.txt

	@echo "\n1. Replacement test:"
	@echo "file before replacement:"
	@cat test.txt
	@echo "\nReplacing 'str' with 'line'..."
	@./$(TARGET) test.txt replace "str" "line"
	@echo "\nFile after replacement:"
	@cat test.txt

	@echo "\n\n2. Str deletion test:"
	@echo "Deleting strs with 'test'..."
	@./$(TARGET) test.txt delete "test"
	@echo "\nFile after deletion:"
	@cat test.txt

	@echo "\n\n3. Beginning addition test:"
	@echo "Adding '>>> ' to the beginning str..."
	@./$(TARGET) test.txt prepend ">>> "
	@echo "\nFile after adding to the beginning:"
	@cat test.txt

	@echo "\n\n4. End addition test:"
	@echo "Adding ' [end]' into  str end..."
	@./$(TARGET) test.txt append " [end]"
	@echo "\nFile after adding to the end:"
	@cat test.txt

	@echo "\n=== Testing ended ==="
	@rm -f test.txt

.PHONY: all clean test
