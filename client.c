/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   client.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: laura <laura@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/24 13:33:34 by laura         #+#    #+#                 */
/*   Updated: 2023/02/24 13:33:34 by laura         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include "printflibft/include/ft_printf.h"
#include "printflibft/include/libft.h"

void send_char_by_bit(int pid, char c)
{
	int bit_walk;

	bit_walk = 0;
	while (bit_walk < 8)
	{
		if ((c & (0x01 << bit_walk)) != 0)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		usleep(200);
		bit_walk++;
	}
}

int check_argc_argv(int argc, char **argv)
{
	int argv_pid_count;

	argv_pid_count = 0;
	if (argc < 3)
	{
		ft_printf("ERROR! Too few arguments!\n");
		return (1);
	}
	while (argv[1][argv_pid_count])
	{
		if (ft_strchr("0123456789,", argv[1][argv_pid_count]) == 0)
		{
			ft_printf("ERROR! invalid PID format!\n");
			return (1);
		}
		argv_pid_count++;
	}
	if (ft_atoi(argv[1]) == 0)
	{
		ft_printf("ERROR! Invalid PID!\n");
		return (1);
	}
	return (0);
}

int main (int argc, char **argv)
{
	int PID;
	int count;

	count = 0;
	if(check_argc_argv(argc, argv) == 1)
		return (1);
	PID = ft_atoi(argv[1]);
	while (argv[2][count] != '\0')
	{
		send_char_by_bit(PID, argv[2][count]);
		count++;
	}
	return (0);
}