/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcapt < wcapt@student.42lausanne.ch >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 14:07:38 by wcapt             #+#    #+#             */
/*   Updated: 2025/02/10 15:33:40 by wcapt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/includes/libft.h"

void get_signal(int signal)
{
    static int  bit;
    static int  m;
    
    if (signal == SIGUSR2)
        m |= (1 << bit);
    bit++;
    if (bit == 8)
    {
        ft_putchar_fd(m, 1);
        bit = 0;
        m = 0;

    }

}

int main(int argc, char **argv)
{
    (void)argv;
    ft_putstr_fd("PID : ", 1);
    ft_putnbr_fd(getpid(), 1);
    ft_putchar_fd('\n', 1);
    ft_putstr_fd("Waiting for the message ...", 1);
    ft_putchar_fd('\n', 1);
    while (argc == 1)
    {
        signal(SIGUSR1, get_signal);
        signal(SIGUSR2, get_signal);
        pause();
    }
    return (0);
}
