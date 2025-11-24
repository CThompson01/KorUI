#ifndef KORUI_H
#define KORUI_H
#include "raylib.h"

/*******************
 * UI Element Code *
 *******************/

// Order structs in decreasing datatype size
typedef struct uibutton {
    int (*callback)();
    int x;
    int y;
    int width;
    int height;
    int pressed;
    char label[50];
} UIButton;

void InitializeButton(UIButton *p_button, char label[], int x, int y, int width, int height);
void DrawButton(UIButton button, Font font);
int CheckButtonPress(UIButton button, int mx, int my);
void ButtonPressed(UIButton *p_button, int mx, int my);
void ButtonReleased(UIButton *p_button, int mx, int my);
int DefaultButtonCallback();

typedef struct uinumberlabel {
    int *value;
    int x;
    int y;
    int width;
    int height;
    char label[50];
} UINumberLabel;
void InitializeNumberLabel(UINumberLabel *p_numberLabel, char label[], int *value, int x, int y, int width, int height);
void DrawNumberLabel(UINumberLabel label, Font font);

typedef struct scrollselector ScrollSelector;
struct scrollselector { // potential to move this to global later
    int (*OnChange)(char selection[]);
    int num_options;

    int display_y; // Button location stuff
    int display_width;
    int display_height;
    int button_r_x;
    int button_l_x;

    int left_pressed; // Release button stuff
    int right_pressed;

    int x;
    int y;
    int selected;
    char label[50];
    char *options[];
};

ScrollSelector* InitializeScrollSelector(ScrollSelector *p_scrollSelector, char label[], char *list_of_options[], int num_options, int x, int y);
void DrawScrollSelector(ScrollSelector *s, Font font);
int ScrollSelectorInput(ScrollSelector *s, int mx, int my);
void ScrollSelectorPressed(ScrollSelector *s, int mx, int my);
void ScrollSelectorReleased(ScrollSelector *s, int mx, int my);
ScrollSelector* ChangeScrollSelectorOptions(ScrollSelector *s, char *list_of_options[], int num_options);
void updateScrollSelectorPositions(ScrollSelector *s, Font font);

enum UIType { UIT_BUTTON, UIT_NUMLABEL, UIT_SCROLLSELECTOR };
typedef struct uielement {
    enum UIType type;
    char key[25];
    union {
        UIButton button;
        UINumberLabel numLabel;
        ScrollSelector *scrollSelector;
    } element;
} UIElement;

void DrawUIElement(UIElement element, Font font);
void CheckUIElementPressed(UIElement *p_element, int mx, int my);
void CheckUIElementReleased(UIElement *p_element, int mx, int my);
int GetIndexOfKey(UIElement *p_elements, int elements_len, char *key);
void UIElementUpdatePosition(UIElement element, int new_x, int new_y);
void InitializeButtonElement(UIElement *p_buttonElement, char key[], char label[], int x, int y, int width, int height, int (*callback)());
void InitializeNumberLabelElement(UIElement *p_numLabelElement, char key[], char label[], int *value, int x, int y, int width, int height);
void InitializeScrollSelectorElement(UIElement *p_scrollSelectorElement, char key[], char label[], char *list_of_options[], int num_options, int x, int y);

/***************
 * Layout Code *
 ***************/

enum LayoutAlignment {
    NONE, LEFT, RIGHT, TOP, BOTTOM, CENTERED, SPACE_BETWEEN
};

enum LayoutDirection {
    HORIZONTAL, VERTICAL
};

typedef struct layoutstyle {
    enum LayoutAlignment horizontalAlignment;
    enum LayoutAlignment verticalAlignment;
    enum LayoutDirection layoutDirection;
} LayoutStyle;

typedef struct layoutdetails {
    int x;
    int y;
    int width;
    int height;
} LayoutDetails;

LayoutDetails AutoLayout(UIElement **layout, int numElements, LayoutStyle style, LayoutDetails container, int padding);
int AutoLayout_Centered(UIElement **layout, int numElements, int width, int height, int padding);
int AutoLayout_SpaceBetween(UIElement **layout, int numElements, int width, int height);

#endif