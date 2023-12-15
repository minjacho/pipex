/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_err_handle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjacho <minjacho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 11:40:43 by minjacho          #+#    #+#             */
/*   Updated: 2023/12/15 13:22:31 by minjacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"

void	exit_with_err(void)
{
	const char	*err_msg = strerror(errno);

	write(2, err_msg, ft_strlen(err_msg));
	exit(errno);
}

void	exit_with_str(t_pipe_info *info, char *str, int custom_errno)
{
	const char	*err_msg = strerror(errno);

	write(2, info->argv[0], ft_strlen(info->argv[0]));
	write(2, ": ", 2);
	write(2, str, ft_strlen(str));
	write(2, ": ", 2);
	write(2, err_msg, ft_strlen(err_msg));
	write(2, "\n", 1);
	if (custom_errno == 0)
		exit(errno);
	else
		exit(custom_errno);
}

void	access_err(char *exe_name, t_pipe_info *info)
{
	const char	*err_msg = "command not found";

	write(2, info->argv[0], ft_strlen(info->argv[0]));
	write(2, ": ", 2);
	write(2, exe_name, ft_strlen(exe_name));
	write(2, ": ", 2);
	write(2, err_msg, ft_strlen(err_msg));
	write(2, "\n", 1);
	exit(127);
}

void	open_err(char *file_name, t_pipe_info *info)
{
	const char	*err_msg = ": no such file or directory: ";

	write(2, info->argv[0], ft_strlen(info->argv[0]));
	write(2, err_msg, ft_strlen(err_msg));
	write(2, file_name, ft_strlen(file_name));
	write(2, "\n", 1);
}

void	free_double_ptr(char **lists)
{
	int	idx;

	idx = 0;
	while (lists[idx])
	{
		free(lists[idx]);
		idx++;
	}
	free(lists);
}
