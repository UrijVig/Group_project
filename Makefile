CC = gcc
CFLAGS = -Wall -Wextra -Werror -I.
LDFLAGS = -lncurses
TARGET = game_of_life
SRCS = game_of_life.c grid.c patterns.c ncurses_utils.c game_logic.c input_handler.c
OBJS = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Запуск с различными паттернами
run1: $(TARGET)
	./$(TARGET) 1

run2: $(TARGET)
	./$(TARGET) 2

run3: $(TARGET)
	./$(TARGET) 3

run4: $(TARGET)
	./$(TARGET) 4

run5: $(TARGET)
	./$(TARGET) 5

# Запуск с вводом из stdin
run-stdin: $(TARGET)
	./$(TARGET) stdin

# Запуск с загрузкой из файла
run-file: $(TARGET)
	@echo "Пример загрузки из файла:"
	@echo "cat ../patterns/glider.txt | ./$(TARGET) stdin"
	@echo ""
	cat ../patterns/glider.txt | ./$(TARGET) stdin

# Интерактивный режим
run-interactive: $(TARGET)
	./$(TARGET)

# Очистка
clean:
	rm -f $(OBJS) $(TARGET)

# Полная пересборка
rebuild: clean all

.PHONY: all clean rebuild run1 run2 run3 run4 run5 run-stdin run-file run-interactive