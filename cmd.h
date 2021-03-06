/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 09:27:39 by lchapren          #+#    #+#             */
/*   Updated: 2021/03/16 21:47:33 by user42           ###   ########.fr       */
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

typedef struct s_lst
{
	struct s_cmd	*cmd;
	struct s_lst	*next;
}					t_lst;

#endif
