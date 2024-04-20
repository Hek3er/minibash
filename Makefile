CC = cc

PATH_F = functions
C_FILES_F = $(PATH_F)/ft_strcmp.c $(PATH_F)/ft_strdup.c $(PATH_F)/ft_strjoin.c \
$(PATH_F)/ft_strlen.c $(PATH_F)/ft_substr.c $(PATH_F)/ft_write.c $(PATH_F)/unsigned_to_str.c \
$(PATH_F)/ft_malloc.c $(PATH_F)/remove_docs.c $(PATH_F)/ft_strncmp.c $(PATH_F)/ft_open.c \
$(PATH_F)/exit_stat.c $(PATH_F)/ft_itoa.c $(PATH_F)/ft_isalnum.c $(PATH_F)/ft_isunder_alpha.c \
$(PATH_F)/ft_split.c $(PATH_F)/ft_strlcpy.c $(PATH_F)/ft_strchr.c $(PATH_F)/ft_tolower.c \
$(PATH_F)/ft_atoi.c $(PATH_F)/arr_dup.c $(PATH_F)/arr_size.c $(PATH_F)/fill_arr_with_str.c


PATH_G = get_next_line
C_FILES_G = $(PATH_G)/get_next_line.c $(PATH_G)/get_next_line_utils.c

PATH_PT = parsing/parse_tree
C_FILES_PT = $(PATH_PT)/build/adjust_redirectionals.c $(PATH_PT)/build/build_tree.c $(PATH_PT)/build/parse_tree.c \
$(PATH_PT)/check/check_here_doc.c $(PATH_PT)/check/check_opers.c $(PATH_PT)/check/check_q_p.c \
$(PATH_PT)/check/check_wildcard.c $(PATH_PT)/check/conditions.c $(PATH_PT)/get/get_environment.c \
$(PATH_PT)/get/get_files.c $(PATH_PT)/get/get_here_doc.c $(PATH_PT)/get/get_input_output.c \
$(PATH_PT)/get/get_wildcard.c $(PATH_PT)/split/split_by_oper.c $(PATH_PT)/split/split_by_parantheses.c \
$(PATH_PT)/split/split_by_space.c $(PATH_PT)/split/split_by_space2.c $(PATH_PT)/split/split_cmds.c \


PATH_PE = parsing/parse_env
C_FILES_PE = $(PATH_PE)/get_value.c $(PATH_PE)/linked_list.c $(PATH_PE)/parse_env.c 

PATH_BUIL = builtins
C_FILES_BUIL = $(PATH_BUIL)/echo/echo.c $(PATH_BUIL)/export/change_val.c $(PATH_BUIL)/export/check_key.c \
$(PATH_BUIL)/export/export.c $(PATH_BUIL)/export/sort_export.c $(PATH_BUIL)/pwd/pwd.c $(PATH_BUIL)/env/env.c \
$(PATH_BUIL)/unset/unset.c $(PATH_BUIL)/cd/cd.c $(PATH_BUIL)/exit/exit.c

PATH_EXEC = execution
C_FILES_EXEC = $(PATH_EXEC)/get_cmd.c $(PATH_EXEC)/exec_try.c $(PATH_EXEC)/is_a_dir.c \
$(PATH_EXEC)/execute_single_command.c $(PATH_EXEC)/linked_list_to_arr.c $(PATH_EXEC)/execute_command.c \
$(PATH_EXEC)/check_builtins.c

C_FILES = $(C_FILES_F) $(C_FILES_G) $(C_FILES_PT) $(C_FILES_PE) $(C_FILES_BUIL) $(C_FILES_EXEC) minibash.c get_cmd_info.c
O_FILES = $(C_FILES:.c=.o)
FLAGS = -Wall -Wextra -Werror
NAME = minibash.a
BONUS_NAME = minibash_bonus.a§
EXE = minibash
EXE_BONUS = minibash_bonus
LINKREADLINELIB = $(shell brew --prefix readline)/lib
LINKREADLINELIB1 = $(shell brew --prefix readline)/include

all:$(NAME)

bonus:$(BONUS_NAME)

$(NAME):$(O_FILES)
	ar -rcs $(NAME) $(O_FILES)
	$(CC) -fsanitize=address -g -L$(LINKREADLINELIB) -lreadline $(NAME) -o $(EXE) 

# $(BONUS_NAME):$(BONUS_O_FILES)
# 	ar -rcs $(BONUS_NAME) $(BONUS_O_FILES)
# 	$(CC) $(BONUS_NAME) -o $(BONUS_EXE)

%.o:%.c push_swap.h
	$(CC) -fsanitize=address -g -I$(LINKREADLINELIB1) $(FLAGS) -c  $< -o $@

clean:
	rm -f $(O_FILES) $(BONUS_O_FILES)

fclean: clean
	rm -f $(NAME) $(BONUS_NAME) $(EXE) $(EXE_BONUS)

re: fclean all

.PHONY: all bonus clean fclean re