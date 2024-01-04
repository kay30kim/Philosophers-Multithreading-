# Name
NAME		=	philo

# Flags
CC			=	gcc
CFLAGS		=	-Wall -Werror -Wextra
AR			=	ar rcs
RM			=	rm -f
LIBRARIES	=	-lpthread

# Directories
SOURCES_DIR	=	./src
INCLUDE_DIR	=	./include
OBJECTS_DIR	=	./objs

# Files
FILES		=	main.c 
SRCS		=	$(foreach FILE, $(FILES), $(SOURCES_DIR)/$(FILE))
#				$(foreach FILE, $(FILES), $(shell find $(SOURCES_DIR) -name $(FILE)))
#				$(addprefix $(SOURCES_DIR)/, $(FILES))
# foreach (var, list, text(rule))
OBJS		=	$(addprefix $(OBJECTS_DIR)/, $(notdir $(SRCS:.c=.o)))

# $@ = target = $(OBJECTS_DIR)/%.o
# $< = right side = $(SOURCES_DIR)/%.c
$(OBJECTS_DIR)/%.o: $(SOURCES_DIR)/%.c
#	$(MKDIR) $(@D)
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -c -o $@ $<

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBRARIES) -o $(NAME)

clean:
	$(RM) $(OBJECTS_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all norminette clean fclean re