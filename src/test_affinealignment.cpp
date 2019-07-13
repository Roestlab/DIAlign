#include <vector>
#include <cmath> // require for std::abs
#include <assert.h>
#include "affinealignment.h"
#include "utils.h" //To propagate #define USE_Rcpp

//TODO update this statement so we know which line failed.
#define ASSERT(condition) if(!(condition)) throw 1; // If you don't put the message, C++ will output the code.

using namespace DIAlign;

void test_doAffineAlignment(){
  double Inf = std::numeric_limits<double>::infinity();
  SimMatrix s;
  s.data = {-2, -2, 10, -2, 10,
            10, -2, -2, -2, -2,
            -2, 10, -2, -2, -2,
            -2, -2, -2, 10, -2};
  s.n_row = 4;
  s.n_col = 5;
  double gapOpen = 22.0, gapExten = 7.0;
  AffineAlignObj obj(4+1, 5+1);
  //........................  CASE 1 ........................................
  doAffineAlignment(obj, s, gapOpen, gapExten, true);

  std::vector< std::vector< TracebackType > > cmp_arr_Traceback;
  std::vector<TracebackType> tmp_tb;
  // Traceback M
  tmp_tb = {SS, SS, SS, SS, SS, SS}; cmp_arr_Traceback.push_back(tmp_tb);
  tmp_tb = {SS, DM, DB, DB, DB, DB}; cmp_arr_Traceback.push_back(tmp_tb);
  tmp_tb = {SS, DA, DM, DM, DM, DM}; cmp_arr_Traceback.push_back(tmp_tb);
  tmp_tb = {SS, DA, DM, DM, DM, DM}; cmp_arr_Traceback.push_back(tmp_tb);
  tmp_tb = {SS, DA, DM, DM, DB, DM}; cmp_arr_Traceback.push_back(tmp_tb);
  // Traceback A
  tmp_tb = {SS, SS, SS, SS, SS, SS}; cmp_arr_Traceback.push_back(tmp_tb);
  tmp_tb = {TM, TB, TB, TB, TB, TB}; cmp_arr_Traceback.push_back(tmp_tb);
  tmp_tb = {TA, TM, TM, TM, TM, TM}; cmp_arr_Traceback.push_back(tmp_tb);
  tmp_tb = {TA, TM, TM, TA, TM, TA}; cmp_arr_Traceback.push_back(tmp_tb);
  tmp_tb = {TA, TA, TM, TB, TA, TM}; cmp_arr_Traceback.push_back(tmp_tb);
  // Traceback B
  tmp_tb = {SS, LM, LB, LB, LB, LB}; cmp_arr_Traceback.push_back(tmp_tb);
  tmp_tb = {SS, LA, LM, LM, LM, LB}; cmp_arr_Traceback.push_back(tmp_tb);
  tmp_tb = {SS, LA, LM, LB, LM, LM}; cmp_arr_Traceback.push_back(tmp_tb);
  tmp_tb = {SS, LA, LM, LM, LB, LB}; cmp_arr_Traceback.push_back(tmp_tb);
  tmp_tb = {SS, LA, LM, LA, LM, LB}; cmp_arr_Traceback.push_back(tmp_tb);

  std::vector< std::vector< double > > cmp_arr_M;
  std::vector<double> tmp;
  tmp = {0, -Inf, -Inf, -Inf, -Inf, -Inf}; cmp_arr_M.push_back(tmp);
  tmp = {-Inf, -2, -2, 10, -2, 10}; cmp_arr_M.push_back(tmp);
  tmp = {-Inf, 10, -4, -4, 8, -4}; cmp_arr_M.push_back(tmp);
  tmp = {-Inf, -2, 20, -6, -6, 6}; cmp_arr_M.push_back(tmp);
  tmp = {-Inf, -2, -4, 18, 8, -8}; cmp_arr_M.push_back(tmp);

  std::vector< std::vector<double> > cmp_arr_A;
  tmp = {-Inf, -Inf, -Inf, -Inf, -Inf, -Inf}; cmp_arr_A.push_back(tmp);
  tmp = {0, -22, -22, -22, -22, -22}; cmp_arr_A.push_back(tmp);
  tmp = {0, -24, -24, -12, -24, -12}; cmp_arr_A.push_back(tmp);
  tmp = {0, -12, -26, -19, -14, -19}; cmp_arr_A.push_back(tmp);
  tmp = {0, -19, -2, -24, -21, -16}; cmp_arr_A.push_back(tmp);

  std::vector< std::vector<double> > cmp_arr_B;
  tmp = {-Inf, 0, 0, 0, 0, 0}; cmp_arr_B.push_back(tmp);
  tmp = {-Inf, -22, -24, -24, -12, -19}; cmp_arr_B.push_back(tmp);
  tmp = {-Inf, -22, -12, -19, -26, -14}; cmp_arr_B.push_back(tmp);
  tmp = {-Inf, -22, -24, -2, -9, -16}; cmp_arr_B.push_back(tmp);
  tmp = {-Inf, -22, -24, -24, -4, -11}; cmp_arr_B.push_back(tmp);

  std::vector< std::vector<bool> > cmp_arr_Path;
  std::vector<bool> tmp_b;
  tmp_b = {0, 0, 0, 0, 0, 0}; cmp_arr_Path.push_back(tmp_b);
  tmp_b = {0, 0, 0, 0, 0, 0}; cmp_arr_Path.push_back(tmp_b);
  tmp_b = {0, 0, 0, 0, 0, 0}; cmp_arr_Path.push_back(tmp_b);
  tmp_b = {0, 0, 0, 0, 0, 0}; cmp_arr_Path.push_back(tmp_b);
  tmp_b = {0, 0, 0, 0, 0, 0}; cmp_arr_Path.push_back(tmp_b);

  // s_data
  for (int i = 0; i < 4; i++){
    for (int j = 0; j < 5; j++){
      //ASSERT(std::abs(obj.s_data[i*5+j] - s.data[i*5+j]) < 1e-06);
    }
  }
  // Traceback
  for (int i = 0; i < 15; i++){
    for (int j = 0; j < 6; j++){
      ASSERT(obj.Traceback[i*6+j] == cmp_arr_Traceback[i][j]);
    }
  }
  // M
  for (int i = 1; i < 5; i++){
    for (int j = 1; j < 6; j++){
      ASSERT(std::abs(obj.M[i*6+j] - cmp_arr_M[i][j]) < 1e-06);
    }
  }
  ASSERT(std::abs(obj.M[0] - cmp_arr_M[0][0]) < 1e-06);
  for (int j = 1; j < 6; j++){
    ASSERT(std::isinf(obj.M[0*6+j]) && std::signbit(obj.M[0*6+j]));
  }
  for (int i = 1; i < 5; i++){
    ASSERT(std::isinf(obj.M[i*6+0]) && std::signbit(obj.M[i*6+0]));
  }
  // A
  for (int i = 1; i < 5; i++){
    for (int j = 0; j < 6; j++){
      ASSERT(std::abs(obj.A[i*6+j] - cmp_arr_A[i][j]) < 1e-06);
    }
  }
  for (int j = 0; j < 6; j++){
    ASSERT(std::isinf(obj.A[0*6+j]) && std::signbit(obj.A[0*6+j]));
  }
  // B
  for (int i = 0; i < 5; i++){
    for (int j = 1; j < 6; j++){
      ASSERT(std::abs(obj.B[i*6+j] - cmp_arr_B[i][j]) < 1e-06);
    }
  }
  for (int i = 0; i < 5; i++){
    ASSERT(std::isinf(obj.B[i*6+0]) && std::signbit(obj.B[i*6+0]));
  }
  // Path
  for (int i = 0; i < 5; i++){
    for (int j = 0; j < 6; j++){
      ASSERT(obj.Path[i*6+j] == cmp_arr_Path[i][j]);
    }
  }
  // signalA_len
  ASSERT(obj.signalA_len == 4);
  // signalB_len
  ASSERT(obj.signalB_len == 5);
  // GapOpen
  ASSERT(std::abs(obj.GapOpen - 22.0) < 1e-6);
  // GapExten
  ASSERT(std::abs(obj.GapExten - 7.0) < 1e-6);
  // FreeEndGaps
  ASSERT(obj.FreeEndGaps == true);
  // indexA_aligned
  ASSERT(obj.indexA_aligned.size() == 0);
  // indexB_aligned
  ASSERT(obj.indexB_aligned.size() == 0);
  // score
  ASSERT(obj.score.size() == 0);

  //........................  CASE 2 ........................................
  obj.reset(4+1, 5+1);
  doAffineAlignment(obj, s, gapOpen, gapExten, false);

  std::vector< std::vector< TracebackType > > cmp_arr_Traceback2;
  // Traceback M
  tmp_tb = {SS, SS, SS, SS, SS, SS}; cmp_arr_Traceback2.push_back(tmp_tb);
  tmp_tb = {SS, DM, DB, DB, DB, DB}; cmp_arr_Traceback2.push_back(tmp_tb);
  tmp_tb = {SS, DA, DM, DM, DM, DM}; cmp_arr_Traceback2.push_back(tmp_tb);
  tmp_tb = {SS, DA, DM, DM, DM, DM}; cmp_arr_Traceback2.push_back(tmp_tb);
  tmp_tb = {SS, DA, DM, DM, DM, DM}; cmp_arr_Traceback2.push_back(tmp_tb);
  // Traceback A
  tmp_tb = {SS, SS, SS, SS, SS, SS}; cmp_arr_Traceback2.push_back(tmp_tb);
  tmp_tb = {TM, TB, TB, TB, TB, TB}; cmp_arr_Traceback2.push_back(tmp_tb);
  tmp_tb = {TA, TM, TM, TM, TM, TM}; cmp_arr_Traceback2.push_back(tmp_tb);
  tmp_tb = {TA, TA, TM, TM, TM, TM}; cmp_arr_Traceback2.push_back(tmp_tb);
  tmp_tb = {TA, TA, TM, TM, TM, TM}; cmp_arr_Traceback2.push_back(tmp_tb);
  // Traceback B
  tmp_tb = {SS, LM, LB, LB, LB, LB}; cmp_arr_Traceback2.push_back(tmp_tb);
  tmp_tb = {SS, LA, LM, LB, LB, LB}; cmp_arr_Traceback2.push_back(tmp_tb);
  tmp_tb = {SS, LA, LM, LM, LB, LB}; cmp_arr_Traceback2.push_back(tmp_tb);
  tmp_tb = {SS, LA, LM, LM, LM, LB}; cmp_arr_Traceback2.push_back(tmp_tb);
  tmp_tb = {SS, LA, LM, LA, LM, LM}; cmp_arr_Traceback2.push_back(tmp_tb);

  std::vector< std::vector< double > > cmp_arr_M2;
  tmp = {0, -Inf, -Inf, -Inf, -Inf, -Inf}; cmp_arr_M2.push_back(tmp);
  tmp = {-Inf, -2, -24, -19, -38, -33}; cmp_arr_M2.push_back(tmp);
  tmp = {-Inf, -12, -4, -26, -21, -40}; cmp_arr_M2.push_back(tmp);
  tmp = {-Inf, -31, -2, -6, -28, -23}; cmp_arr_M2.push_back(tmp);
  tmp = {-Inf, -38, -33, -4, 4, -30}; cmp_arr_M2.push_back(tmp);

  std::vector< std::vector<double> > cmp_arr_A2;
  tmp = {-Inf, -Inf, -Inf, -Inf, -Inf, -Inf}; cmp_arr_A2.push_back(tmp);
  tmp = {-22, -44, -51, -58, -65, -72}; cmp_arr_A2.push_back(tmp);
  tmp = {-29, -24, -46, -41, -60, -55}; cmp_arr_A2.push_back(tmp);
  tmp = {-36, -31, -26, -48, -43, -62}; cmp_arr_A2.push_back(tmp);
  tmp = {-43, -38, -24, -28, -50, -45}; cmp_arr_A2.push_back(tmp);

  std::vector< std::vector<double> > cmp_arr_B2;
  tmp = {-Inf, -22, -29, -36, -43, -50}; cmp_arr_B2.push_back(tmp);
  tmp = {-Inf, -44, -24, -31, -38, -45}; cmp_arr_B2.push_back(tmp);
  tmp = {-Inf, -51, -34, -26, -33, -40}; cmp_arr_B2.push_back(tmp);
  tmp = {-Inf, -58, -53, -24, -28, -35}; cmp_arr_B2.push_back(tmp);
  tmp = {-Inf, -65, -60, -46, -26, -18}; cmp_arr_B2.push_back(tmp);

  std::vector< std::vector<bool> > cmp_arr_Path2;
  tmp_b = {false, 0, 0, 0, 0, 0}; cmp_arr_Path2.push_back(tmp_b);
  tmp_b = {0, false, 0, 0, 0, 0}; cmp_arr_Path2.push_back(tmp_b);
  tmp_b = {0, 0, false, 0, 0, 0}; cmp_arr_Path2.push_back(tmp_b);
  tmp_b = {0, 0, 0, false, 0, 0}; cmp_arr_Path2.push_back(tmp_b);
  tmp_b = {0, 0, 0, 0, false, false}; cmp_arr_Path2.push_back(tmp_b);

  // s_data
  for (int i = 0; i < 4; i++){
    for (int j = 0; j < 5; j++){
      //ASSERT(std::abs(obj.s_data[i*5+j] - s.data[i*5+j]) < 1e-06);
    }
  }
  // Traceback
  for (int i = 0; i < 15; i++){
    for (int j = 0; j < 6; j++){
      ASSERT(obj.Traceback[i*6+j] == cmp_arr_Traceback2[i][j]);
    }
  }
  // M
  for (int i = 1; i < 5; i++){
    for (int j = 1; j < 6; j++){
      ASSERT(std::abs(obj.M[i*6+j] - cmp_arr_M2[i][j]) < 1e-06);
    }
  }
  ASSERT(std::abs(obj.M[0] - cmp_arr_M2[0][0]) < 1e-06);
  for (int j = 1; j < 6; j++){
    ASSERT(std::isinf(obj.M[0*6+j]) && std::signbit(obj.M[0*6+j]));
  }
  for (int i = 1; i < 5; i++){
    ASSERT(std::isinf(obj.M[i*6+0]) && std::signbit(obj.M[i*6+0]));
  }
  // A
  for (int i = 1; i < 5; i++){
    for (int j = 0; j < 6; j++){
      ASSERT(std::abs(obj.A[i*6+j] - cmp_arr_A2[i][j]) < 1e-06);
    }
  }
  for (int j = 0; j < 6; j++){
    ASSERT(std::isinf(obj.A[0*6+j]) && std::signbit(obj.A[0*6+j]));
  }
  // B
  for (int i = 0; i < 5; i++){
    for (int j = 1; j < 6; j++){
      ASSERT(std::abs(obj.B[i*6+j] - cmp_arr_B2[i][j]) < 1e-06);
    }
  }
  for (int i = 0; i < 5; i++){
    ASSERT(std::isinf(obj.B[i*6+0]) && std::signbit(obj.B[i*6+0]));
  }
  // Path
  for (int i = 0; i < 5; i++){
    for (int j = 0; j < 6; j++){
      ASSERT(obj.Path[i*6+j] == cmp_arr_Path2[i][j]);
    }
  }
  // signalA_len
  ASSERT(obj.signalA_len == 4);
  // signalB_len
  ASSERT(obj.signalB_len == 5);
  // GapOpen
  ASSERT(std::abs(obj.GapOpen - 22.0) < 1e-6);
  // GapExten
  ASSERT(std::abs(obj.GapExten - 7.0) < 1e-6);
  // FreeEndGaps
  ASSERT(obj.FreeEndGaps == false);
  // indexA_aligned
  ASSERT(obj.indexA_aligned.size() == 0);
  // indexB_aligned
  ASSERT(obj.indexB_aligned.size() == 0);
  // score
  ASSERT(obj.score.size() == 0);

  //........................  CASE 3 ........................................
  s.data = {0.0, 0.0, 0.0, 0.0, 0.0,
            0.0, 0.0, 0.0, 0.0, 0.0,
            0.0, 0.0, 0.0, 0.0, 0.0,
            0.0, 0.0, 0.0, 0.0, 0.0};
  s.n_row = 4;
  s.n_col = 5;
  obj.reset(4+1, 5+1);
  doAffineAlignment(obj, s, 22, 7, false);

  std::vector< std::vector< TracebackType > > cmp_arr_Traceback3;
  // Traceback M
  tmp_tb = {SS, SS, SS, SS, SS, SS}; cmp_arr_Traceback3.push_back(tmp_tb);
  tmp_tb = {SS, DM, DB, DB, DB, DB}; cmp_arr_Traceback3.push_back(tmp_tb);
  tmp_tb = {SS, DA, DM, DM, DM, DM}; cmp_arr_Traceback3.push_back(tmp_tb);
  tmp_tb = {SS, DA, DM, DM, DM, DM}; cmp_arr_Traceback3.push_back(tmp_tb);
  tmp_tb = {SS, DA, DM, DM, DM, DM}; cmp_arr_Traceback3.push_back(tmp_tb);
  // Traceback A
  tmp_tb = {SS, SS, SS, SS, SS, SS}; cmp_arr_Traceback3.push_back(tmp_tb);
  tmp_tb = {TM, TB, TB, TB, TB, TB}; cmp_arr_Traceback3.push_back(tmp_tb);
  tmp_tb = {TA, TM, TM, TM, TM, TM}; cmp_arr_Traceback3.push_back(tmp_tb);
  tmp_tb = {TA, TA, TM, TM, TM, TM}; cmp_arr_Traceback3.push_back(tmp_tb);
  tmp_tb = {TA, TA, TA, TM, TM, TM}; cmp_arr_Traceback3.push_back(tmp_tb);
  // Traceback B
  tmp_tb = {SS, LM, LB, LB, LB, LB}; cmp_arr_Traceback3.push_back(tmp_tb);
  tmp_tb = {SS, LA, LM, LB, LB, LB}; cmp_arr_Traceback3.push_back(tmp_tb);
  tmp_tb = {SS, LA, LM, LM, LB, LB}; cmp_arr_Traceback3.push_back(tmp_tb);
  tmp_tb = {SS, LA, LM, LM, LM, LB}; cmp_arr_Traceback3.push_back(tmp_tb);
  tmp_tb = {SS, LA, LM, LM, LM, LM}; cmp_arr_Traceback3.push_back(tmp_tb);

  std::vector< std::vector< double > > cmp_arr_M3;
  tmp = {0, -Inf, -Inf, -Inf, -Inf, -Inf}; cmp_arr_M3.push_back(tmp);
  tmp = {-Inf, 0, -22, -29, -36, -43}; cmp_arr_M3.push_back(tmp);
  tmp = {-Inf, -22, 0, -22, -29, -36}; cmp_arr_M3.push_back(tmp);
  tmp = {-Inf, -29, -22, 0, -22, -29}; cmp_arr_M3.push_back(tmp);
  tmp = {-Inf, -36, -29, -22, 0, -22}; cmp_arr_M3.push_back(tmp);

  std::vector< std::vector<double> > cmp_arr_A3;
  tmp = {-Inf, -Inf, -Inf, -Inf, -Inf, -Inf}; cmp_arr_A3.push_back(tmp);
  tmp = {-22, -44, -51, -58, -65, -72}; cmp_arr_A3.push_back(tmp);
  tmp = {-29, -22, -44, -51, -58, -65}; cmp_arr_A3.push_back(tmp);
  tmp = {-36, -29, -22, -44, -51, -58}; cmp_arr_A3.push_back(tmp);
  tmp = {-43, -36, -29, -22, -44, -51}; cmp_arr_A3.push_back(tmp);

  std::vector< std::vector<double> > cmp_arr_B3;
  tmp = {-Inf, -22, -29, -36, -43, -50}; cmp_arr_B3.push_back(tmp);
  tmp = {-Inf, -44, -22, -29, -36, -43}; cmp_arr_B3.push_back(tmp);
  tmp = {-Inf, -51, -44, -22, -29, -36}; cmp_arr_B3.push_back(tmp);
  tmp = {-Inf, -58, -51, -44, -22, -29}; cmp_arr_B3.push_back(tmp);
  tmp = {-Inf, -65, -58, -51, -44, -22}; cmp_arr_B3.push_back(tmp);

  std::vector< std::vector<bool> > cmp_arr_Path3;
  tmp_b = {false, false, 0, 0, 0, 0}; cmp_arr_Path3.push_back(tmp_b);
  tmp_b = {0, false, false, 0, 0, 0}; cmp_arr_Path3.push_back(tmp_b);
  tmp_b = {0, 0, false, false, 0, 0}; cmp_arr_Path3.push_back(tmp_b);
  tmp_b = {0, 0, 0, false, false, 0}; cmp_arr_Path3.push_back(tmp_b);
  tmp_b = {0, 0, 0, 0, false, false}; cmp_arr_Path3.push_back(tmp_b);

  // s_data
  for (int i = 0; i < 4; i++){
    for (int j = 0; j < 5; j++){
      //ASSERT(std::abs(obj.s_data[i*5+j] - s.data[i*5+j]) < 1e-06);
    }
  }
  // Traceback
  for (int i = 0; i < 15; i++){
    for (int j = 0; j < 6; j++){
      ASSERT(obj.Traceback[i*6+j] == cmp_arr_Traceback3[i][j]);
    }
  }
  // M
  for (int i = 1; i < 5; i++){
    for (int j = 1; j < 6; j++){
      ASSERT(std::abs(obj.M[i*6+j] - cmp_arr_M3[i][j]) < 1e-06);
    }
  }
  ASSERT(std::abs(obj.M[0] - cmp_arr_M3[0][0]) < 1e-06);
  for (int j = 1; j < 6; j++){
    ASSERT(std::isinf(obj.M[0*6+j]) && std::signbit(obj.M[0*6+j]));
  }
  for (int i = 1; i < 5; i++){
    ASSERT(std::isinf(obj.M[i*6+0]) && std::signbit(obj.M[i*6+0]));
  }
  // A
  for (int i = 1; i < 5; i++){
    for (int j = 0; j < 6; j++){
      ASSERT(std::abs(obj.A[i*6+j] - cmp_arr_A3[i][j]) < 1e-06);
    }
  }
  for (int j = 0; j < 6; j++){
    ASSERT(std::isinf(obj.A[0*6+j]) && std::signbit(obj.A[0*6+j]));
  }
  // B
  for (int i = 0; i < 5; i++){
    for (int j = 1; j < 6; j++){
      ASSERT(std::abs(obj.B[i*6+j] - cmp_arr_B3[i][j]) < 1e-06);
    }
  }
  for (int i = 0; i < 5; i++){
    ASSERT(std::isinf(obj.B[i*6+0]) && std::signbit(obj.B[i*6+0]));
  }
  // Path
  for (int i = 0; i < 5; i++){
    for (int j = 0; j < 6; j++){
      ASSERT(obj.Path[i*6+j] == cmp_arr_Path3[i][j]);
    }
  }
  // signalA_len
  ASSERT(obj.signalA_len == 4);
  // signalB_len
  ASSERT(obj.signalB_len == 5);
  // GapOpen
  ASSERT(std::abs(obj.GapOpen - 22.0) < 1e-6);
  // GapExten
  ASSERT(std::abs(obj.GapExten - 7.0) < 1e-6);
  // FreeEndGaps
  ASSERT(obj.FreeEndGaps == false);
  // indexA_aligned
  ASSERT(obj.indexA_aligned.size() == 0);
  // indexB_aligned
  ASSERT(obj.indexB_aligned.size() == 0);
  // score
  ASSERT(obj.score.size() == 0);

  //........................  CASE 4 ........................................
  s.data = {0.0, 0.0, 0.0, 0.0, 0.0,
            0.0, 0.0, 0.0, 0.0, 0.0,
            0.0, 0.0, 0.0, 0.0, 0.0,
            0.0, 0.0, 0.0, 0.0, 0.0};
  s.n_row = 4;
  s.n_col = 5;
  obj.reset(4+1, 5+1);
  doAffineAlignment(obj, s, 0, 0, true);

  std::vector< std::vector< TracebackType > > cmp_arr_Traceback4;
  // Traceback M
  tmp_tb = {SS, SS, SS, SS, SS, SS}; cmp_arr_Traceback4.push_back(tmp_tb);
  tmp_tb = {SS, DM, DB, DB, DB, DB}; cmp_arr_Traceback4.push_back(tmp_tb);
  tmp_tb = {SS, DA, DM, DM, DM, DM}; cmp_arr_Traceback4.push_back(tmp_tb);
  tmp_tb = {SS, DA, DM, DM, DM, DM}; cmp_arr_Traceback4.push_back(tmp_tb);
  tmp_tb = {SS, DA, DM, DM, DM, DM}; cmp_arr_Traceback4.push_back(tmp_tb);
  // Traceback A
  tmp_tb = {SS, SS, SS, SS, SS, SS}; cmp_arr_Traceback4.push_back(tmp_tb);
  tmp_tb = {TM, TB, TB, TB, TB, TB}; cmp_arr_Traceback4.push_back(tmp_tb);
  tmp_tb = {TA, TM, TM, TM, TM, TM}; cmp_arr_Traceback4.push_back(tmp_tb);
  tmp_tb = {TA, TM, TM, TM, TM, TM}; cmp_arr_Traceback4.push_back(tmp_tb);
  tmp_tb = {TA, TM, TM, TM, TM, TM}; cmp_arr_Traceback4.push_back(tmp_tb);
  // Traceback B
  tmp_tb = {SS, LM, LB, LB, LB, LB}; cmp_arr_Traceback4.push_back(tmp_tb);
  tmp_tb = {SS, LA, LM, LM, LM, LM}; cmp_arr_Traceback4.push_back(tmp_tb);
  tmp_tb = {SS, LA, LM, LM, LM, LM}; cmp_arr_Traceback4.push_back(tmp_tb);
  tmp_tb = {SS, LA, LM, LM, LM, LM}; cmp_arr_Traceback4.push_back(tmp_tb);
  tmp_tb = {SS, LA, LM, LM, LM, LM}; cmp_arr_Traceback4.push_back(tmp_tb);

  std::vector< std::vector< double > > cmp_arr_M4;
  tmp = {0, -Inf, -Inf, -Inf, -Inf, -Inf}; cmp_arr_M4.push_back(tmp);
  tmp = {-Inf, 0, 0, 0, 0, 0}; cmp_arr_M4.push_back(tmp);
  tmp = {-Inf, 0, 0, 0, 0, 0}; cmp_arr_M4.push_back(tmp);
  tmp = {-Inf, 0, 0, 0, 0, 0}; cmp_arr_M4.push_back(tmp);
  tmp = {-Inf, 0, 0, 0, 0, 0}; cmp_arr_M4.push_back(tmp);

  std::vector< std::vector<double> > cmp_arr_A4;
  tmp = {-Inf, -Inf, -Inf, -Inf, -Inf, -Inf}; cmp_arr_A4.push_back(tmp);
  tmp = {0, 0, 0, 0, 0, 0}; cmp_arr_A4.push_back(tmp);
  tmp = {0, 0, 0, 0, 0, 0}; cmp_arr_A4.push_back(tmp);
  tmp = {0, 0, 0, 0, 0, 0}; cmp_arr_A4.push_back(tmp);
  tmp = {0, 0, 0, 0, 0, 0}; cmp_arr_A4.push_back(tmp);

  std::vector< std::vector<double> > cmp_arr_B4;
  tmp = {-Inf, 0, 0, 0, 0, 0}; cmp_arr_B4.push_back(tmp);
  tmp = {-Inf, 0, 0, 0, 0, 0}; cmp_arr_B4.push_back(tmp);
  tmp = {-Inf, 0, 0, 0, 0, 0}; cmp_arr_B4.push_back(tmp);
  tmp = {-Inf, 0, 0, 0, 0, 0}; cmp_arr_B4.push_back(tmp);
  tmp = {-Inf, 0, 0, 0, 0, 0}; cmp_arr_B4.push_back(tmp);

  std::vector< std::vector<bool> > cmp_arr_Path4;
  tmp_b = {false, false, 0, 0, 0, 0}; cmp_arr_Path4.push_back(tmp_b);
  tmp_b = {0, false, false, 0, 0, 0}; cmp_arr_Path4.push_back(tmp_b);
  tmp_b = {0, 0, false, false, 0, 0}; cmp_arr_Path4.push_back(tmp_b);
  tmp_b = {0, 0, 0, false, false, 0}; cmp_arr_Path4.push_back(tmp_b);
  tmp_b = {0, 0, 0, 0, false, false}; cmp_arr_Path4.push_back(tmp_b);

  // s_data
  for (int i = 0; i < 4; i++){
    for (int j = 0; j < 5; j++){
      //ASSERT(std::abs(obj.s_data[i*5+j] - s.data[i*5+j]) < 1e-06);
    }
  }
  // Traceback
  for (int i = 0; i < 15; i++){
    for (int j = 0; j < 6; j++){
      ASSERT(obj.Traceback[i*6+j] == cmp_arr_Traceback4[i][j]);
    }
  }
  // M
  for (int i = 1; i < 5; i++){
    for (int j = 1; j < 6; j++){
      ASSERT(std::abs(obj.M[i*6+j] - cmp_arr_M4[i][j]) < 1e-06);
    }
  }
  ASSERT(std::abs(obj.M[0] - cmp_arr_M4[0][0]) < 1e-06);
  for (int j = 1; j < 6; j++){
    ASSERT(std::isinf(obj.M[0*6+j]) && std::signbit(obj.M[0*6+j]));
  }
  for (int i = 1; i < 5; i++){
    ASSERT(std::isinf(obj.M[i*6+0]) && std::signbit(obj.M[i*6+0]));
  }
  // A
  for (int i = 1; i < 5; i++){
    for (int j = 0; j < 6; j++){
      ASSERT(std::abs(obj.A[i*6+j] - cmp_arr_A4[i][j]) < 1e-06);
    }
  }
  for (int j = 0; j < 6; j++){
    ASSERT(std::isinf(obj.A[0*6+j]) && std::signbit(obj.A[0*6+j]));
  }
  // B
  for (int i = 0; i < 5; i++){
    for (int j = 1; j < 6; j++){
      ASSERT(std::abs(obj.B[i*6+j] - cmp_arr_B4[i][j]) < 1e-06);
    }
  }
  for (int i = 0; i < 5; i++){
    ASSERT(std::isinf(obj.B[i*6+0]) && std::signbit(obj.B[i*6+0]));
  }
  // Path
  for (int i = 0; i < 5; i++){
    for (int j = 0; j < 6; j++){
      ASSERT(obj.Path[i*6+j] == cmp_arr_Path4[i][j]);
    }
  }
  // signalA_len
  ASSERT(obj.signalA_len == 4);
  // signalB_len
  ASSERT(obj.signalB_len == 5);
  // GapOpen
  ASSERT(std::abs(obj.GapOpen - 0.0) < 1e-6);
  // GapExten
  ASSERT(std::abs(obj.GapExten - 0.0) < 1e-6);
  // FreeEndGaps
  ASSERT(obj.FreeEndGaps == true);
  // indexA_aligned
  ASSERT(obj.indexA_aligned.size() == 0);
  // indexB_aligned
  ASSERT(obj.indexB_aligned.size() == 0);
  // score
  ASSERT(obj.score.size() == 0);
}

