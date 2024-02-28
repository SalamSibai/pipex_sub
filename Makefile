NAME	=	pipex

MAND_MAIN = main.c

BONUS_MAIN = bonus_main.c

FILES	=	parsing.c \
			pipex.c pipex_utils.c \
			redirect_fds.c error_handler.c \
			parsing_utils/ft_split.c \
			parsing_utils/px_libft.c \
			parsing_utils/parse_error.c \

BONUS_FILES =	bonus_main.c parsing.c \
				pipex.c pipex_utils.c \
				redirect_fds.c error_handler.c \
				parsing_utils/ft_split.c \
				parsing_utils/px_libft.c \
				parsing_utils/parse_error.c \
				get_next_line/get_next_line.c get_next_line/get_next_line_utils.c \

OBJS 	=	$(FILES:.c=.o)

MAIN_OBJ = $(MAND_MAIN:.c=.o)

BONUS_MAIN_OBJ = $(BONUS_MAIN:.c=.o)

BONUS_OBJS =	$(BONUS_FILES:.c=.o)

CFLAGS	= -Wall -Werror -Wextra

all : $(NAME)

$(NAME) :	$(OBJS) $(MAIN_OBJ)
	$(CC)	$(CFLAGS) -o $@ $^

bonus:	$(BONUS_OBJS)
		$(CC) $(CFLAGS) $(BONUS_OBJS) -o $(NAME)
		rm -f $(MAIN_OBJ)

clean :
		rm -f $(OBJS)
		rm -f $(BONUS_OBJS)
		@if [ -n "$(MAIN_OBJ)" ]; then rm -f $(MAIN_OBJ); fi
		@if [ -n "$(BONUS_MAIN_OBJ)" ]; then rm -f $(BONUS_MAIN_OBJ); fi

fclean: clean
		rm -f $(NAME)
		@if [ -n "$(MAIN_OBJ)" ]; then rm -f $(MAIN_OBJ); fi
		@if [ -n "$(BONUS_MAIN_OBJ)" ]; then rm -f $(BONUS_MAIN_OBJ); fi
re:	fclean all
 
.PHONY: all clean fclean re