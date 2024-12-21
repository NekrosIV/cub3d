NAME := cub3D
NAME_BONUS := cub3D_bonus
CC := cc
CFLAGS :=  -g3 -MMD -O3
MLX_FLAGS = -Lmlx -lmlx -Imlx -lXext -lX11 -lm -lXfixes
LIBFTDIR := ./libft
MLXDIR := ./mlx
SOUND_FLAGS = -Ivendor/lib/openal/include -Lvendor/lib/openal/lib -lopenal

HEADERS := ./include

FILES := cub3d.c \
		parsing/parsing.c \
		parsing/rgb.c \
		parsing/txtur_pars.c \
		parsing/pars_map.c \
		parsing/flood_fill.c \
		parsing/map_utils.c \
		parsing/parsing_utils.c \
		init/init_mlx.c \
		init/init_struct.c \
		player/player_move.c \
		player/player_move2.c \
		key/key.c \
		draw/draw.c \
		draw/raycasting.c \
		draw/raycasting2.c \
		error/exit.c \
		error/exit2.c \
		utils.c 

SRCS_DIR := ./src
OBJS_DIR := ./poubelle

SRCS := $(addprefix $(SRCS_DIR)/, $(FILES)) 
OBJS := $(addprefix $(OBJS_DIR)/, $(FILES:.c=.o))
DEPS := $(OBJS:.o=.d)

FILES_BONUS := cub3d.c \
		parsing/parsing.c \
		parsing/search.c \
		parsing/rgb.c \
		parsing/txtur_pars.c \
		parsing/pars_map.c \
		parsing/flood_fill.c \
		parsing/map_utils.c \
		parsing/parsing_utils.c \
		error/exit.c \
		error/free_mlx.c\
		error/free_sound.c\
		init/init_struct.c \
		init/init_sound.c\
		init/init_player.c \
		init/init_mlx_textutre.c \
		init/init_mlx_utils.c \
		player/player_move.c \
		player/collision_detection.c \
		minimap/minimap.c \
		minimap/mini_raycasting.c \
		key/key.c \
		key/mouse.c \
		draw/draw.c \
		draw/raycastingbot.c \
		draw/raycasting.c \
		draw/raycasting2.c \
		draw/draw_floor.c \
		draw/dda.c \
		draw/gun.c \
		draw/door.c \
		draw/health.c \
		draw/menu.c \
		draw/crosshair.c \
		bot/enemy_animation.c \
		bot/bot_ai.c \
		bot/movement_utils.c \
		bot/collision_detection.c \
		bot/bot.c \
		bot/bot_utils.c \
		sound/sound.c \
		sound/sound2.c \
		utils.c 

SRCS_DIR_BONUS := ./src_bonus
OBJS_DIR_BONUS := ./poubelle_bonus

SRCS_BONUS := $(addprefix $(SRCS_DIR_BONUS)/, $(FILES_BONUS)) 
OBJS_BONUS := $(addprefix $(OBJS_DIR_BONUS)/, $(FILES_BONUS:.c=.o))
DEPS_BONUS := $(OBJS_BONUS:.o=.d)


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
OBJ_SUBDIRS_BONUS := $(sort $(dir $(OBJS_BONUS)))

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

bonus: $(NAME_BONUS)

$(NAME_BONUS): $(OBJS_BONUS)
	@make --silent -C ${LIBFTDIR}
	@make --silent -C ${MLXDIR}
	@$(CC) $(CFLAGS) $(SOUND_FLAGS) -I$(HEADERS)  $(SOUND_HEADERS) -o $@ $(OBJS_BONUS) ${MLX_FLAGS} -L ${LIBFTDIR} -lft
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
	
$(OBJS_DIR_BONUS) $(OBJ_SUBDIRS_BONUS) :
	@mkdir -p $@

-include $(DEPS_BONUS)

$(OBJS_DIR_BONUS)/%.o: $(SRCS_DIR_BONUS)/%.c | $(OBJ_SUBDIRS_BONUS)
	@printf "$(LBLUE)[Compilation]$(RESET) In progress... $(GREEN)$<" && \
	$(CC) $(CFLAGS) -I$(HEADERS) -c $< -o $@ && \
	printf "\r$(LBLUE)[Compilation]$(RESET) Completed   ... $(GREEN)$<" && \
	printf " $(LBLUE)[$(RESET)$(CC)$(LBLUE)/]$(RESET)\n"

clean:
	@make --silent clean -C ${MLXDIR}
	@make --silent clean -C ${LIBFTDIR}
	@rm -rf $(OBJS_DIR)
	@rm -rf $(OBJS_DIR_BONUS)
	@printf "\r$(GREEN)$(NAME) is Clean\n$(RESET)"

	
fclean: clean
	@rm -f $(LIBFTDIR)/libft.a
	@rm -f $(NAME)
	@rm -f $(NAME_BONUS) 
	
re: fclean all

.PHONY : all clean fclean re 
	