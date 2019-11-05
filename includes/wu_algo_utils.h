/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wu_algo_utils.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaluh <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 18:30:41 by tmaluh            #+#    #+#             */
/*   Updated: 2019/11/05 12:42:10 by tmaluh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WU_ALGO_UTILS_H
# define WU_ALGO_UTILS_H

# include <sys/cdefs.h>
# ifndef __wu_always_inline
#  if defined __header_always_inline
#   define __wu_always_inline __header_always_inline
#  elif defined __always_inline
#   define __wu_always_inline __always_inline
#  else
#   define __wu_always_inline
#  endif
# endif

extern __wu_always_inline void
putpxl_plot(const size_t x,
			const size_t y,
			const double_t c,
			SDL_Surface *restrict surf,
			const Color fg_clr)
{
	if (0.0f <= c && 1.0f >= c)
		if (x && y && (size_t)surf->w > x && (size_t)surf->h > y) {
			Uint32 *restrict	pxls = (Uint32 *restrict)surf->pixels;
			Color				orig = { pxls[y * surf->w + x] };
			Color	pxl_clr = sdl_clrs_bright_inc((Color){0x0}, fg_clr, c);

			if (1.0 > c && orig.hex)
				pxl_clr = sdl_clrs_bright_inc(pxl_clr, orig, 1.0f - c);
			pxls[y * surf->w + x] = pxl_clr.hex;
		}
}

static __wu_always_inline double_t
u_ipart(double_t x) { return floor(x); }

static __wu_always_inline double_t
u_round(double_t x) { return u_ipart(x + 0.5f); }

static __wu_always_inline double_t
u_fpart(double_t x) { return x - floor(x); }

static __wu_always_inline double_t
u_rfpart(double_t x) { return 1 - u_fpart(x); }


/*
**	formula for finding the length of the segment in two-dimensional coordinates
**	 A = √(X²+Y²) = √((X2-X1)²+(Y2-Y1)²).
*/
extern __wu_always_inline double_t
u_line_len(const __v2df x1,
			const __v2df x2)
{
	const double_t	x = x2[0] - x1[0];
	const double_t	y = x2[1] - x1[1];

	return sqrt((x * x) + (y * y));
}


#endif
