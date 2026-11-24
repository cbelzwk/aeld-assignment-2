# Set CROSS_COMPILE=aarch64-none-linux-gnu- on the make command line to
# cross-compile for the ARM target (toolchain in /opt/arm-gnu-toolchain).
CROSS_COMPILE ?=
CC := $(CROSS_COMPILE)gcc
CFLAGS += -Wall -Werror

SRC := writer.c
TARGET = writer
OBJS := $(SRC:.c=.o)

all: $(TARGET)

$(TARGET) : $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) -o $(TARGET) $(LDFLAGS)

clean:
	-rm -f *.o $(TARGET) *.elf *.map
