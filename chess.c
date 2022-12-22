#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

const char PAWN = 1;
const char ROOK = 2;
const char KNIGHT = 3;
const char BISHOP = 4;
const char QUEEN = 5;
const char KING = 6;

const char EMPTY = 0;
const char WHITE = 1;
const char BLACK = 2;

struct

char other_color(char color) {
    if (color > EMPTY) {
        return color == WHITE ? BLACK : WHITE;
    }
    return EMPTY;
}

uint64_t * init_bitboards() {
	uint64_t * bitboards = (uint64_t*)malloc(12 * sizeof(uint64_t));
	uint64_t pawn_row = 0b11111111LL;
	uint64_t rook_row = 0b10000001LL;
	uint64_t knight_row = 0b01000010LL;
	uint64_t bishop_row = 0b00100100LL;
	uint64_t queen_row = 0b00010000LL;
	uint64_t king_row = 0b00001000LL;
	//White
	bitboards[0] = pawn_row << 48;
	bitboards[1] = rook_row << 56;
	bitboards[2] = knight_row << 56;
	bitboards[3] = bishop_row << 56;
	bitboards[4] = queen_row << 56;
	bitboards[5] = king_row << 56;
	//Black
	bitboards[6] = pawn_row << 8;
	bitboards[7] = rook_row;
	bitboards[8] = knight_row;
	bitboards[9] = bishop_row;
	bitboards[10] = queen_row;
	bitboards[11] = king_row;

	return bitboards;
}

void print_bitboard(uint64_t bitboard) {
	for (int i = 0 ; i < 64 ; i ++) {
		if (i % 8 == 0) {
			printf("\n");
		}
		if (bitboard >> i & 1) {
			printf("*");
		} else {
			printf(" ");
		}
	}	
}

uint64_t mask_all(const uint64_t * bitboards) {
	uint64_t mask = 0LL;
	for (char i = 0 ; i < 12 ; i ++ ) {
		mask |= bitboards[i];
	}
	return mask;
}

uint64_t mask_for_color(const uint64_t * bitboards, char color) {
    uint64_t mask = 0LL;
    int offset = 6 * (color - 1);
    for (char i = 0 ; i < 6 ; i ++) {
        mask |= bitboards[i + offset];
    }
    return mask;
}


uint64_t rook_move_mask(const uint64_t * bitboards, char color) {
    uint64_t white_mask = mask_for_color(bitboards, color);
    uint64_t black_mask = mask_for_color(bitboards, other_color(color));

}

uint64_t get_bitboard(uint64_t * bitboards, char piece, char color) {
    return bitboards[(piece * color) - 1];
}

int main() {
	uint64_t * bitboards = init_bitboards();
	print_bitboard(mask_all(bitboards));
	for (char i = 0 ; i < 12 ; i ++ ) {
		printf("--------------------");
		print_bitboard(bitboards[i]);
		printf("--------------------");
	}
}
