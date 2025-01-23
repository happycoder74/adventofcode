#include "aoc_alloc.h"
#include "aoc_array.h"
#include "aoc_header.h"
#include "aoc_string.h"
#include "aoc_timer.h"
#include "aoc_types.h"
#include "aoc_utils.h"
#include <ctype.h>
#include <glib.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#define BUFSIZE 128

uint32_t left_rotate32bits(uint32_t n, size_t rotate) {
    return (n << rotate) | (n >> (32 - rotate));
}

uint8_t is_big_endian() {
    union {
        uint32_t i;
        char     c[4];
    } bint = {0x01020304};

    return bint.c[0] == 1;
}

uint32_t to_little_endian32(uint32_t n) {
    if (!is_big_endian()) {
        return ((n << 24) & 0xFF000000) | ((n << 8) & 0x00FF0000) | ((n >> 8) & 0x0000FF00) |
               ((n >> 24) & 0x000000FF);
    }
    // Machine works on little endian, no need to change anything
    return n;
}

uint64_t to_little_endian64(uint64_t n) {
    if (!is_big_endian()) {
        return ((n << 56) & 0xFF00000000000000) | ((n << 40) & 0x00FF000000000000) |
               ((n << 24) & 0x0000FF0000000000) | ((n << 8) & 0x000000FF00000000) |
               ((n >> 8) & 0x00000000FF000000) | ((n >> 24) & 0x0000000000FF0000) |
               ((n >> 40) & 0x000000000000FF00) | ((n >> 56) & 0x00000000000000FF);
        ;
    }
    // Machine works on little endian, no need to change anything
    return n;
}

