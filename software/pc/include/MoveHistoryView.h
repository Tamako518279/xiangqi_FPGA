#pragma once

#include "Movehistory.h"
#include "raylib.h"

namespace xiangqi {

Font LoadMoveHistoryFont();

void DrawMoveHistoryPanel(const MoveHistory& history, bool boardSynchronized,
                          Font font, float& rowsFromBottom);

}