NAME		= Iza_ary_A
RM 			= rm -rf
MKDIR_P		= mkdir -p
SRCS_PATH	= ./srcs
OBJS_PATH	= ./objs
INCLUDE		= -I ./include
SRCS		= $(shell find $(SRCS_PATH) -name "*.c")
OBJS		= $(patsubst $(SRCS_PATH)/%.c,$(OBJS_PATH)/%.o,$(SRCS))
CC			= gcc -Wall -Wextra -Werror -g
SDL_FLAG	= -lSDL2 -I/usr/include/SDL2

$(OBJS_PATH)/%.o: $(SRCS_PATH)/%.c
	$(MKDIR_P) $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(SDL_FLAG) $(INCLUDE) $(OBJS) -o $(NAME)

all: $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all
