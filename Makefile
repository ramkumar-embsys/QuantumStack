CC = gcc
CFLAGS = -Wall -Wextra -Werror -g -Iinclude -MMD 

SRCS_DIR = src
OBJS_DIR = obj
TARGET_DIR = bin

SRCS = $(wildcard *.c $(addsuffix /*.c,$(SRCS_DIR)))
OBJS = $(patsubst %.c, $(OBJS_DIR)/%.o, $(notdir $(SRCS)))

VPATH = $(SRCS_DIR)

TARGET = $(TARGET_DIR)/QuantumStack

$(OBJS_DIR)/%.o: %.c | $(OBJS_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET): $(OBJS) | $(TARGET_DIR)
	$(CC) $(CFLAGS) $(OBJS) -o $@

$(OBJS_DIR) | $(TARGET_DIR):
	mkdir -p $@

debug:
	echo "SRCS = $(SRCS)"
	echo "OBJS = $(OBJS)"

all: $(TARGET)

clean: 
	rm -rf $(OBJS_DIR) $(TARGET_DIR)

-include $(OBJS:.o=.d)

