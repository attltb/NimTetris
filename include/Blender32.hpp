#ifndef _Blender32Header_
#define _Blender32Header_
#include "Bitmap32.hpp"
enum class BlendMode { COPY = 0, COVER, ADD, MULTIPLY };

class Blender {
private:
	static int fastdiv255(int x) {
		return ((x + 1) * 257) >> 16;
	}
	static int limit255(int x) {
		return min(x, 255);
	}
	static Color32 fix_alpha(Color32 color, int alpha_new) {
		return {
				color.blue,
				color.green,
				color.red,
				(uint8_t)alpha_new
		};
	}

public:
	static Color32 blend_copy_fix(Color32 bg, Color32 fg) {
		return fix_alpha(fg, bg.alpha);
	}
	static Color32 blend_copy(Color32 bg, Color32 fg) {
		return fg;
	}
	static Color32 blend_cover_fix(Color32 bg, Color32 fg) {
		int alpha = fg.alpha;
		if (alpha == 0) return bg;
		if (alpha == 255) return {
				fg.blue,
				fg.green,
				fg.red,
				bg.alpha
		};

		int alpha_inv = 255 - alpha;
		return {
			(uint8_t)fastdiv255(fg.blue * alpha + bg.blue * alpha_inv),
			(uint8_t)fastdiv255(fg.green * alpha + bg.green * alpha_inv),
			(uint8_t)fastdiv255(fg.red * alpha + bg.red * alpha_inv),
			bg.alpha
		};
	}
	static Color32 blend_cover(Color32 bg, Color32 fg) {
		int alpha = fg.alpha;
		int alpha_bg = bg.alpha;
		if (alpha == 0) return bg;
		if (alpha == 255) return fg;
		if (alpha_bg == 0) return fg;
		if (alpha_bg == 255) return blend_cover_fix(bg, fg);

		int alpha_inv = 255 - alpha;
		int alpha_inv_bg = 255 - alpha_bg;

		int mul_fg = alpha * 255;
		int mul_bg = alpha_bg * alpha_inv;
		int divider = 255 * 255 - alpha_inv * alpha_inv_bg;
		return {
			(uint8_t)((fg.blue * mul_fg + bg.blue * mul_bg)/ divider),
			(uint8_t)((fg.green * mul_fg + bg.green * mul_bg) / divider),
			(uint8_t)((fg.red * mul_fg + bg.red * mul_bg) / divider),
			(uint8_t)fastdiv255(divider)
		};
	}
	static Color32 blend_add_fix(Color32 bg, Color32 fg) {
		int alpha = fg.alpha;
		if (alpha == 0) return bg;
		if (alpha == 255) return {
			(uint8_t)limit255((bg.blue + fg.blue)),
			(uint8_t)limit255((bg.green + fg.green)),
			(uint8_t)limit255((bg.red + fg.red)),
			bg.alpha
		};

		return {
			(uint8_t)limit255((bg.blue + fastdiv255(fg.blue * alpha))),
			(uint8_t)limit255((bg.green + fastdiv255(fg.green * alpha))),
			(uint8_t)limit255((bg.red + fastdiv255(fg.red * alpha))),
			bg.alpha
		};
	}
	static Color32 blend_add(Color32 bg, Color32 fg) {
		int alpha = fg.alpha;
		int alpha_bg = bg.alpha;
		if (alpha == 0) return bg;
		if (alpha_bg == 0) return fg;
		if (alpha_bg == 255) return blend_add_fix(bg, fg);

		int alpha_inv = 255 - alpha;
		int alpha_inv_bg = 255 - alpha_bg;
		int divider = fastdiv255(255 * 255 - alpha_inv * alpha_inv_bg);
		return {
			(uint8_t)limit255((fg.blue * alpha + bg.blue * alpha_bg) / divider),
			(uint8_t)limit255((fg.green * alpha + bg.green * alpha_bg) / divider),
			(uint8_t)limit255((fg.red * alpha + bg.red * alpha_bg) / divider),
			(uint8_t)divider
		};
	}
	static Color32 blend_mul_fix(Color32 bg, Color32 fg) {
		int alpha = fg.alpha;
		if (alpha == 0) return bg;
		if (alpha == 255) return {
			(uint8_t)fastdiv255(bg.blue * fg.blue),
			(uint8_t)fastdiv255(bg.green * fg.green),
			(uint8_t)fastdiv255(bg.red * fg.red),
			bg.alpha
		};

		int alpha_inv = 255 - alpha;
		return {
			(uint8_t)fastdiv255(fastdiv255(bg.blue * fg.blue * alpha) + bg.blue * alpha_inv),
			(uint8_t)fastdiv255(fastdiv255(bg.green * fg.green * alpha) + bg.green * alpha_inv),
			(uint8_t)fastdiv255(fastdiv255(bg.red * fg.red * alpha) + bg.red * alpha_inv),
			bg.alpha
		};
	}
	static Color32 blend_mul(Color32 bg, Color32 fg) {
		int alpha = fg.alpha;
		int alpha_bg = bg.alpha;
		if (alpha == 0) return bg;
		if (alpha_bg == 0) return fg;
		if (alpha_bg == 255) return blend_mul_fix(bg, fg);

		int alpha_inv = 255 - alpha;
		int alpha_inv_bg = 255 - alpha_bg;

		int mul_fg = alpha * alpha_inv_bg;
		int mul_bg = alpha_bg * alpha_inv;
		int divider = 255 * 255 - alpha_inv * alpha_inv_bg;
		return {
			(uint8_t)((fg.blue * mul_fg + bg.blue * mul_bg + fastdiv255(fg.blue * bg.blue * alpha * alpha_bg)) / divider),
			(uint8_t)((fg.green * mul_fg + bg.green * mul_bg + fastdiv255(fg.blue * bg.blue * alpha * alpha_bg)) / divider),
			(uint8_t)((fg.red * mul_fg + bg.red * mul_bg + fastdiv255(fg.blue * bg.blue * alpha * alpha_bg)) / divider),
			(uint8_t)fastdiv255(divider)
		};
	}

public:
	static Color32 blend_copy_fix(Color32 bg, Color32 fg, int opa256) {
		if (opa256 == 0) return bg;
		int opa256_inv = 256 - opa256;
		return {
			(uint8_t)(((fg.blue * opa256) + (bg.blue * opa256_inv)) / 256),
			(uint8_t)(((fg.green * opa256) + (bg.green * opa256_inv)) / 256),
			(uint8_t)(((fg.red * opa256) + (bg.red * opa256_inv)) / 256),
			bg.alpha,
		};
	}
	static Color32 blend_copy(Color32 bg, Color32 fg, int opa256) {
		if (opa256 == 0) return bg;
		int opa256_inv = 256 - opa256;
		return {
			(uint8_t)(((fg.blue * opa256) + (bg.blue * opa256_inv)) / 256),
			(uint8_t)(((fg.green * opa256) + (bg.green * opa256_inv)) / 256),
			(uint8_t)(((fg.red * opa256) + (bg.red * opa256_inv)) / 256),
			(uint8_t)(((fg.alpha * opa256) + (bg.alpha * opa256_inv)) / 256),
		};
	}
	static Color32 blend_cover_fix(Color32 bg, Color32 fg, int opa256) {
		int alpha = (fg.alpha * opa256) / 256;
		if (alpha == 0) return bg;

		int alpha_inv = 255 - alpha;
		return {
			(uint8_t)fastdiv255(fg.blue * alpha + bg.blue * alpha_inv),
			(uint8_t)fastdiv255(fg.green * alpha + bg.green * alpha_inv),
			(uint8_t)fastdiv255(fg.red * alpha + bg.red * alpha_inv),
			bg.alpha
		};
	}
	static Color32 blend_cover(Color32 bg, Color32 fg, int opa256) {
		int alpha = (fg.alpha * opa256) / 256;
		int alpha_bg = bg.alpha;
		if (alpha == 0) return bg;
		if (alpha_bg == 0) return fix_alpha(fg, alpha);
		if (alpha == 255) return fg;
		if (alpha_bg == 255) return blend_cover_fix(bg, fg, opa256);

		int alpha_inv = 255 - alpha;
		int alpha_inv_bg = 255 - alpha_bg;

		int mul_fg = alpha * 255;
		int mul_bg = alpha_bg * alpha_inv;
		int divider = 255 * 255 - alpha_inv * alpha_inv_bg;
		return {
			(uint8_t)((fg.blue * mul_fg + bg.blue * mul_bg) / divider),
			(uint8_t)((fg.green * mul_fg + bg.green * mul_bg) / divider),
			(uint8_t)((fg.red * mul_fg + bg.red * mul_bg) / divider),
			(uint8_t)fastdiv255(divider)
		};
	}
	static Color32 blend_add_fix(Color32 bg, Color32 fg, int opa256) {
		int alpha = (fg.alpha * opa256) / 256;
		if (alpha == 0) return bg;

		return {
			(uint8_t)limit255((bg.blue + fastdiv255(fg.blue * alpha))),
			(uint8_t)limit255((bg.green + fastdiv255(fg.green * alpha))),
			(uint8_t)limit255((bg.red + fastdiv255(fg.red * alpha))),
			bg.alpha
		};
	}
	static Color32 blend_add(Color32 bg, Color32 fg, int opa256) {
		int alpha = (fg.alpha * opa256) / 256;
		int alpha_bg = bg.alpha;
		if (alpha == 0) return bg;
		if (alpha == 255) return {
			(uint8_t)limit255(fastdiv255(fg.blue * 255 + bg.blue * alpha_bg)),
			(uint8_t)limit255(fastdiv255(fg.green * 255 + bg.green * alpha_bg)),
			(uint8_t)limit255(fastdiv255(fg.red * 255 + bg.red * alpha_bg)),
			(uint8_t)255
		};
		if (alpha_bg == 0) return fix_alpha(fg, alpha);
		if (alpha_bg == 255) return blend_add_fix(bg, fg, opa256);

		int alpha_inv = 255 - alpha;
		int alpha_inv_bg = 255 - alpha_bg;
		int divider = fastdiv255(255 * 255 - alpha_inv * alpha_inv_bg);
		return {
			(uint8_t)limit255((fg.blue * alpha + bg.blue * alpha_bg) / divider),
			(uint8_t)limit255((fg.green * alpha + bg.green * alpha_bg) / divider),
			(uint8_t)limit255((fg.red * alpha + bg.red * alpha_bg) / divider),
			(uint8_t)divider
		};
	}
	static Color32 blend_mul_fix(Color32 bg, Color32 fg, int opa256) {
		int alpha = (fg.alpha * opa256) / 256;
		if (alpha == 0) return bg;

		int alpha_inv = 255 - alpha;
		return {
			(uint8_t)fastdiv255(fastdiv255(bg.blue * fg.blue * alpha) + bg.blue * alpha_inv),
			(uint8_t)fastdiv255(fastdiv255(bg.green * fg.green * alpha) + bg.green * alpha_inv),
			(uint8_t)fastdiv255(fastdiv255(bg.red * fg.red * alpha) + bg.red * alpha_inv),
			bg.alpha
		};
	}
	static Color32 blend_mul(Color32 bg, Color32 fg, int opa256) {
		int alpha = (fg.alpha * opa256) / 256;
		int alpha_bg = bg.alpha;
		if (alpha == 0) return bg;
		if (alpha == 255) {
			int alpha_inv_bg = 255 - alpha_bg;
			return {
				(uint8_t)(fastdiv255(fg.blue * alpha_inv_bg + fastdiv255(fg.blue * bg.blue * alpha_bg))),
				(uint8_t)(fastdiv255(fg.green * alpha_inv_bg + fastdiv255(fg.blue * bg.blue * alpha_bg))),
				(uint8_t)(fastdiv255(fg.red * alpha_inv_bg + fastdiv255(fg.blue * bg.blue * alpha_bg))),
				(uint8_t)255
			};
		}
		if (alpha_bg == 0) return fix_alpha(fg, alpha);
		if (alpha_bg == 255) return blend_mul_fix(bg, fg, opa256);

		int alpha_inv = 255 - alpha;
		int alpha_inv_bg = 255 - alpha_bg;

		int mul_fg = alpha * alpha_inv_bg;
		int mul_bg = alpha_bg * alpha_inv;
		int divider = 255 * 255 - alpha_inv * alpha_inv_bg;
		return {
			(uint8_t)((fg.blue * mul_fg + bg.blue * mul_bg + fastdiv255(fg.blue * bg.blue * alpha * alpha_bg)) / divider),
			(uint8_t)((fg.green * mul_fg + bg.green * mul_bg + fastdiv255(fg.blue * bg.blue * alpha * alpha_bg)) / divider),
			(uint8_t)((fg.red * mul_fg + bg.red * mul_bg + fastdiv255(fg.blue * bg.blue * alpha * alpha_bg)) / divider),
			(uint8_t)fastdiv255(divider)
		};
	}
};
#endif