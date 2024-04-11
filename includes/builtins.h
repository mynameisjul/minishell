/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblaye <jblaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 15:57:17 by acroue            #+#    #+#             */
/*   Updated: 2024/04/11 10:40:36 by jblaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"

typedef enum e_builtin
{
	B_ERR = 0,
	B_ECHO,
	B_PWD,
	B_EXPORT,
	B_ENV,
	B_CD,
	B_UNSET,
	B_EXIT
}			t_bltin;

# define E_NULL_BUILTIN "The builtin name was NULL\n"
# define E_NO_BUILTIN "does not match any known builtin \
(not supposed to happen)\n"
# define BI_ECHO "echo"
# define BI_PWD "pwd"
# define BI_EXPORT "export"
# define BI_ENV "env"
# define BI_CD "cd"
# define BI_UNSET "unset"
# define BI_EXIT "exit"
# define WRITE_FILE_FULL "tacOS: %s: write error: No space left on device\n"
# define ENV_WRITE_FULL "%s: write error: No space left on device\n"

/*			PWD					*/
int		pwd_built_in(void);
/*			CD					*/
int 	cd_built_in(t_env *env, t_cmd *cd_cmd);
/* 			ENV				 */
int		env_built_in(t_cmd *cmd, int fd_out);
/* 			UNSET			 */
char	**remove_from_env(char **env, char *var);
/* 			EXPORT			 */
char	**add_to_env(char **env, char *arg);
int		is_valid_env_var(const char *s);
size_t	length_until_char(const char *str, char ch);
int		export_print_env(t_cmd *cmd, int fd_out);
/* 			ENV UTILS			 */
t_env	*make_env(char **env_tab);
size_t	tab_len(char **tab);
char	**sort_char_tab(char **tab);
size_t	length_until_char(const char *str, char ch);
/* 			BUILTINS UTILS		 */
pid_t	fork_built_ins(int	fd_out, t_branch *branch, size_t *cmd_number, t_env *env);
int		is_built_in(t_branch *branch);
int		handle_builtins(t_branch *branch, size_t *cmd_number, int outfile, t_env *env);

#endif
