#define DQNT_IMPLEMENTATION
#include "dqnt.h"

#include "stdio.h"

void dqnt_strings_test()
{
	{ // Char Checks
		DQNT_ASSERT(dqnt_char_is_alpha('a') == true);
		DQNT_ASSERT(dqnt_char_is_alpha('A') == true);
		DQNT_ASSERT(dqnt_char_is_alpha('0') == false);
		DQNT_ASSERT(dqnt_char_is_alpha('@') == false);
		DQNT_ASSERT(dqnt_char_is_alpha(' ') == false);
		DQNT_ASSERT(dqnt_char_is_alpha('\n') == false);

		DQNT_ASSERT(dqnt_char_is_digit('1') == true);
		DQNT_ASSERT(dqnt_char_is_digit('n') == false);
		DQNT_ASSERT(dqnt_char_is_digit('N') == false);
		DQNT_ASSERT(dqnt_char_is_digit('*') == false);
		DQNT_ASSERT(dqnt_char_is_digit(' ') == false);
		DQNT_ASSERT(dqnt_char_is_digit('\n') == false);

		DQNT_ASSERT(dqnt_char_is_alphanum('1') == true);
		DQNT_ASSERT(dqnt_char_is_alphanum('a') == true);
		DQNT_ASSERT(dqnt_char_is_alphanum('A') == true);
		DQNT_ASSERT(dqnt_char_is_alphanum('*') == false);
		DQNT_ASSERT(dqnt_char_is_alphanum(' ') == false);
		DQNT_ASSERT(dqnt_char_is_alphanum('\n') == false);

		printf("dqnt_strings_test(): char_checks: Completed successfully\n");
	}

	// String Checks
	{
		// strcmp
		{
			char *a = "str_a";

			// Check simple compares
			{
				DQNT_ASSERT(dqnt_strcmp(a, "str_a") == +0);
				DQNT_ASSERT(dqnt_strcmp(a, "str_b") == -1);
				DQNT_ASSERT(dqnt_strcmp("str_b", a) == +1);
				DQNT_ASSERT(dqnt_strcmp(a, "") == +1);
				DQNT_ASSERT(dqnt_strcmp("", "") == 0);

				// NOTE: Check that the string has not been trashed.
				DQNT_ASSERT(dqnt_strcmp(a, "str_a") == +0);
			}

			// Check ops against null
			{
				DQNT_ASSERT(dqnt_strcmp(NULL, NULL) != +0);
				DQNT_ASSERT(dqnt_strcmp(a, NULL) != +0);
				DQNT_ASSERT(dqnt_strcmp(NULL, a) != +0);
			}

			printf("dqnt_strings_test(): strcmp: Completed successfully\n");
		}

		// strlen
		{
			char *a = "str_a";
			DQNT_ASSERT(dqnt_strlen(a) == 5);
			DQNT_ASSERT(dqnt_strlen("") == 0);
			DQNT_ASSERT(dqnt_strlen("   a  ") == 6);
			DQNT_ASSERT(dqnt_strlen("a\n") == 2);

			// NOTE: Check that the string has not been trashed.
			DQNT_ASSERT(dqnt_strcmp(a, "str_a") == 0);

			DQNT_ASSERT(dqnt_strlen(NULL) == 0);

			printf("dqnt_strings_test(): strlen: Completed successfully\n");
		}

		// strncpy
		{
			{
				char *a    = "str_a";
				char b[10] = {};
				// Check copy into empty array
				{
					char *result = dqnt_strncpy(b, a, dqnt_strlen(a));
					DQNT_ASSERT(dqnt_strcmp(b, "str_a") == 0);
					DQNT_ASSERT(dqnt_strcmp(a, "str_a") == 0);
					DQNT_ASSERT(dqnt_strcmp(result, "str_a") == 0);
					DQNT_ASSERT(dqnt_strlen(result) == 5);
				}

				// Check copy into array offset, overlap with old results
				{
					char *newResult = dqnt_strncpy(&b[1], a, dqnt_strlen(a));
					DQNT_ASSERT(dqnt_strcmp(newResult, "str_a") == 0);
					DQNT_ASSERT(dqnt_strlen(newResult) == 5);

					DQNT_ASSERT(dqnt_strcmp(a, "str_a") == 0);
					DQNT_ASSERT(dqnt_strlen(a) == 5);

					DQNT_ASSERT(dqnt_strcmp(b, "sstr_a") == 0);
					DQNT_ASSERT(dqnt_strlen(b) == 6);
				}
			}

			// Check strncpy with NULL pointers
			{
				DQNT_ASSERT(dqnt_strncpy(NULL, NULL, 5) == NULL);

				char *a      = "str";
				char *result = dqnt_strncpy(a, NULL, 5);

				DQNT_ASSERT(dqnt_strcmp(a, "str") == 0);
				DQNT_ASSERT(dqnt_strcmp(result, "str") == 0);
				DQNT_ASSERT(dqnt_strcmp(result, a) == 0);
			}

			// Check strncpy with 0 chars to copy
			{
				char *a = "str";
				char *b = "ing";

				char *result = dqnt_strncpy(a, b, 0);
				DQNT_ASSERT(dqnt_strcmp(a, "str") == 0);
				DQNT_ASSERT(dqnt_strcmp(b, "ing") == 0);
				DQNT_ASSERT(dqnt_strcmp(result, "str") == 0);
			}

			printf("dqnt_strings_test(): strncpy: Completed successfully\n");
		}

		// str_reverse
		{
			// Basic reverse operations
			{
				char a[] = "aba";
				DQNT_ASSERT(dqnt_str_reverse(a, dqnt_strlen(a)) == true);
				DQNT_ASSERT(dqnt_strcmp(a, "aba") == 0);

				DQNT_ASSERT(dqnt_str_reverse(a, 2) == true);
				DQNT_ASSERT(dqnt_strcmp(a, "baa") == 0);

				DQNT_ASSERT(dqnt_str_reverse(a, dqnt_strlen(a)) == true);
				DQNT_ASSERT(dqnt_strcmp(a, "aab") == 0);

				DQNT_ASSERT(dqnt_str_reverse(&a[1], 2) == true);
				DQNT_ASSERT(dqnt_strcmp(a, "aba") == 0);

				DQNT_ASSERT(dqnt_str_reverse(a, 0) == true);
				DQNT_ASSERT(dqnt_strcmp(a, "aba") == 0);
			}

			// Try reverse empty string
			{
				char a[] = "";
				DQNT_ASSERT(dqnt_str_reverse(a, dqnt_strlen(a)) == true);
				DQNT_ASSERT(dqnt_strcmp(a, "") == 0);
			}

			// Try reverse single char string
			{
				char a[] = "a";
				DQNT_ASSERT(dqnt_str_reverse(a, dqnt_strlen(a)) == true);
				DQNT_ASSERT(dqnt_strcmp(a, "a") == 0);

				DQNT_ASSERT(dqnt_str_reverse(a, 0) == true);
				DQNT_ASSERT(dqnt_strcmp(a, "a") == 0);
			}

			printf(
			    "dqnt_strings_test(): str_reverse: Completed successfully\n");
		}

		// str_to_i32
		{
			char *a = "123";
			DQNT_ASSERT(dqnt_str_to_i32(a, dqnt_strlen(a)) == 123);

			char *b = "-123";
			DQNT_ASSERT(dqnt_str_to_i32(b, dqnt_strlen(b)) == -123);
			DQNT_ASSERT(dqnt_str_to_i32(b, 1) == 0);
			DQNT_ASSERT(dqnt_str_to_i32(&b[1], dqnt_strlen(&b[1])) == 123);

			char *c = "-0";
			DQNT_ASSERT(dqnt_str_to_i32(c, dqnt_strlen(c)) == 0);

			char *d = "+123";
			DQNT_ASSERT(dqnt_str_to_i32(d, dqnt_strlen(d)) == 123);
			DQNT_ASSERT(dqnt_str_to_i32(&d[1], dqnt_strlen(&d[1])) == 123);

			printf("dqnt_strings_test(): str_to_i32: Completed successfully\n");
		}

		// i32_to_str
		{
			char a[DQNT_I32_TO_STR_MAX_BUF_SIZE] = {};
			dqnt_i32_to_str(+100, a, DQNT_ARRAY_COUNT(a));
			DQNT_ASSERT(dqnt_strcmp(a, "100") == 0);

			char b[DQNT_I32_TO_STR_MAX_BUF_SIZE] = {};
			dqnt_i32_to_str(-100, b, DQNT_ARRAY_COUNT(b));
			DQNT_ASSERT(dqnt_strcmp(b, "-100") == 0);

			char c[DQNT_I32_TO_STR_MAX_BUF_SIZE] = {};
			dqnt_i32_to_str(0, c, DQNT_ARRAY_COUNT(c));
			DQNT_ASSERT(dqnt_strcmp(c, "0") == 0);

			printf("dqnt_strings_test(): str_to_i32: Completed successfully\n");
		}
	}

    // UCS <-> UTF8 Checks
    {
	    // Test ascii characters
	    {
		    u32 codepoint = '@';
		    u32 string[1] = {};

		    u32 bytesUsed = dqnt_ucs_to_utf8(&string[0], codepoint);
		    DQNT_ASSERT(bytesUsed == 1);
		    DQNT_ASSERT(string[0] == '@');

		    bytesUsed = dqnt_utf8_to_ucs(&string[0], codepoint);
		    DQNT_ASSERT(string[0] >= 0 && string[0] < 0x80);
		    DQNT_ASSERT(bytesUsed == 1);
	    }

	    // Test 2 byte characters
		{
		    u32 codepoint = 0x278;
		    u32 string[1] = {};

		    u32 bytesUsed = dqnt_ucs_to_utf8(&string[0], codepoint);
		    DQNT_ASSERT(bytesUsed == 2);
		    DQNT_ASSERT(string[0] == 0xC9B8);

		    bytesUsed = dqnt_utf8_to_ucs(&string[0], string[0]);
		    DQNT_ASSERT(string[0] == codepoint);
		    DQNT_ASSERT(bytesUsed == 2);
	    }

	    // Test 3 byte characters
		{
		    u32 codepoint = 0x0A0A;
		    u32 string[1] = {};

			u32 bytesUsed = dqnt_ucs_to_utf8(&string[0], codepoint);
		    DQNT_ASSERT(bytesUsed == 3);
			DQNT_ASSERT(string[0] == 0xE0A88A);

		    bytesUsed = dqnt_utf8_to_ucs(&string[0], string[0]);
		    DQNT_ASSERT(string[0] == codepoint);
		    DQNT_ASSERT(bytesUsed == 3);
	    }

	    // Test 4 byte characters
		{
		    u32 codepoint = 0x10912;
		    u32 string[1] = {};
			u32 bytesUsed = dqnt_ucs_to_utf8(&string[0], codepoint);

		    DQNT_ASSERT(bytesUsed == 4);
		    DQNT_ASSERT(string[0] == 0xF090A492);

		    bytesUsed = dqnt_utf8_to_ucs(&string[0], string[0]);
		    DQNT_ASSERT(string[0] == codepoint);
		    DQNT_ASSERT(bytesUsed == 4);
	    }

		{
		    u32 codepoint = 0x10912;
			u32 bytesUsed = dqnt_ucs_to_utf8(NULL, codepoint);
		    DQNT_ASSERT(bytesUsed == 0);

		    bytesUsed = dqnt_utf8_to_ucs(NULL, codepoint);
		    DQNT_ASSERT(bytesUsed == 0);
	    }

	    printf("dqnt_strings_test(): ucs <-> utf8: Completed successfully\n");
    }

    printf("dqnt_strings_test(): Completed successfully\n");
}

