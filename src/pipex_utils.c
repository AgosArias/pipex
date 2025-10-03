/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agossariass <agossariass@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 19:04:23 by aarias-d          #+#    #+#             */
/*   Updated: 2025/10/03 16:57:24 by agossariass      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

void	ft_error(char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}

void	ft_free_matriz(char **matriz)
{
	int	i;

	if (!matriz)
		return ;
	i = 0;
	while (matriz[i])
	{
		free(matriz[i]);
		i++;
	}
	free(matriz);
}

char	*ft_get_path(char **envp, char *cmd)
{
	char	*path;
	char	**dir;
	char	*path_complete;
	int		i;

	if (!cmd || !envp || !*envp)
		return (NULL);
	while (*envp && !ft_strnstr(*envp, "PATH", 4))
		envp++;
	if (!*envp)
		return (NULL);
	i = 0;
	dir = ft_split((*envp) + 5, ':');
	if (!dir)
		return (NULL);
	path_complete = NULL;
	while (dir[i])
	{
		path = ft_strjoin(dir[i], "/");
		if (!path)
			break;
		path_complete = ft_strjoin(path, cmd);
		if (!path_complete)
			break;
		free(path);
		if (!access(path_complete, X_OK))
			break ;
		else
		{
			free(path_complete);
			path_complete = NULL;
		}
		i++;
	}
	ft_free_matriz(dir);
	return (path_complete);
}

void	execute( char *cmd_arg, char **envp)
{
	char	**cmd;
	char	*path;
	int		i;

	i = 0;
	cmd = ft_split(cmd_arg, ' ');
	if (!cmd)
		ft_error("Error command");
	while (cmd[i])
		i++;
	i = 0;
	path = ft_get_path(envp, cmd[0]);
	if (!path)
		ft_error("Command not found");
	execve(path, cmd, envp);
	free(path);
	ft_free_matriz(cmd);
	ft_error("Execve");
}
