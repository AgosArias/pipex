/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarias-d <aarias-d@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 18:17:17 by aarias-d          #+#    #+#             */
/*   Updated: 2025/09/23 18:31:21 by aarias-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

int	main(int argc, char **argv, char **envp)
{
	int	pid1;

	pid1 = fork();
	if(pid1 == -1)
		printf("Error");
	if (pid1 == 0)
		printf("child");
	else
		printf("father");
	return (0);
}