#include "Windows.h"
#define WIN32_LEAN_AND_MEAN
void dqnt_other_test()
{
	{ // Test Win32 Sleep
		// NOTE: Win32 Sleep is not granular to a certain point so sleep excessively
		u32 sleepInMs = 1000;
		f64 startInMs = dqnt_time_now_in_ms();
		Sleep(sleepInMs);
		f64 endInMs = dqnt_time_now_in_ms();

		DQNT_ASSERT(startInMs < endInMs);
		printf("dqnt_other_test(): time_now: Completed successfully\n");
	}
	printf("dqnt_other_test(): Completed successfully\n");
}

void dqnt_random_test() {

	DqntRandPCGState pcg;
	dqnt_rnd_pcg_init(&pcg);
	for (i32 i = 0; i < 10; i++)
	{
		i32 min    = -100;
		i32 max    = 100000;
		i32 result = dqnt_rnd_pcg_range(&pcg, min, max);
		DQNT_ASSERT(result >= min && result <= max)

		f32 randF32 = dqnt_rnd_pcg_nextf(&pcg);
		DQNT_ASSERT(randF32 >= 0.0f && randF32 <= 1.0f);
		printf("dqnt_random_test(): rnd_pcg: Completed successfully\n");
	}

	printf("dqnt_random_test(): Completed successfully\n");
}

