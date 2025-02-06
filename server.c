#include "libft/includes/libft.h"


int main(void)
{
    ft_putstr_fd("The PID is the following : ", 1);
    ft_putnbr_fd(getpid(), 1);
    ft_putchar_fd('\n', 1);
    return (0);
}