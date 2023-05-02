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

BONUS_CLIENT = $(SRCS_CLIENT:%.c=%_bonus.c)
BONUS_SERVER = $(SRCS_SERVER:%.c=%_bonus.c)
BONUS_OBJS_CLIENT = $(BONUS_CLIENT:%.c=%.o)
BONUS_OBJS_SERVER = $(BONUS_SERVER:%.c=%.o)

all: $(NAME_CLIENT) $(NAME_SERVER)

$(NAME_CLIENT): $(OBJS_CLIENT) $(LIBFT)
	cc $(CFLAGS) $(OBJS_CLIENT) -L$(LIBFT_DIR) -lft -o $(NAME_CLIENT)

$(NAME_SERVER): $(OBJS_SERVER) $(LIBFT)
	cc $(CFLAGS) $(OBJS_SERVER) -L$(LIBFT_DIR) -lft -o $(NAME_SERVER)

%.o: %.c $(LIBFT)
	cc $(CFLAGS) -c $< -o $@

$(LIBFT):
	make -C $(LIBFT_DIR)

clean:
	rm -f $(OBJS_CLIENT) $(OBJS_SERVER)
	rm -f $(BONUS_OBJS_CLIENT) $(BONUS_OBJS_SERVER)
	make -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME_CLIENT) $(NAME_SERVER)
	rm -f $(LIBFT)
	make -C $(LIBFT_DIR) fclean

re: fclean all

bonus: $(NAME_CLIENT) $(NAME_SERVER)

$(BONUS_CLIENT): $(BONUS_OBJS_CLIENT) $(LIBFT)
	cc $(CFLAGS) $(BONUS_OBJS_CLIENT) -L$(LIBFT_DIR) -lft -o $(NAME_CLIENT)

$(BONUS_SERVER): $(BONUS_OBJS_SERVER) $(LIBFT)
	cc $(CFLAGS) $(BONUS_OBJS_SERVER) -L$(LIBFT_DIR) -lft -o $(NAME_SERVER)

$(BONUS_OBJS_CLIENT): $(BONUS_CLIENT)
	cc $(CFLAGS) -c $< -o $@

$(BONUS_OBJS_SERVER): $(BONUS_SERVER)
	cc $(CFLAGS) -c $< -o $@