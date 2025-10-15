# 編譯器
CC = gcc

# 標頭檔路徑
INCLUDE_PATHS = -Iinclude -Isrc/header

# 編譯旗標
CFLAGS = -g -Wall $(INCLUDE_PATHS)

# 函式庫名稱
TARGET_LIB = lib/libdstruct.a

# 來源檔案 (注意：移除了 examples/main.c)
SRCS = src/core.c src/linked_list.c src/queue.c src/stack.c

# 將 .c 來源檔案列表轉換成 .o 物件檔案列表
OBJS = $(SRCS:.c=.o)

# --- 規則定義 ---

# 預設目標是建立函式庫
all: $(TARGET_LIB)

# 建立函式庫的規則
# $@ 代表目標 (libdstruct.a)
# $^ 代表所有的依賴項 (core.o linked_list.o ...)
$(TARGET_LIB): $(OBJS)
	ar rcs $@ $^

# 編譯 .c 到 .o 的規則 (不變)
%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

# 清理規則 (也清理函式庫檔案)
clean:
	rm -f $(TARGET_LIB) $(OBJS)

.PHONY: all clean
