/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroue <acroue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 10:12:39 by acroue            #+#    #+#             */
/*   Updated: 2024/03/06 15:19:32 by acroue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "minishell.h"

void	cmd_error(t_branch *branch, char *err_msg);
void	redirection_error(t_branch *branch, char *err_msg);
void	free_tab(void **tab);
void	free_cmd(t_cmd *cmd);
void	free_tree(t_branch *branch);
void	execute_tree(t_branch *branch, char **env);
void	differentiate_branches(t_branch *branch);

#endif
