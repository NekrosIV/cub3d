NAME = libft.a
CC = cc
CFLAGS = -Wall -Wextra -Werror -g3 -MMD

# COLOR #
GREEN	:= \033[38;5;76m
RED		:= \033[38;5;160m
YELLOW	:= \033[38;5;226m
ORANGE	:= \033[38;5;202m
PURPLE	:= \033[38;5;213m
LBLUE	:= \033[38;5;51m
BLUE	:= \033[38;5;117m
INDI	:= \033[38;5;99m
RESET	:= \033[00m

FILES = ft_isalpha.c  \
		ft_isdigit.c \
		ft_isalnum.c  \
		ft_isascii.c  \
		ft_isprint.c  \
		ft_strlen.c  \
		ft_memset.c  \
		ft_bzero.c  \
		ft_memcpy.c \
		ft_memmove.c \
		ft_strlcpy.c \
		ft_strlcat.c \
		ft_toupper.c \
		ft_tolower.c \
		ft_strchr.c \
		ft_strrchr.c \
		ft_strncmp.c \
		ft_memchr.c \
		ft_memcmp.c  \
		ft_strnstr.c \
		ft_atoi.c \
		ft_calloc.c \
		ft_strdup.c \
		ft_substr.c \
		ft_strjoin.c \
		ft_strtrim.c \
		ft_split.c \
		ft_itoa.c \
		ft_putchar_fd.c  \
		ft_putstr_fd.c \
		ft_putendl_fd.c \
		ft_putnbr_fd.c \
		ft_strmapi.c \
		ft_striteri.c \
		ft_lstnew.c  \
		ft_lstadd_front.c  \
		ft_lstsize.c  \
		ft_lstlast.c  \
		ft_lstadd_back.c  \
		ft_lstdelone.c  \
		ft_lstclear.c \
		ft_lstiter.c \
		ft_lstmap.c \
		ft_printf.c \
		ft_print_char.c \
		ft_print_str.c \
		ft_print_p.c \
		ft_print_int.c \
		ft_print_unsigned_int.c \
		ft_putnbr_base_16.c \
		get_next_line.c \
		ft_split_piscine.c \
		get_next_line_utils.c

SRCS_DIR := ./src
OBJS_DIR := ./poubelle

SRCS := $(addprefix $(SRCS_DIR)/, $(FILES)) 
OBJS := $(addprefix $(OBJS_DIR)/, $(FILES:.c=.o))
DEPS := $(OBJS:.o=.d)

HEADER = ./include

all : ${NAME} 

${NAME} : ${OBJS}
	@ar rc $@ $^

$(OBJS_DIR) :
	@mkdir -p $@

-include $(DEPS)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c | $(OBJS_DIR)
	@printf "$(LBLUE)[Compilation]$(RESET) In progress... $(GREEN)$<" && \
	$(CC) $(CFLAGS) -I$(HEADER) -c $< -o $@ && \
	printf "\r$(LBLUE)[Compilation]$(RESET) Completed   ... $(GREEN)$<" && \
	printf " $(LBLUE)[$(RESET)$(CC)$(LBLUE)/]$(RESET)\n"

clean :
	@rm -rf ${OBJS_DIR}
	@printf "$(GREEN)Libft is Clean\n$(RESET)"

fclean : clean
	@rm -f ${NAME}


re : fclean all

.PHONY : all clean fclean re
