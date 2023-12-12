/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_space_parse.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjacho <minjacho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 15:21:04 by minjacho          #+#    #+#             */
/*   Updated: 2023/12/12 14:31:26 by minjacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"

int	is_space(char c)
{
	if (c == '\t' || c == '\n' || c == '\v' \
		|| c == '\f' || c == '\r' || c == ' ')
		return (1);
	return (0);
}

static char	*trim_backslash(char *str)
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

static void	count_word(t_split_info *info)
{
	size_t	idx;
	int		flag;

	idx = 0;
	info->word_cnt = 0;
	while (idx < info->str_len)
	{
		if (info->str[idx] == '\'' || info->str[idx] == '\"')
		{
			flag = info->str[idx];
			info->word_cnt++;
			info->str[idx++] = 0;
			while (idx < info->str_len && info->str[idx] != flag)
				idx++;
			info->str[idx++] = 0;
		}
		else if (!is_space(info->str[idx]))
		{
			info->word_cnt++;
			while (idx < info->str_len && !is_space(info->str[idx]))
				idx++;
		}
		else
			info->str[idx++] = 0;
	}
}

static void free_err(t_split_info *info, int idx)
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

void	str_to_arr(t_split_info *info)
{
	size_t	idx;
	int		word_idx;

	idx = 0;
	word_idx = 0;
	while (idx < info->str_len)
	{
		if (info->str[idx])
		{
			info->result[word_idx] = trim_backslash(&info->str[idx]);
			if (!info->result[word_idx])
			{
				free_err(info, word_idx);
				return ;
			}
			word_idx++;
			while (info->str[idx] && idx < info->str_len)
				idx++;
		}
		else
			idx++;
	}
	free(info->str);
}

char	**ft_exe_split(char *str)
{
	t_split_info	info;

	info.str_len = ft_strlen(str);
	info.str = ft_strdup(str);
	if (!info.str)
		return (NULL);
	count_word(&info);
	info.result = (char **)ft_calloc(info.word_cnt + 1, sizeof(char *));
	if (!info.result)
	{
		free(info.str);
		info.str = NULL;
		return (NULL);
	}
	str_to_arr(&info);
	return (info.result);
}
int main(int argc, char *argv[])
{
	char **ptr = ft_exe_split(argv[1]);
	for (int i = 0 ; ptr[i] ; i++)
		printf("%s\n", ptr[i]);
}
