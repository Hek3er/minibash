CC = cc
CFLAGS = -Wall -Werror -Wextra 
LDFLAGS = -lreadline
LINKREADLINELIB = $(shell brew --prefix readline)/lib
LINKREADLINEINC = $(shell brew --prefix readline)/include

RL_REPLACE_LINE = -L .brew/opt/readline/lib -I .brew/opt/readline/include

NAME = minishell

SRCS = minibash.c get_cmd_info/get_cmd_info.c get_cmd_info/remove_quotes.c get_cmd_info/compare_arrays.c \
       get_cmd_info/remove_redirections.c get_cmd_info/sep_env.c builtins/cd/cd.c builtins/cd/cd_utils.c builtins/echo/echo.c builtins/env/env.c builtins/exit/exit.c \
       builtins/export/change_val.c builtins/export/check_key.c builtins/export/export.c builtins/export/sort_export.c builtins/export/export_utils.c\
       builtins/pwd/pwd.c builtins/unset/unset.c execution/signals.c execution/execute_one_command.c execution/execute_right_left.c\
       execution/check_builtins.c execution/main_exec.c execution/execute_command.c execution/execute_pipe.c \
       execution/execute_single_command.c execution/get_cmd.c execution/is_a_dir.c execution/linked_list_to_arr.c \
       functions/exit_stat.c functions/ft_atoi.c functions/ft_isalnum.c functions/ft_isunder_alpha.c functions/ft_itoa.c \
       functions/ft_malloc.c functions/ft_open.c functions/ft_split.c functions/ft_strchr.c functions/ft_strcmp.c \
       functions/ft_strdup.c functions/ft_strjoin.c functions/ft_strlcpy.c functions/ft_strlen.c functions/ft_strncmp.c \
       functions/ft_substr.c functions/ft_tolower.c functions/ft_write.c functions/remove_docs.c functions/unsigned_to_str.c \
       functions/arr_dup.c functions/arr_size.c functions/fill_arr_with_str.c functions/ft_dup_and_close.c \
       functions/is_white_space.c functions/condition.c \
       parsing/parse_env/get_value.c parsing/parse_env/parse_env.c parsing/parse_env/linked_list.c parsing/parse_env/parse_env2.c \
       parsing/parse_tree/build/adjust_redirectionals.c parsing/parse_tree/build/build_tree.c parsing/parse_tree/build/parse_tree.c \
       parsing/parse_tree/check/check_here_doc.c parsing/parse_tree/check/check_opers.c parsing/parse_tree/check/check_q_p.c \
       parsing/parse_tree/check/check_wildcard.c parsing/parse_tree/check/conditions.c parsing/parse_tree/get/get_environment.c \
       parsing/parse_tree/get/get_files.c parsing/parse_tree/get/get_here_doc.c parsing/parse_tree/get/get_input_output.c parsing/parse_tree/get/ambiguity.c \
       parsing/parse_tree/get/get_wildcard.c  parsing/parse_tree/get/get_hdoc_delimiter.c parsing/parse_tree/split/split_by_oper.c parsing/parse_tree/split/split_by_parantheses.c \
       parsing/parse_tree/split/split_by_space.c parsing/parse_tree/split/split_by_space2.c parsing/parse_tree/split/split_cmds.c  \
       parsing/parse_tree/get/get_environment2.c 

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC)  $(CFLAGS) $(OBJS) -o $@ $(LDFLAGS) -L $(LINKREADLINELIB)

%.o: %.c minibash.h
	$(CC)  $(CFLAGS) -c $< -o $@ -I $(LINKREADLINEINC)

bonus: all

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

