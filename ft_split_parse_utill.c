/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_parse_utill.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjacho <minjacho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 11:09:18 by minjacho          #+#    #+#             */
/*   Updated: 2023/12/15 11:24:04 by minjacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"

void	free_err(t_split_info *info, int idx)
{
	int	i;

	i = 0;
	while (i < idx)
	{
		free(info->result[i]);
		info->result[i] = NULL;
		i++;
	}
	free(info->result);
	free(info->str);
	info->str = NULL;
	return ;
}

int	is_space(char c)
{
	if (c == '\t' || c == '\n' || c == '\v' \
		|| c == '\f' || c == '\r' || c == ' ')
		return (1);
	return (0);
}

char	*trim_backslash(char *str)
{
	int		i;
	int		j;
	int		flag;
	char	*result;

	i = -1;
	j = 0;
	result = (char *)ft_calloc(ft_strlen(str) + 1, sizeof(char));
	if (result == NULL)
		return (NULL);
	flag = 0;
	while (str[++i])
	{
		if (str[i] == '\\')
		{
			if (flag == 0)
				flag = 1;
			else
				flag = 0;
		}
		if (flag == 0)
			result[j++] = str[i];
		flag = 0;
	}
	return (result);
}
