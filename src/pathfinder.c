/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfinder.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phialfai <phialfai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 15:06:31 by phialfai          #+#    #+#             */
/*   Updated: 2023/11/28 13:38:08 by phialfai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/**
 * 
*/
char	*get_system_env(void)
{
	int		i;
	int		fd;
	char	*path;

	fd = open("/etc/environment", O_RDONLY);
	if (fd == -1)
		perror("fd error: /etc/environment");
	path = get_next_line(fd);
	close(fd);
	ft_memmove(path, path + 6, ft_strlen(path) - 6);
	i = 0;
	while (path[i] != '\0')
	{
		if (path[i] == '"' || path[i] == '\n')
			path[i] = '\0';
		i++;
	}
	return (path);
}

/**
 * 
*/
char	**set_paths(char *envp[])
{
	int		i;
	char	*path;
	char	**paths;

	if (*envp == NULL)
		path = get_system_env();
	else
	{
		i = 0;
		while (envp[i] && ft_strncmp(envp[i], "PATH=", 5) != 0)
			i++;
		path = envp[i];
	}
	if (path != NULL)
		paths = ft_split(path, ':');
	return (paths);
}

/**
 * 
*/
char	*pathfinder(char *argv, char *paths[])
{
	int		i;
	char	*path;
	char	*temp;

	path = NULL;
	if (access(argv, F_OK) == 0 && access(argv, R_OK) == 0)
		path = ft_strdup(argv);
	i = 0;
	while (paths[i] != NULL && path == NULL)
	{
		temp = ft_strjoin(paths[i], "/");
		path = ft_strjoin(temp, argv);
		free(temp);
		temp = NULL;
		if (access(path, F_OK) == -1 || access(path, R_OK) == -1)
		{
			free(path);
			path = NULL;
		}
		i++;
	}
	return (path);
}
