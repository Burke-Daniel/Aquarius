#include <cstdint>

#include "Window.h"

namespace Aquarius {
	namespace Input {


		enum class KeyState : int
		{
			Released = 0,
			Pressed = 1
		};

		using MouseButtonState = KeyState;

		enum class KeyCode : int
		{
			// From glfw3.h
			Key_unknown = -1,
			Key_space = 32,
			Key_apostrophe = 39 /* ' */,
			Key_comma = 44 /* , */,
			Key_minus = 45 /* - */,
			Key_period = 46 /* . */,
			Key_slash = 47 /* / */,
			Key_0 = 48,
			Key_1 = 49,
			Key_2 = 50,
			Key_3 = 51,
			Key_4 = 52,
			Key_5 = 53,
			Key_6 = 54,
			Key_7 = 55,
			Key_8 = 56,
			Key_9 = 57,
			Key_semicolon = 59 /* ; */,
			Key_equal = 61 /* = */,
			Key_a = 65,
			Key_b = 66,
			Key_c = 67,
			Key_d = 68,
			Key_e = 69,
			Key_f = 70,
			Key_g = 71,
			Key_h = 72,
			Key_i = 73,
			Key_j = 74,
			Key_k = 75,
			Key_l = 76,
			Key_m = 77,
			Key_n = 78,
			Key_o = 79,
			Key_p = 80,
			Key_q = 81,
			Key_r = 82,
			Key_s = 83,
			Key_t = 84,
			Key_u = 85,
			Key_v = 86,
			Key_w = 87,
			Key_x = 88,
			Key_y = 89,
			Key_z = 90,
			Key_left_bracket = 91 /* [ */,
			Key_backslash = 92 /* \ */,
			Key_right_bracket = 93 /* ] */,
			Key_grave_accent = 96 /* ` */,
			Key_world_1 = 161 /* non-us #1 */,
			Key_world_2 = 162 /* non-us #2 */,
			Key_escape = 256,
			Key_enter = 257,
			Key_tab = 258,
			Key_backspace = 259,
			Key_insert = 260,
			Key_delete = 261,
			Key_right = 262,
			Key_left = 263,
			Key_down = 264,
			Key_up = 265,
			Key_page_up = 266,
			Key_page_down = 267,
			Key_home = 268,
			Key_end = 269,
			Key_caps_lock = 280,
			Key_scroll_lock = 281,
			Key_num_lock = 282,
			Key_print_screen = 283,
			Key_pause = 284,
			Key_f1 = 290,
			Key_f2 = 291,
			Key_f3 = 292,
			Key_f4 = 293,
			Key_f5 = 294,
			Key_f6 = 295,
			Key_f7 = 296,
			Key_f8 = 297,
			Key_f9 = 298,
			Key_f10 = 299,
			Key_f11 = 300,
			Key_f12 = 301,
			Key_f13 = 302,
			Key_f14 = 303,
			Key_f15 = 304,
			Key_f16 = 305,
			Key_f17 = 306,
			Key_f18 = 307,
			Key_f19 = 308,
			Key_f20 = 309,
			Key_f21 = 310,
			Key_f22 = 311,
			Key_f23 = 312,
			Key_f24 = 313,
			Key_f25 = 314,
			Key_kp_0 = 320,
			Key_kp_1 = 321,
			Key_kp_2 = 322,
			Key_kp_3 = 323,
			Key_kp_4 = 324,
			Key_kp_5 = 325,
			Key_kp_6 = 326,
			Key_kp_7 = 327,
			Key_kp_8 = 328,
			Key_kp_9 = 329,
			Key_kp_decimal = 330,
			Key_kp_divide = 331,
			Key_kp_multiply = 332,
			Key_kp_subtract = 333,
			Key_kp_add = 334,
			Key_kp_enter = 335,
			Key_kp_equal = 336,
			Key_left_shift = 340,
			Key_left_control = 341,
			Key_left_alt = 342,
			Key_left_super = 343,
			Key_right_shift = 344,
			Key_right_control = 345,
			Key_right_alt = 346,
			Key_right_super = 347,
			Key_menu = 348
		};

		enum class MouseButtonCode : int
		{
			Mouse_button_1 = 0,
			Mouse_button_2 = 1,
			Mouse_button_3 = 2,
			Mouse_button_4 = 3,
			Mouse_button_5 = 4,
			Mouse_button_6 = 5,
			Mouse_button_7 = 6,
			Mouse_button_8 = 7,
			Mouse_button_last = Mouse_button_8,
			Mouse_button_left = Mouse_button_1,
			Mouse_button_right = Mouse_button_2,
			Mouse_button_middle = Mouse_button_3
		};

		struct MousePosition
		{
			double x;
			double y;
		};

		KeyState getKeyState(KeyCode key);
		MouseButtonState getMouseButtonState(MouseButtonCode button);
		bool isKeyPressed(KeyCode key);
		bool isMouseButtonPressed(MouseButtonCode button);
		MousePosition getMousePosition();
	} // namespace Input
} // namespace Aquarius
