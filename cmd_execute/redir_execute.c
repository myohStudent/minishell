/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_execute.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoh <myoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 17:16:15 by myoh              #+#    #+#             */
/*   Updated: 2020/11/22 22:45:24 by myoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//'>'out에 대한 함수랑 '<' in에 대한 함수 '>>' 따로 만들어야 함(3개).
// 파싱 방법 구상해 보기 : 
// asdf | sdf > sdfl  => 이런 경우, 파이프 안의 플래그로 작용.
// pwd > sdfkl | sdfkl => 역시 파이프 안의 플래그로 작용
// sdpf > sdklf => 단독 리다이렉션 플래그로 작용.         
// 그래서 파싱을 1) 파이프 안에서 옵션 넣고서 한다 2) 단독으로도 한다 3) 세미콜론으로 혹은 다음 파이프로 돌아가는 flag 처리도 파이프와 같이 해야 함 
//  
//
//


int exec_redir(t_cmd *curr, t_minishell *minishell) 
{
    int     i;
    int     fd;

    i = 0;
    // 1. 인풋 파싱하기 '>'이 있나 
    // 2. 파싱한 뒤 
   /* if (curr->command)
    {
        if (!curr->next)
            return (-1);
        else // 리다이렉션 파일 생성하기
        {
            if ((fd = open(curr->next->command, O_RDWR | O_CREAT | S_IROTH, 0644)) == -1)
                return (-1); //perror 
        }
        dup2(fd, STDOUT_FILENO);
        close(fd);
        curr->command = NULL;
        curr->next->command = NULL;
        if (curr->command != NULL)
        {
            curr->next = curr->next->next;
            curr = curr->next;
        }
    curr->command = NULL;
    }*/
    return (1);
}

/* 깃헙에 있는 거 가져옴!
int redirect(char * input, char * output, char * error){
	int fd;
	
	//Redirección de entrada.
	if(input != NULL){
		fd = open(input,O_RDONLY);
		if(fd == -1){
			printf("%s, Error: fallo en apertura de fichero.\n",input);
			exit(1);
		}else{
			dup2(fd,0);
			close(fd);
		}
	}
	//Redireccion de salida
	if(output != NULL){
		fd = creat(output,S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		if(fd == -1){
			printf("%s, Error: fallo en apertura o creacion de fichero.\n",output);
			exit(1);
		}else{
			dup2(fd,1);
			close(fd);
		}
	}
	//Redireccion de error
	if(error != NULL){
		fd = creat(error,S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		if(fd == -1){
			printf("%s, Error: fallo en apertura o creacion de fichero.\n",error);
			exit(1);
		}else{
			dup2(fd,2);
			close(fd);
		}
	}
	return EXIT_SUCCESS;
}
*/

/* 깃헙에 있는 거 가져옴!
int redirect(char * input, char * output, char * error){
	int fd;
	
	//Redirección de entrada.
	if(input != NULL){
		fd = open(input,O_RDONLY);
		if(fd == -1){
			printf("%s, Error: fallo en apertura de fichero.\n",input);
			exit(1);
		}else{
			dup2(fd,0);
			close(fd);
		}
	}
	//Redireccion de salida
	if(output != NULL){
		fd = creat(output,S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		if(fd == -1){
			printf("%s, Error: fallo en apertura o creacion de fichero.\n",output);
			exit(1);
		}else{
			dup2(fd,1);
			close(fd);
		}
	}
	//Redireccion de error
	if(error != NULL){
		fd = creat(error,S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		if(fd == -1){
			printf("%s, Error: fallo en apertura o creacion de fichero.\n",error);
			exit(1);
		}else{
			dup2(fd,2);
			close(fd);
		}
	}
	return EXIT_SUCCESS;
}
*/