#include "Board.h"

namespace xiangqi
{
    Board::Board()
    {
        Reset();
    }

    void Board::Reset()
    {//先清空棋盘
        for(auto& row: cells_)
           {
            for(auto& cell: row)
            {
                cell.reset();
            }
           }

        //用一维数组存储底线棋子排列顺序
        const std::array<PieceType,BOARD_COLS> backRank = {
            PieceType::Chariot,
            PieceType::Horse,
            PieceType::Elephant,
            PieceType::Advisor,
            PieceType::General,
            PieceType::Advisor,
            PieceType::Elephant,
            PieceType::Horse,
            PieceType::Chariot

        };
       
        //放置底线棋子
        for(int col = 0; col < BOARD_COLS; col++)
        {
            cells_[0][col] = Piece{backRank[col],Side::Black};
            cells_[BOARD_ROWS - 1][col] = Piece{backRank[col],Side::Red};
        };

         // 布置双方炮
    cells_[2][1] = Piece{
         PieceType::Cannon,
         Side::Black
    };

    cells_[2][7] = Piece{
        PieceType::Cannon,
        Side::Black
    };

    cells_[7][1] = Piece{
        PieceType::Cannon,
        Side::Red
    };

    cells_[7][7] = Piece{
        PieceType::Cannon,
        Side::Red
    };

    // 布置双方兵卒
    for (int col = 0; col < BOARD_COLS; col += 2) {

        cells_[3][col] = Piece{
            PieceType::Soldier,
            Side::Black
        };

        cells_[6][col] = Piece{
            PieceType::Soldier,
            Side::Red
        };
    }


    }

     const Board::Cell& Board::GetPiece(int row, int col) const {
    return cells_.at(row).at(col);
}

// 统计棋子数量
int Board::CountPieces() const {

    int count = 0;

    for (const auto& row : cells_) {
        for (const auto& cell : row) {

            if (cell.has_value()) {
                count++;
            }
        }
    }

    return count;
}

  bool Board::MovePieces(int fromrow,int fromcol,int torow,int tocol)
  {
     auto inside = [] (int row,int col)
     {
        return row >= 0 && row < BOARD_ROWS && col >= 0 && col < BOARD_ROWS;
     };

     if(!inside(fromrow, fromcol) || !inside(torow, tocol))
        return false;

     if(fromrow == torow && fromcol == tocol)
        return false;

     Cell& source = cells_[fromrow][fromcol];
     Cell& target = cells_[torow][tocol];

    if(!source.has_value())
        return false;

    if(target.has_value() && target->side == source->side)
        return false;

    target = *source;
    source.reset();

    return true;

    
    



  }

}