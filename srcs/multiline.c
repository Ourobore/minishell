/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiline.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 10:23:28 by user42            #+#    #+#             */
/*   Updated: 2021/03/20 08:45:14 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	multiline_character(char *line, char c, int *i, int mode)
{
	int	ret;

	ret = 0;
	if (c == '\'' || c == '\"')
	{
		if (!closed_quote(line, *i, line[*i]))
			ret = 1;
	}
	else if(c == '\\' && (*i == (int)ft_strlen(line) - 1 || \
			(line[(*i) + 1] && line[(*i) + 1] == ' ')))
		ret = 1;
	else if (c == '|' && *i == (int)ft_strlen(line) - 1)
		ret = 1;
	if (ret == 1)
	{
		*i = -1;
		if (mode == 1)
			print_syntax_error(c);
	}
	return (ret);
}

int	in_quotes(char *line, int pos)
{
	int	i;
	int	in_single;
	int	in_double;

	i = 0;
	in_single = 0;
	in_double = 0;
	//printf("\n\n");
	while (line[i] && i <= pos && pos != 0)
	{
		//printf("CHARAC: [%c]\tIN SINGLE: [%d]\tIN DOUBLE[%d]\n", line[i], in_single, in_double);
		if (line[i] == '\\' && !in_single && !in_double)//line[i - 1] != '\'
			i++;
		else if (line[i] == '\'' && !in_double && i != pos)
			in_single = !in_single;
		else if (line[i] == '\"' && !in_single && i != pos)//
			in_double = !in_double;
		i++;
	}
	if (in_single)
		return (1);
	else if (in_double)
		return (2);
	return (0);
}

int	closed_quote(char *line, int pos, char quote_type)
{
	int	i;
	int	in_quote;

	i = 0;
	in_quote = 0;
	if (quote_type != '\'' && quote_type != '\"')
		return (1);
	//printf("charac: %c\n", line[pos]);
	if (in_quotes(line, pos))
	{
		//printf("in quotes\n");
		return (1);
	}
	while (line[i])
	{
		if (line[i] == '\\' && !in_quote)
			i++;
		else if (i < pos && line[i] == quote_type)
			in_quote = !in_quote;
		else if (i == pos && in_quote)
			return (1);
		else if (i > pos && line[i] == quote_type)
			return (1);
		i++;
	}
	//printf("QUOTE [%c] NOT CLOSED\n", line[pos]);
	return (0);
}

int	is_special_character(char c)
{
	if (c == '|' || c == ' ' || c == '>' || c == '<' || c == ';')
		return (1);
	else
		return (0);
}

//int	is_multiline_character()
