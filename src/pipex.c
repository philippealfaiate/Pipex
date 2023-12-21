/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phialfai <phialfai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 12:49:11 by phialfai          #+#    #+#             */
/*   Updated: 2023/11/16 11:04:29 by phialfai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	execute_cmd(char *argv, char *envp[])
{
	char	**cmd;
	char	*path;

	cmd = ft_split(argv, ' ');
	path = pathfinder(cmd[0], set_paths(envp));
	exit_if(execve(path, cmd, envp) == -1, "Error: execve");
}

void	child_process_0(int pipe_fd[2], int fd_in, char *argv[], char *envp[])
{
	dup2(pipe_fd[1], STDOUT_FILENO);
	close(pipe_fd[0]);
	dup2(fd_in, STDIN_FILENO);
	execute_cmd(argv[2], envp);
}

void	child_process_1(int pipe_fd[2], int fd_out, char *argv[], char *envp[])
{
	dup2(pipe_fd[0], STDIN_FILENO);
	close(pipe_fd[1]);
	dup2(fd_out, STDOUT_FILENO);
	execute_cmd(argv[3], envp);
}

void	pipex(char *argv[], char *envp[])
{
	pid_t	pid[2];
	int		file_fd[2];
	int		pipe_fd[2];

	file_fd[0] = open(argv[1], O_RDONLY);
	exit_if(file_fd[0] == -1, "Error: File in");
	file_fd[1] = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	exit_if(file_fd[1] == -1, "Error: File out");
	exit_if(pipe(pipe_fd) == -1, "Error: Pipe");
	pid[0] = fork();
	exit_if(pid[0] == -1, "Error: Fork 0");
	if (pid[0] == 0)
		child_process_0(pipe_fd, file_fd[0], argv, envp);
	pid[1] = fork();
	exit_if(pid[1] == -1, "Error: Fork 1");
	if (pid[1] == 0)
		child_process_1(pipe_fd, file_fd[1], argv, envp);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	waitpid(pid[0], NULL, 0);
	waitpid(pid[1], NULL, 0);
	close(file_fd[0]);
	close(file_fd[1]);
}

int	main(int argc, char *argv[], char *envp[])
{
	exit_if(argc != 5, "usage: file1 cmd1 cmd2 file2");
	pipex(argv, envp);
	return (0);
}
