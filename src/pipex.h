/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phialfai <phialfai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 21:01:29 by philippe          #+#    #+#             */
/*   Updated: 2023/11/28 14:53:02 by phialfai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <string.h>
# include <errno.h>
# include <sys/stat.h>

# include "../libft/libft.h"

/** ./pipex.c */
void	pipex(char *argv[], char *envp[]);
void	child_process_0(int pipe_fd[2], int fd_in, char *argv[], char *envp[]);
void	child_process_1(int pipe_fd[2], int fd_out, char *argv[], char *envp[]);
void	execute_cmd(char *argv, char *envp[]);

/** ./pathfinder.c */
char	*get_system_env(void);
char	*pathfinder(char *argv, char *paths[]);
char	**set_paths(char *envp[]);

/** ./error.c */
void	*print_error(char *err_msg, char *strerr_msg);
void	exit_if(int state, char *err_msg);

#endif
