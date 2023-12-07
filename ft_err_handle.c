/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_err_handle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjacho <minjacho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 11:40:43 by minjacho          #+#    #+#             */
/*   Updated: 2023/12/07 11:40:45 by minjacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"

void	exit_with_err(void)
{
	perror(strerror(errno));
	exit(errno);
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
