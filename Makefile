NAME		= Iza_ary_A
CC			= gcc -Wall -Wextra -Werror
RM 			= rm -rf
# MKDIR_P		= mkdir -p

# SRCS_PATH	= ./srcs
# OBJS_PATH	= ./objs

# SRCS		= $(shell find $(SRCS_PATH) -name "*.c")
# OBJS		= $(patsubst $(SRCS_PATH)/%.c,$(OBJS_PATH)/%.o,$(SRCS))

# $(OBJS_PATH)/%.o: $(SRCS_PATH)/%.c
# 	$(MKDIR_P) $(dir $@)
# 	$(CC) $(CFLAGS) -c $< -o $@

# $(NAME): $(OBJS)
# 	make -C libft
# 	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -L./libft -lft -lreadline

all: $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all
