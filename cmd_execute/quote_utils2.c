/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoh <myoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/29 15:38:29 by myoh              #+#    #+#             */
/*   Updated: 2020/11/29 17:51:42 by myoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*int		ft_envlen(char *src, int i)
{
	int		count;
	char	buf[4096];

	count = 0;
	ft_bzero(buf, sizeof(buf));
	i++;
	while (src[i] && (ft_is_alnum(src[i]) || is_instr(src[i], "?_")))
	{
		if (ft_isdigit(src[i]) && count == 0)
			return (0);
		buf[count] = src[i];
		if (src[i] == '?' && count == 0)
			break ;
		i = i + 1;
		count++;
	}
	if (get_env(env_list, buf))
		count = ft_strlen(get_env(env_list, buf));
	return (count);
}*/

int		quote_len(char *src, int type, int env)
{
	int	i;
	int	j;
	int	esc;

	i = 0;
	j = 0;
	esc = 0;
	while (src[i])
	{
		if (!esc && src[i] == '\'' && type == 2)
			return (i);
		if (!esc && src[i] == '\'' && type == 0)
			return (i + j);
	//	if (!esc && src[i] == '$' && (type == 0 || type == 1 || type == 4) && env)
		//	j += ft_envlen(src, i);
		if (!esc && src[i] == '\"' && (type == 0 || type == 1))
			return (i + j);
		esc = 0;
		src[i] == '\\' && type != 2 ? esc = 1 : 0;
		i++;
	}
	return (i + j);
}

char	*simple_quote(char *src, int *i)
{
	char	*res;
	int		j;

	(*i)++;
	j = quote_len(src + *i, 2, 0);
	if (!(res = (char *)ft_calloc(1, j + 1)))
		exit(1);
	j = 0;
	while (src[*i] && src[*i] != '\'')
	{
		res[j] = src[*i];
		*i = *i + 1;
		j++;
	}
	res[j] = '\0';
	return (res);
}

char	*no_quote(char *src, int *i, int j, int env)
{
	char	*res;
	char	*tmp;
	int		k;

	k = quote_len(src + *i, 0, env);
	if (!(res = (char *)ft_calloc(1, k + 5)))
		exit(1);
	while (src[*i] && j < k)
	{
		if ((src[*i] == '\'' || src[*i] == '\"') && !line_escape(src, *i - 1))
			break ;
		if (src[*i] == '$' && !line_escape(src, *i - 1) && env
			&& (ft_is_alnum(src[*i + 1]) || is_instr(src[*i + 1], "?_")))
		{
			//tmp = replace_env2(src, i);
			j = ft_strlcat(res, tmp, k);
			free(tmp);
			continue ;
		}
		if ((src[*i] != '\\' || line_escape(src, *i - 1)) && j < k)
			res[j++] = src[*i];
		(*i)++;
	}
	return ((res[j] = '\0') == 0 ? res : res);
}

char	*double_quote(char *src, int *i, int j, int env)
{
	char	*res;
	char	*tmp;
	int		k;

	k = quote_len(src + *i, 1, env);
	if (!(res = (char *)ft_calloc(1, k + 1)))
		exit(1);
	while (src[*i] && j < k)
	{
		if (src[*i] == '\"' && !line_escape(src, *i - 1))
			break ;
		if (src[*i] == '$' && !line_escape(src, *i - 1) && env
			&& (ft_is_alnum(src[*i + 1]) || is_instr(src[*i + 1], "?_")))
		{
			//tmp = replace_env2(src, i);
			j = ft_strlcat(res, tmp, k);
			free(tmp);
			continue ;
		}
		if ((src[*i] != '\\' || line_escape(src, *i - 1) || (src[*i + 1] != '\"'
			&& src[*i + 1] != '\\' && src[*i + 1] != '$')) && j < k)
			res[j++] = src[*i];
		(*i)++;
	}
	return ((res[j] = '\0') == 0 ? res : res);
}

char	*exec_quotes(char *src, int env)
{
	int		i;
	char	*res;

	if (src == NULL)
		return (src);
	i = 0;
	res = ft_strdup("");
	while (src[i])
	{
		if (src[i] == '\'' && !line_escape(src, i - 1))
			res = ft_strjoin_free(res, simple_quote(src, &i));
		else if (src[i] == '\"' && !line_escape(src, i - 1))
		{
			i++;
			res = ft_strjoin_free(res, double_quote(src, &i, 0, env));
		}
		else
		{
			res = ft_strjoin_free(res, no_quote(src, &i, 0, env));
			continue ;
		}
		src[i] ? i++ : 0;
	}
	ft_strdel(&src);
	return (res);
}