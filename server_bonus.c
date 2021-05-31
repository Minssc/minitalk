/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsunki <minsunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/29 23:18:04 by minsunki          #+#    #+#             */
/*   Updated: 2021/05/31 15:05:04 by minsunki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server_bonus.h"

static void		sighandl(int sig, siginfo_t *sigi, void *context)
{
	static int	dat;
	static int	bc;

	(void)context;
	if (!sigi->si_pid)
		return ;
	if (kill(sigi->si_pid, sig) != 0)
		return ;
	if (sig == SIGUSR1)
		dat |= (1 << bc);
	if (++bc == 8)
	{
		bc = 0;
		if (dat)
			write(1, &dat, 1);
		else
			write(1, "\n", 1);
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
	t_sigact	sa;
	sigset_t	smask;
	pid_t		pid;

	pid = getpid();
	write(1, "server pid: ", 12);
	putnbr((int)pid);
	write(1, "\n", 1);
	sigemptyset(&smask);
	mset(&sa, sizeof(t_sigact));
	sa.sa_sigaction = &sighandl;
	sa.sa_flags = SA_SIGINFO;
	sigaddset(&smask, SIGUSR1);
	sigaddset(&smask, SIGUSR2);
	sa.sa_mask = smask;
	if (sigaction(SIGUSR1, &sa, NULL) || sigaction(SIGUSR2, &sa, NULL))
	{
		write(1, "sigaction failed\n", 17);
		return (1);
	}
	while (1)
		pause();
	return (0);
}
