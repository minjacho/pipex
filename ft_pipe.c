/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjacho <minjacho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 13:32:32 by minjacho          #+#    #+#             */
/*   Updated: 2023/12/07 14:23:58 by minjacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"

void	exec_child(int is_last, int *pipe_fd, int idx, t_pipe_info info)
{
	t_exe	exe;

	if (!is_last)
	{
		close(pipe_fd[0]);
		if (dup2(pipe_fd[1], STDOUT_FILENO) < 0)
			exit_with_err();
		close(pipe_fd[1]);
	}
	get_exe(&exe, info.argv[idx], info.paths);
	execve(exe.path, exe.args, info.envp);
	exit_with_err();
}

pid_t	fork_argv(int idx, t_pipe_info info, int is_last)
{
	pid_t	pid;
	int		pipe_fd[2];

	if (!is_last)
		if (pipe(pipe_fd) < 0)
			exit_with_err();
	pid = fork();
	if (pid < 0)
		exit_with_err();
	if (pid == 0)
		exec_child(is_last, pipe_fd, idx, info);
	if (!is_last)
	{
		close(pipe_fd[1]);
		if (dup2(pipe_fd[0], STDIN_FILENO) < 0)
			exit_with_err();
		close(pipe_fd[0]);
	}
	else
		close(STDIN_FILENO);
	return (pid);
}

void	open_in_out_file(char *infile, char *outfile)
{
	int	in_fd;
	int	out_fd;

	in_fd = open(infile, O_RDONLY);
	out_fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (in_fd < 0 || out_fd < 0)
		exit_with_err();
	if (dup2(in_fd, STDIN_FILENO) < 0)
		exit_with_err();
	if (dup2(out_fd, STDOUT_FILENO) < 0)
		exit_with_err();
	close(in_fd);
	close(out_fd);
}

void	set_pipe_info(t_pipe_info *info, char **argv, char **envp, char **paths)
{
	info->argv = argv;
	info->envp = envp;
	info->paths = paths;
}

int	main(int argc, char *argv[], char **envp)
{
	int			idx;
	char		**paths;
	t_pstat		*child_stats;
	int			exit_stat;
	t_pipe_info	info;


	if (argc < 5)
		exit(EXIT_FAILURE);
	child_stats = (t_pstat *)malloc(sizeof(t_pstat) * (argc - 2));
	if (!child_stats)
		exit_with_err();
	idx = 2;
	paths = parse_path(envp);
	set_pipe_info(&info, argv, envp, paths);
	open_in_out_file(argv[1], argv[argc - 1]);
	while (idx < argc - 1)
	{
		child_stats[idx - 2].pid = \
			fork_argv(idx, info, (idx == argc - 2));
		idx++;
	}
	idx = -1;
	while (idx++ < argc - 2)
		waitpid(child_stats[idx].pid, &child_stats[idx].exit_stat, 0);
	exit_stat = WEXITSTATUS(child_stats[argc - 3].exit_stat);
	free(child_stats);
	free_double_ptr(paths);
	exit(exit_stat);
}
