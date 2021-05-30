/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsunki <minsunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/29 23:18:04 by minsunki          #+#    #+#             */
/*   Updated: 2021/05/30 13:36:54 by minsunki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

static void		sigh(int sig, siginfo_t *sigi, void *context)
{
	static int	bits;
	static int	dat;

	(void)context;
	if (sig == SIGUSR1)
		dat |= (1 << bits);
	if (++bits == 8)
	{
		bits = 0;
		if (!dat)
			kill(sigi->si_pid, SIGUSR2);
		else
			write(1, &dat, 1);
		dat = 0;
	}
}

static void		mset(void *p, int n)
{
	char		*mp;

	mp = (char *)p;
	while (n--)
		*mp++ = 0;
}

static void		putnbr(int n)
{
	char		c;

	c = n % 10 + '0';
	if (n >= 10)
		putnbr(n / 10);
	write(1, &c, 1);
}

int				main(void)
{
	t_sigact	sa_one;
	t_sigact	sa_two;
	pid_t		pid;

	pid = getpid();
	write(1, "server pid: ", 12);
	putnbr((int)pid);
	write(1, "\n", 1);
	mset(&sa_one, sizeof(t_sigact));
	mset(&sa_two, sizeof(t_sigact));
	sa_one.sa_sigaction = &sigh;
	sa_one.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &sa_one, NULL);
	sa_two.sa_sigaction = &sigh;
	sa_two.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR2, &sa_two, NULL);
	while (1)
		;
	return (0);
}
