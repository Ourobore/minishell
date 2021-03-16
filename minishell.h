/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 15:50:12 by lchapren          #+#    #+#             */
/*   Updated: 2021/03/16 17:58:24 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <unistd.h>
# include <dirent.h>
# include <fcntl.h>
# include <errno.h>
# include <stdio.h>
# include <term.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>

# include "libft/libft.h"
# include "cmd.h"

# define STDIN 0
# define STDOUT 1
# define STDERR 2

# define MTRUNC O_CREAT | O_TRUNC | O_WRONLY
# define MAPPEND O_CREAT | O_APPEND | O_WRONLY
# define RFILE S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH

# define PROMPT "lchapren@minishell $ "
# define MINISHELL "minishell: "
# define SYNTAX "syntax error near: "

extern int	exit_value;

//Built-ins
int		call_builtin_or_pipe(t_lst *cmd_line, char **envp[]);
int		call_builtin(t_cmd *head, char **envp[]);
int		is_builtin(char **token);
int		builtin_echo(char **token);
int		builtin_exit(char *line);
int		builtin_pwd(void);
int		builtin_env(char *envp[]);
int		builtin_cd(char **token, char **envp[]);
int		builtin_export(char **token, char **envp[]);
int		builtin_unset(char **token, char **envp[]);

//General functions
int		execution_loop(char *line, char **envp[]);
char	**copy_envp(char *envp[]);
char	*get_pwd(void);

//Prompt functions
char	*get_line(struct termios backup);
void	set_termios(struct termios *settings);
int	    prompt_special_caracter(char c);

//Pipes
void	call_builtin_pipe(t_cmd *cmd, char *envp[]);
int		exec_pipeline(t_cmd *cmd, char *envp[]);
void	open_close_pipes(int *pipefd, int nb_pipes, int mode);
void	child_pipe_redir(t_cmd *head, int *pipefd, int cmd_num, int nb_pipes);
void	child_exec(t_cmd *cmd, t_cmd *head, char *envp[]);
int		get_child_status(int child_process, int nb_pipes);


//Redirections
//int		get_redirection(t_cmd *head, char *line, int *i , char *buffer);
void	get_redir_name(char *line, int *i , char **buffer, char *envp[]);
int		get_redir_type(char *line, int *i, char **buffer);
void	builtin_redir(t_cmd *cmd, int *save_in, int *save_out, int mode);
void	open_redir_hub(t_cmd **cmd);
void 	open_redir_in(t_cmd **cmd, char *file_name);
void 	open_redir_out(t_cmd **cmd, char *file_name, int open_mode);



//Manipulation of envp
int		add_token_in_envp(char *token, char **envp[]);
int		modify_token_in_envp(char *token, int token_index, char **envp[]);
int		search_token_in_envp(char *token, char *envp[]);
int		remove_token_in_envp(int token_index, char **envp[]);
void	update_pwd_envp(char *oldpwd, char **envp[]);
char	*get_token_value_in_envp(char *token, char *envp[]);
char	*get_env_variable(char *line, int *i, char *envp[]);
int		is_env_character(char c);

//Execution functions
int		exec_command(char **command, char *envp[]);
char	*search_executable_in_path(char *executable, char **path);
char	*search_executable_in_dir(char *executable, char *path);
char	*is_an_executable(char *file_path, char *file_name);
int		is_absolute_or_relative_path(char *path);
int		directory_exists(char *dir_path);
char	**get_env_path(char *envp[]);

//Linked list
int		add_cmd(t_cmd **cmd);
t_cmd	*allocate_list(t_cmd *cmd);
t_lst	*add_command_line(t_lst *cmd_line);
void	free_command_list(t_cmd *head);
int		get_length_list(t_cmd *head);
char	**copy_buffer_on_array(char *buffer, char **array);

//Parsing
//int		parse_line(char *line, t_cmd **head, int i, char *envp[]);
int		parsing_hub(char *line, t_lst **cmd_line, char *envp[]);
int		parse_command_line(char *line, t_cmd **cmd, int i, char *envp[]);
int		in_quotes(char *line, int pos);
int		closed_quote(char *line, int pos, char quote_type);
int		special_action(char *line, t_cmd **cmd, int i, char *envp[]);
int		is_special_character(char c);
void	parse_backslash(char *line, char *buffer, int *i, int *j);
void	parse_dollar(char *line, int *i, char **buffer, char *envp[]);
char	*get_next_token(char *line, int *i, char *buffer, char *envp[]);
char	*add_on_buffer(char *buffer, char *to_add, char *line);

void 	add_to_token(t_cmd **tmp, char **buffer);

//Error handling
void	print_syntax_error(char c);
int		multiline_character(char *line, char c, int i);

//Utility functions
char	**alphabetically_sort_env(char *envp[]);
char	**alphabetical_bubble_sort(char **array);
int		characters_before_equal(char *token);
int		print_export(char **sorted_env);
int		nb_cd_args(char **token);
int		verify_cd_args(char **token, char *envp[]);

#endif
