/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcapt < wcapt@student.42lausanne.ch >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 14:07:38 by wcapt             #+#    #+#             */
/*   Updated: 2025/02/14 15:24:18 by wcapt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/includes/libft.h"

static char	g_temp[2] = {0, 0};

static void	put_in_string(unsigned char m, char **dest)
{
	char		*new_dest;

	if (m == '\0')
	{
		ft_putstr_fd(*dest, 1);
		ft_putchar_fd('\n', 1);
		free(*dest);
		*dest = NULL;
	}
	else
	{
		g_temp[0] = m;
		if (!*dest)
			*dest = ft_strdup(g_temp);
		else
		{
			new_dest = ft_strjoin(*dest, g_temp);
			free(dest);
			*dest = new_dest;
		}
	}
}

void	get_signal(int signal, siginfo_t *info, void *context)
{
	static int				bit = 0;
	static unsigned char	m = 0;
	pid_t					pid_client;
	static char				*dest;

	(void)context;
	pid_client = info->si_pid;
	m = (m << 1) | (signal == SIGUSR2);
	//if (signal == SIGUSR2)
	//	m |= (1 << (7 - bit));
	bit++;
	if (bit == 8)
	{
		put_in_string(m, &dest);
		if (m == '\0')
		{
			ft_printf("%s\n", dest);
			if (kill(pid_client, SIGUSR2) == -1)
				ft_printf("Error with the confirmation message.\n");
		}
		bit = 0;
		m = 0;
	}
}

int	main(int argc, char **argv)
{
	pid_t				pid;
	struct sigaction	sig;

	pid = getpid();
	(void)argv;
	if (argc != 1)
		return (ft_printf("Too many arguments. Try again !!!\n"), 1);
	ft_printf("PID : %d\n", pid);
	ft_printf("Waiting for the message ...\n");
	sig.sa_flags = SA_SIGINFO;
	sig.sa_sigaction = get_signal;
	sigemptyset(&sig.sa_mask);
	while (argc == 1)
	{
		if (sigaction(SIGUSR2, &sig, NULL) == -1)
			return (ft_printf("Error, failed to get the signal.\n"), 1);
		if (sigaction(SIGUSR1, &sig, NULL) == -1)
			return (ft_printf("Error, failed to get the siganl.\n"), 1);
	}
	return (0);
}
