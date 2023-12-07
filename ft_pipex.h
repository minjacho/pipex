/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjacho <minjacho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 11:41:13 by minjacho          #+#    #+#             */
/*   Updated: 2023/12/07 13:45:33 by minjacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PIPEX_H
# define FT_PIPEX_H

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h> // perror
# include <string.h> // strerror
# include <sys/wait.h>
# include <sys/errno.h>
# include "libft/libft.h"

typedef struct s_exe
{
	char	*path;
	char	**args;
}	t_exe;

typedef struct s_pstat
{
	pid_t	pid;
	int		exit_stat;
}	t_pstat;

typedef struct s_pipe_info
{
	char	**argv;
	char	**paths;
	char	**envp;
}	t_pipe_info;

void	exit_with_err(void);
char	**parse_path(char **envp);
void	get_exe(t_exe *exe, char *argv, char **paths);
void	free_double_ptr(char **lists);

#endif
