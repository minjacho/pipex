/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjacho <minjacho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 13:32:32 by minjacho          #+#    #+#             */
/*   Updated: 2023/12/10 14:42:23 by minjacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"

void	dup_file_to_fd(t_pipe_info *info, char *name, int fd, int open_flag)
{
	int	file_fd;

	if (fd == STDOUT_FILENO)
		file_fd = open(name, open_flag, 0644);
	else
		file_fd = open(name, open_flag);
	if (file_fd < 0)
		exit_with_str(info, name);
	if (dup2(file_fd, fd) < 0)
		exit_with_str(info, name);
	close(file_fd);
}

void	exec_child(int *pipe_fd, int idx, t_pipe_info *info)
{
	t_exe	exe;

	if (idx < info->argc - 2)
	{
		close(pipe_fd[0]);
		if (dup2(pipe_fd[1], STDOUT_FILENO) < 0)
			exit_with_str(info, info->argv[idx]);
		close(pipe_fd[1]);
	}
	else
		dup_file_to_fd(info, info->argv[info->argc - 1], STDOUT_FILENO, \
			O_WRONLY | O_CREAT | O_TRUNC);
	get_exe(&exe, idx, info);
	if (access(exe.path, X_OK) < 0)
		access_err(exe.args[0], info);
	if (idx == 2)
		dup_file_to_fd(info, info->argv[1], STDIN_FILENO, O_RDONLY);
	execve(exe.path, exe.args, info->envp);
	exit_with_str(info, info->argv[idx]);
}

pid_t	fork_argv(int idx, t_pipe_info *info)
{
	pid_t	pid;
	int		pipe_fd[2];

	if (idx < info->argc -2)
		if (pipe(pipe_fd) < 0)
			exit_with_str(info, info->argv[idx]);
	pid = fork();
	if (pid < 0)
		exit_with_str(info, info->argv[idx]);
	if (pid == 0)
		exec_child(pipe_fd, idx, info);
	if (idx < info->argc -2)
	{
		close(pipe_fd[1]);
		if (dup2(pipe_fd[0], STDIN_FILENO) < 0)
			exit_with_str(info, info->argv[idx]);
		close(pipe_fd[0]);
	}
	else
		close(STDIN_FILENO);
	return (pid);
}

void	set_pipe_info(t_pipe_info *info, int argc, char **argv, char **envp)
{
	info->argc = argc;
	info->argv = argv;
	info->envp = envp;
	info->paths = parse_path(envp);
}

int	main(int argc, char *argv[], char **envp)
{
	int			idx;
	t_pstat		*child_stats;
	int			exit_stat;
	t_pipe_info	info;

	if (argc < 5)
		exit(EXIT_FAILURE);
	set_pipe_info(&info, argc, argv, envp);
	child_stats = (t_pstat *)malloc(sizeof(t_pstat) * (argc - 3));
	if (!child_stats)
		exit_with_err();
	idx = 2;
	while (idx < argc - 1)
	{
		child_stats[idx - 2].pid = fork_argv(idx, &info);
		idx++;
	}
	idx = -1;
	while (idx++ < argc - 2)
		waitpid(child_stats[idx].pid, &child_stats[idx].exit_stat, 0);
	exit_stat = WEXITSTATUS(child_stats[argc - 4].exit_stat);
	free(child_stats);
	free_double_ptr(info.paths);
	exit(exit_stat);
}
