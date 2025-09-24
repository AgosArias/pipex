/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarias-d <aarias-d@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 18:17:17 by aarias-d          #+#    #+#             */
/*   Updated: 2025/09/24 10:12:10 by aarias-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

void	ft_child_process(int argc, char **argv, char **envp, int *pdf)
{
	close(pdf[0]);
	dup2(pdf[1], STDIN_FILENO);
	dup("Procesar", STDOUT_FILENO);
	_exit(EXIT_SUCCESS);
	
}

int	main(int argc, char **argv, char **envp)
{
	pid_t	pid1;
	int	pfd[2];

	if(argc != 5)
	{
		printf("Need 4 arguments");
		exit(EXIT_FAILURE);
	}
	if (pipe(pfd) == -1)
	{
		perror("Error pipe");
		exit(EXIT_FAILURE);
	}
	pid1 = fork();
	if(pid1 == -1)
		perror("Error fork");
	if (pid1 == 0)
		ft_child_process(argc, argv, envp, pfd);
	else
	{
		wait(pfd);
		if (close(pfd[0]) == -1)
			perror("close in father");
		if(write(pfd[1] , argv [1], 1) != 1)
			perror("error write in father");
		if (close(pfd[1]) == -1)
			perror("close in father, second");

		printf("\nFather\n");
		exit(EXIT_SUCCESS);
	}
}