void test_getAffineAlignedIndices(){
  double Inf = std::numeric_limits<double>::infinity();
  AffineAlignObj obj(4+1, 5+1);
  SimMatrix s;
  s.data = {-2, -2, 10, -2, 10,
            10, -2, -2, -2, -2,
            -2, 10, -2, -2, -2,
            -2, -2, -2, 10, -2};
  s.n_row = 4;
  s.n_col = 5;
  double gapOpen = 22.0, gapExten = 7.0;

  std::vector< std::vector< TracebackType > > cmp_arr_Traceback;
  std::vector<TracebackType> tmp_tb;
  // Traceback M
  tmp_tb = {SS, SS, SS, SS, SS, SS}; cmp_arr_Traceback.push_back(tmp_tb);
  tmp_tb = {SS, DM, DB, DB, DB, DB}; cmp_arr_Traceback.push_back(tmp_tb);
  tmp_tb = {SS, DA, DM, DM, DM, DM}; cmp_arr_Traceback.push_back(tmp_tb);
  tmp_tb = {SS, DA, DM, DM, DM, DM}; cmp_arr_Traceback.push_back(tmp_tb);
  tmp_tb = {SS, DA, DM, DM, DB, DM}; cmp_arr_Traceback.push_back(tmp_tb);
  // Traceback A
  tmp_tb = {SS, SS, SS, SS, SS, SS}; cmp_arr_Traceback.push_back(tmp_tb);
  tmp_tb = {TM, TB, TB, TB, TB, TB}; cmp_arr_Traceback.push_back(tmp_tb);
  tmp_tb = {TA, TM, TM, TM, TM, TM}; cmp_arr_Traceback.push_back(tmp_tb);
  tmp_tb = {TA, TM, TM, TA, TM, TA}; cmp_arr_Traceback.push_back(tmp_tb);
  tmp_tb = {TA, TA, TM, TB, TA, TM}; cmp_arr_Traceback.push_back(tmp_tb);
  // Traceback B
  tmp_tb = {SS, LM, LB, LB, LB, LB}; cmp_arr_Traceback.push_back(tmp_tb);
  tmp_tb = {SS, LA, LM, LM, LM, LB}; cmp_arr_Traceback.push_back(tmp_tb);
  tmp_tb = {SS, LA, LM, LB, LM, LM}; cmp_arr_Traceback.push_back(tmp_tb);
  tmp_tb = {SS, LA, LM, LM, LB, LB}; cmp_arr_Traceback.push_back(tmp_tb);
  tmp_tb = {SS, LA, LM, LA, LM, LB}; cmp_arr_Traceback.push_back(tmp_tb);
  obj.Traceback = new TracebackType[3*5*6]; // This causes memory leak. Should be fixed.
  // Can't use initializer list, because of certain issues.
  for(int i = 0; i < 15; i++){
    for(int j = 0; j < 6; j++){
      obj.Traceback[i*6+j] = cmp_arr_Traceback[i][j];
    }
  }

  std::vector< std::vector< double > > cmp_arr_M;
  std::vector<double> tmp;
  tmp = {0, -Inf, -Inf, -Inf, -Inf, -Inf}; cmp_arr_M.push_back(tmp);
  tmp = {-Inf, -2, -2, 10, -2, 10}; cmp_arr_M.push_back(tmp);
  tmp = {-Inf, 10, -4, -4, 8, -4}; cmp_arr_M.push_back(tmp);
  tmp = {-Inf, -2, 20, -6, -6, 6}; cmp_arr_M.push_back(tmp);
  tmp = {-Inf, -2, -4, 18, 8, -8}; cmp_arr_M.push_back(tmp);
  obj.M = new double[5*6]; // This causes memory leak. Should be fixed.
  // Can't use initializer list, because of certain issues.
  for(int i = 0; i < 5; i++){
    for(int j = 0; j < 6; j++){
      obj.M[i*6+j] = cmp_arr_M[i][j];
    }
  }

  std::vector< std::vector<double> > cmp_arr_A;
  tmp = {-Inf, -Inf, -Inf, -Inf, -Inf, -Inf}; cmp_arr_A.push_back(tmp);
  tmp = {0, -22, -22, -22, -22, -22}; cmp_arr_A.push_back(tmp);
  tmp = {0, -24, -24, -12, -24, -12}; cmp_arr_A.push_back(tmp);
  tmp = {0, -12, -26, -19, -14, -19}; cmp_arr_A.push_back(tmp);
  tmp = {0, -19, -2, -24, -21, -16}; cmp_arr_A.push_back(tmp);
  obj.A = new double[5*6]; // This causes memory leak. Should be fixed.
  // Can't use initializer list, because of certain issues.
  for(int i = 0; i < 5; i++){
    for(int j = 0; j < 6; j++){
      obj.A[i*6+j] = cmp_arr_A[i][j];
    }
  }

  std::vector< std::vector<double> > cmp_arr_B;
  tmp = {-Inf, 0, 0, 0, 0, 0}; cmp_arr_B.push_back(tmp);
  tmp = {-Inf, -22, -24, -24, -12, -19}; cmp_arr_B.push_back(tmp);
  tmp = {-Inf, -22, -12, -19, -26, -14}; cmp_arr_B.push_back(tmp);
  tmp = {-Inf, -22, -24, -2, -9, -16}; cmp_arr_B.push_back(tmp);
  tmp = {-Inf, -22, -24, -24, -4, -11}; cmp_arr_B.push_back(tmp);
  obj.B = new double[5*6]; // This causes memory leak. Should be fixed.
  // Can't use initializer list, because of certain issues.
  for(int i = 0; i < 5; i++){
    for(int j = 0; j < 6; j++){
      obj.B[i*6+j] = cmp_arr_B[i][j];
    }
  }

  obj.signalA_len = 4;
  obj.signalB_len = 5;
  obj.GapOpen = 22.0;
  obj.GapExten = 7.0;
  obj.FreeEndGaps = true;

  getAffineAlignedIndices(obj);

  std::vector< std::vector<bool> > cmp_arr_Path;
  std::vector<bool> tmp_b;
  tmp_b = {1, 0, 0, 0, 0, 0}; cmp_arr_Path.push_back(tmp_b);
  tmp_b = {1, 0, 0, 0, 0, 0}; cmp_arr_Path.push_back(tmp_b);
  tmp_b = {0, 1, 0, 0, 0, 0}; cmp_arr_Path.push_back(tmp_b);
  tmp_b = {0, 0, 1, 0, 0, 0}; cmp_arr_Path.push_back(tmp_b);
  tmp_b = {0, 0, 0, 1, 1, 1}; cmp_arr_Path.push_back(tmp_b);
  std::vector<int> cmp_indexA_aligned = {1, 2, 3, 4, 0, 0};
  std::vector<int> cmp_indexB_aligned = {0, 1, 2, 3, 4, 5};
  std::vector<double> cmp_score = {0, 10, 20, 18, 18, 18};

  // s_data
  for (int i = 0; i < 4; i++){
    for (int j = 0; j < 5; j++){
      //ASSERT(std::abs(obj.s_data[i*5+j] - s.data[i*5+j]) < 1e-06);
    }
  }
  // Traceback
  for (int i = 0; i < 15; i++){
    for (int j = 0; j < 6; j++){
      ASSERT(obj.Traceback[i*6+j] == cmp_arr_Traceback[i][j]);
    }
  }
  // M
  for (int i = 1; i < 5; i++){
    for (int j = 1; j < 6; j++){
      ASSERT(std::abs(obj.M[i*6+j] - cmp_arr_M[i][j]) < 1e-06);
    }
  }
  ASSERT(std::abs(obj.M[0] - cmp_arr_M[0][0]) < 1e-06);
  for (int j = 1; j < 6; j++){
    ASSERT(std::isinf(obj.M[0*6+j]) && std::signbit(obj.M[0*6+j]));
  }
  for (int i = 1; i < 5; i++){
    ASSERT(std::isinf(obj.M[i*6+0]) && std::signbit(obj.M[i*6+0]));
  }
  // A
  for (int i = 1; i < 5; i++){
    for (int j = 0; j < 6; j++){
      ASSERT(std::abs(obj.A[i*6+j] - cmp_arr_A[i][j]) < 1e-06);
    }
  }
  for (int j = 0; j < 6; j++){
    ASSERT(std::isinf(obj.A[0*6+j]) && std::signbit(obj.A[0*6+j]));
  }
  // B
  for (int i = 0; i < 5; i++){
    for (int j = 1; j < 6; j++){
      ASSERT(std::abs(obj.B[i*6+j] - cmp_arr_B[i][j]) < 1e-06);
    }
  }
  for (int i = 0; i < 5; i++){
    ASSERT(std::isinf(obj.B[i*6+0]) && std::signbit(obj.B[i*6+0]));
  }
  // Path
  for (int i = 0; i < 5; i++){
    for (int j = 0; j < 6; j++){
      ASSERT(obj.Path[i*6+j] == cmp_arr_Path[i][j]);
    }
  }
  // signalA_len
  ASSERT(obj.signalA_len == 4);
  // signalB_len
  ASSERT(obj.signalB_len == 5);
  // GapOpen
  ASSERT(std::abs(obj.GapOpen - 22.0) < 1e-6);
  // GapExten
  ASSERT(std::abs(obj.GapExten - 7.0) < 1e-6);
  // FreeEndGaps
  ASSERT(obj.FreeEndGaps == true);
  // indexA_aligned
  for(int i = 0; i < obj.indexA_aligned.size(); i++){
    ASSERT(obj.indexA_aligned[i] == cmp_indexA_aligned[i]);
  }
  // indexB_aligned
  for(int i = 0; i < obj.indexB_aligned.size(); i++){
    ASSERT(obj.indexB_aligned[i] == cmp_indexB_aligned[i]);
  }
  // score
  for(int i = 0; i < obj.score.size(); i++){
    ASSERT(std::abs(obj.score[i] - cmp_score[i]) < 1e-06);
  }

  //........................  CASE 2 ........................................
  obj.reset(4+1, 5+1);

  std::vector< std::vector< TracebackType > > cmp_arr_Traceback2;
  // Traceback M
  tmp_tb = {SS, SS, SS, SS, SS, SS}; cmp_arr_Traceback2.push_back(tmp_tb);
  tmp_tb = {SS, DM, DB, DB, DB, DB}; cmp_arr_Traceback2.push_back(tmp_tb);
  tmp_tb = {SS, DA, DM, DM, DM, DM}; cmp_arr_Traceback2.push_back(tmp_tb);
  tmp_tb = {SS, DA, DM, DM, DM, DM}; cmp_arr_Traceback2.push_back(tmp_tb);
  tmp_tb = {SS, DA, DM, DM, DM, DM}; cmp_arr_Traceback2.push_back(tmp_tb);
  // Traceback A
  tmp_tb = {SS, SS, SS, SS, SS, SS}; cmp_arr_Traceback2.push_back(tmp_tb);
  tmp_tb = {TM, TB, TB, TB, TB, TB}; cmp_arr_Traceback2.push_back(tmp_tb);
  tmp_tb = {TA, TM, TM, TM, TM, TM}; cmp_arr_Traceback2.push_back(tmp_tb);
  tmp_tb = {TA, TA, TM, TM, TM, TM}; cmp_arr_Traceback2.push_back(tmp_tb);
  tmp_tb = {TA, TA, TM, TM, TM, TM}; cmp_arr_Traceback2.push_back(tmp_tb);
  // Traceback B
  tmp_tb = {SS, LM, LB, LB, LB, LB}; cmp_arr_Traceback2.push_back(tmp_tb);
  tmp_tb = {SS, LA, LM, LB, LB, LB}; cmp_arr_Traceback2.push_back(tmp_tb);
  tmp_tb = {SS, LA, LM, LM, LB, LB}; cmp_arr_Traceback2.push_back(tmp_tb);
  tmp_tb = {SS, LA, LM, LM, LM, LB}; cmp_arr_Traceback2.push_back(tmp_tb);
  tmp_tb = {SS, LA, LM, LA, LM, LM}; cmp_arr_Traceback2.push_back(tmp_tb);
  obj.Traceback = new TracebackType[3*5*6]; // This causes memory leak. Should be fixed.
  // Can't use initializer list, because of certain issues.
  for(int i = 0; i < 15; i++){
    for(int j = 0; j < 6; j++){
      obj.Traceback[i*6+j] = cmp_arr_Traceback2[i][j];
    }
  }

  std::vector< std::vector< double > > cmp_arr_M2;
  tmp = {0, -Inf, -Inf, -Inf, -Inf, -Inf}; cmp_arr_M2.push_back(tmp);
  tmp = {-Inf, -2, -24, -19, -38, -33}; cmp_arr_M2.push_back(tmp);
  tmp = {-Inf, -12, -4, -26, -21, -40}; cmp_arr_M2.push_back(tmp);
  tmp = {-Inf, -31, -2, -6, -28, -23}; cmp_arr_M2.push_back(tmp);
  tmp = {-Inf, -38, -33, -4, 4, -30}; cmp_arr_M2.push_back(tmp);
  obj.M = new double[5*6]; // This causes memory leak. Should be fixed.
  // Can't use initializer list, because of certain issues.
  for(int i = 0; i < 5; i++){
    for(int j = 0; j < 6; j++){
      obj.M[i*6+j] = cmp_arr_M2[i][j];
    }
  }

  std::vector< std::vector<double> > cmp_arr_A2;
  tmp = {-Inf, -Inf, -Inf, -Inf, -Inf, -Inf}; cmp_arr_A2.push_back(tmp);
  tmp = {-22, -44, -51, -58, -65, -72}; cmp_arr_A2.push_back(tmp);
  tmp = {-29, -24, -46, -41, -60, -55}; cmp_arr_A2.push_back(tmp);
  tmp = {-36, -31, -26, -48, -43, -62}; cmp_arr_A2.push_back(tmp);
  tmp = {-43, -38, -24, -28, -50, -45}; cmp_arr_A2.push_back(tmp);
  obj.A = new double[5*6]; // This causes memory leak. Should be fixed.
  // Can't use initializer list, because of certain issues.
  for(int i = 0; i < 5; i++){
    for(int j = 0; j < 6; j++){
      obj.A[i*6+j] = cmp_arr_A2[i][j];
    }
  }

  std::vector< std::vector<double> > cmp_arr_B2;
  tmp = {-Inf, -22, -29, -36, -43, -50}; cmp_arr_B2.push_back(tmp);
  tmp = {-Inf, -44, -24, -31, -38, -45}; cmp_arr_B2.push_back(tmp);
  tmp = {-Inf, -51, -34, -26, -33, -40}; cmp_arr_B2.push_back(tmp);
  tmp = {-Inf, -58, -53, -24, -28, -35}; cmp_arr_B2.push_back(tmp);
  tmp = {-Inf, -65, -60, -46, -26, -18}; cmp_arr_B2.push_back(tmp);
  obj.B = new double[5*6]; // This causes memory leak. Should be fixed.
  // Can't use initializer list, because of certain issues.
  for(int i = 0; i < 5; i++){
    for(int j = 0; j < 6; j++){
      obj.B[i*6+j] = cmp_arr_B2[i][j];
    }
  }

  obj.signalA_len = 4;
  obj.signalB_len = 5;
  obj.GapOpen = 22.0;
  obj.GapExten = 7.0;
  obj.FreeEndGaps = false;

  getAffineAlignedIndices(obj);

  std::vector< std::vector<bool> > cmp_arr_Path2;
  tmp_b = {1, 0, 0, 0, 0, 0}; cmp_arr_Path2.push_back(tmp_b);
  tmp_b = {0, 1, 0, 0, 0, 0}; cmp_arr_Path2.push_back(tmp_b);
  tmp_b = {0, 0, 1, 0, 0, 0}; cmp_arr_Path2.push_back(tmp_b);
  tmp_b = {0, 0, 0, 1, 0, 0}; cmp_arr_Path2.push_back(tmp_b);
  tmp_b = {0, 0, 0, 0, 1, 1}; cmp_arr_Path2.push_back(tmp_b);
  cmp_indexA_aligned = {1, 2, 3, 4, 0};
  cmp_indexB_aligned = {1, 2, 3, 4, 5};
  cmp_score = {-2, -4, -6, 4, -18};

  // s_data
  for (int i = 0; i < 4; i++){
    for (int j = 0; j < 5; j++){
      //ASSERT(std::abs(obj.s_data[i*5+j] - s.data[i*5+j]) < 1e-06);
    }
  }
  // Traceback
  for (int i = 0; i < 15; i++){
    for (int j = 0; j < 6; j++){
      ASSERT(obj.Traceback[i*6+j] == cmp_arr_Traceback2[i][j]);
    }
  }
  // M
  for (int i = 1; i < 5; i++){
    for (int j = 1; j < 6; j++){
      ASSERT(std::abs(obj.M[i*6+j] - cmp_arr_M2[i][j]) < 1e-06);
    }
  }
  ASSERT(std::abs(obj.M[0] - cmp_arr_M2[0][0]) < 1e-06);
  for (int j = 1; j < 6; j++){
    ASSERT(std::isinf(obj.M[0*6+j]) && std::signbit(obj.M[0*6+j]));
  }
  for (int i = 1; i < 5; i++){
    ASSERT(std::isinf(obj.M[i*6+0]) && std::signbit(obj.M[i*6+0]));
  }
  // A
  for (int i = 1; i < 5; i++){
    for (int j = 0; j < 6; j++){
      ASSERT(std::abs(obj.A[i*6+j] - cmp_arr_A2[i][j]) < 1e-06);
    }
  }
  for (int j = 0; j < 6; j++){
    ASSERT(std::isinf(obj.A[0*6+j]) && std::signbit(obj.A[0*6+j]));
  }
  // B
  for (int i = 0; i < 5; i++){
    for (int j = 1; j < 6; j++){
      ASSERT(std::abs(obj.B[i*6+j] - cmp_arr_B2[i][j]) < 1e-06);
    }
  }
  for (int i = 0; i < 5; i++){
    ASSERT(std::isinf(obj.B[i*6+0]) && std::signbit(obj.B[i*6+0]));
  }
  // Path
  for (int i = 0; i < 5; i++){
    for (int j = 0; j < 6; j++){
      ASSERT(obj.Path[i*6+j] == cmp_arr_Path2[i][j]);
    }
  }
  // signalA_len
  ASSERT(obj.signalA_len == 4);
  // signalB_len
  ASSERT(obj.signalB_len == 5);
  // GapOpen
  ASSERT(std::abs(obj.GapOpen - 22.0) < 1e-6);
  // GapExten
  ASSERT(std::abs(obj.GapExten - 7.0) < 1e-6);
  // FreeEndGaps
  ASSERT(obj.FreeEndGaps == false);
  // indexA_aligned
  for(int i = 0; i < obj.indexA_aligned.size(); i++){
    ASSERT(obj.indexA_aligned[i] == cmp_indexA_aligned[i]);
  }
  // indexB_aligned
  for(int i = 0; i < obj.indexB_aligned.size(); i++){
    ASSERT(obj.indexB_aligned[i] == cmp_indexB_aligned[i]);
  }
  // score
  for(int i = 0; i < obj.score.size(); i++){
    ASSERT(std::abs(obj.score[i] - cmp_score[i]) < 1e-06);
  }

  //........................  CASE 3 ........................................
  obj.reset(4+1, 5+1);

  std::vector< std::vector< TracebackType > > cmp_arr_Traceback3;
  // Traceback M
  tmp_tb = {SS, SS, SS, SS, SS, SS}; cmp_arr_Traceback3.push_back(tmp_tb);
  tmp_tb = {SS, DM, DB, DB, DB, DB}; cmp_arr_Traceback3.push_back(tmp_tb);
  tmp_tb = {SS, DA, DM, DM, DM, DM}; cmp_arr_Traceback3.push_back(tmp_tb);
  tmp_tb = {SS, DA, DM, DM, DM, DM}; cmp_arr_Traceback3.push_back(tmp_tb);
  tmp_tb = {SS, DA, DM, DM, DM, DM}; cmp_arr_Traceback3.push_back(tmp_tb);
  // Traceback A
  tmp_tb = {SS, SS, SS, SS, SS, SS}; cmp_arr_Traceback3.push_back(tmp_tb);
  tmp_tb = {TM, TB, TB, TB, TB, TB}; cmp_arr_Traceback3.push_back(tmp_tb);
  tmp_tb = {TA, TM, TM, TM, TM, TM}; cmp_arr_Traceback3.push_back(tmp_tb);
  tmp_tb = {TA, TA, TM, TM, TM, TM}; cmp_arr_Traceback3.push_back(tmp_tb);
  tmp_tb = {TA, TA, TA, TM, TM, TM}; cmp_arr_Traceback3.push_back(tmp_tb);
  // Traceback B
  tmp_tb = {SS, LM, LB, LB, LB, LB}; cmp_arr_Traceback3.push_back(tmp_tb);
  tmp_tb = {SS, LA, LM, LB, LB, LB}; cmp_arr_Traceback3.push_back(tmp_tb);
  tmp_tb = {SS, LA, LM, LM, LB, LB}; cmp_arr_Traceback3.push_back(tmp_tb);
  tmp_tb = {SS, LA, LM, LM, LM, LB}; cmp_arr_Traceback3.push_back(tmp_tb);
  tmp_tb = {SS, LA, LM, LM, LM, LM}; cmp_arr_Traceback3.push_back(tmp_tb);
  obj.Traceback = new TracebackType[3*5*6]; // This causes memory leak. Should be fixed.
  // Can't use initializer list, because of certain issues.
  for(int i = 0; i < 15; i++){
    for(int j = 0; j < 6; j++){
      obj.Traceback[i*6+j] = cmp_arr_Traceback3[i][j];
    }
  }

  std::vector< std::vector< double > > cmp_arr_M3;
  tmp = {0, -Inf, -Inf, -Inf, -Inf, -Inf}; cmp_arr_M3.push_back(tmp);
  tmp = {-Inf, 0, -22, -29, -36, -43}; cmp_arr_M3.push_back(tmp);
  tmp = {-Inf, -22, 0, -22, -29, -36}; cmp_arr_M3.push_back(tmp);
  tmp = {-Inf, -29, -22, 0, -22, -29}; cmp_arr_M3.push_back(tmp);
  tmp = {-Inf, -36, -29, -22, 0, -22}; cmp_arr_M3.push_back(tmp);
  obj.M = new double[5*6]; // This causes memory leak. Should be fixed.
  // Can't use initializer list, because of certain issues.
  for(int i = 0; i < 5; i++){
    for(int j = 0; j < 6; j++){
      obj.M[i*6+j] = cmp_arr_M3[i][j];
    }
  }

  std::vector< std::vector<double> > cmp_arr_A3;
  tmp = {-Inf, -Inf, -Inf, -Inf, -Inf, -Inf}; cmp_arr_A3.push_back(tmp);
  tmp = {-22, -44, -51, -58, -65, -72}; cmp_arr_A3.push_back(tmp);
  tmp = {-29, -22, -44, -51, -58, -65}; cmp_arr_A3.push_back(tmp);
  tmp = {-36, -29, -22, -44, -51, -58}; cmp_arr_A3.push_back(tmp);
  tmp = {-43, -36, -29, -22, -44, -51}; cmp_arr_A3.push_back(tmp);
  obj.A = new double[5*6]; // This causes memory leak. Should be fixed.
  // Can't use initializer list, because of certain issues.
  for(int i = 0; i < 5; i++){
    for(int j = 0; j < 6; j++){
      obj.A[i*6+j] = cmp_arr_A3[i][j];
    }
  }

  std::vector< std::vector<double> > cmp_arr_B3;
  tmp = {-Inf, -22, -29, -36, -43, -50}; cmp_arr_B3.push_back(tmp);
  tmp = {-Inf, -44, -22, -29, -36, -43}; cmp_arr_B3.push_back(tmp);
  tmp = {-Inf, -51, -44, -22, -29, -36}; cmp_arr_B3.push_back(tmp);
  tmp = {-Inf, -58, -51, -44, -22, -29}; cmp_arr_B3.push_back(tmp);
  tmp = {-Inf, -65, -58, -51, -44, -22}; cmp_arr_B3.push_back(tmp);
  obj.B = new double[5*6]; // This causes memory leak. Should be fixed.
  // Can't use initializer list, because of certain issues.
  for(int i = 0; i < 5; i++){
    for(int j = 0; j < 6; j++){
      obj.B[i*6+j] = cmp_arr_B3[i][j];
    }
  }

  obj.signalA_len = 4;
  obj.signalB_len = 5;
  obj.GapOpen = 22.0;
  obj.GapExten = 7.0;
  obj.FreeEndGaps = false;

  getAffineAlignedIndices(obj);

  std::vector< std::vector<bool> > cmp_arr_Path3;
  tmp_b = {1, 1, 0, 0, 0, 0}; cmp_arr_Path3.push_back(tmp_b);
  tmp_b = {0, 0, 1, 0, 0, 0}; cmp_arr_Path3.push_back(tmp_b);
  tmp_b = {0, 0, 0, 1, 0, 0}; cmp_arr_Path3.push_back(tmp_b);
  tmp_b = {0, 0, 0, 0, 1, 0}; cmp_arr_Path3.push_back(tmp_b);
  tmp_b = {0, 0, 0, 0, 0, 1}; cmp_arr_Path3.push_back(tmp_b);
  cmp_indexA_aligned = {0, 1, 2, 3, 4};
  cmp_indexB_aligned = {1, 2, 3, 4, 5};
  cmp_score = {-22, -22, -22, -22, -22};

  // s_data
  for (int i = 0; i < 4; i++){
    for (int j = 0; j < 5; j++){
      //ASSERT(std::abs(obj.s_data[i*5+j] - s.data[i*5+j]) < 1e-06);
    }
  }
  // Traceback
  for (int i = 0; i < 15; i++){
    for (int j = 0; j < 6; j++){
      ASSERT(obj.Traceback[i*6+j] == cmp_arr_Traceback3[i][j]);
    }
  }
  // M
  for (int i = 1; i < 5; i++){
    for (int j = 1; j < 6; j++){
      ASSERT(std::abs(obj.M[i*6+j] - cmp_arr_M3[i][j]) < 1e-06);
    }
  }
  ASSERT(std::abs(obj.M[0] - cmp_arr_M3[0][0]) < 1e-06);
  for (int j = 1; j < 6; j++){
    ASSERT(std::isinf(obj.M[0*6+j]) && std::signbit(obj.M[0*6+j]));
  }
  for (int i = 1; i < 5; i++){
    ASSERT(std::isinf(obj.M[i*6+0]) && std::signbit(obj.M[i*6+0]));
  }
  // A
  for (int i = 1; i < 5; i++){
    for (int j = 0; j < 6; j++){
      ASSERT(std::abs(obj.A[i*6+j] - cmp_arr_A3[i][j]) < 1e-06);
    }
  }
  for (int j = 0; j < 6; j++){
    ASSERT(std::isinf(obj.A[0*6+j]) && std::signbit(obj.A[0*6+j]));
  }
  // B
  for (int i = 0; i < 5; i++){
    for (int j = 1; j < 6; j++){
      ASSERT(std::abs(obj.B[i*6+j] - cmp_arr_B3[i][j]) < 1e-06);
    }
  }
  for (int i = 0; i < 5; i++){
    ASSERT(std::isinf(obj.B[i*6+0]) && std::signbit(obj.B[i*6+0]));
  }
  // Path
  for (int i = 0; i < 5; i++){
    for (int j = 0; j < 6; j++){
      ASSERT(obj.Path[i*6+j] == cmp_arr_Path3[i][j]);
    }
  }
  // signalA_len
  ASSERT(obj.signalA_len == 4);
  // signalB_len
  ASSERT(obj.signalB_len == 5);
  // GapOpen
  ASSERT(std::abs(obj.GapOpen - 22.0) < 1e-6);
  // GapExten
  ASSERT(std::abs(obj.GapExten - 7.0) < 1e-6);
  // FreeEndGaps
  ASSERT(obj.FreeEndGaps == false);
  // indexA_aligned
  for(int i = 0; i < obj.indexA_aligned.size(); i++){
    ASSERT(obj.indexA_aligned[i] == cmp_indexA_aligned[i]);
  }
  // indexB_aligned
  for(int i = 0; i < obj.indexB_aligned.size(); i++){
    ASSERT(obj.indexB_aligned[i] == cmp_indexB_aligned[i]);
  }
  // score
  for(int i = 0; i < obj.score.size(); i++){
    ASSERT(std::abs(obj.score[i] - cmp_score[i]) < 1e-06);
  }

  //........................  CASE 4 ........................................
  obj.reset(4+1, 5+1);

  std::vector< std::vector< TracebackType > > cmp_arr_Traceback4;
  // Traceback M
  tmp_tb = {SS, SS, SS, SS, SS, SS}; cmp_arr_Traceback4.push_back(tmp_tb);
  tmp_tb = {SS, DM, DB, DB, DB, DB}; cmp_arr_Traceback4.push_back(tmp_tb);
  tmp_tb = {SS, DA, DM, DM, DM, DM}; cmp_arr_Traceback4.push_back(tmp_tb);
  tmp_tb = {SS, DA, DM, DM, DM, DM}; cmp_arr_Traceback4.push_back(tmp_tb);
  tmp_tb = {SS, DA, DM, DM, DM, DM}; cmp_arr_Traceback4.push_back(tmp_tb);
  // Traceback A
  tmp_tb = {SS, SS, SS, SS, SS, SS}; cmp_arr_Traceback4.push_back(tmp_tb);
  tmp_tb = {TM, TB, TB, TB, TB, TB}; cmp_arr_Traceback4.push_back(tmp_tb);
  tmp_tb = {TA, TM, TM, TM, TM, TM}; cmp_arr_Traceback4.push_back(tmp_tb);
  tmp_tb = {TA, TM, TM, TM, TM, TM}; cmp_arr_Traceback4.push_back(tmp_tb);
  tmp_tb = {TA, TM, TM, TM, TM, TM}; cmp_arr_Traceback4.push_back(tmp_tb);
  // Traceback B
  tmp_tb = {SS, LM, LB, LB, LB, LB}; cmp_arr_Traceback4.push_back(tmp_tb);
  tmp_tb = {SS, LA, LM, LM, LM, LM}; cmp_arr_Traceback4.push_back(tmp_tb);
  tmp_tb = {SS, LA, LM, LM, LM, LM}; cmp_arr_Traceback4.push_back(tmp_tb);
  tmp_tb = {SS, LA, LM, LM, LM, LM}; cmp_arr_Traceback4.push_back(tmp_tb);
  tmp_tb = {SS, LA, LM, LM, LM, LM}; cmp_arr_Traceback4.push_back(tmp_tb);
  obj.Traceback = new TracebackType[3*5*6]; // This causes memory leak. Should be fixed.
  // Can't use initializer list, because of certain issues.
  for(int i = 0; i < 15; i++){
    for(int j = 0; j < 6; j++){
      obj.Traceback[i*6+j] = cmp_arr_Traceback4[i][j];
    }
  }

  std::vector< std::vector< double > > cmp_arr_M4;
  tmp = {0, -Inf, -Inf, -Inf, -Inf, -Inf}; cmp_arr_M4.push_back(tmp);
  tmp = {-Inf, 0, 0, 0, 0, 0}; cmp_arr_M4.push_back(tmp);
  tmp = {-Inf, 0, 0, 0, 0, 0}; cmp_arr_M4.push_back(tmp);
  tmp = {-Inf, 0, 0, 0, 0, 0}; cmp_arr_M4.push_back(tmp);
  tmp = {-Inf, 0, 0, 0, 0, 0}; cmp_arr_M4.push_back(tmp);
  obj.M = new double[5*6]; // This causes memory leak. Should be fixed.
  // Can't use initializer list, because of certain issues.
  for(int i = 0; i < 5; i++){
    for(int j = 0; j < 6; j++){
      obj.M[i*6+j] = cmp_arr_M4[i][j];
    }
  }

  std::vector< std::vector<double> > cmp_arr_A4;
  tmp = {-Inf, -Inf, -Inf, -Inf, -Inf, -Inf}; cmp_arr_A4.push_back(tmp);
  tmp = {0, 0, 0, 0, 0, 0}; cmp_arr_A4.push_back(tmp);
  tmp = {0, 0, 0, 0, 0, 0}; cmp_arr_A4.push_back(tmp);
  tmp = {0, 0, 0, 0, 0, 0}; cmp_arr_A4.push_back(tmp);
  tmp = {0, 0, 0, 0, 0, 0}; cmp_arr_A4.push_back(tmp);
  obj.A = new double[5*6]; // This causes memory leak. Should be fixed.
  // Can't use initializer list, because of certain issues.
  for(int i = 0; i < 5; i++){
    for(int j = 0; j < 6; j++){
      obj.A[i*6+j] = cmp_arr_A4[i][j];
    }
  }

  std::vector< std::vector<double> > cmp_arr_B4;
  tmp = {-Inf, 0, 0, 0, 0, 0}; cmp_arr_B4.push_back(tmp);
  tmp = {-Inf, 0, 0, 0, 0, 0}; cmp_arr_B4.push_back(tmp);
  tmp = {-Inf, 0, 0, 0, 0, 0}; cmp_arr_B4.push_back(tmp);
  tmp = {-Inf, 0, 0, 0, 0, 0}; cmp_arr_B4.push_back(tmp);
  tmp = {-Inf, 0, 0, 0, 0, 0}; cmp_arr_B4.push_back(tmp);
  obj.B = new double[5*6]; // This causes memory leak. Should be fixed.
  // Can't use initializer list, because of certain issues.
  for(int i = 0; i < 5; i++){
    for(int j = 0; j < 6; j++){
      obj.B[i*6+j] = cmp_arr_B4[i][j];
    }
  }

  obj.signalA_len = 4;
  obj.signalB_len = 5;
  obj.GapOpen = 0.0;
  obj.GapExten = 0.0;
  obj.FreeEndGaps = true;

  getAffineAlignedIndices(obj);

  std::vector< std::vector<bool> > cmp_arr_Path4;
  tmp_b = {1, 1, 0, 0, 0, 0}; cmp_arr_Path4.push_back(tmp_b);
  tmp_b = {0, 0, 1, 0, 0, 0}; cmp_arr_Path4.push_back(tmp_b);
  tmp_b = {0, 0, 0, 1, 0, 0}; cmp_arr_Path4.push_back(tmp_b);
  tmp_b = {0, 0, 0, 0, 1, 0}; cmp_arr_Path4.push_back(tmp_b);
  tmp_b = {0, 0, 0, 0, 0, 1}; cmp_arr_Path4.push_back(tmp_b);
  cmp_indexA_aligned = {0, 1, 2, 3, 4};
  cmp_indexB_aligned = {1, 2, 3, 4, 5};
  cmp_score = {0, 0, 0, 0, 0};

  // s_data
  for (int i = 0; i < 4; i++){
    for (int j = 0; j < 5; j++){
      //ASSERT(std::abs(obj.s_data[i*5+j] - s.data[i*5+j]) < 1e-06);
    }
  }
  // Traceback
  for (int i = 0; i < 15; i++){
    for (int j = 0; j < 6; j++){
      ASSERT(obj.Traceback[i*6+j] == cmp_arr_Traceback4[i][j]);
    }
  }
  // M
  for (int i = 1; i < 5; i++){
    for (int j = 1; j < 6; j++){
      ASSERT(std::abs(obj.M[i*6+j] - cmp_arr_M4[i][j]) < 1e-06);
    }
  }
  ASSERT(std::abs(obj.M[0] - cmp_arr_M4[0][0]) < 1e-06);
  for (int j = 1; j < 6; j++){
    ASSERT(std::isinf(obj.M[0*6+j]) && std::signbit(obj.M[0*6+j]));
  }
  for (int i = 1; i < 5; i++){
    ASSERT(std::isinf(obj.M[i*6+0]) && std::signbit(obj.M[i*6+0]));
  }
  // A
  for (int i = 1; i < 5; i++){
    for (int j = 0; j < 6; j++){
      ASSERT(std::abs(obj.A[i*6+j] - cmp_arr_A4[i][j]) < 1e-06);
    }
  }
  for (int j = 0; j < 6; j++){
    ASSERT(std::isinf(obj.A[0*6+j]) && std::signbit(obj.A[0*6+j]));
  }
  // B
  for (int i = 0; i < 5; i++){
    for (int j = 1; j < 6; j++){
      ASSERT(std::abs(obj.B[i*6+j] - cmp_arr_B4[i][j]) < 1e-06);
    }
  }
  for (int i = 0; i < 5; i++){
    ASSERT(std::isinf(obj.B[i*6+0]) && std::signbit(obj.B[i*6+0]));
  }
  // Path
  for (int i = 0; i < 5; i++){
    for (int j = 0; j < 6; j++){
      ASSERT(obj.Path[i*6+j] == cmp_arr_Path4[i][j]);
    }
  }
  // signalA_len
  ASSERT(obj.signalA_len == 4);
  // signalB_len
  ASSERT(obj.signalB_len == 5);
  // GapOpen
  ASSERT(std::abs(obj.GapOpen - 0.0) < 1e-6);
  // GapExten
  ASSERT(std::abs(obj.GapExten - 0.0) < 1e-6);
  // FreeEndGaps
  ASSERT(obj.FreeEndGaps == true);
  // indexA_aligned
  for(int i = 0; i < obj.indexA_aligned.size(); i++){
    ASSERT(obj.indexA_aligned[i] == cmp_indexA_aligned[i]);
  }
  // indexB_aligned
  for(int i = 0; i < obj.indexB_aligned.size(); i++){
    ASSERT(obj.indexB_aligned[i] == cmp_indexB_aligned[i]);
  }
  // score
  for(int i = 0; i < obj.score.size(); i++){
    ASSERT(std::abs(obj.score[i] - cmp_score[i]) < 1e-06);
  }
}

