#include "Windows.h"
#include "ColourBrushes.h"

HBRUSH redBrush = CreateSolidBrush(RGB(255, 0, 0));
HBRUSH yellowBrush = CreateSolidBrush(RGB(255, 255, 0));
HBRUSH greenBrush = CreateSolidBrush(RGB(0, 255, 0));
HBRUSH blueBrush = CreateSolidBrush(RGB(0, 0, 255));
HBRUSH blackBrush = CreateSolidBrush(RGB(0, 0, 0));
HBRUSH whiteBrush = CreateSolidBrush(RGB(255, 255, 255));

HBRUSH bgBrush = CreateSolidBrush(RGB(50, 50, 50));
HBRUSH offBrush = CreateSolidBrush(RGB(180, 180, 180));

HPEN tlOutlinePen = CreatePen(PS_SOLID, 5, RGB(0, 0, 0));

HBRUSH roadBrush = CreateSolidBrush(RGB(100, 100, 100));

HPEN noPen = CreatePen(PS_NULL, 0, RGB(0, 0, 0));