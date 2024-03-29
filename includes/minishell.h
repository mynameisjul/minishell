/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblaye <jblaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 17:14:34 by acroue            #+#    #+#             */
/*   Updated: 2024/03/14 10:41:07 by jblaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include "struct.h"
# include "../libs/libft/libft.h"
# include "redirections.h"
# include "exec.h"
# include <errno.h>
# include <sys/wait.h>
# include "parsing.h"
# include "parsing_struct.h"
# include "builtins.h"

void	print_parsing(void);
void	print_exec(void);

#endif
