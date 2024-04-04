/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_parsing_checks.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblaye <jblaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 09:48:00 by julieblaye        #+#    #+#             */
/*   Updated: 2024/04/04 13:31:20 by jblaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/// @brief Checks whether all quotes are closed in the user input
/// @param str user input read with readline
/// @return 1 upon succes or 0 if at least one quote is not properly closed

int	all_quotes_are_closed(char *str)
{
	int	i;
	int	c;

	i = 0;
	if (str)
	{
		while (str[i] != 0)
		{
			if (str[i] == '\'' || str[i] == '\"')
			{
				c = str[i];
				i++;
				while (str[i] != 0 && str[i] != c)
					i++;
				if (str[i] != c)
					return (ft_dprintf(2, "tacos: unclosed quotes\n"), 0);
			}
			i++;
		}
		return (1);
	}
	return (ft_dprintf(2, "tacos: unclosed quotes\n"), 0);
}

static int	pipe_syntax_error(char *str, size_t i)
{
	ssize_t	j;

	j = i - 1;
	while (j >= 0 && str[j] == ' ')
		j--;
	if (j == -1)
		return (ft_dprintf(2, "tacos: syntax error near unexpected token `|'\n"), 0);
	return (1);
}

static int	redirection_syntax_error(char *str, size_t *i)
{
	*i += 1;
	if (str[*i] == str[*i - 1])
		*i += 1;
	while (str[*i] == ' ')
		*i += 1;
	if (str[*i] == '<' || str[*i] == '>' || str[*i] == '|')
		return (ft_dprintf(2, "tacos: syntax error near unexpected token `%c'\n", str[*i]), 0);
	if (str[*i] == 0)
		return (ft_dprintf(2, "tacos: syntax error near unexpected token `newline'\n"), 0);
	return (1);
}

int	no_syntax_error(char *str, t_hd_fd_list *first)
{
	size_t			i;
	t_hd_fd_list	*first;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == '|')
		{
			if (pipe_syntax_error(str, i) == 0)
				return (hd_fd_list_clear(first), 0);
		}
		if (str[i] == '<' || str[i] == '>')
		{
			if (redirection_syntax_error(str, &i) == 0)
				return (hd_fd_list_clear(first), 0);
			if (get_parsing_type(&str, 0, &i) == PARS_HERE_DOC)
			{
				if (list_heredocs_fd(str, i, first) == 0)
					return (hd_fd_list_clear(first), 0);
			}
		}
		i++;
	}
	return (1);
}
