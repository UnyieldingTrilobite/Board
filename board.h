#ifndef __BOARD_H_
#define __BOARD_H_
#include <cstring>
namespace dabiao {
int b[18][18][18][18][5];
bool isv[18][18][18][18];
struct __dabiao__initer__ {
  __dabiao__initer__();
} __init;
}  // namespace dabiao
class Board {
 private:
  int _score;
  int last_dir;
  int mat[4][4];
 public:
  Board() : _score(0), last_dir(-1) { memset(mat, 0, sizeof mat); }
  void setup(int s[][4]);
  void get_valid_move(bool *moves);
  int get_valid_move(int *move);
  bool apply_move(int move);
  void get_valid_state(bool *state);
  int get_valid_state(int *state);
  void apply_state(int state);
  int random_gennum();
  int random_move();
#if 0
    double rollout(int n_time);
#endif
  int score();
  void print_board();
  void reset();
  int rollout_with_UT_understand();
  double rollout_with_UT_understand(int times);
};
#endif
