NAME := Cub3d
CC := cc
CFLAGS :=  -g3 -MMD -O3
MLX_FLAGS = -Lmlx -lmlx -Imlx -lXext -lX11 -lm 
LIBFTDIR := ./libft
MLXDIR := ./mlx

FILES := cub3d.c \
		parsing/parsing.c \
		error/exit.c \
		init/init_mlx.c \
		init/init_struct.c \
		player/player_move.c \
		minimap/minimap.c \
		key/key.c \
		draw/draw.c \
		draw/raycastingbot.c \
		draw/raycasting.c \
		utils.c 

SRCS_DIR := ./src
OBJS_DIR := ./poubelle

SRCS := $(addprefix $(SRCS_DIR)/, $(FILES)) 
OBJS := $(addprefix $(OBJS_DIR)/, $(FILES:.c=.o))
DEPS := $(OBJS:.o=.d)

HEADERS := ./include

# COLOR #
GREEN	:= \033[38;5;76m
RED		:= \033[38;5;160m
BRIGHT_RED := \033[38;5;196m
YELLOW	:= \033[38;5;226m
ORANGE	:= \033[38;5;202m
PURPLE	:= \033[38;5;213m
LBLUE	:= \033[38;5;51m
BLUE	:= \033[38;5;117m
INDI	:= \033[38;5;99m
RESET	:= \033[00m
BROWN   := \033[38;5;130m
PINK    := \033[38;5;218m
GOLD := \033[38;5;220m
DARK_BLUE := \033[38;5;26m
MINT_GREEN := \033[38;5;38m

OBJ_SUBDIRS := $(sort $(dir $(OBJS)))

all: $(NAME)

$(NAME): $(OBJS)
	@make --silent -C ${LIBFTDIR}
	@make --silent -C ${MLXDIR}
	@$(CC) $(CFLAGS) -I$(HEADERS) -o $@ $(OBJS) ${MLX_FLAGS} -L ${LIBFTDIR} -lft
	@printf "$(RESET)\n\n\n"
	@printf "⠀⠀$(PURPLE)⢀⠂⠘⠀⠱⠈⡝⣏⠐⠀⠑⠒⠤⣼⢶⠁⣠⠀⠠$(INDI)⠀⠀⠀⠀⢸⠍⣎⢙⣿⣿⢿⡁⠤⠀⠀⠀⠀⠀⣠⣾⣿⣿⣿⣿⣿⣿⣿⣿⣷⣦⣄⡀⠀$(RED)⠀⠀⠀⠀⠀⠀⠄⣡⠀⠈⠒⠄⢄⠀⠀⠀$(INDI)⠐⣫⡇⠀⠀⠀⠀⠀⠀⠀⠀⠈⠙⠶⣷⣴⣥⣐⠘⢟⡟⡧⢛⣤⣳⣿⣿⠿⠟⠉⠀⠀⣰⡛⠄$(BLUE)⠀⠀⠀⠀⠀⠀⠈⢿⣿⣿⡇⠒⡤$(RESET)\n"
	@printf "⠀$(PURPLE)⠀⡠⠒⠂⠡⠐⠁⡠⠠⢈⠍⠁⠀⠘⢟⢾⣿⣿⡀⠁$(INDI)⠀⠀⠀⠀⠘⢦⠰⣍⡻⣿⢀⢺⠁⠀⠀⠀⢀⣼⣿⣿⣿⣿⣿⣿⣿⣿⡿⣿⢹⣿⣿⣿⣆⡀$(RED)⠀⠀⠀⠀⢠⢚⡤⡸⢊⣀⢨⣌⠀⠀⠀$(INDI)⢚⡿⠀⡰⠀⡀⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠁⠉⠛⠊⢀⠔⠿⠿⠋⠉⠀⠀⠀⠀⠀⣸⣿⣯$(BLUE)⠀⢀⡠⠶⣀⠀⠀⠀⠘⣿⡅⠈⠌⠋$(RESET)\n"
	@printf "⠀$(PURPLE)⠈⡄⠀⠀⠆⠈⢐⠡⠀⠀⠀⢀⣐⡁⠐⠉⡛⡛⠹⠈⢄⠀$(INDI)⠀⠀⠀⢿⡂⢿⣿⣮⠸⡇⠀⠀⠀⠀⢰⣿⣿⣿⣿⣿⣛⠛⠿⣿⣶⡶⢬⣉⣿⣿⣿⡥$(RED)⠀⠀⠀⠀⠢⠋⡠⢴⣋⢆⠁⠈⠁⡀$(INDI)⢰⣿⠁⢠⠁⢸⡗⠀⠁⢢⡄⢀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⡽⣿⣿$(BLUE)⢲⠟⠨⠽⣛⣤⠀⠈⠀⣥⣰⡆⣄⣂$(RESET)\n"
	@printf "⠀$(PURPLE)⠀⠀⠀⠁⠂⠀⠀⢃⣠⣾⣿⣿⣿⣿⡀⠀⠁⠈⠀⢀⠨⡀$(INDI)⠀⢀⡳⠵⣥⡘⢿⣯⠳⡀⣀⠀⠀⢠⣿⣿⣿⠡⣶⠂⢉⡐⡠⠄⡙⣿⣼⡿⠿⠿⣟⢾$(RED)⠀⠀⠀⠀⠈⢠⡍⣤⢭⣤⣬⢀⠀⠀$(INDI)⠢⠈⠀⠎⠀⣈⠁⠀⠀⠛⠃⠀⠈$(GOLD)⣠⡄⡄⢠⣐⢠⣴⣷⣾⣄⢆⡠$(INDI)⠀⠄⢀⠀⠀⢀⠎⡽⣿⣿⠇$(BLUE)⠶⣤⣾⣿⣿⡆⢀⠀⣿⣿⣿⣷⡇$(RESET)\n"
	@printf "⠀⠀⠀⠀$(PURPLE)⢰⣶⣶⣶⣿⣿⣿⣿⡿⠿⠿⢷⣤⣄⠀⢀⠠⠚⢱$(INDI)⣶⢮⣥⢄⣬⠝⢷⣝⠃⢂⠌⠻⣄⣾⣿⣿⣿⣧⣬⣤⣤⣜⣹⣾⣿⣿⠉⠀⠀⠐⢢⡝⡐⠀⢀$(RED)⠀⡡⡀⢃⣶⣶⣶⣯⡜⠁⠀$(INDI)⡟⠀⠘⠀⡀⣈⠀⠀⢰⡇$(GOLD)⠠⣀⣀⢟⠵⣚⣭⣴⣿⣿⣶⣶⣆⡤⢆⣉⢁⠐⠪⢐$(INDI)⠻⣆⠹⠝$(BLUE)⡁⠠⠈⠁⠀⣹⡿⠁⢸⣦⠘⢟⢣⠤⠈$(RESET)\n"
	@printf "⠀$(PURPLE)⠀⠌⡧⢘⣿⣿⣿⣿⣿⣿⢿⣾⣿⣿⣿⢿⣿⡆$(INDI)⣮⣀⠈⢐⡪⢦⡄⠈⠗⢠⣷⣍⠂⡿⠰⠂⣽⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣟⢠⡀⠈⠽⡀⠀⣠⡴⠃$(RED)⠀⢑⡄⣒⠐⠒⠂⠭⢑⠀$(INDI)⣴⠇⠀⣶⠀⠀⠩⠒$(GOLD)⣰⣵⣿⣿⣯⡝⡵⢟⣻⣿⣿⣿⣿⣿⣿⣟⡻⢿⣾⣽⣖⡥⣺⢿⣮⣕⡆$(BLUE)⣷⠀⠀⢀⠺⠟⠀⣠⠼⣫⣴⠆⠀⠂⠄$(RESET)\n"
	@printf "⠀⠀$(PURPLE)⠼⡓⡀⣌⠛⢿⣿⣿⣧⢊⡾⣟⠩⣢⣿⣿⡿$(INDI)⢘⣟⠃⠨⠀⠋⢥⡜⠿⠿⣿⡟⠂⠑⢄⣀⢹⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⣿⡿⠃⣿⣿⣟⠃⡜⠉⢔⣡⣶⡿$(RED)⠐⠡⢣⠒⠜⠦⠀$(INDI)⢸⡏⠀⠀⣋⡀⠀$(GOLD)⢖⢿⣿⣿⡿⠳⠶⢠⣾⢿⣿⣿⣿⣿⣿⣿⣿⣿⢿⡻⣾⣽⡻⣿⣶⣥⡚⣙⠢$(BLUE)⠿⠇⣀⣀⡈⠰⠂⠲⣿⣿⡿⠁⠀⠀⠀$(RESET)\n"
	@printf "⠀⠀$(PURPLE)⠠⢡⠱⣄⠛⢗⢹⣿⣷⣷⣾⣿⡏⠻⣿⣿⣿$(INDI)⠂⠩⡔⣠⡦⢚⣵⣶⣽⡆⣹⡟⠀⠀⠀⠧⠈⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣋⠤⣜⢿⣻⡞⠀⢀⣼⣿⣿⡟⠁⠀⠀⡀$(RED)⠀⠀$(INDI)⣀⣤⣾⠀⠀⠀⠹⢃$(GOLD)⢆⣵⡿⣫⣶⣾⣭⢋⢉⣾⣿⣿⣿⣿⣿⣛⠿⣿⣿⣿⣶⣼⡛⢿⣷⣭⡻⢯⡒⢝⠿⠆$(BLUE)⠀⠀⢁⡄⠀⢰⣝⡛⠀⠀⠀⠀⠀$(RESET)\n"
	@printf "⠀⠀$(PURPLE)⢐⡠⢿⣿⡆⠘⢻⣿⣿⣿⣿⣿⣿⣀⣽⣿⣿⣇$(INDI)⢀⠄⢿⡡⢾⣿⣝⣿⡇⣤⠠⠁⠀⠀⠇⠀⢸⣿⣿⣿⣿⣿⣿⡿⠿⠿⣭⡐⠻⣜⣯⡟⠀⣠⠟⣽⢫⢃⣠⣤⣶⠟$(INDI)⠀⠀⠠⠿⣿⡃$(GOLD)⠀⠀⠀⠰⢋⣾⡷⢢⡿⣿⣿⡿⢠⣾⣿⣿⣿⣿⣿⣿⣿⣿⣶⣄⡛⣿⣽⢿⣷⣤⡠⣍⡛⠚⠥⠈⠈⠢⠀$(BLUE)⠿⣀⠆⣪⡶⠁⠀⠀⠀⠀⠀\n"
	@printf "⠀⠀$(PURPLE)⠰⡜⣄⠢⢍⠀⣼⣿⡿⣿⣿⣿⣿⢟⣽⣝⠻⣃$(INDI)⣀⡙⠶⣝⣂⠉⠛⢿⣧⢿⡀⠀⠀⠀⠀⡄⠀⠙⠿⣿⣿⣿⣿⣷⡲⡰⢤⡬⣗⣿⠊⠀⡰⢥⠛$(BRIGHT_RED)⣈⢤⣭⣅⡲⢔⠄⡀$(INDI)⠀⠀⠀⠀⠉⠲⣦$(GOLD)⣔⣜⣾⣻⣱⡿⣹⣿⣿⡷⣸⣿⣿⣿⠿⣿⣿⣝⡻⣮⣻⣿⣿⣮⡛⠿⣿⣝⢿⣦⡙⢦⢈⠛⢧⣢$(BLUE)⡹⡏⠀⢰⡿⠁⠀⠀⠀⠀⠀⠀$(RESET)\n"
	@printf "⠀⠀⠀$(PURPLE)⢡⠂⡍⢢⣦⢩⡑⢐⠛⠫⠽⣢⣯⣝⢟⣡$(INDI)⣤⣬⣭⣿⣿⣮⣗⡠⣂⠹⣞⣿⡈⠄⠀⢰⣧⣃⠐⣀⠈⠻⣿⣿⣿⣷⣙⣧⢻⠝⠀⠀⢌⠑⡂$(BRIGHT_RED)⣨⣙⡛⡔⠢⡙⡌⠇⠁⡤$(GOLD)⠀⠀⠀⠀⠀⢨⢎⣞⡏⣿⣸⣡⡿⡟⣿⣧⣙⣿⣿⠿⣿⣮⡛⣿⣿⣮⡻⣷⣽⡙⠿⣧⡈⠙⢧⠈⠛⢦⠻⣕⢤⡁⠹$(BLUE)⡜⡄⠘$(RESET)⠀⠀⠀⠀⠀⠀⠀⠀\n"
	@printf "⠀⠀$(PURPLE)⡀⠡⠈⢄⢫⡿⠋⣠⣾⣿⣿⣶⡿⣹⠋$(INDI)⠀⡝⠿⣿⣿⡿⣿⣿⣿⣿⣾⣶⣜⣿⣧⠁⠀⠀⠉⠻⠄⠲⢢⠄⠈⠙⠟⣶⡹⠎⠁⠀⠀⠈⠀⣴⡇$(BRIGHT_RED)⣟⢭⠁⢨⣵⣶⣶⣾⣇⠀⠀⠐⢢⠈⡗$(GOLD)⠎⣼⢻⢹⣟⣿⢿⣷⡇⡟⢿⣧⢘⣿⣎⢮⡻⣿⣶⣍⢻⣿⣶⡙⢷⣄⠈⠛⢆⠀⠑⢤⣀⠑⠙⢮⣻⣄⢻⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
	@printf "⠀⠀$(PURPLE)⠴⣣⣼⠀⣦⢎⡊⠀⣼⣿⡿⠫⠞⠁$(INDI)⢀⠍⢘⣛⣂⣉⠹⠒⠦⠋⠝⠻⢿⣍⠘⢿⡆⠀⣀⠀⢄⠀⠀⠀⠙⣦⠀⡀⠀⠀⣠⠀⠀⠀⠀⢘⣻⣿⡄$(BRIGHT_RED)⡁⠀⣦⠿⠿⠷⣉⠁⠈⢄⠀⣼⢠⢃⣾$(GOLD)⠇⡟⣺⡧⣟⢹⡇⡇⣿⣤⢻⡆⠻⣿⣄⡙⢬⠻⢿⢧⡘⢿⣌⠪⣧⡀⢀⠀⠡⠑⢦⡘⣦⡈⠀⡳⢻⢘$(DARK_BLUE)⠄⢀⢀⠀⠀⠀⠀⠀⠀⠀\n"
	@printf "⠀⠀$(PURPLE)⠠⠛⢃⡋⢗⢃⣵⠾⡿⡫⢄⡃$(INDI)⠀⠀⠈⠀⠀⠙⠟⢿⣿⣿⣿⡿⢶⣦⠄⠩⠂⠈⢿⡰⠀⠀⠈⢳⡠⠀⢡⣿⡝⡶⠀⡞⡄⣀⠀⠀⠀⠎⢙⣭⡟$(BRIGHT_RED)⠀⠀⢿⣷⣶⣾⡿⠄⠉⠸⡄⣾⢺$(GREEN)⢄⠵⡄$(GOLD)⡇⢟⣅⣿⠸⠁⡇⢿⡌⢏⢿⡀⠉⠻⣿⡄⠑⡀⠁⠙⣄⠻⣆⠀⢻⡄⠂⠄⠀⠄⠻⣌⠏$(DARK_BLUE)⣦⣼⣧⣈⣿⣾⣥⣢⡤⣄⡀⠀⠀⠀$(RESET)\n"
	@printf "⠀⠀⠀$(PURPLE)⣦⣅⠢⠍⠉⠉⠈⢊⣙⡀⠂$(INDI)⠀⠀⠀⠀⠀⠰⠦⠥⡽⠋⠁⢐⠠⠂⡀⠁⠀⠁⠎⢣⠐⠎⡂⡀⠑⢄⣻⣛⠋⠑⣪⡗⠃⠀⠀⠀⠀⠐⠿⠟$(BRIGHT_RED)⠀⠹⣶⡀⠛⠿⣟⡀⢀⢟⣬⠀⡿$(GREEN)⡑⠁⠀⠃$(GOLD)⠀⠞⠋⠀⢀⡇⠱⠘⣧⠘⠌⢳⡀⠀⠈⠻⡄⣌⠠⠀⠀⠂⠙⡆⡄⠻⡄⢃⡆⡨$(DARK_BLUE)⠠⢭⣭⣾⣿⣿⠿⣿⣻⣿⣿⢷⣽⠃⠀⡄⢆$(RESET)\n"
	@printf "⠀$(PURPLE)⣠⡾⡿⠂⡰⠀$(RESET)⣤⣧⣄$(PURPLE)⠒⠀⠀⠥⠀$(MINT_GREEN)⠀⠒⢒⠀⠀⢤⡄⠐⠀⠀⡀⠀⠻⢿⣿⣷⣶$(INDI)⡱⢠⠠⣤⠔⢤⠚⢂⢢⡄⢀⡘⠃⠀⠀⠀⠀⠀⠀⠀$(BRIGHT_RED)⢠⣿⣄⠀⠀⠙⠀⠀⠈⠁⠈⡏⠇$(GREEN)⠈⠔⠀⠀⠀⠀⠀⠀⠀⠀$(GOLD)⣼⠝⡠⠃⠈⠆⠈⠀⠡⠀⠌⢦⣀⠙⢠⠀⡀⣶⣄⡐⠸⡀⢻⡀$(DARK_BLUE)⡜⠌⡳⣓⠽⡿⠛⠡⠒⠙⠿⢿⣿⣓⢁⣠⠺⣿⡆$(RESET)\n"
	@printf "⠀⣩⣵⣃⠀⠁⡴⣿⣟⣯$(PURPLE)⠰⡦⠐⠐⠶⠂$(MINT_GREEN)⢀⣨⣤⣶⠞⠁⠐⢶⢶⠇⡀⠀⠈⢙⠿⢫$(INDI)⢃⣾⡦⡉⠀⣈⠦⢊⠺⡷⠺⠁⠀⡐⠂⠀⠀⠀⠀$(BRIGHT_RED)⢠⣾⣿⣿⣦⣀⢀⡀⠀⠀⢀⠠⢱⠀⠀⠀⠀⠀$(GREEN)⡀$(GOLD)⠀⠀⠀⠀⠀⢉⣴⠃⢀⠀⠀⠀⠀⠠⣄⠐⢮⠛⢠⣌⠀⢣⡿⣽⣧⠀⢣⠘⣇⢡$(DARK_BLUE)⠐⢳⣽⡔⠡⢀⣠⣆⠀⠐⠚⢯⢛⣬⡯⠴⣿⡓$(RESET)\n"
	@printf "⠀⢉⣉⠛⠿⡆⣯⣉⡭⠍⢂⡔⠂⠀⠀⠁$(MINT_GREEN)⠻⣿⣿⠁⠀⢀⠘⡠⢜⣀⡾⠀⠀⠀⠀$(ORANGE)⢃⢸⡏⢩⣕⠊⠀⠉⠂⠀⠠⢂⡀⠀⠡⣓⡀⠀⠀$(BRIGHT_RED)⢀⣿⣿⣿⣟⢹⣿⠿⣪⣿⣿⣈⠤⠈⠁$(GREEN)⣤⣶⡿⠉⠩⣥⠀⠀⠀⠀$(GOLD)⠉⣠⢆⠀⡣⠍⠱⠷⣒⣬⡺⣬⣿⣥⣶⣶⣶⣿⣿⣿⠀⠈⠀$(DARK_BLUE)⠨⠈⠑⠒⠙⢏⠀⢹⣿⣿⣶⣒⠩⠑⢽⢩⠉⠀⠘⠃$(RESET)\n"
	@printf "⠀⠈⠛⠿⣦⢀⠐⠆⡠⢀⡒⠀$(YELLOW)⢲⡿⡿⣝⣕⣌⡳⠀$(MINT_GREEN)⠀⢠⠀⢛⡓⣉⡕⠐⡀$(ORANGE)⣴⣦⡌⢸⡱⠋⠈⠀⠀⠀⠀⠀⠀⢀⠃⠠⡒⠋⠀⠀⠀$(BRIGHT_RED)⣸⣿⣫⣶⡾$(PURPLE)⣦⡀⢰⡙⣣⠞⣫⠴⡲⠦$(GREEN)⠢⢹⣶⣧⣠⣿⡃⠀⠀$(GOLD)⡀⢼⡚⢇⡂⠉⣷⢿⣿⣿⡿⠁⢹⣿⣿⣿⣿⡿⠛⠉⠁⠀⠀$(DARK_BLUE)⠉⠀⠀⠀⠀⠀⠀⠀⠀⠙⢿⣽⣿⢆⢐⠄⡛⣁⢦⠀⠀$(RESET)\n"
	@printf "⠀⠀⠀⢀⣐⠮⠥⠄⣀⡠$(YELLOW)⡀⢶⡿⡇⠹⠜⠎⢫⡄⠁$(MINT_GREEN)⠀⡄⢩⣐⡉⠌⡈⠴$(ORANGE)⠀⠉⠉⠀⠘⣠⡄⠀⢀⠀⠀⠀⠀⠀⢸⡇⢀⡠⠄⠀⠀⠀$(BRIGHT_RED)⣿⠃$(PURPLE)⠈⠻⡧⠹⢯⠳⣣⠉⠊⡔⠣⠄⠙⢻⣦$(GREEN)⠛⠙⢿⡿⠀⠀$(GOLD)⠈⠣⢀⠑⠆⠙⠤⠀⠙⣿⣻⡵⣖⠤⢿⣿⣿⣿⡇⠀⠀⠀$(DARK_BLUE)⠁⠀⠀⢠⡀⠀⠀⠀⠀⠀⠀$(GOLD)⢀⣶⣦⣰⡀⠀⠀⠀$(DARK_BLUE)⠋⠈⠀⠀$(RESET)\n"
	@printf "⠀⠀⣰⣭⣛⡛⣛⣫⠍$(YELLOW)⠀⠧⠀⠘⠈⣀⡄⠀⠀⠀⠀$(MINT_GREEN)⠐⠃⠈⠻⠏⠀⠀⣱$(ORANGE)⠀⠀⠀⠀⢀⠑⠠⣦⣨⣬⠀⠀⠀⠀⣼⣇⡉⡸⠁⠀⠀⠀$(BRIGHT_RED)⢹⠀⡀$(PURPLE)⠔⢊⠵⠉⠂⠀⠠⢶⣶⠶⣦⣄⠀⠺$(GREEN)⢕⣰⠂⠚⡟⢧⣉⠐⡒⢄$(GOLD)⠠⠁⣀⠁⠀⠀⠁⠛⢼⣫⣭⣿⣿⢟⣾⡦⠀⠀$(DARK_BLUE)⢐⠎⢗⠈⢰⠀⠀⠀⠀⠀⠀$(GOLD)⠈⣿⣿⣷⢵⣕⣔⣀⡀⠀⣠⡇\n"
	@printf "⠀⠀$(RESET)⢹⣛⣙⠁$(YELLOW)⠨⠡⠄⠀⠀⠀⠀⣌⣿⣷⣾⠟⣱⡇$(MINT_GREEN)⠀⠀⠀⠀⠀⠀⡰⠁$(ORANGE)⠀⠀⠀⠀⠈⠳⠦⠙⠿⠮⠉⠀⠀⠀⣉⠅⠀⠁⠀⠀⠀⠀$(BRIGHT_RED)⠘$(PURPLE)⠄⠘⠀⢃⠒⡡⠄⢤⠩⢍⠈⠓⢡⠈⠓⡀⠀$(GREEN)⢹⡀⠈⢀⠃⢚⡓⠦⠈⢂⠦⣐⠦⣄⠤⢀⠀⠀⠀$(GOLD)⠋⠉⢠⡾⠃⣠⡧⠀$(DARK_BLUE)⢼⠎⠈⢿⣆⠀⠀⠀⠀⠀⠀$(GOLD)⣠⠿⠻⠟⣸⡞⣿⣿⣿⣿⣷⣽\n"
	@printf "⠀⠀$(YELLOW)⢷⡍⠿⣀⠀⣀⡠⠂⣀⠀⠀⠙⠛⠿⢫⠦⠉⣀⠀⠀⠐⡀⡄$(ORANGE)⠀⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠰⣬⡆⡿⠀⠁⠀⠀⠀$(PURPLE)⢠⣋⠡⡌⠥⢉⠄⡐⣂⠒⠢⠄⣈⠥⢘⡂⠁⠀⠑⡀$(GREEN)⡇⢨⡄⢀⠘⠣⠙⠐⠀⢂⠆⠙⠖⠀⢠⠀⠔⠑$(GOLD)⣢⠤⠛⣈⣥⠾⠿⠁⠀⠀⠀⠀⠀$(DARK_BLUE)⠈⠉⠀⠀⠀⠀$(GOLD)⢠⠖⢶⣚⠗⣩⢾⠿⠿⢍⣝⣳⣭\n"
	@printf "⠀⠀$(YELLOW)⠈⠉⠈⣼⡶⢛⡑⠄⢀⢖⣦⣦⠲⠈⣠⡆⠂⠹⠛⠽⢿⣿⡿⢍⣴⣆$(ORANGE)⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡀⠄⠜⠐⢠⠀$(PURPLE)⢀⠔⢛⣫⣷⡟⡰⢂⠌⢀⡑⢦⣙⡰⣦⡐⡙⢶⡈⡀$(GREEN)⠀⠠⣣⡴⣮⣤⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀$(GREEN)⠈⡀⠀$(GOLD)⢀⣠⣡⣄⠶⠘⢋⣼⡄⠀⠀⠀⠀⠀⠀⠀⠀⢠⠆⠀⢀⣫⣻⠛⠁⠌⣋⣤⢷⣾⣻⢿⡿⣟\n"
	@printf "⠀⠀$(YELLOW)⠠⣌⡄⣿⣅⠘⠀⠀⣌⣿⣿⣿⠁⢀⠗⣀⢯⢻⡇$(PINK)⢀⣿⡎⢙⣆⡉⠿⠆⣠⣀⠀$(ORANGE)⠀⠀⠀⠀⠀⠀⢀⣿⠀⠀⢠⠃⠀$(PURPLE)⢀⠴⢋⣽⠿⡼⢳⠃⢀⣤⡸⢢⡝⣿⣮⡻⢮⠲⡙⣄$(GREEN)⢢⢠⣅⠛⣫⡾⣷⠀⠀⠀⠀⠀⠀⢀⠐⡐⠲⡅$(GOLD)⡤⠟⠋⣉⢠⡔⢞⣾⡇⠀$(DARK_BLUE)⣀⠐⠒⣒⣀⠀⠀$(GOLD)⠀⡞⡀⠀⠀⠘⠁⣀⠶⠩⠛⠯⣿⡼⣏⡿⣵⢫\n"
	@printf "⠀⠀$(YELLOW)⠐⠀⠀⣿⣿⠀⣰⣦⢸⡏⡆⡿⠀⢰⣏⣏$(PINK)⡈⠘⢃⣰⣜⢷⣌⢿⣿$(BLUE)⡘⣷⣦⡉⠃⠉⠑⡀$(ORANGE)⢀⠒⠀⡀⠀⠀⠈⠂$(PURPLE)⠀⠀⠈⢠⠙⠁⠘⠁⢀⠀⢾⣿⣧⠁⠻⠑⡉⢓⠀⠀⠂⠴$(GREEN)⡈⢖⣤⠦⣄⣘⣩$(GOLD)⠴⣾⣶⡆$(GREEN)⠀⠀⣀⡤⢠⠈⡃⠕$(GOLD)⢞⠛⠋⡀⣴⡿⢊⡀$(DARK_BLUE)⠰⡭⣤⣜⡛⠯⣷⢦⣄$(GOLD)⠸⠈⠀⡀⠀⠀⠙⢾⡀⠀⠈⠀⠈⠉⠓⢭⣥\n"
	@printf "⠀⠀$(YELLOW)⣱⡀⢸⣿⣿⡎⣿⠇⢸⢱⠇⠀⠀⣾⢸⢹⣇$(PINK)⠛⢈⢳⣿⣮⢿⣷⣿⣷⢠$(BLUE)⡛⢿⣶⣄⡀⠀⠀⠀⠁⣠⣤⣶⣶⣾⣷⣶⣄$(PURPLE)⠂⠀⠄⠀⠀⢈⢘⡊⣿⣿⠀⡄⢡⠀⠀⠡⢀⠈⠄⠸$(GOLD)⣜⣷⣾⣿⣿⣿⣿⡶⢩⠆$(GREEN)⣀⣤⣶⣦⣕⠂⡈⠆$(GOLD)⢸⣿⡌⠁⢀⢠⡩⠗⡀$(DARK_BLUE)⠙⠚⠶⢹⠳⠖⠋⠓⢠⣤⣖⢍⣢⢀⠠⡶⢊⣀⠀⠀⠀⠀$(GOLD)⠤⠘⠛\n"
	@printf "⠀⠀$(YELLOW)⠘⠀⡘⣿⠸⠃⠁⠀⠘⢬⠈⠀⢐⢯⠬⡜⠃$(PINK)⠉⡄⡧⢻⢿⣧⢹⣿⢿⠏⢿⡀$(BLUE)⠈⠋⠀⠀⠀⣀⣿⣿⣿⣿⣿⣿⣿⣟⢿⣷⡄$(PURPLE)⠀⠀⠀⡿⠐⠁⢾⡿⣘⠁⣰⡆⢰⠀⠀⠂⢉⢎$(GOLD)⣾⣿⣿⠿⠿⠟⢋⡁$(GREEN)⢳⣿⣿⢙⣏⢿⡿⠀⠀⠀$(GOLD)⡾⠉⠀⠰⢊⠁⠀⠀⠘⢤⡀⢀⡀$(DARK_BLUE)⠐⠃⠀⠻⣱⣌⠛⢷⣮⡠⠉⡠$(GOLD)⡽⣿⣿⣿⡿⠿⠿⠓⠒\n"
	@printf "⠀⠀$(YELLOW)⠀⠀⠀⠘⠀⠀⠀⠀⠰⠎⠃⠀⠮⢍⣊$(PINK)⠀⡆⡀⠁⢉⣀⠸⢻⠅⢿⠘⠀⠘⡇$(BLUE)⠀⠀⠀⠀⠀⢼⣿⢟⡡⣦⣤⠤⠐⣈⢻⡏⠐$(PURPLE)⠀⠀⢸⣿⣷⡚⢘⣿⣯⡴⡖⠂⢀⠀⠀⡀⡦$(GOLD)⣿⢟⡵⠚⢉$(GREEN)⣤⣷⡿⣣⡐⡠⠹⣾⣿⣦⡀⠀⠀$(GOLD)⣌⡵⣶⢫⠁⢇⡂⠀⣠⣄⡄⠒⢉⠀⠀⠀⠀⠀$(DARK_BLUE)⡀⢀⣀⣂⣐⣾⣦⡃$(GOLD)⢷⠉⠀⠀⠀⠀⠀⠀⠀\n"
	@printf "⠀⠀$(GREEN)⠠⣄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀$(PINK)⢠⢆⢇⠉⠄⠚⢷⡀⠈⠄⠈⠀⢠⡄⠀$(BLUE)⠀⠀⠀⠀⠀⢨⣿⣿⣯⣱⠊⣟⣥⣧⣾⢛⢷⣄⠀$(PURPLE)⠀⠹⣿⡷⢾⣿⢿⣿⣷⣤⠾⢀⣀⣐$(GOLD)⠉⠡⢁$(GREEN)⣤⣾⣿⢟⣯⣿⡿⠛⠀⠥⠙⠫⢱⡒⠒$(GOLD)⠈⢻⠟⣰⠃⠀⣊⡠⠜⠛⢣⣄⠴⠾⠓$(DARK_BLUE)⠤⢔⡬⣲⢭⣛⡼⡣⠟⠳⢻⠃$(GOLD)⢸⠀⠀⠀⠀⠀⠀⠀⠀\n"
	@printf "⠀⠀$(GREEN)⠀⠀⠐⡂⠄⣀⢆⣭⣿⣤⣤⠃⠆⠀$(PINK)⠠⣾⣿⣆⡄⢀⡶⠁⠀⡀⠀⠀⠆⠉⠐$(BLUE)⠀⠀⡠⠄⡀⢸⣿⣿⣿⣿⣿⣿⣿⣿⣏⠼⠢⠻⣧⡁$(PURPLE)⠀⠈⢻⡕⣽⢯⠿⣉⢁⣽⣿⠿⠋$(GREEN)⣠⣷⣿⣿⢟⣵⠿⢋⠡⢀⢐⣠⡆⠀⠀⠀⠃⠁⠂⢀$(GOLD)⠘⠃⠒⠈⢩⠀$(DARK_BLUE)⣚⡍⢛⣭⢡⢪⢋⡟⠙⠒⠃⠛⠈⠁⢀⡤⠄⠒⠀$(GOLD)⢸⠁⠀⠀⠀⠀⠀⠀⠀\n"
	@printf "⠀⠀$(GREEN)⠀⢠⡾⢋⠾⢡⠀⡿⡟⠺⢶⣅⠐⠄$(PINK)⠑⢻⡿⠚⠀⠈⠁⠀⠀⠀⠀⠀⠀⠀⠀$(BLUE)⠀⠀⢴⡀⠈⠲⣙⠻⢿⣿⣿⣿⣿⣿⣿⢦⣴⡤⠀$(PURPLE)⠀⠀⠀⠀⠈⣿⠠⠒⢢⡴⢶⠞$(GREEN)⢄⡖⣿⣿⢟⢱⡟⢁⠒⠌⣀⡾⠛⠿⡦⢄⠀⠀⠩⠦⢤⠉$(GOLD)⠠⡀⠀⠀⢸⠄$(DARK_BLUE)⠡⠠⠏⠹⠂⠀⠈⣀⠤⠠⠤⠀⠀⠀⠀⠃⠀⠀⠀$(GOLD)⢸⠀⠀⠀⠀⠀⠀⠀⠀\n"
	@printf "⠀⠀⠀$(GREEN)⠃⠁⠈⠘⠀⠀⠁⠁⠀⠀⠈⠁⠁⠀$(PINK)⠈⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀$(BLUE)⠀⠀⠈⠀⠀⠀⠀⠀⠀⠉⠛⠙⠋⠉⠐⠉⠁⠀$(PURPLE)⠀⠀⠀⠀⠀⠂⠘⠀⠐⠈⠉⠃⠀$(GREEN)⠚⠉⠛⠁⠈⠁⠀⠀⠀⠀⠀⠀⠀⠀⠈⠓⠀⠀⠀⠀⠉⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀$(DARK_BLUE)⠚⠁⠀⠁⠀⠀⠀⠀⠀⠀$(GOLD)⠀⠀⠀⠈⠀⠀⠀⠀⠀⠀⠀⠀$(RESET)\n"
	
$(OBJS_DIR) $(OBJ_SUBDIRS) :
	@mkdir -p $@

-include $(DEPS)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c | $(OBJ_SUBDIRS)
	@printf "$(LBLUE)[Compilation]$(RESET) In progress... $(GREEN)$<" && \
	$(CC) $(CFLAGS) -I$(HEADERS) -c $< -o $@ && \
	printf "\r$(LBLUE)[Compilation]$(RESET) Completed   ... $(GREEN)$<" && \
	printf " $(LBLUE)[$(RESET)$(CC)$(LBLUE)/]$(RESET)\n"

clean:
	@make --silent clean -C ${MLXDIR}
	@make --silent clean -C ${LIBFTDIR}
	@rm -rf $(OBJS_DIR)
	@printf "\r$(GREEN)$(NAME) is Clean\n$(RESET)"

	
fclean: clean
	@rm -f $(LIBFTDIR)/libft.a
	@rm -f $(NAME)  
	
re: fclean all

.PHONY : all clean fclean re 
	