.DEFAULT_GOAL := all
SRCS = ft_pipe.c ft_parser.c ft_err_handle.c
LIBFT_DIR = ./libft
LIBFT_NAME = ft
LIBFT = libft/libft.a
OBJS = $(SRCS:.c=.o)
DEPS = $(SRCS:.c=.d)
CC = cc -Wall -Wextra -Werror -MMD -MP
NAME = pipex
-include $(DEPS)

all :
	make $(NAME)

$(LIBFT) :
	make -C $(LIBFT_DIR)

$(NAME) : $(LIBFT) $(OBJS)
	$(CC) -o $(NAME) $(OBJS) -l$(LIBFT_NAME) -L$(LIBFT_DIR)

%.o : %.c
	$(CC) -c $<

clean :
	rm -f $(OBJS) $(DEPS)
	make -C $(LIBFT_DIR) clean

fclean :
	rm -f $(OBJS) $(NAME) $(DEPS)
	make -C $(LIBFT_DIR) fclean

re : fclean
	make all

.PHONY: all clean fclean re
