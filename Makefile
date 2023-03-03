CLIENT = client
SERVER = server
LIBFT_PATH = printflibft
LIBFT_LIB = $(LIBFT_PATH)/libft.a

CLIENT_SRC = client.c
SERVER_SRC = server.c

CLIENT_OBJ = $(CLIENT_SRC:.c=.o)
SERVER_OBJ = $(SERVER_SRC:.c=.o)

CC = gcc
CFLAGS += -g -Wall -Wextra -Werror -I$(LIBFT_PATH)/include
LDFLAGS = -L$(LIBFT_PATH) -lft
ASAN_FLAGS = -fsanitize=address -fno-omit-frame-pointer -Wno-format-security
ASAN_LIBS  = -static-libasan

all: $(CLIENT) $(SERVER)

$(CLIENT): $(CLIENT_OBJ) $(LIBFT_LIB)
	$(CC) $(LDFLAGS) $^ -o $@

$(SERVER): $(SERVER_OBJ) $(LIBFT_LIB)
	$(CC) $(LDFLAGS) $^ -o $@

$(CLIENT_OBJ): $(CLIENT_SRC)
	$(CC) $(CFLAGS) $(ASAN_FLAGS)-c $< -o $@

$(SERVER_OBJ): $(SERVER_SRC)
	$(CC) $(CFLAGS) $(ASAN_FLAGS)-c $< -o $@

$(LIBFT_LIB):
	make -C $(LIBFT_PATH)

clean:
	rm -f $(CLIENT_OBJ) $(SERVER_OBJ)
	make -C $(LIBFT_PATH) clean

fclean: clean
	rm -f $(CLIENT) $(SERVER)
	make -C $(LIBFT_PATH) fclean

re: fclean all