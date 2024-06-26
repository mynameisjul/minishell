/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroue <acroue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 14:59:48 by acroue            #+#    #+#             */
/*   Updated: 2024/04/10 14:20:20 by acroue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Handles the edge case when echo has a parameter such as '-nnnnnnnn'
 * @return 1 if string is only 'ch', 0 otherwise
 */
static int	str_only_n(char *str, char ch)
{
	size_t	i;

	i = 2;
	while (str[i])
	{
		if (str[i] != ch)
			return (0);
		i++;
	}
	return (1);
}

/**
 * @brief This function returns the first str that needs to be printed and sets 
 * print_newline to 1 if the [-n] flag was present.
 */
static char	**skip_n_flag(t_cmd *cmd, int *print_newline)
{
	size_t	i;
	char	**args;

	i = 1;
	*print_newline = 1;
	args = cmd->args;
	while (args[i])
	{
		if (args[i][0] == '-' && args[i][1] == 'n' && str_only_n(args[i], 'n'))
			*print_newline = 0;
		else
			break ;
		i++;
	}
	return (&args[i]);
}

/**
 * @brief Prints the strings passed as args on the FD.
 * Also manages errors for full files
 * 
 * @param branch The Command Branch.
 * @return int The errno
 */
int	echo_built_in(t_branch *branch, int fd_out)
{
	char	**args;
	int		print_newline;
	size_t	i;

	i = 0;
	args = skip_n_flag(branch->elmnt, &print_newline);
	while (args[i])
	{
		if (i && write(fd_out, " ", (i > 0)) < 0)
			return ((void)ft_dprintf(2, WRITE_FILE_FULL, "echo"), 1);
		if (write(fd_out, args[i], ft_safe_strlen(args[i])) < 0)
			return ((void)ft_dprintf(2, WRITE_FILE_FULL, "echo"), 1);
		i++;
	}
	if (print_newline && write(fd_out, "\n", print_newline) < 0)
		return ((void)ft_dprintf(2, WRITE_FILE_FULL, "echo"), 1);
	return (0);
}

/* int	main(int argc, char *argv[])
{
	t_branch	*br;
	t_cmd		*cmd;
	int			fd;
	int			err;

	fd = open("/dev/full", O_WRONLY);
	if (fd < 0)
		return (perror("/dev/full"), 1);
	br = ft_calloc(1, sizeof(t_branch));
	cmd = ft_calloc(1, sizeof(t_cmd));
	br->elmnt = cmd;
	cmd->args = argv;
	err = echo_built_in(br, fd);
	free(cmd);
	free(br);
	close(fd);
	(void)argc;
	return (err);
} */
