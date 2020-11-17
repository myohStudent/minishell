/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_execute.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoh <myoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 17:16:15 by myoh              #+#    #+#             */
/*   Updated: 2020/11/17 14:44:19 by myoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//'>'out에 대한 함수랑 '<' in에 대한 함수 따로 만들어야 함.
int exec_redirs_out(t_cmd *curr, t_minishell *minishell) 
{
    int     i;
    int     fd;

    i = 0;
    // 1. 인풋 파싱하기 '>'이 있나 
    // 2. 파싱한 뒤 
    // 3. parsed_input은 이중배열이어야 함. 혹은 cmd_array로 파싱하기
    if (parsed_input[i])
    {
        if (!parsed_input[i + 1])
            return (-1);
        else // 리다이렉션 파일 생성하기
        {
            if ((fd = open(parsed_input[i + 1], O_RDWR | O_CREAT | S_IROTH, 0644)) == -1)
                return (-1); //perror 
        }
        dup2(fd, STDOUT_FILENO);
        close(fd);
        parsed_input[i] = NULL;
        parsed_input[i + 1] = NULL;
        for (i = i ; parsed_input[i] != NULL; i++)
        {
            parsed_input = parsed_input[i + 2];
        }
    parsed_input = NULL;
    }
    return (1);
}