void hash_bs(const uint8_t *input_bs, const size_t size, uint8_t *sig) {
    const uint8_t *input = input_bs;
    size_t         input_size = size;

    // Step 0: Initial Data (Those are decided in the MD5 protocol)
    // s is the shift used in the leftrotate each round
    uint32_t s[64] = {7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,
                      5, 9,  14, 20, 5, 9,  14, 20, 5, 9,  14, 20, 5, 9,  14, 20,
                      4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23,
                      6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21};
    // K is pseudo-random values used each round
    // The values can be obtained by the following python code:

    /**
     * @brief Values of K are pseudo-random and used to "salt" each round
     * The values can be obtained by the following python code
     * @code{.py}
     * from math import floor, sin
     *
     * for i in range(64):
     *     print(floor(2**32 * abs(sin(i+1))))
     * @endcode
     */
    static const uint32_t K[64] = {
        3614090360, 3905402710, 606105819,  3250441966, 4118548399, 1200080426, 2821735955,
        4249261313, 1770035416, 2336552879, 4294925233, 2304563134, 1804603682, 4254626195,
        2792965006, 1236535329, 4129170786, 3225465664, 643717713,  3921069994, 3593408605,
        38016083,   3634488961, 3889429448, 568446438,  3275163606, 4107603335, 1163531501,
        2850285829, 4243563512, 1735328473, 2368359562, 4294588738, 2272392833, 1839030562,
        4259657740, 2763975236, 1272893353, 4139469664, 3200236656, 681279174,  3936430074,
        3572445317, 76029189,   3654602809, 3873151461, 530742520,  3299628645, 4096336452,
        1126891415, 2878612391, 4237533241, 1700485571, 2399980690, 4293915773, 2240044497,
        1873313359, 4264355552, 2734768916, 1309151649, 4149444226, 3174756917, 718787259,
        3951481745};

    // The initial 128-bit state
    uint32_t a0 = 0x67452301, A = 0;
    uint32_t b0 = 0xefcdab89, B = 0;
    uint32_t c0 = 0x98badcfe, C = 0;
    uint32_t d0 = 0x10325476, D = 0;

    // Step 1: Processing the bytestring

    // First compute the size the padded message will have
    // so it is possible to allocate the right amount of memory
    uint64_t padded_message_size =
        input_size + (input_size % 64 < 56 ? 64 : 128) - (input_size % 64);

    uint8_t *padded_message = (uint8_t *)calloc(padded_message_size, sizeof(uint8_t));

    // Beginning of the padded message is the original message
    memmove(padded_message, input, input_size * sizeof(uint8_t));
    /* std::copy(input, input + input_size, padded_message.begin()); */

    // Afterwards comes a single 1 bit and then only zeroes
    padded_message[input_size] = 1 << 7; // 10000000
    for (uint64_t i = input_size; i % 64 != 56; i++) {
        if (i == input_size) {
            continue; // pass first iteration
        }
        padded_message[i] = 0;
    }

    // We then have to add the 64-bit size of the message at the end
    // When there is a conversion from int to bytestring or vice-versa
    // We always need to make sure it is little endian
    uint64_t input_bitsize_le = to_little_endian64(input_size * 8);
    for (uint8_t i = 0; i < 8; i++) {
        padded_message[padded_message_size - 8 + i] = (input_bitsize_le >> (56 - 8 * i)) & 0xFF;
    }

    // Already allocate memory for blocks
    uint32_t blocks[16] = {0};

    // Rounds
    for (uint64_t chunk = 0; chunk * 64 < padded_message_size; chunk++) {
        // First, build the 16 32-bits blocks from the chunk
        for (uint8_t bid = 0; bid < 16; bid++) {
            blocks[bid] = 0;

            // Having to build a 32-bit word from 4-bit words
            // Add each and shift them to the left
            for (uint8_t cid = 0; cid < 4; cid++) {
                blocks[bid] = (blocks[bid] << 8) + padded_message[chunk * 64 + bid * 4 + cid];
            }
        }

        A = a0;
        B = b0;
        C = c0;
        D = d0;

        // Main "hashing" loop
        for (uint8_t i = 0; i < 64; i++) {
            uint32_t F = 0, g = 0;
            if (i < 16) {
                F = (B & C) | ((~B) & D);
                g = i;
            } else if (i < 32) {
                F = (D & B) | ((~D) & C);
                g = (5 * i + 1) % 16;
            } else if (i < 48) {
                F = B ^ C ^ D;
                g = (3 * i + 5) % 16;
            } else {
                F = C ^ (B | (~D));
                g = (7 * i) % 16;
            }

            // Update the accumulators
            F += A + K[i] + to_little_endian32(blocks[g]);

            A = D;
            D = C;
            C = B;
            B += left_rotate32bits(F, s[i]);
        }
        // Update the state with this chunk's hash
        a0 += A;
        b0 += B;
        c0 += C;
        d0 += D;
    }

    // Build signature from state
    // Note, any type could be used for the signature
    // uint8_t was used to make the 16 bytes obvious
    // The sig needs to be little endian
    // auto* sig = new uint8_t[16];
    for (uint8_t i = 0; i < 4; i++) {
        sig[i] = (a0 >> (8 * i)) & 0xFF;
        sig[i + 4] = (b0 >> (8 * i)) & 0xFF;
        sig[i + 8] = (c0 >> (8 * i)) & 0xFF;
        sig[i + 12] = (d0 >> (8 * i)) & 0xFF;
    }

    free(padded_message);
    // return sig;
}

void *solve_part_1(AocData_t *data) {
    unsigned char to_hash[BUFSIZE];
    const char   *hashed;
    int           counter = 0;
    int           found = 0;
    char          code[] = "________";
    char         *doorID;
    int           count = 0;
    GChecksum    *checksum;

    doorID = aoc_str_array_index(aoc_data_get(data), 0);

    printf("Part 1:\n");
    printf("\t%s\r", code);
    while ((found < 8) && (count < 5)) {
        snprintf((char *)to_hash, BUFSIZE, "%s%d", doorID, counter++);
        checksum = g_checksum_new(G_CHECKSUM_MD5);
        g_checksum_update(checksum, to_hash, strlen((const char *)to_hash));
        hashed = g_checksum_get_string(checksum);
        if (((hashed[0] == '0') && (hashed[1] == '0') && (hashed[2] == '0') && (hashed[3] == '0') &&
             (hashed[4] == '0'))) {
            code[found++] = hashed[5];
            printf("\t%s\r", code);
            fflush(stdout);
        }
    }
    printf("\n");
    return strdup_printf("%s (%d)", code, counter);
}

