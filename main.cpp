#include <cmath>
#include <iostream>
#include <raylib.h>

static const int SCR_WIDTH  = 720;
static const int SCR_HEIGHT = 720;
static const Vector2 SCR_DIM = { SCR_WIDTH, SCR_HEIGHT };
static const Vector2 SCR_CENTER = { SCR_DIM.x / 2, SCR_DIM.y / 2 };
static const char *WINDOW_TITLE = "Raylib Tests";

static const float ARROW_TIP_SIDE_LENGTH = 100;
static const float ARROW_TIP_HEIGHT = sqrt((3.0f/4)*ARROW_TIP_SIDE_LENGTH*ARROW_TIP_SIDE_LENGTH);
static const float ARROW_BASE_WIDTH = 80;

static const float POINT_RADIUS = 10;
static const Color POINT_COLOR = BLACK;

typedef struct Arrow {
    Vector2 source, target;
    Vector2 pivot; // source relative to top left of `base` (base.x, base.y)
    Rectangle base;
    float angle;
    Color color;
    float scale;
} Arrow;

float dist(Vector2 a, Vector2 b) {
    return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}

Arrow create_arrow(Vector2 source, Vector2 target, float scale, Color color) {
    Arrow arrow;
    arrow.source = source;
    arrow.target = target;

    float arrow_base_height = dist(source, target) - scale*(1.0f/3)*ARROW_TIP_HEIGHT + scale*ARROW_BASE_WIDTH / 2;
    arrow.base = { source.x - scale*ARROW_BASE_WIDTH / 2, source.y - (arrow_base_height - scale*ARROW_BASE_WIDTH / 2), scale*ARROW_BASE_WIDTH, arrow_base_height };
    arrow.pivot = { source.x - arrow.base.x, source.y - arrow.base.y };
    arrow.angle = atan2f(source.y - target.y, source.x - target.x) - PI/2;

    arrow.scale = scale;
    arrow.color = color;
    return arrow;
}

void draw_arrow(Arrow const& arrow) {
    Rectangle adjusted_base = { arrow.base.x + arrow.pivot.x, arrow.base.y + arrow.pivot.y, arrow.base.width, arrow.base.height };
    DrawRectanglePro(adjusted_base, arrow.pivot, RAD2DEG*arrow.angle, arrow.color);
    DrawPoly(arrow.target, 3, arrow.scale*ARROW_TIP_SIDE_LENGTH, RAD2DEG*(arrow.angle - PI/2), arrow.color);
    DrawCircleV(arrow.source, arrow.scale*POINT_RADIUS, POINT_COLOR);
    DrawCircleV(arrow.target, arrow.scale*POINT_RADIUS, POINT_COLOR);
}

int main(void) {
    InitWindow(SCR_WIDTH, SCR_HEIGHT, WINDOW_TITLE);

    Vector2 source = { SCR_DIM.x / 2, SCR_DIM.y - 100 };
    Vector2 target;
    Arrow arrow;

    float degrees = 0;
    while (!WindowShouldClose()) {
        target = { (float)GetMouseX(), (float)GetMouseY() };
        arrow = create_arrow(source, target, 0.2f, RED);
        BeginDrawing();
        ClearBackground(RAYWHITE);
            draw_arrow(arrow);
        EndDrawing();
    }
    CloseWindow();
}

