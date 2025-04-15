SRC = parser.c \
      1-ft_tokenize.c \
	  ft_split_tokens.c \
	  ft_isspace.c \
	  ft_isquot.c \
	  ft_token_new.c \
	  ft_token_add_back.c \
	  ft_token_delone.c \
	  ft_token_clear.c \
	  ft_token_size.c \
	  ft_print.c \


OBJS = $(SRC:.c=.o)

NAME = parsi
CC = cc 
CFLAGS = -Wall -Wextra -Werror -I/mnt/homes/eel-garo/Desktop/readline/include 
LDFLAG = -L/mnt/homes/eel-garo/Desktop/readline/lib -lreadline -lncurses
RM = rm -rf

all: $(NAME)

$(NAME): $(OBJS) parser.h
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LDFLAG)


%.o:%.c parser.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	${RM} ${OBJS}

fclean: clean
	${RM} ${NAME}

re: fclean all

run:
	@$(MAKE) all
	@$(MAKE) clean
	@echo "Build complete, object files cleand."
	
