/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wu_algo.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaluh <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 18:17:12 by tmaluh            #+#    #+#             */
/*   Updated: 2019/08/24 16:49:50 by tmaluh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WU_ALGO_H
# define WU_ALGO_H

# include <SDL2/SDL.h>
# include "libft_macroses.h"

void	wu_draw_line(__v2df xy0,
					__v2df xy1,
					SDL_Surface *const surf) __nonnull((3));

#endif
