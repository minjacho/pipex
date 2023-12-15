/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_parse.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjacho <minjacho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 15:21:04 by minjacho          #+#    #+#             */
/*   Updated: 2023/12/15 11:23:46 by minjacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"

static int	count_word_sub(t_split_info *info, size_t idx)
{
	int	flag;
	int	has_back;

	flag = info->str[idx];
	info->word_cnt++;
	info->str[idx++] = 0;
	while (idx < info->str_len)
	{
		if (info->str[idx] == flag && !has_back)
			break ;
		has_back = (info->str[idx] == '\\');
		idx++;
	}
	info->str[idx++] = 0;
	return (idx);
}

static void	count_word(t_split_info *info)
{
	size_t	idx;
	int		has_back;

	idx = 0;
	info->word_cnt = 0;
	has_back = 0;
	while (idx < info->str_len)
	{
		if (info->str[idx] == '\\')
			has_back = 1;
		else
			has_back = 0;
		if ((info->str[idx] == '\'' || info->str[idx] == '\"') && !has_back)
			idx = count_word_sub(info, idx);
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

static void	str_to_arr(t_split_info *info)
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
