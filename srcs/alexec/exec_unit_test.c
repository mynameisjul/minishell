/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_unit_test.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acroue <acroue@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 10:10:23 by acroue            #+#    #+#             */
/*   Updated: 2024/03/06 13:22:46 by acroue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define TEST_ERR "./a.out /usr/bin/cat cat -n <in1> <in2> <out1> <out2>\n"

static t_branch	*define_test_infile(char *path)
{
	t_branch	*branch;
	t_infile	*infile;

	branch = ft_calloc(sizeof(t_branch), 1);
	infile = ft_calloc(sizeof(t_infile), 1);
	branch->type = T_INFILE;
	branch->elmnt = infile;
	infile->path = ft_strdup(path);
	infile->type = IT_RDONLY;
	return (branch);
}

static t_branch	*define_test_outifle(char *path, t_out_type type)
{
	t_branch	*branch;
	t_outfile	*outfile;

	branch = ft_calloc(sizeof(t_branch), 1);
	outfile = ft_calloc(sizeof(t_outfile), 1);
	branch->type = T_OUTFILE;
	branch->elmnt = outfile;
	outfile->path = ft_strdup(path);
	outfile->type = type;
	return (branch);
}

static t_branch	*define_test_cmd(t_branch *branch, char **args)
{
	t_cmd	*cmd;

	cmd = ft_calloc(sizeof(t_cmd), 1);
	cmd->cmd_path = ft_strdup(args[0]);
	cmd->args = ft_calloc(sizeof(char *), 3);
	cmd->args[0] = ft_strdup(args[1]);
	cmd->args[1] = ft_strdup(args[2]);
	cmd->args[2] = NULL;
	branch->elmnt = cmd;
	branch->type = T_CMD;
	cmd->tree = ft_calloc(sizeof(t_branch *), 6);
	cmd->tree[0] = define_test_infile(args[3]);
	cmd->tree[1] = define_test_infile(args[4]);
	cmd->tree[2] = define_test_outifle(args[5], OT_APPEND);
	cmd->tree[3] = define_test_outifle(args[6], OT_TRUNC);
	cmd->tree[4] = NULL;
	return (branch);
}

static int	wait_children(int pid)
{
	int	wait_status;
	int	error_status;

	while (errno != ECHILD)
		if (wait(&wait_status) == pid && WIFEXITED(wait_status))
			error_status = WEXITSTATUS(wait_status);
	if (pid == -1)
		return (127);
	return (error_status);
}

int	main(int argc, char *argv[], char **env)
{
	t_branch	*branch;

	if (argc < 8)
		return (ft_dprintf(2, TEST_ERR));
	branch = ft_calloc(sizeof(t_branch), 1);
	branch = define_test_cmd(branch, &argv[1]);
	differentiate_branches(branch);
	execute_tree(branch, env);
	wait_children(1);
	(void)argc;
	(void)argv;
	return (0);
}
