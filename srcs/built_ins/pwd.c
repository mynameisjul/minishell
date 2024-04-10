/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroue <acroue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 11:03:17 by jblaye            #+#    #+#             */
/*   Updated: 2024/04/10 14:16:33 by acroue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pwd_built_in(int fd_out)
{
	char	*to_be_freed;
	
	to_be_freed = getcwd(0, 0);
	if (to_be_freed == NULL)
		strerror(errno);
	else
		ft_dprintf(fd_out, "%s\n", to_be_freed);
	free(to_be_freed);
	return (errno);
}