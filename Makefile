CC = gcc
CFLAGS = -Wall -g -Iinclude -MD

SRCS_DIR = src
OBJS_DIR = obj
TARGET_DIR = bin

SRCS = 
OBJS = 

TARGET = $(TARGET_DIR)/QuantumStack

all: $(TARGET)

clean: $(OBJS_DIR)
	rm -rf $<

