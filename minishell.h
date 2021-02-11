/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchapren <lchapren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 15:50:12 by lchapren          #+#    #+#             */
/*   Updated: 2021/02/11 16:20:37 by lchapren         ###   ########.fr       */
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

# define STDIN 0
# define STDOUT 1
# define STDERR 2
# define FDREAD 0
# define FDWRITE 1

//General functions
int		prompt_line(char **line);
int		tokenization(char *line, char **envp[]);
int		tokenize_pipeline(char *command_line, char **envp[]);
char	**copy_envp(char *envp[]);
char	*get_pwd(void);

int		exec_pipeline(char ***pipeline, char **envp[]);
char	***create_pipeline(char *line);
void	open_pipe_fd(int **pipe_fd);
void	close_pipe_fd(int *pipe_fd);



//Built-ins
int		call_builtin(char **token, char **envp[]);
int		builtin_echo(char **token);
int		builtin_exit(char *line);
int		builtin_pwd(void);
int		builtin_env(char *envp[]);
int		builtin_cd(char **token, char **envp[]);
int		builtin_export(char **token, char **envp[]);
int		builtin_unset(char **token, char **envp[]);

//Manipulation of envp
int		add_token_in_envp(char *token, char **envp[]);
int		modify_token_in_envp(char *token, int token_index, char **envp[]);
int		search_token_in_envp(char *token, char *envp[]);
int		remove_token_in_envp(int token_index, char **envp[]);
void	update_pwd_envp(char *oldpwd, char **envp[]);
char	*get_token_value_in_envp(char *token, char *envp[]);
char	**env_variable_expansion(char **command_line, char *envp[]);


//Execution functions
int		exec_command(char **command, char *envp[]);
int		execute_path(char *exec_path, char **command, char *envp[]);
char	*search_executable_in_path(char *executable, char **path);
char	*search_executable_in_dir(char *executable, char *path);
char	*is_an_executable(char *file_path, char *file_name);
int		is_absolute_or_relative_path(char *path);
int		directory_exists(char *dir_path);
char	**get_env_path(char *envp[]);

//Utility functions
//int		is_directory(char *token);
char	**alphabetically_sort_env(char *envp[]);
char	**alphabetical_bubble_sort(char **array);
int		characters_before_equal(char *token);
int		print_export(char **sorted_env);
int		nb_cd_args(char **token);
int		verify_cd_args(char **token, char *envp[]);

#endif
