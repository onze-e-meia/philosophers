/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 17:28:26 by tforster          #+#    #+#             */
/*   Updated: 2024/06/28 17:57:21 by tforster         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	if (argc < 5)
		return (printf("To few arguments, need 4 or 5 (int)!\n"));
	else if (argc > 6)
		return (printf("To many arguments, need 4 or 5 (int)!\n"));

	if (!argv)
		return (1);
	return (0);
}
