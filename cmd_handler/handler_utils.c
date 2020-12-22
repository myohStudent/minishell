/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoh <myoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/02 19:50:45 by myoh              #+#    #+#             */
/*   Updated: 2020/12/22 22:44:22 by myoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    free_arr(char **arr)
{
    int i;

    i = 0;
    while (arr[i] != NULL)
        free(arr[i++]);
    free(arr);
}

int     arr_len(char **env)
{
    int i;

    i = 0;
    while (env[i] != NULL)
        i++;
    return (i);
}

char    *parse_space(char *s, char *space)
{
    int i;

    i = 0;
    if (!space || !s)
        return (NULL);
    while (ft_strchr(s, space && s[i] != '\0'))
    {
        s++;
        i++;
    }
    i = ft_strlen(s);
    while (ft_strchr(space, s[i]) && s != 0)
        i--;
    return (ft_substr(s, 0, i + 1));
}

int         exceptions2(char *input, int i)
{
    while (input[i])
    {
        if (input[i] == '|' && input[i + 1] == '|')
        {
            ft_printf("syntax error near unexpected token `|'\n");
            free(input);
            return (-1);
        }
        else if (input[i] == '<' && (input[i + 1] == '<' || input[i + 1] == '>'))
        {
            ft_printf("syntax error near unexpected token `newline'\n");
            free(input);
            return (-1);
        }
        else if (input[i] == '>' && input[i + 1] == '>' && input[i + 2] == '>')
        {
            ft_printf("syntax error near unexpected token `newline'\n");
            free(input);
            return (-1);
        }
        i++;
    }
    return (1);
}

int         exceptions(char *input)
{
    int     i;

    i = 0;
    if (!input)
        return (-1);
    if (input[i] == '|')
    {
        ft_printf("syntax error near unexpected token `|'\n");
        free(input);
        return (-1);
    }
    else if (input[i] == '>' || input[i] == '<')
    {
        ft_printf("syntax error near unexpected token `newline'\n");
        free(input);
        return (-1);
    }
    if (exceptions2(input, i) < 0)
        return (-1);
    return (1);
}

void        init_num(t_minishell *minishell)
{
    pipe_num = 0;
    minishell->redir_num = 0;
}

int         check_last_token(char *input)
{
    char    *s;

    s = ft_trim(input);
    if (s[ft_strlen(s) -1] == '|' || s[ft_strlen(s) -1] == '>'
        || s[ft_strlen(s) -1] == '<')
    {
        ft_printf("올바르게 다시 입력하세요\n");
        free(input);
        free(s);
        return (-1);
    }
    free(raw_input);
    raw_input = NULL;
    raw_input = ft_strdup(s);
    free(input);
    input = NULL;
    input = ft_strdup(s);
    free(s);
    return (1);
}

int         check_token(t_minishell *minishell, t_cmd *curr)
{
    char    *input;
    int     i;

    init_num(minishell);
    input = ft_strdup(raw_input);
    if (check_last_token(input) < 0)
        return (0);
    i = 0;
    if (exceptions(input) < 0)
        return (0);
    while (input[i])
    {
        if (input[i] == '|')
            pipe_num++;
        else if (input[i] == '>' || input[i] == '<')
            minishell->redir_num++;
        i++;
    }
    free(input);
    return (1);
}