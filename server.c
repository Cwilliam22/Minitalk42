/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcapt < wcapt@student.42lausanne.ch >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 14:07:38 by wcapt             #+#    #+#             */
/*   Updated: 2025/02/13 12:39:42 by wcapt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/includes/libft.h"

#include <unistd.h>
#include <stdio.h>

void	get_signal(int signal)
{
	static int				bit = 0;
	static unsigned char	m = 0;

	if (signal == SIGUSR2)
		m |= (1 << (7 - bit));
	bit++;
	if (bit == 8)
	{
		if (m == '\0')
			ft_printf("\n");
		else
			ft_printf("%c", m);
		fflush(stdout);
		bit = 0;
		m = 0;
	}
}

int	main(int argc, char **argv)
{
	__pid_t	pid;

	pid = getpid();
	(void)argv;
	if (argc != 1)
		return (ft_printf("Too many arguments. Try again !!!\n"), 1);
	ft_printf("PID : %d\n", pid);
	ft_printf("Waiting for the message ...\n");
	while (argc == 1)
	{
		signal(SIGUSR2, get_signal);
		signal(SIGUSR1, get_signal);
	}
	return (0);
}
