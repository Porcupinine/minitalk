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
#include "printflibft/include/libft.h"

static char	*append_char(char const *s1, char const c)
{
	size_t	counts1;
	char	*join;
	size_t	len;

	counts1 = 0;
	len = ft_strlen(s1) + 1;
	join = malloc((len + 1) * sizeof(char));
	if (join == NULL)
		return (NULL);
	while (s1[counts1] != '\0')
	{
		join[counts1] = s1[counts1];
		counts1++;
	}
	join[counts1] = c;
	counts1++;
	join[counts1] = '\0';
	return (join);

}

static void handler(int signal)
{
	static int bit_walk = 0;
	static int c = 0;
	static char *string = NULL;

	if (string == NULL)
	{
		string = ft_calloc(1, sizeof(char));
		{
			if (string == NULL)
				return;
		}
	}
	if (signal == SIGUSR1)
		c |= (0x01 << bit_walk);
	bit_walk++;
	if (bit_walk == 8)
	{
		if (c == '\0')
		{
			ft_printf("%s", string);
			free(string);
			string = NULL;
			bit_walk = 0;
			c = 0;
		}
		else
		{
			string = append_char(string, c);
			bit_walk = 0;
			c = 0;
		}
	}
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
		pause();
	}
	return (0);
}