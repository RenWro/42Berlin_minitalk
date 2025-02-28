/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwrobles <rwrobles@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 16:11:47 by rwrobles          #+#    #+#             */
/*   Updated: 2025/02/28 16:11:49 by rwrobles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
#include <sys/types.h> 

/* 
 * Function to send a single bit to the server via a signal.
 * It sends SIGUSR1 if the bit is 1 and SIGUSR2 if the bit is 0.
 * The function uses a small delay (usleep) to allow the server to 
 * process the signal.
 */

/*
 * The `pid_t` (Process ID Type) is a data type defined in the POSIX standard 
 *library (`sys/types.h`) that represents a process identifier (Process ID or 
 * simply PID). 
 * It is used to store values that identify processes in the operating system.
 * It is a signed integer type, usually represented as `int`, but the exact 
 *  implementation may vary between operating systems.
 * It is used to identify processes in system calls such as `fork()`, `kill()`, 
 * `wait()`, and `getpid()`.
 */

void	send_bit_to_server(pid_t server_pid, int bit_value)
{
	if (bit_value == 1)
		kill(server_pid, SIGUSR1);
	else
		kill(server_pid, SIGUSR2);
	usleep(42);
}

/* 
 * Function to send the entire message to the server.
 * It sends the message character by character, converting each character to 
 * its binary representation. After sending the message, it sends a final 8 
 * bits (all 0s) to mark the end of the message.
 */

void	send_message_to_server(pid_t server_pid, const char *message)
{
	unsigned char	current_char;
	int				bit_position;

	while (*message != '\0')
	{
		current_char = *message;
		bit_position = 7; 
		while (bit_position >= 0)
		{
			send_bit_to_server(server_pid, (current_char >> bit_position) & 1);
			bit_position--;
		}
		message++;
	}

	bit_position = 7;
	while (bit_position >= 0)
	{
		send_bit_to_server(server_pid, 0);  
		bit_position--;
	}
}

/* 
 * Main function to execute the client.
 * It takes the server PID and the message to be sent as command-line arguments.
 * It then sends the message to the server.
 */
int	main(int argc, char **argv)
{
	pid_t		server_pid;
	const char	*message;

	if (argc != 3)
	{
		ft_putendl_fd("Usage: <server PID> <message>", 1);
		exit(1);
	}

	server_pid = ft_atoi(argv[1]);
	message = argv[2];

	send_message_to_server(server_pid, message);

	return (0);
}
