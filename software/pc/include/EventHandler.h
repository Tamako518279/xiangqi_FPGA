#pragma once

#include "Appstate.h"
#include "FPGAEvent.h"

namespace xiangqi {

void HandleFpgaEvent(AppState& app, const FpgaEvent& event);

}
