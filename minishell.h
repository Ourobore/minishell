/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchapren <lchapren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 15:50:12 by lchapren          #+#    #+#             */
/*   Updated: 2021/01/28 10:12:28 by lchapren         ###   ########.fr       */
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
# include <sys/wait.h>

# include "libft/libft.h"

//General functions
int	prompt_line(char **line);
int	tokenization(char *line, char *envp[]);


//Built-ins
int	call_builtin(char **token, char *envp[]);
int	builtin_echo(char **token);
int	builtin_exit(char *line);
int	builtin_pwd(void);
int	builtin_cd(char *path);
int	builtin_env(char *envp[]);
int	builtin_export(char **token, char *envp[]);

char	**alphabetically_sort_env(char *envp[]);
char	**alphabetical_bubble_sort(char **array);


//Utility functions
int	is_directory(char *token);

#endif