void dqnt_math_test()
{
	{ // Lerp
		{
			f32 start = 10;
			f32 t     = 0.5f;
			f32 end   = 20;
			DQNT_ASSERT(dqnt_math_lerp(start, t, end) == 15);
		}

		{
			f32 start = 10;
			f32 t     = 2.0f;
			f32 end   = 20;
			DQNT_ASSERT(dqnt_math_lerp(start, t, end) == 30);
		}

		printf("dqnt_math_test(): lerp: Completed successfully\n");
	}

	{ // sqrtf
		DQNT_ASSERT(dqnt_math_sqrtf(4.0f) == 2.0f);
		printf("dqnt_math_test(): sqrtf: Completed successfully\n");
	}

	printf("dqnt_math_test(): Completed successfully\n");
}

void dqnt_vec_test()
{
	{ // V2

		// V2 Creating
		{
			DqntV2 vec = dqnt_v2(5.5f, 5.0f);
			DQNT_ASSERT(vec.x == 5.5f && vec.y == 5.0f);
			DQNT_ASSERT(vec.w == 5.5f && vec.h == 5.0f);
		}

		// V2i Creating
		{
			DqntV2 vec = dqnt_v2i(3, 5);
			DQNT_ASSERT(vec.x == 3 && vec.y == 5.0f);
			DQNT_ASSERT(vec.w == 3 && vec.h == 5.0f);
		}

		// V2 Arithmetic
		{
			DqntV2 vecA = dqnt_v2(5, 10);
			DqntV2 vecB = dqnt_v2i(2, 3);
			DQNT_ASSERT(dqnt_v2_equals(vecA, vecB) == false);
			DQNT_ASSERT(dqnt_v2_equals(vecA, dqnt_v2(5, 10)) == true);
			DQNT_ASSERT(dqnt_v2_equals(vecB, dqnt_v2(2, 3)) == true);

			DqntV2 result = dqnt_v2_add(vecA, dqnt_v2(5, 10));
			DQNT_ASSERT(dqnt_v2_equals(result, dqnt_v2(10, 20)) == true);

			result = dqnt_v2_sub(result, dqnt_v2(5, 10));
			DQNT_ASSERT(dqnt_v2_equals(result, dqnt_v2(5, 10)) == true);

			result = dqnt_v2_scale(result, 5);
			DQNT_ASSERT(dqnt_v2_equals(result, dqnt_v2(25, 50)) == true);

			result = dqnt_v2_hadamard(result, dqnt_v2(10, 0.5f));
			DQNT_ASSERT(dqnt_v2_equals(result, dqnt_v2(250, 25)) == true);

			f32 dotResult = dqnt_v2_dot(dqnt_v2(5, 10), dqnt_v2(3, 4));
			DQNT_ASSERT(dotResult == 55);
		}

		// V2 Properties
		{
			DqntV2 a = dqnt_v2(0, 0);
			DqntV2 b = dqnt_v2(3, 4);

			f32 lengthSq = dqnt_v2_length_squared(a, b);
			DQNT_ASSERT(lengthSq == 25);

			f32 length = dqnt_v2_length(a, b);
			DQNT_ASSERT(length == 5);

			DqntV2 normalised = dqnt_v2_normalise(b);
			DQNT_ASSERT(normalised.x == (b.x / 5.0f));
			DQNT_ASSERT(normalised.y == (b.y / 5.0f));

			DqntV2 c = dqnt_v2(3.5f, 8.0f);
			DQNT_ASSERT(dqnt_v2_overlaps(b, c) == true);
			DQNT_ASSERT(dqnt_v2_overlaps(b, a) == false);

			DqntV2 d = dqnt_v2_perpendicular(c);
			DQNT_ASSERT(dqnt_v2_dot(c, d) == 0);
		}

		{ // constrain_to_ratio
			DqntV2 ratio  = dqnt_v2(16, 9);
			DqntV2 dim    = dqnt_v2(2000, 1080);
			DqntV2 result = dqnt_v2_constrain_to_ratio(dim, ratio);
			DQNT_ASSERT(result.w == 1920 && result.h == 1080);
		}

		printf("dqnt_vec_test(): vec2: Completed successfully\n");
	}

	{ // V3

		// V3i Creating
		{
			DqntV3 vec = dqnt_v3(5.5f, 5.0f, 5.875f);
			DQNT_ASSERT(vec.x == 5.5f && vec.y == 5.0f && vec.z == 5.875f);
			DQNT_ASSERT(vec.r == 5.5f && vec.g == 5.0f && vec.b == 5.875f);
		}

		// V3i Creating
		{
			DqntV3 vec = dqnt_v3i(3, 4, 5);
			DQNT_ASSERT(vec.x == 3 && vec.y == 4 && vec.z == 5);
			DQNT_ASSERT(vec.r == 3 && vec.g == 4 && vec.b == 5);
		}

		// V3 Arithmetic
		{
			DqntV3 vecA = dqnt_v3(5, 10, 15);
			DqntV3 vecB = dqnt_v3(2, 3, 6);
			DQNT_ASSERT(dqnt_v3_equals(vecA, vecB) == false);
			DQNT_ASSERT(dqnt_v3_equals(vecA, dqnt_v3(5, 10, 15)) == true);
			DQNT_ASSERT(dqnt_v3_equals(vecB, dqnt_v3(2, 3, 6)) == true);

			DqntV3 result = dqnt_v3_add(vecA, dqnt_v3(5, 10, 15));
			DQNT_ASSERT(dqnt_v3_equals(result, dqnt_v3(10, 20, 30)) == true);

			result = dqnt_v3_sub(result, dqnt_v3(5, 10, 15));
			DQNT_ASSERT(dqnt_v3_equals(result, dqnt_v3(5, 10, 15)) == true);

			result = dqnt_v3_scale(result, 5);
			DQNT_ASSERT(dqnt_v3_equals(result, dqnt_v3(25, 50, 75)) == true);

			result = dqnt_v3_hadamard(result, dqnt_v3(10.0f, 0.5f, 10.0f));
			DQNT_ASSERT(dqnt_v3_equals(result, dqnt_v3(250, 25, 750)) == true);

			f32 dotResult = dqnt_v3_dot(dqnt_v3(5, 10, 2), dqnt_v3(3, 4, 6));
			DQNT_ASSERT(dotResult == 67);

			DqntV3 cross = dqnt_v3_cross(vecA, vecB);
			DQNT_ASSERT(dqnt_v3_equals(cross, dqnt_v3(15, 0, -5)) == true);
		}

		printf("dqnt_vec_test(): vec3: Completed successfully\n");
	}

	{ // V4

		// V4 Creating
		{
			DqntV4 vec = dqnt_v4(5.5f, 5.0f, 5.875f, 5.928f);
			DQNT_ASSERT(vec.x == 5.5f && vec.y == 5.0f && vec.z == 5.875f && vec.w == 5.928f);
			DQNT_ASSERT(vec.r == 5.5f && vec.g == 5.0f && vec.b == 5.875f && vec.a == 5.928f);
		}

		// V4i Creating
		{
			DqntV4 vec = dqnt_v4i(3, 4, 5, 6);
		    DQNT_ASSERT(vec.x == 3 && vec.y == 4 && vec.z == 5 && vec.w == 6);
		    DQNT_ASSERT(vec.r == 3 && vec.g == 4 && vec.b == 5 && vec.a == 6);
	    }

		// V4 Arithmetic
		{
			DqntV4 vecA = dqnt_v4(5, 10, 15, 20);
			DqntV4 vecB = dqnt_v4i(2, 3, 6, 8);
			DQNT_ASSERT(dqnt_v4_equals(vecA, vecB) == false);
			DQNT_ASSERT(dqnt_v4_equals(vecA, dqnt_v4(5, 10, 15, 20)) == true);
			DQNT_ASSERT(dqnt_v4_equals(vecB, dqnt_v4(2, 3, 6, 8)) == true);

			DqntV4 result = dqnt_v4_add(vecA, dqnt_v4(5, 10, 15, 20));
			DQNT_ASSERT(dqnt_v4_equals(result, dqnt_v4(10, 20, 30, 40)) == true);

			result = dqnt_v4_sub(result, dqnt_v4(5, 10, 15, 20));
			DQNT_ASSERT(dqnt_v4_equals(result, dqnt_v4(5, 10, 15, 20)) == true);

			result = dqnt_v4_scale(result, 5);
			DQNT_ASSERT(dqnt_v4_equals(result, dqnt_v4(25, 50, 75, 100)) == true);

			result = dqnt_v4_hadamard(result, dqnt_v4(10, 0.5f, 10, 0.25f));
			DQNT_ASSERT(dqnt_v4_equals(result, dqnt_v4(250, 25, 750, 25)) == true);

			f32 dotResult = dqnt_v4_dot(dqnt_v4(5, 10, 2, 8), dqnt_v4(3, 4, 6, 5));
			DQNT_ASSERT(dotResult == 107);
		}

		printf("dqnt_vec_test(): vec4: Completed successfully\n");
	}

	// Rect
	{
		DqntRect rect = dqnt_rect(dqnt_v2(-10, -10), dqnt_v2(20, 20));
		DQNT_ASSERT(dqnt_v2_equals(rect.min, dqnt_v2(-10, -10)));
		DQNT_ASSERT(dqnt_v2_equals(rect.max, dqnt_v2(10, 10)));

		f32 width, height;
		dqnt_rect_get_size_2f(rect, &width, &height);
		DQNT_ASSERT(width == 20);
		DQNT_ASSERT(height == 20);

		DqntV2 dim = dqnt_rect_get_size_v2(rect);
		DQNT_ASSERT(dqnt_v2_equals(dim, dqnt_v2(20, 20)));

		DqntV2 rectCenter = dqnt_rect_get_centre(rect);
		DQNT_ASSERT(dqnt_v2_equals(rectCenter, dqnt_v2(0, 0)));

		// Test shifting rect
		DqntRect shiftedRect = dqnt_rect_move(rect, dqnt_v2(10, 0));
		DQNT_ASSERT(dqnt_v2_equals(shiftedRect.min, dqnt_v2(0, -10)));
		DQNT_ASSERT(dqnt_v2_equals(shiftedRect.max, dqnt_v2(20, 10)));

		dqnt_rect_get_size_2f(shiftedRect, &width, &height);
		DQNT_ASSERT(width == 20);
		DQNT_ASSERT(height == 20);

		dim = dqnt_rect_get_size_v2(shiftedRect);
		DQNT_ASSERT(dqnt_v2_equals(dim, dqnt_v2(20, 20)));

		// Test rect contains p
		DqntV2 inP  = dqnt_v2(5, 5);
		DqntV2 outP = dqnt_v2(100, 100);
		DQNT_ASSERT(dqnt_rect_contains_p(shiftedRect, inP));
		DQNT_ASSERT(!dqnt_rect_contains_p(shiftedRect, outP));

		printf("dqnt_vec_test(): rect: Completed successfully\n");
	}

	printf("dqnt_vec_test(): Completed successfully\n");
}

