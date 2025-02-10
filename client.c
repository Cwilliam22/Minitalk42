/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcapt < wcapt@student.42lausanne.ch >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 14:07:20 by wcapt             #+#    #+#             */
/*   Updated: 2025/02/10 14:07:23 by wcapt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "libft/includes/libft.h"


#include <stdio.h>

int pid_control(char *str)
{
    if (!str)
        return (0);
    while (*str)
    {
        if (*str < 48 && *str > 57)
            return(0);
        str++;
    }
    return (1);
}

int get_bits(unsigned char octet, __pid_t pid_serveur)
{
    int i;

    i = 7;
    while (i >= 0)
    {
        if ((octet >> i) & 1)
        {
            if (kill(pid_serveur, SIGUSR2) == -1)
                return (0);
        }
        else
        {
            if(kill(pid_serveur, SIGUSR1) == -1)
                return (0);
        }
        i--;
        usleep(5000);
    }
    return (1);
}

int main(int argc, char **argv)
{
    char    *value;
    __pid_t pid_serveur;

    if (argc != 3)
    {
        printf("The number of argument is incorrect. Try again ! \n");
        return (1);
    }
    else if (!pid_control(argv[1]))
        return (1);
    else
    {
        pid_serveur = ft_atoi(argv[1]);
        if (pid_serveur < 2 || pid_serveur > 4194304)
        {
            printf("The PID is invalid. Try again ! \n");
            return (1);
        }
        value = argv[2];
        while (*value)
        {
            if (!get_bits(*value, pid_serveur))
                return (1);
            value++;
        }
    }
    get_bits('\0', pid_serveur);
    printf("PID valide ! Sending in progress... \n");
    return (0);
}

// Méthode atoi_base
// Méthode bits_shift