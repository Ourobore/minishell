/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiline.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 10:23:28 by user42            #+#    #+#             */
/*   Updated: 2021/03/20 10:52:03 by user42           ###   ########.fr       */
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
	else if (c == '\\' && (*i == (int)ft_strlen(line) - 1 || \
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
	while (line[i] && i < pos && pos != 0)
	{
		if (line[i] == '\\' && !in_single)
			i++;
		else if (line[i] == '\'' && !in_double)
			in_single = !in_single;
		else if (line[i] == '\"' && !in_single)
			in_double = !in_double;
		i++;
	}
	return (return_closed_quote(line, i, in_single, in_double));
}

int	return_closed_quote(char *line, int i, int in_single, int in_double)
{
	if (in_single)
	{
		if (line[i] == '\'')
			return (0);
		return (1);
	}
	if (in_double)
	{
		if (line[i] == '\"')
			return (0);
		return (2);
	}
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
	if (in_quotes(line, pos))
		return (1);
	while (line[i])
	{
		if (line[i] == '\\' && (!in_quote || (in_quote && quote_type == '\"')))
			i++;
		else if (i < pos && line[i] == quote_type)
			in_quote = !in_quote;
		else if (i == pos && in_quote)
			return (1);
		else if (i > pos && line[i] == quote_type)
			return (1);
		i++;
	}
	return (0);
}

int	is_special_character(char c)
{
	if (c == '|' || c == ' ' || c == '>' || c == '<' || c == ';')
		return (1);
	else
		return (0);
}
