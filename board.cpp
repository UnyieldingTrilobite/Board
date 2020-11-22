#include <cassert>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iostream>
#include "board.h"
using namespace std;
dabiao::__dabiao__initer__::__dabiao__initer__() {
  using namespace dabiao;
  srand(time(0));
  for (int a1 = 0; a1 < 18; a1++) {
    for (int a2 = 0; a2 < 18; a2++) {
      for (int a3 = 0; a3 < 18; a3++) {
        for (int a4 = 0; a4 < 18; a4++) {
          int *p = b[a1][a2][a3][a4];
          p[0] = a1, p[1] = a2, p[2] = a3, p[3] = a4;
          for (int i = 1, j; i <= 3; ++i) {
            j = i;
            while (j && !p[j - 1]) {
              p[j - 1] = p[j], p[j--] = 0;
            }
          }
          for (int i = 1; i <= 3; ++i) {
            if (p[i] && p[i - 1] == p[i]) {
              p[4] += 1 << p[i];
              ++p[i - 1], p[i] = 0;
            }
          }
          for (int i = 1, j; i <= 3; ++i) {
            j = i;
            while (j && !p[j - 1]) {
              p[j - 1] = p[j], p[j--] = 0;
            }
          }
          isv[a1][a2][a3][a4] =
              (a1 != p[0] || a2 != p[1] || a3 != p[2] || a4 != p[3]);
        }
      }
    }
  }
}
void Board::setup(int s[][4]) {
  for (size_t i = 0; i < 4; i++) {
    for (size_t j = 0; j < 4; j++) {
      int b = 0;
      while (s[i][j] >>= 1) ++b;
      mat[i][j] = b;
    }
  }
}
void Board::get_valid_move(bool *moves) {
  using namespace dabiao;
  memset(moves, false, sizeof(bool) * 4);
  int op1, op2, op3, op4;
  for (int i = 0; i < 4; ++i) {
    op1 = mat[0][i], op2 = mat[1][i], op3 = mat[2][i], op4 = mat[3][i];
    if (isv[op1][op2][op3][op4]) {
      moves[0] = true;
      break;
    }
  }
  for (int i = 0; i < 4; ++i) {
    op1 = mat[i][3], op2 = mat[i][2], op3 = mat[i][1], op4 = mat[i][0];
    if (isv[op1][op2][op3][op4]) {
      moves[1] = true;
      break;
    }
  }
  for (int i = 0; i < 4; ++i) {
    op1 = mat[3][i], op2 = mat[2][i], op3 = mat[1][i], op4 = mat[0][i];
    if (isv[op1][op2][op3][op4]) {
      moves[2] = true;
      break;
    }
  }
  for (int i = 0; i < 4; ++i) {
    op1 = mat[i][0], op2 = mat[i][1], op3 = mat[i][2], op4 = mat[i][3];
    if (isv[op1][op2][op3][op4]) {
      moves[3] = true;
      break;
    }
  }
}
int Board::get_valid_move(int *moves) {
  using namespace dabiao;
  int tot = 0;
  int op1, op2, op3, op4;
  for (int i = 0; i < 4; ++i) {
    op1 = mat[0][i], op2 = mat[1][i], op3 = mat[2][i], op4 = mat[3][i];
    if (isv[op1][op2][op3][op4]) {
      moves[tot++] = 0;
      break;
    }
  }
  for (int i = 0; i < 4; ++i) {
    op1 = mat[i][3], op2 = mat[i][2], op3 = mat[i][1], op4 = mat[i][0];
    if (isv[op1][op2][op3][op4]) {
      moves[tot++] = 1;
      break;
    }
  }
  for (int i = 0; i < 4; ++i) {
    op1 = mat[3][i], op2 = mat[2][i], op3 = mat[1][i], op4 = mat[0][i];
    if (isv[op1][op2][op3][op4]) {
      moves[tot++] = 2;
      break;
    }
  }
  for (int i = 0; i < 4; ++i) {
    op1 = mat[i][0], op2 = mat[i][1], op3 = mat[i][2], op4 = mat[i][3];
    if (isv[op1][op2][op3][op4]) {
      moves[tot++] = 3;
      break;
    }
  }
  return tot;
}
bool Board::apply_move(int dir) {
  using namespace dabiao;
  int op1, op2, op3, op4;
  last_dir = -1;
  switch (dir) {
    case 0:
      for (int i = 0; i < 4; ++i) {
        op1 = mat[0][i], op2 = mat[1][i], op3 = mat[2][i], op4 = mat[3][i];
        if (isv[op1][op2][op3][op4]) {
          for (int j = 0; j < 4; ++j) {
            mat[j][i] = b[op1][op2][op3][op4][j];
          }
          last_dir = dir, _score += b[op1][op2][op3][op4][4];
        }
      }
      break;
    case 1:
      for (int i = 0; i < 4; ++i) {
        op1 = mat[i][3], op2 = mat[i][2], op3 = mat[i][1], op4 = mat[i][0];
        if (isv[op1][op2][op3][op4]) {
          for (int j = 3; j >= 0; --j) {
            mat[i][j] = b[op1][op2][op3][op4][3 - j];
          }
          last_dir = dir, _score += b[op1][op2][op3][op4][4];
        }
      }
      break;
    case 2:
      for (int i = 0; i < 4; ++i) {
        op1 = mat[3][i], op2 = mat[2][i], op3 = mat[1][i], op4 = mat[0][i];
        if (isv[op1][op2][op3][op4]) {
          for (int j = 3; j >= 0; --j) {
            mat[j][i] = b[op1][op2][op3][op4][3 - j];
          }
          last_dir = dir, _score += b[op1][op2][op3][op4][4];
        }
      }
      break;
    case 3:
      for (int i = 0; i < 4; ++i) {
        op1 = mat[i][0], op2 = mat[i][1], op3 = mat[i][2], op4 = mat[i][3];
        if (isv[op1][op2][op3][op4]) {
          for (int j = 0; j < 4; ++j) {
            mat[i][j] = b[op1][op2][op3][op4][j];
          }
          last_dir = dir, _score += b[op1][op2][op3][op4][4];
        }
      }
      break;
  }
  return last_dir != -1;
}
void Board::get_valid_state(bool *states) {
  assert(last_dir != -1);
  switch (last_dir) {
    case 0:
      for (size_t i = 0; i < 4; i++) {
        states[i] = !mat[3][i];
      }
      break;
    case 1:
      for (size_t i = 0; i < 4; i++) {
        states[i] = !mat[i][0];
      }
      break;
    case 2:
      for (size_t i = 0; i < 4; i++) {
        states[i] = !mat[0][i];
      }
      break;
    case 3:
      for (size_t i = 0; i < 4; i++) {
        states[i] = !mat[i][3];
      }
      break;
  }
}
int Board::get_valid_state(int *states) {
  assert(last_dir != -1);
  int tot(0);
  switch (last_dir) {
    case 0:
      for (size_t i = 0; i < 4; i++) {
        (!mat[3][i]) && (states[tot++] = i);
      }
      break;
    case 1:
      for (size_t i = 0; i < 4; i++) {
        (!mat[i][0]) && (states[tot++] = i);
      }
      break;
    case 2:
      for (size_t i = 0; i < 4; i++) {
        (!mat[0][i]) && (states[tot++] = i);
      }
      break;
    case 3:
      for (size_t i = 0; i < 4; i++) {
        (!mat[i][3]) && (states[tot++] = i);
      }
      break;
  }
  return tot;
}
void Board::apply_state(int state) {
  assert(last_dir != -1);
  switch (last_dir) {
    case 0:
      mat[3][state >> 1] = 1 + (state & 1);
      break;
    case 1:
      mat[state >> 1][0] = 1 + (state & 1);
      break;
    case 2:
      mat[0][state >> 1] = 1 + (state & 1);
      break;
    case 3:
      mat[state >> 1][3] = 1 + (state & 1);
      break;
  }
  // printf("state:%d,%d\n",state>>1,state&1);
}
int Board::random_gennum() {
  int states[4], tot = get_valid_state(states);
  if (!tot) return -1;
  int pos = rand() % tot, num = !!(rand() % 10);
  apply_state(states[pos] << 1 | num);
  return (num + 1) << 1;
}
int Board::random_move() {
  int moves[4], tot = get_valid_move(moves);
  if (!tot) return -1;
  int todo = moves[rand() % tot];
  apply_move(todo);
  return todo;
}
#if 0
double Board::rollout(int n_time){
    double total=0.;
    bool states[8];
    bool moves[8];

    for(int i=0;i<n_time;i++){
        Board copy(*this);

        while(true){
            //move
            copy.get_valid_move(moves);
            int m[4];
            int nm=0;
            for(size_t j=0;j<4;j++){
                if(moves[j]){
                    m[nm++]=j;
                }
            }
            int r=rand()%nm;
            bool fz=copy.apply_move(m[r]);
            if(fz){
                break;
            }

            //state
            copy.get_valid_state(states);
            int s[8];
            int ns=0;
            for(size_t j=0;j<8;j++){
                if(moves[j]){
                    s[ns++]=j;
                }
            }
            r=rand()%ns;
            copy.apply_move(s[r]);
       }
        total+=copy.score();
    }
    return total/n_time;
}
#endif
int Board::rollout_with_UT_understand() {
  Board copy(*this);
  int tot = 0;
  while (copy.random_move() != -1) {
    ++tot;
    copy.random_gennum();
  }
  copy.print_board();
  return tot;
}
int Board::score() { return _score; }
void Board::print_board() {
  fprintf(stderr, "score=%d", _score);
  int tot = 8;
  for (int j = _score; j; j /= 10) --tot;
  while (tot--) fputc(' ', stderr);
  fputc('\n', stderr);
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j) {
      if (mat[i][j] == 0) {
        fprintf(stderr, "%8s", ".");
      } else {
        fprintf(stderr, "%8d", 1 << mat[i][j]);
      }
    }
    fputc('\n', stderr);
  }
  fputc('\n', stderr);
}
void Board::reset() {
  _score = 0;
  memset(mat, 0, sizeof(mat));
  last_dir = -1;
  mat[rand() & 3][rand() & 3] = 1 + !(rand() % 10);
}
double Board::rollout_with_UT_understand(int times){
	long long tot(0);
	for(int i=0;i<times;++i)tot+=rollout_with_UT_understand();
	return tot*1./times;
}
