/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   server.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: laura <laura@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/24 11:23:41 by laura         #+#    #+#                 */
/*   Updated: 2023/02/24 11:23:41 by laura         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include "printflibft/include/ft_printf.h"
#include <unistd.h>

void handler(int signal)
{
	static int bit_size;
	static int c;

	bit_size = 0;
	while (bit_size < 8)
	{
		if (signal == SIGUSR1)
			c |= (0x01 << bit_size);
		bit_size++;
	}
	ft_printf("%c", c);
	bit_size = 0;
	c = 0;
}

int main (void)
{
	int PID;

	PID = (int)getpid();
	ft_printf("%d\n", PID);
	while (1)
	{
		signal(SIGUSR1, handler);
		signal(SIGUSR2, handler);
	}
}