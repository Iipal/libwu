/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wu_draw_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaluh <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 09:00:31 by tmaluh            #+#    #+#             */
/*   Updated: 2019/11/05 12:41:47 by tmaluh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>

#include "libftsdl.h"

#include "wu_algo.h"
#include "wu_algo_utils.h"

static void
s_draw_line(const bool steep,
			const double_t gradient,
			double_t intery,
			const __v2df pxl1,
			const __v2df pxl2,
			SDL_Surface *restrict surf)
{
	for (size_t i = X(pxl1) + 1; i < X(pxl2) - 1; i++) {
		if (steep) {
			putpxl_plot(u_ipart(intery), i, u_rfpart(intery), surf,
				(Color){0xffffff});
			putpxl_plot(u_ipart(intery) + 1, i, u_fpart(intery), surf,
				(Color){0xffffff});
		} else {
			putpxl_plot(i, u_ipart(intery), u_rfpart(intery), surf,
				(Color){0xffffff});
			putpxl_plot(i, u_ipart(intery) + 1, u_fpart(intery), surf,
				(Color){0xffffff});
		}
		intery += gradient;
	}
}

static __wu_always_inline __v2df
s_calc_endpoint(const __v2df xy,
				const double_t gradient,
				const bool steep,
				SDL_Surface *restrict surf)
{
	const double_t	xgap = u_rfpart(X(xy) + 0.5);
	const __v2df	end = { u_round(X(xy)),
		Y(xy) + gradient * (u_round(X(xy)) - X(xy)) };
	const __v2df	pxl = {X(end), u_ipart(Y(end))};

	if (steep) {
		putpxl_plot(Y(pxl) , X(pxl), u_rfpart(Y(end)) * xgap, surf,
			(Color){0xffffff});
		putpxl_plot(Y(pxl) + 1, X(pxl), u_fpart(Y(end)) * xgap, surf,
			(Color){0xffffff});
	} else {
		putpxl_plot(X(pxl), Y(pxl), u_rfpart(Y(end)) * xgap, surf,
			(Color){0xffffff});
		putpxl_plot(X(pxl), Y(pxl) + 1, u_fpart(Y(end)) * xgap, surf,
			(Color){0xffffff});
	}
	return pxl;
}

void
wu_draw_line(__v2df xy0, __v2df xy1, SDL_Surface *restrict surf)
{
	const bool	steep = fabs(Y(xy1) - Y(xy0)) > fabs(X(xy1) - X(xy0));
	double_t	gradient;

	if (steep) {
		SWAP(X(xy0), Y(xy0));
		SWAP(X(xy1), Y(xy1));
	}
	if (X(xy0) > X(xy1)) {
		SWAP(X(xy0), X(xy1));
		SWAP(Y(xy0), Y(xy1));
	}
	{
		__v2df const	d = {X(xy1) - X(xy0), Y(xy1) - Y(xy0)};
		gradient = Y(d) / X(d);
		if (0.0 == X(d))
			gradient = 1.0;
	}
	s_draw_line(steep, gradient,
		(Y(xy0) + gradient * (u_round(X(xy0)) - X(xy0))) + gradient,
		s_calc_endpoint(xy0, gradient, steep, surf),
		s_calc_endpoint(xy1, gradient, steep, surf), surf);
}
