.DEFAULT_GOAL := all
SRCS = ft_pipe.c ft_parser.c ft_err_handle.c ft_split_parse.c ft_split_parse_utill.c
SRCS_BONUS = ft_pipe_bonus.c ft_parser_bonus.c ft_err_handle_bonus.c ft_split_parse_bonus.c ft_split_parse_utill_bonus.c
LIBFT_DIR = ./libft
LIBFT_NAME = ft
LIBFT = libft/libft.a
OBJS = $(SRCS:.c=.o)
OBJS_BONUS = $(SRCS_BONUS:.c=.o)
DEPS = $(SRCS:.c=.d)
DEPS_BONUS = $(SRCS_BONUS:.c=.d)
CC = cc -Wall -Wextra -Werror -MMD -MP
NAME = pipex
NAME_BONUS = .bonus
-include $(DEPS)

all :
	make $(NAME)

bonus :
	make $(NAME_BONUS)

$(LIBFT) :
	make -C $(LIBFT_DIR)

$(NAME) : $(LIBFT) $(OBJS)
	$(CC) -o $(NAME) $(OBJS) -l$(LIBFT_NAME) -L$(LIBFT_DIR) -I$(LIBFT_DIR)

$(NAME_BONUS) : $(LIBFT) $(OBJS_BONUS)
	$(CC) -o $(NAME) $(OBJS_BONUS) -l$(LIBFT_NAME) -L$(LIBFT_DIR) -I$(LIBFT_DIR)
	touch $(NAME_BONUS)

%.o : %.c
	$(CC) -c $<  -I$(LIBFT_DIR)

clean :
	rm -f $(OBJS) $(DEPS) $(OBJS_BONUS) $(DEPS_BONUS)
	make -C $(LIBFT_DIR) clean

fclean :
	rm -f $(OBJS) $(NAME) $(DEPS) $(OBJS_BONUS) $(DEPS_BONUS) $(NAME_BONUS)
	make -C $(LIBFT_DIR) fclean

re : fclean
	make all

.PHONY: all clean fclean re
