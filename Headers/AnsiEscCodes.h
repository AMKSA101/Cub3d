/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AnsiEscCodes.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abamksa <abamksa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 10:46:52 by abamksa           #+#    #+#             */
/*   Updated: 2024/12/18 10:50:16 by abamksa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ANSIESCCODES_H
#define ANSIESCCODES_H

// Reset
#define RESET "\033[0m"

// Text styles
#define STRIKETHROUGH "\033[9m"
#define UNDERLINED "\033[4m"
#define REVERSE "\033[7m"
#define HIDDEN "\033[8m"
#define ITALIC "\033[3m"
#define BLINK "\033[5m"
#define BOLD "\033[1m"
#define DIM "\033[2m"

// Text colors
#define RED "\033[31m"
#define CYAN "\033[36m"
#define BLUE "\033[34m"
#define WHITE "\033[37m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define MAGENTA "\033[35m"

// Background colors
#define MAGENTA_BG "\033[45m"
#define YELLOW_BG "\033[43m"
#define GREEN_BG "\033[42m"
#define WHITE_BG "\033[47m"
#define BLUE_BG "\033[44m"
#define CYAN_BG "\033[46m"
#define RED_BG "\033[41m"

#endif