void dqnt_darray_test()
{
	{
		DqntV2 *vecDArray = DQNT_DARRAY_INIT(DqntV2, 1);
		DQNT_ASSERT(vecDArray);
		DQNT_ASSERT(dqnt_darray_get_capacity(vecDArray) == 1);
		DQNT_ASSERT(dqnt_darray_get_num_items(vecDArray) == 0);

		// Test basic insert
		{
			DqntV2 va = dqnt_v2(5, 10);
			DQNT_ASSERT(DQNT_DARRAY_PUSH(&vecDArray, &va));

			DqntV2 vb = vecDArray[0];
			DQNT_ASSERT(dqnt_v2_equals(va, vb));

			DQNT_ASSERT(dqnt_darray_get_capacity(vecDArray) == 1);
			DQNT_ASSERT(dqnt_darray_get_num_items(vecDArray) == 1);

			DqntV2 *empty = NULL;
			DQNT_ASSERT(DQNT_DARRAY_PUSH(NULL, empty) == false);
			DQNT_ASSERT(DQNT_DARRAY_PUSH(NULL, &va) == false);
			DQNT_ASSERT(DQNT_DARRAY_PUSH(&vecDArray, empty) == false);
		}

		// Test array resizing and freeing
		{
			DqntV2 va = dqnt_v2(10, 15);
			DQNT_DARRAY_PUSH(&vecDArray, &va);

			DqntV2 vb = vecDArray[0];
			DQNT_ASSERT(dqnt_v2_equals(va, vb) == false);

			vb = vecDArray[1];
			DQNT_ASSERT(dqnt_v2_equals(va, vb) == true);

			DQNT_ASSERT(dqnt_darray_get_capacity(vecDArray) == 2);
			DQNT_ASSERT(dqnt_darray_get_num_items(vecDArray) == 2);

			DQNT_DARRAY_PUSH(&vecDArray, &va);
			DQNT_ASSERT(dqnt_darray_get_capacity(vecDArray) == 3);
			DQNT_ASSERT(dqnt_darray_get_num_items(vecDArray) == 3);

			DQNT_DARRAY_PUSH(&vecDArray, &va);
			DQNT_ASSERT(dqnt_darray_get_capacity(vecDArray) == 4);
			DQNT_ASSERT(dqnt_darray_get_num_items(vecDArray) == 4);

			DQNT_DARRAY_PUSH(&vecDArray, &va);
			DQNT_ASSERT(dqnt_darray_get_capacity(vecDArray) == 5);
			DQNT_ASSERT(dqnt_darray_get_num_items(vecDArray) == 5);

			DQNT_DARRAY_PUSH(&vecDArray, &va);
			DQNT_ASSERT(dqnt_darray_get_capacity(vecDArray) == 6);
			DQNT_ASSERT(dqnt_darray_get_num_items(vecDArray) == 6);

			DQNT_DARRAY_PUSH(&vecDArray, &va);
			DQNT_ASSERT(dqnt_darray_get_capacity(vecDArray) == 7);
			DQNT_ASSERT(dqnt_darray_get_num_items(vecDArray) == 7);

			DQNT_DARRAY_PUSH(&vecDArray, &va);
			DQNT_ASSERT(dqnt_darray_get_capacity(vecDArray) == 8);
			DQNT_ASSERT(dqnt_darray_get_num_items(vecDArray) == 8);

			DQNT_DARRAY_PUSH(&vecDArray, &va);
			DQNT_ASSERT(dqnt_darray_get_capacity(vecDArray) == 9);
			DQNT_ASSERT(dqnt_darray_get_num_items(vecDArray) == 9);

			DQNT_DARRAY_PUSH(&vecDArray, &va);
			DQNT_ASSERT(dqnt_darray_get_capacity(vecDArray) == 10);
			DQNT_ASSERT(dqnt_darray_get_num_items(vecDArray) == 10);

			DQNT_DARRAY_PUSH(&vecDArray, &va);
			DQNT_ASSERT(dqnt_darray_get_capacity(vecDArray) == 12);
			DQNT_ASSERT(dqnt_darray_get_num_items(vecDArray) == 11);

			DqntV2 vc = dqnt_v2(90, 100);
			DQNT_DARRAY_PUSH(&vecDArray, &vc);
			DQNT_ASSERT(dqnt_darray_get_capacity(vecDArray) == 12);
			DQNT_ASSERT(dqnt_darray_get_num_items(vecDArray) == 12);
			DQNT_ASSERT(dqnt_v2_equals(vc, vecDArray[11]));

			DQNT_ASSERT(dqnt_darray_free(vecDArray) == true);
		}
	}

	{
		f32 *array = DQNT_DARRAY_INIT(f32, 1);
		DQNT_ASSERT(array);
		DQNT_ASSERT(dqnt_darray_get_capacity(array) == 1);
		DQNT_ASSERT(dqnt_darray_get_num_items(array) == 0);

		f32 *empty = NULL;
		DQNT_ASSERT(DQNT_DARRAY_PUSH(NULL, empty) == false);
		DQNT_ASSERT(DQNT_DARRAY_PUSH(&array, empty) == false);
	}

	printf("dqnt_darray_test(): Completed successfully\n");
}

