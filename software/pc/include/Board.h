#pragma once

#include "Piece.h"

#include <array>
#include <optional>

namespace xiangqi
{
  //尺寸
  inline constexpr int BOARD_ROWS = 10;
  inline constexpr int BOARD_COLS = 9;

  class Board
 {
  public:
     using Cell = std::optional<Piece>;

     Board();   //构造函数

     void Reset(); //初始化

     const Cell& GetPiece(int row, int col) const; 
     //获取指定位置的棋子
     
     //统计现有棋子数量
     int CountPieces() const;

     bool MovePieces(int fromrow,int fromcol,int torow,int tocol);

  private:
     //内部数据
     std::array<
         std::array<Cell, BOARD_COLS>, 
         BOARD_ROWS
         > cells_{};


        
 };
}
