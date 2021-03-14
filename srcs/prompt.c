/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 15:53:52 by lchapren          #+#    #+#             */
/*   Updated: 2021/03/11 16:17:06 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_putchar(int c) //add to libft
{
	unsigned char	uc;

	uc = (unsigned char)c;
	write(1, &uc, 1);
	return (c);
}

char	*get_line(struct termios backup)
{
	int				i;
	char			c;
	char 			*line;
	char			buffer[2048];
	struct termios	non_canon;

	i = 0;
	c = 0;
	non_canon = backup;
	ft_putstr_fd("\033[1;33m"PROMPT"\033[0;0m", 2);
	set_termios(&non_canon);
	while(read(STDIN, &c, 1) == 1 && c != '\n')
	{
		//prompt_special_caracter();
		//read(STDIN, &c, 1);
		//printf("INT: %d\n", c);
		prompt_special_caracter(c);
		if (c != '\n')
			buffer[i] = c;
		i++;
	}
	line = ft_strdup(buffer);
	ft_bzero(buffer, i);
	tcsetattr(STDIN, TCSANOW, &backup);
	return (line);
}

int	prompt_special_caracter(char c)
{
	//char	*arrow;
	//char	*left;

	//arrow = tgetstr("kl", NULL);
	//for(int i = 0; arrow[i]; i++)
	//	printf("ARROW: %d\n",arrow[i]);
	//printf("BACKSPACE: %s\n", backspace);
	if (c == 127)
	{
		//\printf("IN backspace\n");
		//left = tgetstr("le", NULL);
		//printf("OUTPUT: %s\n", left);
		tputs(tgetstr("le", NULL), 1, ft_putchar);
		tputs(tgetstr("le", NULL), 1, ft_putchar);
		tputs(tgetstr("le", NULL), 1, ft_putchar);
		tputs(tgetstr("ce", NULL), 1, ft_putchar);
		fflush(stdout);
		//tputs(tgetstr("nd", NULL), 1, ft_putchar);
	}
	//printf("OUTPUT: %s\n", backspace);
	//tputs(backspace, 1, ft_putchar);
	return (1);
}

void	set_termios(struct termios *settings)
{
	settings->c_lflag &= ~(ICANON);
	//termios_p.c_lflag &= ~(ECHO);
	settings->c_cc[VMIN] = 1;
	settings->c_cc[VTIME] = 0;
	tcsetattr(0, TCSANOW, settings);
}
