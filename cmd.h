/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 09:27:39 by lchapren          #+#    #+#             */
/*   Updated: 2021/03/19 18:47:26 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_H
# define CMD_H

typedef struct s_cmd
{
	char			**token;
	char			**redir_file;
	int				redir_in;
	int				redir_out;
	struct s_cmd	*next;
}					t_cmd;

typedef struct s_data
{
	struct s_cmd	*cmd;
	char			*line;
	char			**envp_copy;
	int				in_fork;
	int				exit_value;
}					t_data;

#endif