void dqnt_file_test()
{
	// File i/o
	{
		DqntFile file = {};
		DQNT_ASSERT(dqnt_file_open(".clang-format", &file));
		DQNT_ASSERT(file.size == 1320);

		u8 *buffer = (u8 *)calloc(1, (size_t)file.size * sizeof(u8));
		DQNT_ASSERT(dqnt_file_read(file, buffer, (u32)file.size) == file.size);
		free(buffer);

		dqnt_file_close(&file);
		DQNT_ASSERT(!file.handle && file.size == 0);

		printf("dqnt_file_test(): file_io: Completed successfully\n");
	}

	{
		u32 numFiles;
		char **filelist = dqnt_dir_read("*", &numFiles);
		printf("dqnt_file_test(): dir_read: Display read files\n");

		for (u32 i = 0; i < numFiles; i++)
			printf("dqnt_file_test(): dir_read: %s\n", filelist[i]);

		dqnt_dir_read_free(filelist, numFiles);
		printf("dqnt_file_test(): dir_read: Completed successfully\n");
	}

	printf("dqnt_file_test(): Completed successfully\n");
}

int main(void)
{
	dqnt_strings_test();
	dqnt_random_test();
	dqnt_math_test();
	dqnt_vec_test();
	dqnt_other_test();
	dqnt_darray_test();
	dqnt_file_test();

	printf("\nPress 'Enter' Key to Exit\n");
	getchar();

	return 0;
}