static int digit_value(char c) {
    if (!isdigit(c))
        return -1;
    return c - '0';
}

void *solve_part_2(AocData_t *data) {
    const char   *hashed;
    int           counter = 0, found = 0;
    int           pos;
    unsigned int  j;
    GChecksum    *checksum;
    char          code[] = "________";
    unsigned char to_hash[BUFSIZE];
    char         *doorID;

    doorID = aoc_str_array_index(aoc_data_get(data), 0);

    printf("\nPart 2:\n");
    found = 0;
    counter = 0;

    while (found < 8) {
        snprintf((char *)to_hash, BUFSIZE, "%s%d", doorID, counter++);
        checksum = g_checksum_new(G_CHECKSUM_MD5);
        g_checksum_update(checksum, to_hash, strlen((const char *)to_hash));
        hashed = g_checksum_get_string(checksum);
        if (!strncasecmp(hashed, "00000", 5)) {
            if ((pos = digit_value(hashed[5])) != -1) {
                if ((pos < 8) && (code[pos] == '_')) {
                    found++;
                    code[pos] = hashed[6];
                }
            }
        }
        if ((((counter - 1) % 100000) == 0) || (found == 8)) {
            printf("\t");
            for (j = 0; j < strlen(code); j++) {
                if (code[j] == '_') {
                    printf("\033[1;32m%x\033[0m", (0 + rand() % 16));
                } else {
                    printf("\033[1;33m%c\033[0m", code[j]);
                }
            }
            printf("\r");
            fflush(stdout);
        }
        g_checksum_free(checksum);
    }
    printf("\n");
    return strdup(code);
}

void *solve(void *inp) {
    AocData_t *data = (AocData_t *)inp;
    uint8_t   *input = (uint8_t *)aoc_str_array_index(aoc_data_get(data), 0);
    size_t     len = 8;
    uint8_t    buf[16] = {'\0'};

    uint8_t part1[65] = {'\0'};
    uint8_t part2[9] = {'\0'};
    for (int i = 0; i < 8; i++) {
        part2[i] = '*';
    }
    part2[8] = '\0';

    const uint8_t dec2hex[] = "0123456789abcdef";

    size_t p1_index = 0;
    for (size_t i = 0, k = 0; k < len; ++i) {
        uint8_t input_buf[100] = {0};
        snprintf((char *)input_buf, 100, "%s%zu", input, i);
        hash_bs(input_buf, strlen((char *)input_buf), buf);

        const uint8_t mask = 15U;
        if (buf[0] == 0 && buf[1] == 0 && (buf[2] >> 4U) == 0) {
            size_t pos = buf[2] & mask;
            part1[p1_index++] = dec2hex[pos];
            if (pos < len && part2[pos] == '*') {
                part2[pos] = dec2hex[mask & (buf[3] >> 4U)];
                ++k;
            }
        }
    }

    part1[len] = '\0';
    return strdup_printf("%s, %s", part1, part2);
}

void *solve_all(AocData_t *data) {

    if (aoc_data_get(data)) {
        timer_func(1, solve_part_1, data, 1);
        timer_func(2, solve_part_2, data, 1);
    }

    return NULL;
}

int main(int argc, char **argv) {

    const unsigned year = 2016;
    const unsigned day = 5;

    AocTimer_t *timer = aoc_timer_new();

    aoc_timer_start(timer);
    AocData_t *data = get_data(argc, argv, year, day, NULL);
    aoc_timer_stop(timer);

    aoc_header(year, day);
    aoc_timer_gen("Preparation time:", timer, BORDER_BOTTOM);
    timer_func(0, solve_all, data, 0);
    timer_func_new_str(1, solve, data, 1);
    aoc_timer_stop(timer);
    aoc_timer_gen("Total time:", timer, BORDER_TOP | BORDER_BOTTOM);

    aoc_timer_delete(timer);
    aoc_data_free(data);

    return aoc_mem_gc();
}