void test_getOlapAffineAlignStartIndices(){
  int OlapStartRow, OlapStartCol;
  tbJump MatrixName;
  double affineAlignmentScore;

  double Inf = std::numeric_limits<double>::infinity();
  AffineAlignObj obj(4+1, 5+1);
  double gapOpen = 22.0, gapExten = 7.0;
  std::vector< std::vector< TracebackType > > cmp_arr_Traceback;
  std::vector<TracebackType> tmp_tb;
  // Traceback M
  tmp_tb = {SS, SS, SS, SS, SS, SS}; cmp_arr_Traceback.push_back(tmp_tb);
  tmp_tb = {SS, DM, DB, DB, DB, DB}; cmp_arr_Traceback.push_back(tmp_tb);
  tmp_tb = {SS, DA, DM, DM, DM, DM}; cmp_arr_Traceback.push_back(tmp_tb);
  tmp_tb = {SS, DA, DM, DM, DM, DM}; cmp_arr_Traceback.push_back(tmp_tb);
  tmp_tb = {SS, DA, DM, DM, DB, DM}; cmp_arr_Traceback.push_back(tmp_tb);
  // Traceback A
  tmp_tb = {SS, SS, SS, SS, SS, SS}; cmp_arr_Traceback.push_back(tmp_tb);
  tmp_tb = {TM, TB, TB, TB, TB, TB}; cmp_arr_Traceback.push_back(tmp_tb);
  tmp_tb = {TA, TM, TM, TM, TM, TM}; cmp_arr_Traceback.push_back(tmp_tb);
  tmp_tb = {TA, TM, TM, TA, TM, TA}; cmp_arr_Traceback.push_back(tmp_tb);
  tmp_tb = {TA, TA, TM, TB, TA, TM}; cmp_arr_Traceback.push_back(tmp_tb);
  // Traceback B
  tmp_tb = {SS, LM, LB, LB, LB, LB}; cmp_arr_Traceback.push_back(tmp_tb);
  tmp_tb = {SS, LA, LM, LM, LM, LB}; cmp_arr_Traceback.push_back(tmp_tb);
  tmp_tb = {SS, LA, LM, LB, LM, LM}; cmp_arr_Traceback.push_back(tmp_tb);
  tmp_tb = {SS, LA, LM, LM, LB, LB}; cmp_arr_Traceback.push_back(tmp_tb);
  tmp_tb = {SS, LA, LM, LA, LM, LB}; cmp_arr_Traceback.push_back(tmp_tb);
  obj.Traceback = new TracebackType[3*5*6]; // This causes memory leak. Should be fixed.
  // Can't use initializer list, because of certain issues.
  for(int i = 0; i < 15; i++){
    for(int j = 0; j < 6; j++){
      obj.Traceback[i*6+j] = cmp_arr_Traceback[i][j];
    }
  }

  std::vector< std::vector< double > > cmp_arr_M;
  std::vector<double> tmp;
  tmp = {0, -Inf, -Inf, -Inf, -Inf, -Inf}; cmp_arr_M.push_back(tmp);
  tmp = {-Inf, -2, -2, 10, -2, 10}; cmp_arr_M.push_back(tmp);
  tmp = {-Inf, 10, -4, -4, 8, -4}; cmp_arr_M.push_back(tmp);
  tmp = {-Inf, -2, 20, -6, -6, 6}; cmp_arr_M.push_back(tmp);
  tmp = {-Inf, -2, -4, 18, 8, -8}; cmp_arr_M.push_back(tmp);
  obj.M = new double[5*6]; // This causes memory leak. Should be fixed.
  // Can't use initializer list, because of certain issues.
  for(int i = 0; i < 5; i++){
    for(int j = 0; j < 6; j++){
      obj.M[i*6+j] = cmp_arr_M[i][j];
    }
  }

  std::vector< std::vector<double> > cmp_arr_A;
  tmp = {-Inf, -Inf, -Inf, -Inf, -Inf, -Inf}; cmp_arr_A.push_back(tmp);
  tmp = {0, -22, -22, -22, -22, -22}; cmp_arr_A.push_back(tmp);
  tmp = {0, -24, -24, -12, -24, -12}; cmp_arr_A.push_back(tmp);
  tmp = {0, -12, -26, -19, -14, -19}; cmp_arr_A.push_back(tmp);
  tmp = {0, -19, -2, -24, -21, -16}; cmp_arr_A.push_back(tmp);
  obj.A = new double[5*6]; // This causes memory leak. Should be fixed.
  // Can't use initializer list, because of certain issues.
  for(int i = 0; i < 5; i++){
    for(int j = 0; j < 6; j++){
      obj.A[i*6+j] = cmp_arr_A[i][j];
    }
  }

  std::vector< std::vector<double> > cmp_arr_B;
  tmp = {-Inf, 0, 0, 0, 0, 0}; cmp_arr_B.push_back(tmp);
  tmp = {-Inf, -22, -24, -24, -12, -19}; cmp_arr_B.push_back(tmp);
  tmp = {-Inf, -22, -12, -19, -26, -14}; cmp_arr_B.push_back(tmp);
  tmp = {-Inf, -22, -24, -2, -9, -16}; cmp_arr_B.push_back(tmp);
  tmp = {-Inf, -22, -24, -24, -4, -11}; cmp_arr_B.push_back(tmp);
  obj.B = new double[5*6]; // This causes memory leak. Should be fixed.
  // Can't use initializer list, because of certain issues.
  for(int i = 0; i < 5; i++){
    for(int j = 0; j < 6; j++){
      obj.B[i*6+j] = cmp_arr_B[i][j];
    }
  }

  obj.signalA_len = 4;
  obj.signalB_len = 5;
  obj.GapOpen = 22.0;
  obj.GapExten = 7.0;
  obj.FreeEndGaps = true;

  affineAlignmentScore = getOlapAffineAlignStartIndices(obj.M, obj.A, obj.B, 5, 6, OlapStartRow, OlapStartCol, MatrixName);

  std::vector< std::vector<bool> > cmp_arr_Path;
  std::vector<bool> tmp_b;
  tmp_b = {0, 0, 0, 0, 0, 0}; cmp_arr_Path.push_back(tmp_b);
  tmp_b = {0, 0, 0, 0, 0, 0}; cmp_arr_Path.push_back(tmp_b);
  tmp_b = {0, 0, 0, 0, 0, 0}; cmp_arr_Path.push_back(tmp_b);
  tmp_b = {0, 0, 0, 0, 0, 0}; cmp_arr_Path.push_back(tmp_b);
  tmp_b = {0, 0, 0, 0, 0, 0}; cmp_arr_Path.push_back(tmp_b);

  // s_data
  for (int i = 0; i < 4; i++){
    for (int j = 0; j < 5; j++){
      //ASSERT(std::abs(obj.s_data[i*5+j] - s.data[i*5+j]) < 1e-06);
    }
  }
  // Traceback
  for (int i = 0; i < 15; i++){
    for (int j = 0; j < 6; j++){
      ASSERT(obj.Traceback[i*6+j] == cmp_arr_Traceback[i][j]);
    }
  }
  // M
  for (int i = 1; i < 5; i++){
    for (int j = 1; j < 6; j++){
      ASSERT(std::abs(obj.M[i*6+j] - cmp_arr_M[i][j]) < 1e-06);
    }
  }
  ASSERT(std::abs(obj.M[0] - cmp_arr_M[0][0]) < 1e-06);
  for (int j = 1; j < 6; j++){
    ASSERT(std::isinf(obj.M[0*6+j]) && std::signbit(obj.M[0*6+j]));
  }
  for (int i = 1; i < 5; i++){
    ASSERT(std::isinf(obj.M[i*6+0]) && std::signbit(obj.M[i*6+0]));
  }
  // A
  for (int i = 1; i < 5; i++){
    for (int j = 0; j < 6; j++){
      ASSERT(std::abs(obj.A[i*6+j] - cmp_arr_A[i][j]) < 1e-06);
    }
  }
  for (int j = 0; j < 6; j++){
    ASSERT(std::isinf(obj.A[0*6+j]) && std::signbit(obj.A[0*6+j]));
  }
  // B
  for (int i = 0; i < 5; i++){
    for (int j = 1; j < 6; j++){
      ASSERT(std::abs(obj.B[i*6+j] - cmp_arr_B[i][j]) < 1e-06);
    }
  }
  for (int i = 0; i < 5; i++){
    ASSERT(std::isinf(obj.B[i*6+0]) && std::signbit(obj.B[i*6+0]));
  }
  // Path
  for (int i = 0; i < 5; i++){
    for (int j = 0; j < 6; j++){
      ASSERT(obj.Path[i*6+j] == cmp_arr_Path[i][j]);
    }
  }
  // signalA_len
  ASSERT(obj.signalA_len == 4);
  // signalB_len
  ASSERT(obj.signalB_len == 5);
  // GapOpen
  ASSERT(std::abs(obj.GapOpen - 22.0) < 1e-6);
  // GapExten
  ASSERT(std::abs(obj.GapExten - 7.0) < 1e-6);
  // FreeEndGaps
  ASSERT(obj.FreeEndGaps == true);
  // indexA_aligned
  ASSERT(obj.indexA_aligned.size() == 0);
  // indexB_aligned
  ASSERT(obj.indexB_aligned.size() == 0);
  // score
  ASSERT(obj.score.size() == 0);
  ASSERT(OlapStartRow == 4);
  ASSERT(OlapStartCol == 3);
  ASSERT(MatrixName == M);
  ASSERT(std::abs(affineAlignmentScore - 18.0) < 1e-6);

  //........................  CASE 4 ........................................
  obj.reset(4+1, 5+1);

  std::vector< std::vector< TracebackType > > cmp_arr_Traceback4;
  // Traceback M
  tmp_tb = {SS, SS, SS, SS, SS, SS}; cmp_arr_Traceback4.push_back(tmp_tb);
  tmp_tb = {SS, DM, DB, DB, DB, DB}; cmp_arr_Traceback4.push_back(tmp_tb);
  tmp_tb = {SS, DA, DM, DM, DM, DM}; cmp_arr_Traceback4.push_back(tmp_tb);
  tmp_tb = {SS, DA, DM, DM, DM, DM}; cmp_arr_Traceback4.push_back(tmp_tb);
  tmp_tb = {SS, DA, DM, DM, DM, DM}; cmp_arr_Traceback4.push_back(tmp_tb);
  // Traceback A
  tmp_tb = {SS, SS, SS, SS, SS, SS}; cmp_arr_Traceback4.push_back(tmp_tb);
  tmp_tb = {TM, TB, TB, TB, TB, TB}; cmp_arr_Traceback4.push_back(tmp_tb);
  tmp_tb = {TA, TM, TM, TM, TM, TM}; cmp_arr_Traceback4.push_back(tmp_tb);
  tmp_tb = {TA, TM, TM, TM, TM, TM}; cmp_arr_Traceback4.push_back(tmp_tb);
  tmp_tb = {TA, TM, TM, TM, TM, TM}; cmp_arr_Traceback4.push_back(tmp_tb);
  // Traceback B
  tmp_tb = {SS, LM, LB, LB, LB, LB}; cmp_arr_Traceback4.push_back(tmp_tb);
  tmp_tb = {SS, LA, LM, LM, LM, LM}; cmp_arr_Traceback4.push_back(tmp_tb);
  tmp_tb = {SS, LA, LM, LM, LM, LM}; cmp_arr_Traceback4.push_back(tmp_tb);
  tmp_tb = {SS, LA, LM, LM, LM, LM}; cmp_arr_Traceback4.push_back(tmp_tb);
  tmp_tb = {SS, LA, LM, LM, LM, LM}; cmp_arr_Traceback4.push_back(tmp_tb);
  obj.Traceback = new TracebackType[3*5*6]; // This causes memory leak. Should be fixed.
  // Can't use initializer list, because of certain issues.
  for(int i = 0; i < 15; i++){
    for(int j = 0; j < 6; j++){
      obj.Traceback[i*6+j] = cmp_arr_Traceback4[i][j];
    }
  }

  std::vector< std::vector< double > > cmp_arr_M4;
  tmp = {0, -Inf, -Inf, -Inf, -Inf, -Inf}; cmp_arr_M4.push_back(tmp);
  tmp = {-Inf, 0, 0, 0, 0, 0}; cmp_arr_M4.push_back(tmp);
  tmp = {-Inf, 0, 0, 0, 0, 0}; cmp_arr_M4.push_back(tmp);
  tmp = {-Inf, 0, 0, 0, 0, 0}; cmp_arr_M4.push_back(tmp);
  tmp = {-Inf, 0, 0, 0, 0, 0}; cmp_arr_M4.push_back(tmp);
  obj.M = new double[5*6]; // This causes memory leak. Should be fixed.
  // Can't use initializer list, because of certain issues.
  for(int i = 0; i < 5; i++){
    for(int j = 0; j < 6; j++){
      obj.M[i*6+j] = cmp_arr_M4[i][j];
    }
  }

  std::vector< std::vector<double> > cmp_arr_A4;
  tmp = {-Inf, -Inf, -Inf, -Inf, -Inf, -Inf}; cmp_arr_A4.push_back(tmp);
  tmp = {0, 0, 0, 0, 0, 0}; cmp_arr_A4.push_back(tmp);
  tmp = {0, 0, 0, 0, 0, 0}; cmp_arr_A4.push_back(tmp);
  tmp = {0, 0, 0, 0, 0, 0}; cmp_arr_A4.push_back(tmp);
  tmp = {0, 0, 0, 0, 0, 0}; cmp_arr_A4.push_back(tmp);
  obj.A = new double[5*6]; // This causes memory leak. Should be fixed.
  // Can't use initializer list, because of certain issues.
  for(int i = 0; i < 5; i++){
    for(int j = 0; j < 6; j++){
      obj.A[i*6+j] = cmp_arr_A4[i][j];
    }
  }

  std::vector< std::vector<double> > cmp_arr_B4;
  tmp = {-Inf, 0, 0, 0, 0, 0}; cmp_arr_B4.push_back(tmp);
  tmp = {-Inf, 0, 0, 0, 0, 0}; cmp_arr_B4.push_back(tmp);
  tmp = {-Inf, 0, 0, 0, 0, 0}; cmp_arr_B4.push_back(tmp);
  tmp = {-Inf, 0, 0, 0, 0, 0}; cmp_arr_B4.push_back(tmp);
  tmp = {-Inf, 0, 0, 0, 0, 0}; cmp_arr_B4.push_back(tmp);
  obj.B = new double[5*6]; // This causes memory leak. Should be fixed.
  // Can't use initializer list, because of certain issues.
  for(int i = 0; i < 5; i++){
    for(int j = 0; j < 6; j++){
      obj.B[i*6+j] = cmp_arr_B4[i][j];
    }
  }

  obj.signalA_len = 4;
  obj.signalB_len = 5;
  obj.GapOpen = 0.0;
  obj.GapExten = 0.0;
  obj.FreeEndGaps = true;

  affineAlignmentScore = getOlapAffineAlignStartIndices(obj.M, obj.A, obj.B, 4+1, 5+1, OlapStartRow, OlapStartCol, MatrixName);

  std::vector< std::vector<bool> > cmp_arr_Path4;
  tmp_b = {0, 0, 0, 0, 0, 0}; cmp_arr_Path4.push_back(tmp_b);
  tmp_b = {0, 0, 0, 0, 0, 0}; cmp_arr_Path4.push_back(tmp_b);
  tmp_b = {0, 0, 0, 0, 0, 0}; cmp_arr_Path4.push_back(tmp_b);
  tmp_b = {0, 0, 0, 0, 0, 0}; cmp_arr_Path4.push_back(tmp_b);
  tmp_b = {0, 0, 0, 0, 0, 0}; cmp_arr_Path4.push_back(tmp_b);

  // s_data
  for (int i = 0; i < 4; i++){
    for (int j = 0; j < 5; j++){
      //ASSERT(std::abs(obj.s_data[i*5+j] - s.data[i*5+j]) < 1e-06);
    }
  }
  // Traceback
  for (int i = 0; i < 15; i++){
    for (int j = 0; j < 6; j++){
      ASSERT(obj.Traceback[i*6+j] == cmp_arr_Traceback4[i][j]);
    }
  }
  // M
  for (int i = 1; i < 5; i++){
    for (int j = 1; j < 6; j++){
      ASSERT(std::abs(obj.M[i*6+j] - cmp_arr_M4[i][j]) < 1e-06);
    }
  }
  ASSERT(std::abs(obj.M[0] - cmp_arr_M4[0][0]) < 1e-06);
  for (int j = 1; j < 6; j++){
    ASSERT(std::isinf(obj.M[0*6+j]) && std::signbit(obj.M[0*6+j]));
  }
  for (int i = 1; i < 5; i++){
    ASSERT(std::isinf(obj.M[i*6+0]) && std::signbit(obj.M[i*6+0]));
  }
  // A
  for (int i = 1; i < 5; i++){
    for (int j = 0; j < 6; j++){
      ASSERT(std::abs(obj.A[i*6+j] - cmp_arr_A4[i][j]) < 1e-06);
    }
  }
  for (int j = 0; j < 6; j++){
    ASSERT(std::isinf(obj.A[0*6+j]) && std::signbit(obj.A[0*6+j]));
  }
  // B
  for (int i = 0; i < 5; i++){
    for (int j = 1; j < 6; j++){
      ASSERT(std::abs(obj.B[i*6+j] - cmp_arr_B4[i][j]) < 1e-06);
    }
  }
  for (int i = 0; i < 5; i++){
    ASSERT(std::isinf(obj.B[i*6+0]) && std::signbit(obj.B[i*6+0]));
  }
  // Path
  for (int i = 0; i < 5; i++){
    for (int j = 0; j < 6; j++){
      ASSERT(obj.Path[i*6+j] == cmp_arr_Path4[i][j]);
    }
  }
  // signalA_len
  ASSERT(obj.signalA_len == 4);
  // signalB_len
  ASSERT(obj.signalB_len == 5);
  // GapOpen
  ASSERT(std::abs(obj.GapOpen - 0.0) < 1e-6);
  // GapExten
  ASSERT(std::abs(obj.GapExten - 0.0) < 1e-6);
  // FreeEndGaps
  ASSERT(obj.FreeEndGaps == true);
  // indexA_aligned
  ASSERT(obj.indexA_aligned.size() == 0);
  // indexB_aligned
  ASSERT(obj.indexB_aligned.size() == 0);
  // score
  ASSERT(obj.score.size() == 0);
  ASSERT(OlapStartRow == 4);
  ASSERT(OlapStartCol == 5);
  ASSERT(MatrixName == M);
  ASSERT(std::abs(affineAlignmentScore - 0.0) < 1e-6);
}

#ifdef USE_Rcpp
int main_affinealignment(){
#else
int main(){
#endif
  test_doAffineAlignment();
  test_getAffineAlignedIndices();
  test_getOlapAffineAlignStartIndices();
  std::cout << "test affinealignment successful" << std::endl;
  return 0;
}
