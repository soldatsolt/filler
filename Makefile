MAKE=make
NAME=kmills.filler
SRCS=SRCS/main.c
OBJS=$(SRCS:SRCS%.c=OBJS%.o)
INCLUDES=INCLUDES/
A_FILES=libft/libft.a libft/libftprintf.a
NO_COLOR=\x1b[0m
OK_COLOR=\x1b[32;01m
ERROR_COLOR=\x1b[31;01m
WARN_COLOR=\x1b[33;01m
COMPILING_STRING=$(OK_COLOR)[KMILLS.FILLER COMPILED]$(NO_COLOR)
REMOVE_ALL_STRING=$(ERROR_COLOR)[KMILLS.FILLER REMOVED]$(NO_COLOR)
REMOVE_O_STRING=$(WARN_COLOR)[ALL .O REMOVED]$(NO_COLOR)
ECHO=echo
override G +=

all: $(NAME)

$(NAME): $(OBJS) $(INCLUDES)
	@$(MAKE) -C libft
	@gcc $(A_FILES) $(OBJS) -o $(NAME)
	@$(ECHO) "$(COMPILING_STRING)"

OBJS/%.o: SRCS/%.c $(INCLUDES)
	@gcc -c $< -I$(INCLUDES) -o $@

clean:
	@rm -f $(OBJS)
	@$(MAKE) -C libft clean
	@$(ECHO) "$(REMOVE_O_STRING)"

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C libft fclean
	@$(ECHO) "$(REMOVE_ALL_STRING)"

git:
	git add .
	git commit -am "$(G)"
	git push

re: fclean all
