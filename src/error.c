/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phialfai <phialfai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 10:10:12 by phialfai          #+#    #+#             */
/*   Updated: 2023/11/16 10:44:16 by phialfai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/**
 * 
*/
void	*print_error(char *err_msg, char *strerr_msg)
{
	write(2, "Error\n", ft_strlen("Error\n"));
	write(2, err_msg, ft_strlen(err_msg));
	if (strerr_msg != NULL)
	{
		write(2, ": ", ft_strlen(": "));
		write(2, strerr_msg, ft_strlen(strerr_msg));
	}
	write(2, "\n", 1);
	return (NULL);
}

/**
 * 
*/
void	exit_if(int state, char *err_msg)
{
	if (!state)
		return ;
	if (err_msg != NULL)
	{
		write(2, err_msg, ft_strlen(err_msg));
		write(2, "\n", 1);
	}
	exit(EXIT_FAILURE);
}
