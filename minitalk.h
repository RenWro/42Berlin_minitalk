/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwrobles <rwrobles@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 15:53:24 by rwrobles          #+#    #+#             */
/*   Updated: 2025/03/02 11:53:39 by rwrobles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <signal.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include "libft/libft.h"

# define BUFFER 90000

/* 
 * Struct to manage dynamic message storage.
 * - `char *msg`: Holds the dynamically allocated message.
 * - `int current_char`: Stores the character being reconstructed from bits.
 */
typedef struct s_message
{
	char	*msg;
	int		current_char;
}	t_message;

#endif

