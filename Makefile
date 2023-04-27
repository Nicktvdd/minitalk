NAME_CLIENT = client
NAME_SERVER = server

SRCS_CLIENT = client.c
SRCS_SERVER = server.c

OBJS_CLIENT = $(SRCS_CLIENT:%.c=%.o)
OBJS_SERVER = $(SRCS_SERVER:%.c=%.o)

LIBFT_DIR = libft/
LIBFT_NAME = libft.a
LIBFT = $(LIBFT_DIR)$(LIBFT_NAME)

CFLAGS = -Wall -Wextra -Werror
LDFLAGS = 

all: $(NAME_CLIENT) (NAME_SERVER)

$(NAME_CLIENT): $(OBJS_CLIENT) $(LIBFT)
	cc $(CFLAGS) $(LDFLAGS) $(OBJS_CLIENT) -L$(LIBFT_DIR) -lft -o $(NAME_CLIENT)

$(NAME_SERVER): $(OBJS_SERVER) $(LIBFT)
	cc $(CFLAGS) $(LDFLAGS) $(OBJS_SERVER) -L$(LIBFT_DIR) -lft -o $(NAME_SERVER)

%.o: %.c $(LIBFT)
	cc $(CFLAGS) -c $< -o $@

$(LIBFT):
	make -C $(LIBFT_DIR)

clean:
	rm -f $(OBJS_CLIENT)
	rm -f $(OBJS_SERVER)
	make -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME_CLIENT)
	rm -f $(NAME_SERVER)
	rm -f $(LIBFT)
	make -C $(LIBFT_DIR) fclean

re: fclean all
