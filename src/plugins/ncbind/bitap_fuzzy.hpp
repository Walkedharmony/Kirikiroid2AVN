#pragma once

#include <limits>
#include <vector>
#include <cassert>

template <typename CHAR, typename MASK>
int bitap_fuzzy_bitwise_search(const CHAR *text,    const size_t text_len,
							   const CHAR *pattern, const size_t pattern_len,
							   size_t k, size_t maskbits = sizeof(MASK))
{
	typedef std::numeric_limits<MASK> MaskLimit;
	static_assert(MaskLimit::is_integer && !MaskLimit::is_signed && (MaskLimit::radix == 2), "MASK must be unsigned integer type");

	if (!text || !text_len || !pattern) return -3; // invalid args
	if (!pattern_len) return 0; // no search pattern (= found first)
	else if (pattern_len >= sizeof(MASK)*MaskLimit::digits) return -2; // too long pattern

	const size_t char_mask = (size_t)((1uLL << maskbits)-1);
	const MASK eop = (MASK)(1uLL << pattern_len);

	typedef std::vector<MASK> MaskTable;
	MaskTable R(k+1, (MASK)~1uLL);
	MaskTable pattern_mask(char_mask + 1, (MASK)~0uLL);

	// initialize the pattern bitmasks
	for (size_t i = 0; i < pattern_len; ++i)
		pattern_mask[char_mask & pattern[i]] &= (MASK)~(1uLL << i);

	for (size_t i = 0; i < text_len; ++i) {
		// update the bit arrays
		MASK old_Rd1 = R[0];
		const MASK text_mask = pattern_mask[char_mask & text[i]];

		R[0] |= text_mask;
		R[0] <<= 1;

		for (size_t d = 1; d <= k; ++d) {
			const MASK tmp = R[d];
			// substitution is all we care about
			R[d] = (old_Rd1 & (R[d] | text_mask)) << 1;
			old_Rd1 = tmp;
		}
		
		if (0 == (R[k] & eop)) {
			const int result = (1 + i - pattern_len);
			assert(result >= 0);
			return result;
		}
	}
	return -1; // not found
}