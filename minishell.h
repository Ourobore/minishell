/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchapren <lchapren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 15:50:12 by lchapren          #+#    #+#             */
/*   Updated: 2021/01/16 16:48:38 by lchapren         ###   ########.fr       */
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

# include "libft/libft.h"

int	prompt_line(char **line);

//Built ins
int	call_builtin(char **token);
int	builtin_echo(char **token);
int	builtin_pwd(void);

#endif
