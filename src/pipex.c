/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agossariass <agossariass@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 18:17:17 by aarias-d          #+#    #+#             */
/*   Updated: 2025/10/03 13:44:23 by agossariass      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

void	ft_father_process(int argc, char **argv, char **envp, int *pfd)
{
	int	fd;

	dup2(pfd[0], STDIN_FILENO);
	close(pfd[0]);
	close(pfd[1]);
	fd = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		ft_error("Error with file");
	dup2(fd, STDOUT_FILENO);
	close(fd);
	execute(argc, argv[3], envp, pfd);
}

void	ft_child_process(int argc, char **argv, char **envp, int *pfd)
{
	int	file;

	file = open(argv[1], O_RDONLY);
	if (file == -1)
		ft_error("File not found");
	close(pfd[0]);
	dup2(pfd[1],STDOUT_FILENO);
	close(pfd[1]);
	dup2(file, STDIN_FILENO);
	close(file);
	execute(argc, argv[2], envp, pfd);
}

int	main(int argc, char **argv, char **envp)
{
	pid_t	pid;
	int		pfd[2];
	int		status;


	if (argc != 5)
		ft_error("Need 4 arguments");
	if (pipe(pfd) == -1)
		ft_error("Error pipe");
	pid = fork();
	if (pid == -1)
		ft_error("Error fork");
	if (pid == 0)
		ft_child_process(argc, argv, envp, pfd);
	else
	{
		ft_father_process(argc, argv, envp, pfd);
		waitpid(pid, &status, 0);
	}
}
