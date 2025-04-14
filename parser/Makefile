SRC = parser.c \
      1-ft_tokenize.c \
	  ft_split.c \
	  ft_isspace.c \
	  ft_token_new.c \
	  ft_token_add_back.c \

OBJS = $(SRC:.c=.o)

NAME = parsi
CC = cc 
CFLAGS = -Wall -Wextra -Werror
LDFLAG = -lreadline
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
	
