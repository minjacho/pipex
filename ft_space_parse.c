/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_space_parse.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjacho <minjacho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 15:21:04 by minjacho          #+#    #+#             */
/*   Updated: 2023/12/10 15:31:20 by minjacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"

static char	*backslash_deleter(char *str)
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

static int	count_word(size_t org_len, char *tmp)
{
	size_t	idx;
	int		flag;
	int		word_cnt;

	idx = 0;
	word_cnt = 0;
	while (idx < org_len)
	{
		if (tmp[idx] == '\'' || tmp[idx] == '\"')
		{
			flag = tmp[idx];
			word_cnt++;
			tmp[idx++] = 0;
			while (idx < org_len && tmp[idx] != flag)
				idx++;
			tmp[idx++] = 0;
		}
		else if (!is_space(tmp[idx]))
		{
			word_cnt++;
			while (idx < org_len && !is_space(tmp[idx]))
				idx++;
		}
		else
			tmp[idx++] = 0;
	}
	return (word_cnt);
}

static char	**clean(char **str_arr, char *str, size_t size)
{
	size_t	idx;

	idx = 0;
	while (idx < size)
	{
		free(str_arr[idx]);
		str_arr[idx] = NULL;
		idx++;
	}
	free(str_arr);
	free(str);
	str = NULL;
	return (NULL);
}

void	str_to_arr(size_t org_len, char *str)
{
	size_t	idx;
	size_t	word_idx;

	idx = 0;
	word_idx = 0;
	while (idx < org_len)
	{
		if (str[idx])
		{
			split->result[word_idx] = backslash_deleter(&str[idx]);
			if (!split->result[word_idx])
			{
				clean(split->result, str, word_idx);
				return ;
			}
			word_idx++;
			while (str[idx] && idx < org_len)
				idx++;
		}
		else
			idx++;
	}
	free(str);
}

char	**new_split(char *s)
{
	size_t	org_len;
	int		word_cnt;
	char	*result;
	char	*tmp;

	org_len = ft_strlen(s);
	tmp = ft_strdup(s);
	if (!tmp)
		return (NULL);
	word_cnt = count_word(org_len, tmp);
	result = (char **)ft_calloc(word_cnt + 1, sizeof(char *));
	if (!result)
	{
		free(tmp);
		tmp = NULL;
		return (NULL);
	}
	str_to_arr(&tmp);
	return (result);
}
