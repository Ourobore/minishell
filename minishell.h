/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchapren <lchapren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 15:50:12 by lchapren          #+#    #+#             */
/*   Updated: 2021/02/25 15:52:02 by lchapren         ###   ########.fr       */
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
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>

# include "libft/libft.h"
# include "cmd.h"

# define STDIN 0
# define STDOUT 1
# define STDERR 2
# define FDREAD 0
# define FDWRITE 1

int	verify_quotes(char *line);
int	is_in_quotes(char *line, int pos);
int	is_in_line(char *line, char *search);

//Built-ins
int		call_builtin_or_pipe(t_cmd *head, char *buffer, char **envp[]);
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
char	*prompt_line(void);
int		tokenization(char *line, char **envp[]);
int		tokenize_pipeline(char *command_line, char **envp[]);
char	**copy_envp(char *envp[]);
char	*get_pwd(void);

//Pipes
void	call_builtin_pipe(t_cmd *cmd, char *envp[]);
int		exec_pipeline(t_cmd *cmd, char *buffer, char *envp[]);
int		verify_pipeline(char ***pipeline, char *command_line, char *envp[]);
int		verify_executable(char ***pipeline, char *envp[]);
char	***create_pipeline(char *line, char *envp[]);
int		get_pipes_number(char *command_line);
int		get_length_pipeline(char ***pipeline);
void	pipes_forks_redirs(t_cmd *head, int *input_fd, int (*pipe_fd)[2], int *child_process);
void	free_pipeline(char ***pipeline);

//Redirections
int		get_redirection(t_cmd *head, char *line, int *i , char *buffer);


//Manipulation of envp
int		add_token_in_envp(char *token, char **envp[]);
int		modify_token_in_envp(char *token, int token_index, char **envp[]);
int		search_token_in_envp(char *token, char *envp[]);
int		remove_token_in_envp(int token_index, char **envp[]);
void	update_pwd_envp(char *oldpwd, char **envp[]);
char	*get_token_value_in_envp(char *token, char *envp[]);
char	**expend_env_variable(char **command_line, char *envp[]);

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
int		allocate_list(t_cmd **cmd);
void	free_command_list(t_cmd *head);
int		get_length_list(t_cmd *head);
char	**copy_buffer_on_token(t_cmd *head, char *buffer);


int		parse_line(char *line, char **envp[]);
int		is_special_character(char c);



//Utility functions
char	**alphabetically_sort_env(char *envp[]);
char	**alphabetical_bubble_sort(char **array);
int		characters_before_equal(char *token);
int		print_export(char **sorted_env);
int		nb_cd_args(char **token);
int		verify_cd_args(char **token, char *envp[]);

#endif
