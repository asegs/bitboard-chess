#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

const char PAWN = 0;
const char ROOK = 1;
const char KNIGHT = 2;
const char BISHOP = 3;
const char QUEEN = 4;
const char KING = 5;
const char NONE = 6;

const char EMPTY = 0;
const char WHITE = 1;
const char BLACK = 2;

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

uint64_t * copy_bitboards (const uint64_t * bitboards) {
    uint64_t * bitboards_copy = malloc(12 * sizeof(uint64_t));
    for (int i = 0 ; i < 12 ; i ++ ) {
        bitboards_copy[i] = bitboards[i];
    }
    return bitboards_copy;
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

uint64_t get_bitboard(const uint64_t * bitboards, char piece, char color) {
    return bitboards[piece + (color - 1) * 6];
}

double score_board(uint64_t * bitboards) {
    double score = 0;
    score += __builtin_popcount(bitboards[0]);
    score += __builtin_popcount(bitboards[1]) * 5;
    score += __builtin_popcount(bitboards[2]) * 3;
    score += __builtin_popcount(bitboards[3]) * 3;
    score += __builtin_popcount(bitboards[4]) * 9;
    score += __builtin_popcount(bitboards[5]) * 999;

    score -= __builtin_popcount(bitboards[6]);
    score -= __builtin_popcount(bitboards[7]) * 5;
    score -= __builtin_popcount(bitboards[8]) * 3;
    score -= __builtin_popcount(bitboards[9]) * 3;
    score -= __builtin_popcount(bitboards[10]) * 9;
    score -= __builtin_popcount(bitboards[11]) * 999;

    return score;
}

uint64_t * create_new_bitboards_with_change_of_2(const uint64_t * old_bitboards, uint64_t change_one, uint64_t change_two, char pos_one, char pos_two) {
    uint64_t * new_bitboards = copy_bitboards(old_bitboards);
    new_bitboards[pos_one] = change_one;
    new_bitboards[pos_two] = change_two;
    return new_bitboards;
}

bool is_set_coords(const uint64_t bitboard, char row, char col) {
    return bitboard & (1 << (row * 8 + col));
}

bool is_set(const uint64_t bitboard, int pos) {
    return bitboard & (1 << pos);
}

char from_which(const uint64_t * bitboards, int pos, char color) {
    for (int i = 0 ; i < 6 ; i ++ ) {
        if (is_set(get_bitboard(bitboards, i, color), pos)) {
            return i;
        }
    }
    return NONE;
}




//Struct with 12 spaced list of bitboards and count
uint64_t * moves_for_color(const uint64_t * bitboards, char color) {
    uint64_t my_mask = mask_for_color(bitboards, color);
    char position = 0;
    char piece_type = 6;
    while (my_mask > 0) {
        if (my_mask & 1) {
            piece_type = from_which(bitboards, position, color);
            //instead of returning a bunch of arrays, build this into alpha beta.
            switch (piece_type) {
                
            }
        }
    }
}


uint64_t rook_move_mask(const uint64_t * bitboards, char color) {
    uint64_t white_mask = mask_for_color(bitboards, color);
    uint64_t black_mask = mask_for_color(bitboards, other_color(color));

    uint64_t move_mask  = 0LL;
    uint64_t attack_mask = 0LL;

    uint64_t my_rooks = get_bitboard(bitboards, ROOK, color);
    char position = 0;
    while (my_rooks > 0) {
        if (my_rooks & 1) {
            //Detect moves and attacks at position
        }
        my_rooks = my_rooks >> 1;
        position ++;

    }
    //Somehow return move and attack mask
}

double alpha_beta_root(uint64_t * bitboards, int depth, char color) {
    uint64_t *
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
