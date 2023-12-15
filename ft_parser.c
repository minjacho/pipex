/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjacho <minjacho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 14:06:51 by minjacho          #+#    #+#             */
/*   Updated: 2023/12/15 11:10:30 by minjacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"

static char	*get_path(char **envp)
{
	int		idx;
	char	*path;

	idx = 0;
	while (envp[idx])
	{
		if (ft_strncmp(envp[idx], "PATH", 4) == 0)
			break ;
		idx++;
	}
	if (!envp[idx])
		return (NULL);
	path = ft_strchr(envp[idx], '=');
	path++;
	return (path);
}

char	**parse_path(char **envp)
{
	char	*tmp;
	char	*path;
	char	**paths;
	int		idx;

	idx = 0;
	path = get_path(envp);
	if (!path)
		exit_with_err();
	paths = ft_split(path, ':');
	if (!paths)
		exit_with_err();
	while (paths[idx])
	{
		tmp = ft_strjoin(paths[idx], "/");
		if (!tmp)
			exit_with_err();
		free(paths[idx]);
		paths[idx] = tmp;
		idx++;
	}
	return (paths);
}

char	*find_path(char *file_name, char **paths)
{
	int		idx;
	char	*file_path;

	idx = 0;
	while (paths[idx])
	{
		file_path = ft_strjoin(paths[idx], file_name);
		if (!file_path)
			exit_with_err();
		if (access(file_path, X_OK) == 0)
			break ;
		free(file_path);
		file_path = NULL;
		idx++;
	}
	return (file_path);
}

void	get_exe(t_exe *exe, int idx, t_pipe_info *info)
{
	char	*file_path;

	exe->args = ft_exe_split(info->argv[idx]);
	if (!exe->args)
		exit_with_err();
	exe->path = ft_strdup(exe->args[0]);
	if (!exe->path)
		exit_with_err();
	if (ft_strncmp(exe->path, "./", 2) == 0)
	{
		if (access(ft_strchr(exe->path, '/') + 1, X_OK))
			exit_with_str(info, exe->args[0]);
		return ;
	}
	file_path = find_path(exe->path, info->paths);
	if (file_path)
	{
		free(exe->path);
		exe->path = file_path;
	}
	return ;
}
