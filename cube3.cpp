#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <map>
#include <string>
#include <cassert>
#include <ctime>

class Cube3 {
public:
    Cube3();
    static std::vector<std::string> prase_string_to_rotate_op(std::string s);
    static bool is_correct_rotate_option(std::string op);
    static bool is_correct_rotate_character(char ch);
    static void add_option(std::vector<std::string>& v, std::string new_option);
    static bool is_opposite_rotate(std::string ra, std::string rb);
    static std::vector<std::string> merge_two_rotate_option(std::string pre, std::string post);
    static std::vector<std::string> get_a_random_disturb();
    bool reset_color(char front_color, char up_color);
    void show_face_color_msg();
    static const char * convert_color_to_chinese(char color); 
    void set_face_color(const char * face_up, const char * face_down,const char * face_left, 
                        const char * face_right, const char * face_front, const char * face_back);
    void show_face_color(char op); 
    void show_all_face_color();
    std::vector<std::string> get_face_9_color(char op);
    void show_all_face_color_graphically();
    char get_center_color(char op);
    const char * get_face_name(char op);
    void restore_directly();    
    void disturb_cube(const std::vector<std::string>& disturb_list) {
        this->restore_directly();
        for (int i = 0; i < (int)disturb_list.size(); ++i) {
            this->rotate_op(disturb_list[i]);
        }            
    }
    // 魔方的旋转操作
    void rotate_r();
    void rotate_r_plus();
    void rotate_l();
    void rotate_l_plus();
    void rotate_u();
    void rotate_u_plus();
    void rotate_d();
    void rotate_d_plus();
    void rotate_f();
    void rotate_f_plus();
    void rotate_b();
    void rotate_b_plus();
    void rotate_op(char * op);
    void rotate_op(std::string op);
private:    
    static const char GREEN;
    static const char RED;
    static const char BLUE;
    static const char ORANGE;
    static const char WHITE;
    static const char YELLOW;
    // 魔方的配色信息以及面的朝向
    char _front_color;
    char _back_color;
    char _left_color;
    char _right_color;
    char _up_color;
    char _down_color;
    
    // 魔方面的颜色，从0-8顺时针
    char _face_front[8];
    char _face_back[8];
    char _face_left[8];
    char _face_right[8];
    char _face_up[8];
    char _face_down[8];

    char get_opposite_color(char color);
    bool is_exists_color(char color);
    char get_left_face_color(char up_color, char front_color);

};

const char Cube3::GREEN = 'G';
const char Cube3::RED = 'R';
const char Cube3::BLUE = 'B';
const char Cube3::ORANGE = 'O';
const char Cube3::WHITE = 'W';
const char Cube3::YELLOW = 'Y';

Cube3::Cube3() {
    _front_color = RED;
    _back_color = ORANGE;
    _left_color = BLUE;
    _right_color = GREEN;
    _up_color = YELLOW;
    _down_color = WHITE;
    this->restore_directly();
}

void Cube3::restore_directly() {
    for (int i = 0; i < 8 ; ++i) { // 一个面有8个块和1个中心块
        _face_front[i] = _front_color;
        _face_back[i] = _back_color;
        _face_left[i] = _left_color;
        _face_right[i] = _right_color;
        _face_up[i] = _up_color;
        _face_down[i] = _down_color;
    }
}

bool Cube3::reset_color(char front_color, char up_color) {
    if (!is_exists_color(front_color) || !is_exists_color(up_color)) {
        return false;
    } 
    if (front_color == get_opposite_color(up_color)) {
        return false;
    }
    this->_front_color = front_color;
    this->_up_color = up_color;
    this->_back_color = get_opposite_color(front_color);
    this->_down_color = get_opposite_color(up_color);
    this->_left_color = get_left_face_color(up_color, front_color);
    this->_right_color = get_opposite_color(this->_left_color);
    this->restore_directly();
    return true;
}

char Cube3::get_opposite_color(char color) {
    assert(color==GREEN || color == RED || color == BLUE || color == ORANGE || color == WHITE || color == YELLOW);
    if (color == GREEN) {
        return BLUE;
    } else if (color == BLUE) {
        return GREEN;
    } else if (color == RED) {
        return ORANGE;
    } else if (color == ORANGE) {
        return RED;
    } else if (color == WHITE) {
        return YELLOW;
    } else if (color == YELLOW) {
        return WHITE;
    }
    return '0';
}

bool Cube3::is_exists_color(char color) {
    return (color == GREEN || color == BLUE || color == RED || color == ORANGE || color || color == WHITE || color == YELLOW);
} 

char Cube3::get_left_face_color(char up_color, char front_color) {
    assert(is_exists_color(up_color));
    assert(is_exists_color(front_color));
    char side_face_colors[4] = {'0', '0','0', '0'}; // 不取g r b w y o等表示颜色的字母即可
    if (up_color == YELLOW || up_color == WHITE) {
       char tmp_array[] = {RED, GREEN, ORANGE, BLUE};
       for (int i = 0; i < 4; ++i) {
           side_face_colors[i] = tmp_array[i];
       }
    } else if (up_color == BLUE || up_color == GREEN) {
        char tmp_array[] = {WHITE, RED, YELLOW, ORANGE};
        for (int i = 0; i < 4; ++i) {
            side_face_colors[i] = tmp_array[i];
        }
    } else if (up_color == RED || up_color == ORANGE) {
        char tmp_array[] = {YELLOW, BLUE, WHITE, GREEN};
        for (int i = 0; i < 4; ++i) {
            side_face_colors[i] = tmp_array[i];
        }
    }

    int index = -1;
    for (int i = 0; i < 4; ++i) {
        if (side_face_colors[i] == front_color) {
            index = i;
            break;
        }
    }
    assert(index != -1);
    if (up_color == YELLOW || up_color == BLUE || up_color == RED) {
        return side_face_colors[(index + 3) % 4];
    } else { // up_face = WHITE or GREEN or ORANGE
        return side_face_colors[(index + 1) % 4];
    }
}
const char * Cube3::convert_color_to_chinese(char color) {
    if (color == GREEN) {
        return "绿";
    } else if (color == RED) {
        return "红";
    } else if (color == BLUE) {
        return "蓝";
    } else if (color == ORANGE) {
        return "橙";
    } else if (color == WHITE) {
        return "白";
    } else if (color == YELLOW) {
        return "黄";
    } else {
        return "False";
    }
}
void Cube3::show_face_color_msg() {
    printf("----魔方的朝向和配色信息如下----\n");
    printf("上: %s\n", convert_color_to_chinese(this->_up_color));
    printf("下: %s\n", convert_color_to_chinese(this->_down_color));
    printf("左: %s\n", convert_color_to_chinese(this->_left_color));
    printf("右: %s\n", convert_color_to_chinese(this->_right_color));
    printf("前: %s\n", convert_color_to_chinese(this->_front_color));
    printf("后: %s\n\n", convert_color_to_chinese(this->_back_color));
}

void Cube3::set_face_color(const char * face_up, const char * face_down,const char * face_left, 
                           const char * face_right, const char * face_front, const char * face_back) {
    for (int i = 0; i < 8; ++i) {
        this->_face_up[i] = face_up[i];
        this->_face_down[i] = face_down[i];
        this->_face_left[i] = face_left[i];
        this->_face_right[i] = face_right[i];
        this->_face_front[i] = face_front[i];
        this->_face_back[i] = face_back[i];
    }
}

void Cube3::show_all_face_color() {
    printf("魔方的状态如下：____\n");
    char list_op[] = "ufdlrb";
    for (int i = 0; i < 6; ++i) {
        show_face_color(list_op[i]);
    }

    printf("____________________\n");
}

std::vector<std::string> Cube3::get_face_9_color(char op) {
    const char * pface = NULL;
    std::vector<std::string> v;
    if (op == 'u') {
        pface = _face_up;
    } else if (op == 'd') {
        pface = _face_down;
    } else if (op == 'l') {
        pface = _face_left;
    } else if (op == 'r') {
        pface = _face_right;
    } else if (op == 'f') {
        pface = _face_front;
    } else if (op == 'b') {
        pface = _face_back;
    } else {
        printf("get_face_9_color(char op) 参数错误，op只能为'u','d','l','r','f','b'中的一个！\n");
        return v;
    }
    char tmp[9] = {pface[0], pface[1], pface[2], pface[7],'0', pface[3], pface[6], pface[5], pface[4]};
    tmp[4] = get_center_color(op);
    for (int i = 0; i < 9; ++i) {
        v.push_back(convert_color_to_chinese(tmp[i]));
    }
    return v;
}

void Cube3::show_all_face_color_graphically() {
    std::vector<std::string> v_front = get_face_9_color('f');
    std::vector<std::string> v_back = get_face_9_color('b');
    std::vector<std::string> v_left = get_face_9_color('l');
    std::vector<std::string> v_right = get_face_9_color('r');
    std::vector<std::string> v_up = get_face_9_color('u');
    std::vector<std::string> v_down = get_face_9_color('d');

    printf("魔方展开图如下：\n");
    printf("  上\n");
    printf("左前右后\n");
    printf("  下\n");
    printf("-----------------------------------------\n");
    int cnt = 0;
    for(int i = 0; i < 3; ++i) {
        printf("        ");
        for (int j = 0; j < 3; ++j) {
            printf("%s", v_up[cnt++].c_str());
        }
        printf("\n");
    }
    printf("\n");
    for (int i = 0; i < 3; ++i) {
        printf("%s%s%s  ", v_left[i*3+0].c_str(), v_left[i*3+1].c_str(), v_left[i*3+2].c_str());
        printf("%s%s%s  ", v_front[i*3+0].c_str(), v_front[i*3+1].c_str(), v_front[i*3+2].c_str());
        printf("%s%s%s  ", v_right[i*3+0].c_str(), v_right[i*3+1].c_str(), v_right[i*3+2].c_str());
        printf("%s%s%s\n", v_back[i*3+0].c_str(), v_back[i*3+1].c_str(), v_back[i*3+2].c_str());
    }
    printf("\n");
    cnt = 0;
    for (int i = 0; i < 3; ++i) {
        printf("        ");
        for (int j = 0; j < 3; ++j) {
            printf("%s", v_down[cnt++].c_str());
        }
        printf("\n");
    }
    printf("-----------------------------------------\n");
}

void Cube3::show_face_color(char op) {
    const char * pface = NULL;
    if (op == 'u') {
        pface = _face_up;
    } else if (op == 'd') {
        pface = _face_down;
    } else if (op == 'l') {
        pface = _face_left;
    } else if (op == 'r') {
        pface = _face_right;
    } else if (op == 'f') {
        pface = _face_front;
    } else if (op == 'b') {
        pface = _face_back;
    } else {
        printf("show_face_color(char op) 参数错误，op只能为'u','d','l','r','f','b'中的一个！\n");
        return;
    }
    char tmp[9] = {pface[0], pface[1], pface[2], pface[7],'0', pface[3], pface[6], pface[5], pface[4]};
    tmp[4] = get_center_color(op);

    printf("%s面：\n", get_face_name(op));
    for (int i = 0; i < 9; ++i) {
        printf("%s ", convert_color_to_chinese(tmp[i]));
        if (i % 3 == 2) {
            printf("\n");
        }
    }

}

char Cube3::get_center_color(char op) {
    switch (op) {
    case 'f':
        return this->_front_color;
    case 'b':
        return this->_back_color;
    case 'u':
        return this->_up_color;
    case 'd':
        return this->_down_color;
    case 'l':
        return this->_left_color;
    case 'r':
        return this->_right_color;
    default:
        printf("get_center_color(char op) 参数错误，op只能为'u','d','l','r','f','b'中的一个！\n");
        assert(false);
        return 'R';
    }
}

const char * Cube3::get_face_name(char op) {
    switch (op) {
    case 'u':
        return "上";
    case 'd':
        return "下";
    case 'l':
        return "左";
    case 'r':
        return "右";
    case 'f':
        return "前";
    case 'b':
        return "后";
    default:
        printf("get_face_name(char op) 参数错误, op只能为'u','d','l','r','f','b'中的一个!\n");
        return "False";
    }
}

void Cube3::rotate_r() {
    // 处理right面的棱块循环
    int mp[] = {1, 3, 5, 7};
    char tmp_ch = _face_right[7];
    for (int i = 3; i > 0; --i) {
        _face_right[mp[i]] = _face_right[mp[i-1]];
    } 
    _face_right[1] = tmp_ch;
    // 处理right面的角块循环
    int mp2[] = {0, 2, 4, 6};
    tmp_ch = _face_right[6];
    for (int i = 3; i > 0; --i) {
        _face_right[mp2[i]] = _face_right[mp2[i-1]];
    }
    _face_right[0] = tmp_ch;

    //处理前后上下4个面上的棱块循环：
    char * mp3[] = {&_face_front[3], &_face_up[3], &_face_back[7], &_face_down[3]};
    tmp_ch = *mp3[3];
    for (int i = 3; i > 0; --i) {
        *mp3[i] = *mp3[i-1];
    }
    *mp3[0] = tmp_ch;

    //处理前后上下四个面上的角块循环：
    char * mp4[] = {&_face_front[2], &_face_up[2], &_face_back[6], &_face_down[2]};
    tmp_ch = *mp4[3];
    for (int i = 3; i > 0; --i) {
        *mp4[i] = *mp4[i-1];
    }
    *mp4[0] = tmp_ch;

    char * mp5[] = {&_face_front[4], &_face_up[4], &_face_back[0], &_face_down[4]};
    tmp_ch = *mp5[3];
    for (int i = 3; i > 0; --i) {
        *mp5[i] = *mp5[i-1];
    }
    *mp5[0] = tmp_ch;
}

void Cube3::rotate_r_plus() {
    // 处理right面的棱块循环
    int mp[] = {1, 3, 5, 7};
    char tmp_ch = _face_right[1];
    for (int i = 0; i < 3; ++i) {
        _face_right[mp[i]] = _face_right[mp[i+1]];
    } 
    _face_right[7] = tmp_ch;
    // 处理right面的角块循环
    int mp2[] = {0, 2, 4, 6};
    tmp_ch = _face_right[0];
    for (int i = 0; i < 3; ++i) {
        _face_right[mp2[i]] = _face_right[mp2[i+1]];
    }
    _face_right[6] = tmp_ch;

    //处理前后上下4个面上的棱块循环：
    char * mp3[] = {&_face_front[3], &_face_up[3], &_face_back[7], &_face_down[3]};
    tmp_ch = *mp3[0];
    for (int i = 0; i < 3; ++i) {
        *mp3[i] = *mp3[i+1];
    }
    *mp3[3] = tmp_ch;

    //处理前后上下四个面上的角块循环：
    char * mp4[] = {&_face_front[2], &_face_up[2], &_face_back[6], &_face_down[2]};
    tmp_ch = *mp4[0];
    for (int i = 0; i < 3; ++i) {
        *mp4[i] = *mp4[i+1];
    }
    *mp4[3] = tmp_ch;

    char * mp5[] = {&_face_front[4], &_face_up[4], &_face_back[0], &_face_down[4]};
    tmp_ch = *mp5[0];
    for (int i = 0; i < 3; ++i) {
        *mp5[i] = *mp5[i+1];
    }
    *mp5[3] = tmp_ch;
}

void Cube3::rotate_u() {
    // 处理up面上的棱块循环
    int mp[] = {1, 3, 5, 7};
    char tmp_ch = _face_up[mp[3]];
    for (int i = 3; i > 0; --i) {
        _face_up[mp[i]] = _face_up[mp[i-1]];
    }
    _face_up[mp[0]] = tmp_ch;
    // 处理up面上的角块循环
    int mp2[] = {0, 2, 4, 6};
    tmp_ch = _face_up[mp2[3]];
    for (int i = 3; i > 0; --i) {
        _face_up[mp2[i]] = _face_up[mp2[i-1]];
    }
    _face_up[mp2[0]] = tmp_ch;
    // 处理前后左右四个面上的棱块循环：
    char * mp3[] = {&_face_front[1], &_face_left[1], &_face_back[1], &_face_right[1]};
    tmp_ch = *mp3[3];
    for (int i = 3; i > 0; --i) {
        *mp3[i] = *mp3[i-1];
    }
    *mp3[0] = tmp_ch;
    // 处理前后左右四个面上的角块循环：
    char * mp4[] = {&_face_front[0], &_face_left[0], &_face_back[0], &_face_right[0]};
    tmp_ch = *mp4[3];
    for (int i = 3; i > 0; --i) {
        *mp4[i] = *mp4[i-1];
    }
    *mp4[0] = tmp_ch;

    char * mp5[] = {&_face_front[2], &_face_left[2], &_face_back[2], &_face_right[2]};
    tmp_ch = *mp5[3];
    for (int i = 3; i > 0; --i) {
        *mp5[i] = *mp5[i-1];
    }
    *mp5[0] = tmp_ch;
}

void Cube3::rotate_u_plus() {
    // 处理up面上的棱块循环
    int mp[] = {1, 3, 5, 7};
    char tmp_ch = _face_up[mp[0]];
    for (int i = 0; i < 3; ++i) {
        _face_up[mp[i]] = _face_up[mp[i+1]];
    }
    _face_up[mp[3]] = tmp_ch;
    // 处理up面上的角块循环
    int mp2[] = {0, 2, 4, 6};
    tmp_ch = _face_up[mp2[0]];
    for (int i = 0; i < 3; ++i) {
        _face_up[mp2[i]] = _face_up[mp2[i+1]];
    }
    _face_up[mp2[3]] = tmp_ch;
    // 处理前后左右四个面上的棱块循环：
    char * mp3[] = {&_face_front[1], &_face_left[1], &_face_back[1], &_face_right[1]};
    tmp_ch = *mp3[0];
    for (int i = 0; i < 3; ++i) {
        *mp3[i] = *mp3[i+1];
    }
    *mp3[3] = tmp_ch;
    // 处理前后左右四个面上的角块循环：
    char * mp4[] = {&_face_front[0], &_face_left[0], &_face_back[0], &_face_right[0]};
    tmp_ch = *mp4[0];
    for (int i = 0; i < 3; ++i) {
        *mp4[i] = *mp4[i+1];
    }
    *mp4[3] = tmp_ch;

    char * mp5[] = {&_face_front[2], &_face_left[2], &_face_back[2], &_face_right[2]};
    tmp_ch = *mp5[0];
    for (int i = 0; i < 3; ++i) {
        *mp5[i] = *mp5[i+1];
    }
    *mp5[3] = tmp_ch;
}

void Cube3::rotate_f() { 
    // 处理front面上的棱块循环
    int mp[] = {1, 3, 5, 7};
    char tmp_ch = _face_front[mp[3]];
    for (int i = 3; i > 0; --i) {
        _face_front[mp[i]] = _face_front[mp[i-1]];
    }
    _face_front[mp[0]] = tmp_ch;
    // 处理front面上的角块循环
    int mp2[] = {0, 2, 4, 6};
    tmp_ch = _face_front[mp2[3]];
    for (int i = 3; i > 0; --i) {
        _face_front[mp2[i]] = _face_front[mp2[i-1]];
    }
    _face_front[mp2[0]] = tmp_ch;
    // 处理上下左右四个面上的棱块循环：
    char * mp3[] = {&_face_up[5], &_face_right[7], &_face_down[1], &_face_left[3]};
    tmp_ch = *mp3[3];
    for (int i = 3; i > 0; --i) {
        *mp3[i] = *mp3[i-1];
    }
    *mp3[0] = tmp_ch;
    // 处理上下左右四个面上的角块循环：
    char * mp4[] = {&_face_up[6], &_face_right[0], &_face_down[2], &_face_left[4]};
    tmp_ch = *mp4[3];
    for (int i = 3; i > 0; --i) {
        *mp4[i] = *mp4[i-1];
    }
    *mp4[0] = tmp_ch;

    char * mp5[] = {&_face_up[4], &_face_right[6], &_face_down[0], &_face_left[2]};
    tmp_ch = *mp5[3];
    for (int i = 3; i > 0; --i) {
        *mp5[i] = *mp5[i-1];
    }
    *mp5[0] = tmp_ch;
}

void Cube3::rotate_f_plus() {
    // 处理front面上的棱块循环
    int mp[] = {1, 3, 5, 7};
    char tmp_ch = _face_front[mp[0]];
    for (int i = 0; i < 3; ++i) {
        _face_front[mp[i]] = _face_front[mp[i+1]];
    }
    _face_front[mp[3]] = tmp_ch;
    // 处理front面上的角块循环
    int mp2[] = {0, 2, 4, 6};
    tmp_ch = _face_front[mp2[0]];
    for (int i = 0; i < 3; ++i) {
        _face_front[mp2[i]] = _face_front[mp2[i+1]];
    }
    _face_front[mp2[3]] = tmp_ch;
    // 处理上下左右四个面上的棱块循环：
    char * mp3[] = {&_face_up[5], &_face_right[7], &_face_down[1], &_face_left[3]};
    tmp_ch = *mp3[0];
    for (int i = 0; i < 3; ++i) {
        *mp3[i] = *mp3[i+1];
    }
    *mp3[3] = tmp_ch;
    // 处理上下左右四个面上的角块循环：
    char * mp4[] = {&_face_up[6], &_face_right[0], &_face_down[2], &_face_left[4]};
    tmp_ch = *mp4[0];
    for (int i = 0; i < 3; ++i) {
        *mp4[i] = *mp4[i+1];
    }
    *mp4[3] = tmp_ch;

    char * mp5[] = {&_face_up[4], &_face_right[6], &_face_down[0], &_face_left[2]};
    tmp_ch = *mp5[0];
    for (int i = 0; i < 3; ++i) {
        *mp5[i] = *mp5[i+1];
    }
    *mp5[3] = tmp_ch;
}

void Cube3::rotate_l() {
    // 处理left面上的棱块循环
    int mp[] = {1, 3, 5, 7};
    char tmp_ch = _face_left[mp[3]];
    for (int i = 3; i > 0; --i) {
        _face_left[mp[i]] = _face_left[mp[i-1]];
    }
    _face_left[mp[0]] = tmp_ch;
    // 处理left面上的角块循环
    int mp2[] = {0, 2, 4, 6};
    tmp_ch = _face_left[mp2[3]];
    for (int i = 3; i > 0; --i) {
        _face_left[mp2[i]] = _face_left[mp2[i-1]];
    }
    _face_left[mp2[0]] = tmp_ch;
    // 处理上下前后四个面上的棱块循环：
    char * mp3[] = {&_face_up[7], &_face_front[7], &_face_down[7], &_face_back[3]};
    tmp_ch = *mp3[3];
    for (int i = 3; i > 0; --i) {
        *mp3[i] = *mp3[i-1];
    }
    *mp3[0] = tmp_ch;
    // 处理上下前后四个面上的角块循环：
    char * mp4[] = {&_face_up[0], &_face_front[0], &_face_down[0], &_face_back[4]};
    tmp_ch = *mp4[3];
    for (int i = 3; i > 0; --i) {
        *mp4[i] = *mp4[i-1];
    }
    *mp4[0] = tmp_ch;

    char * mp5[] = {&_face_up[6], &_face_front[6], &_face_down[6], &_face_back[2]};
    tmp_ch = *mp5[3];
    for (int i = 3; i > 0; --i) {
        *mp5[i] = *mp5[i-1];
    }
    *mp5[0] = tmp_ch;
}

void Cube3::rotate_l_plus() { 
    // 处理left面上的棱块循环
    int mp[] = {1, 3, 5, 7};
    char tmp_ch = _face_left[mp[0]];
    for (int i = 0; i < 3; ++i) {
        _face_left[mp[i]] = _face_left[mp[i+1]];
    }
    _face_left[mp[3]] = tmp_ch;
    // 处理left面上的角块循环
    int mp2[] = {0, 2, 4, 6};
    tmp_ch = _face_left[mp2[0]];
    for (int i = 0; i < 3; ++i) {
        _face_left[mp2[i]] = _face_left[mp2[i+1]];
    }
    _face_left[mp2[3]] = tmp_ch;
    // 处理上下前后四个面上的棱块循环：
    char * mp3[] = {&_face_up[7], &_face_front[7], &_face_down[7], &_face_back[3]};
    tmp_ch = *mp3[0];
    for (int i = 0; i < 3; ++i) {
        *mp3[i] = *mp3[i+1];
    }
    *mp3[3] = tmp_ch;
    // 处理上下前后四个面上的角块循环：
    char * mp4[] = {&_face_up[0], &_face_front[0], &_face_down[0], &_face_back[4]};
    tmp_ch = *mp4[0];
    for (int i = 0; i < 3; ++i) {
        *mp4[i] = *mp4[i+1];
    }
    *mp4[3] = tmp_ch;

    char * mp5[] = {&_face_up[6], &_face_front[6], &_face_down[6], &_face_back[2]};
    tmp_ch = *mp5[0];
    for (int i = 0; i < 3; ++i) {
        *mp5[i] = *mp5[i+1];
    }
    *mp5[3] = tmp_ch;
}

void Cube3::rotate_d() {
    // 处理down面上的棱块循环
    int mp[] = {1, 3, 5, 7};
    char tmp_ch = _face_down[mp[3]];
    for (int i = 3; i > 0; --i) {
        _face_down[mp[i]] = _face_down[mp[i-1]];
    }
    _face_down[mp[0]] = tmp_ch;
    // 处理down面上的角块循环
    int mp2[] = {0, 2, 4, 6};
    tmp_ch = _face_down[mp2[3]];
    for (int i = 3; i > 0; --i) {
        _face_down[mp2[i]] = _face_down[mp2[i-1]];
    }
    _face_down[mp2[0]] = tmp_ch;
    // 处理前后左右四个面上的棱块循环：
    char * mp3[] = {&_face_front[5], &_face_right[5], &_face_back[5], &_face_left[5]};
    tmp_ch = *mp3[3];
    for (int i = 3; i > 0; --i) {
        *mp3[i] = *mp3[i-1];
    }
    *mp3[0] = tmp_ch;
    // 处理前后左右四个面上的角块循环：
    char * mp4[] = {&_face_front[6], &_face_right[6], &_face_back[6], &_face_left[6]};
    tmp_ch = *mp4[3];
    for (int i = 3; i > 0; --i) {
        *mp4[i] = *mp4[i-1];
    }
    *mp4[0] = tmp_ch;

    char * mp5[] = {&_face_front[4], &_face_right[4], &_face_back[4], &_face_left[4]};
    tmp_ch = *mp5[3];
    for (int i = 3; i > 0; --i) {
        *mp5[i] = *mp5[i-1];
    }
    *mp5[0] = tmp_ch;
}

void Cube3::rotate_d_plus() {
    // 处理down面上的棱块循环
    int mp[] = {1, 3, 5, 7};
    char tmp_ch = _face_down[mp[0]];
    for (int i = 0; i < 3; ++i) {
        _face_down[mp[i]] = _face_down[mp[i+1]];
    }
    _face_down[mp[3]] = tmp_ch;
    // 处理down面上的角块循环
    int mp2[] = {0, 2, 4, 6};
    tmp_ch = _face_down[mp2[0]];
    for (int i = 0; i < 3; ++i) {
        _face_down[mp2[i]] = _face_down[mp2[i+1]];
    }
    _face_down[mp2[3]] = tmp_ch;
    // 处理前后左右四个面上的棱块循环：
    char * mp3[] = {&_face_front[5], &_face_right[5], &_face_back[5], &_face_left[5]};
    tmp_ch = *mp3[0];
    for (int i = 0; i < 3; ++i) {
        *mp3[i] = *mp3[i+1];
    }
    *mp3[3] = tmp_ch;
    // 处理前后左右四个面上的角块循环：
    char * mp4[] = {&_face_front[6], &_face_right[6], &_face_back[6], &_face_left[6]};
    tmp_ch = *mp4[0];
    for (int i = 0; i < 3; ++i) {
        *mp4[i] = *mp4[i+1];
    }
    *mp4[3] = tmp_ch;

    char * mp5[] = {&_face_front[4], &_face_right[4], &_face_back[4], &_face_left[4]};
    tmp_ch = *mp5[0];
    for (int i = 0; i < 3; ++i) {
        *mp5[i] = *mp5[i+1];
    }
    *mp5[3] = tmp_ch;
}

void Cube3::rotate_b() {
    // 处理back面上的棱块循环
    int mp[] = {1, 3, 5, 7};
    char tmp_ch = _face_back[mp[3]];
    for (int i = 3; i > 0; --i) {
        _face_back[mp[i]] = _face_back[mp[i-1]];
    }
    _face_back[mp[0]] = tmp_ch;
    // 处理back面上的角块循环
    int mp2[] = {0, 2, 4, 6};
    tmp_ch = _face_back[mp2[3]];
    for (int i = 3; i > 0; --i) {
        _face_back[mp2[i]] = _face_back[mp2[i-1]];
    }
    _face_back[mp2[0]] = tmp_ch;
    // 处理上下左右四个面上的棱块循环：
    char * mp3[] = {&_face_up[1], &_face_left[7], &_face_down[5], &_face_right[3]};
    tmp_ch = *mp3[3];
    for (int i = 3; i > 0; --i) {
        *mp3[i] = *mp3[i-1];
    }
    *mp3[0] = tmp_ch;
    // 处理上下左右四个面上的角块循环：
    char * mp4[] = {&_face_up[0], &_face_left[6], &_face_down[4], &_face_right[2]};
    tmp_ch = *mp4[3];
    for (int i = 3; i > 0; --i) {
        *mp4[i] = *mp4[i-1];
    }
    *mp4[0] = tmp_ch;

    char * mp5[] = {&_face_up[2], &_face_left[0], &_face_down[6], &_face_right[4]};
    tmp_ch = *mp5[3];
    for (int i = 3; i > 0; --i) {
        *mp5[i] = *mp5[i-1];
    }
    *mp5[0] = tmp_ch;
}

void Cube3::rotate_b_plus() {
    // 处理back面上的棱块循环
    int mp[] = {1, 3, 5, 7};
    char tmp_ch = _face_back[mp[0]];
    for (int i = 0; i < 3; ++i) {
        _face_back[mp[i]] = _face_back[mp[i+1]];
    }
    _face_back[mp[3]] = tmp_ch;
    // 处理back面上的角块循环
    int mp2[] = {0, 2, 4, 6};
    tmp_ch = _face_back[mp2[0]];
    for (int i = 0; i < 3; ++i) {
        _face_back[mp2[i]] = _face_back[mp2[i+1]];
    }
    _face_back[mp2[3]] = tmp_ch;
    // 处理上下左右四个面上的棱块循环：
    char * mp3[] = {&_face_up[1], &_face_left[7], &_face_down[5], &_face_right[3]};
    tmp_ch = *mp3[0];
    for (int i = 0; i < 3; ++i) {
        *mp3[i] = *mp3[i+1];
    }
    *mp3[3] = tmp_ch;
    // 处理上下左右四个面上的角块循环：
    char * mp4[] = {&_face_up[0], &_face_left[6], &_face_down[4], &_face_right[2]};
    tmp_ch = *mp4[0];
    for (int i = 0; i < 3; ++i) {
        *mp4[i] = *mp4[i+1];
    }
    *mp4[3] = tmp_ch;

    char * mp5[] = {&_face_up[2], &_face_left[0], &_face_down[6], &_face_right[4]};
    tmp_ch = *mp5[0];
    for (int i = 0; i < 3; ++i) {
        *mp5[i] = *mp5[i+1];
    }
    *mp5[3] = tmp_ch;
}

void Cube3::rotate_op(std::string op) {
    if (op == "R") {
        rotate_r();
    } else if (op == "R\'") {
        rotate_r_plus();
    } else if (op == "R2") {
        rotate_r();
        rotate_r();
    } else if (op == "U") {
        rotate_u();
    } else if (op == "U\'") {
        rotate_u_plus();
    } else if (op == "U2") {
        rotate_u();
        rotate_u(); 
    } else if (op == "F") {
        rotate_f();
    } else if (op == "F\'") {
        rotate_f_plus();
    } else if (op == "F2") {
        rotate_f();
        rotate_f();
    } else if (op == "D") {
        rotate_d();
    } else if (op == "D\'") {
        rotate_d_plus();
    } else if (op == "D2") {
        rotate_d();
        rotate_d();
    } else if (op == "L") {
        rotate_l();
    } else if (op == "L\'") {
        rotate_l_plus();
    } else if (op == "L2") {
        rotate_l();
        rotate_l();
    } else if (op == "B") {
        rotate_b();
    } else if (op == "B\'") {
        rotate_b_plus();
    } else if (op == "B2") {
        rotate_b();
        rotate_b();
    } else {
        printf("rotate_op(%s), 未知的参数！\n", op.c_str());    
    } 
}

void Cube3::rotate_op(char * op) {
    if (strcmp(op, "R") == 0) {
        rotate_r();
    } else if (strcmp(op, "R\'") == 0) {
        rotate_r_plus();
    } else if (strcmp(op, "R2") == 0) {
        rotate_r();
        rotate_r(); // 偷懒
    } else if (strcmp(op, "U") == 0) {
        rotate_u();
    } else if (strcmp(op, "U\'") == 0) {
        rotate_u_plus();
    } else if (strcmp(op, "U2") == 0) {
        rotate_u();
        rotate_u(); 
    } else if (strcmp(op, "F") == 0) {
        rotate_f();
    } else if (strcmp(op, "F\'") == 0) {
        rotate_f_plus();
    } else if (strcmp(op, "F2") == 0) {
        rotate_f();
        rotate_f();
    } else if (strcmp(op, "D") == 0) {
        rotate_d();
    } else if (strcmp(op, "D\'") == 0) {
        rotate_d_plus();
    } else if (strcmp(op, "D2") == 0) {
        rotate_d();
        rotate_d();
    } else if (strcmp(op, "L") == 0) {
        rotate_l();
    } else if (strcmp(op, "L\'") == 0) {
        rotate_l_plus();
    } else if (strcmp(op, "L2") == 0) {
        rotate_l();
        rotate_l();
    } else if (strcmp(op, "B") == 0) {
        rotate_b();
    } else if (strcmp(op, "B\'") == 0) {
        rotate_b_plus();
    } else if (strcmp(op, "B2") == 0) {
        rotate_b();
        rotate_b();
    } else {
        printf("rotate_op(%s), 未知的参数！\n", op);
    }
}

bool Cube3::is_correct_rotate_option(std::string op) {
    int len = op.size();
    if (len > 2) {
        return false;
    }
    if (op[0] != 'R' && op[0] != 'L' && op[0] != 'U' && op[0] != 'D' && op[0] != 'F' && op[0] != 'B') {
        return false;
    }
    if (len == 1) {
        return true;
    }
    return op[1] == '2' || op[1] == '\'';
}
std::vector<std::string> Cube3::prase_string_to_rotate_op(std::string s) {
    std::vector<std::string> v, e;
    e.push_back("Error");
    int len = s.length();
    std::string tmp;
    for (int i = 0; i < len; ++i) {
        if (isspace(s[i])) {
            continue;
        }
        if (tmp=="") {
            if (!Cube3::is_correct_rotate_character(s[i])) {
                return e;
            }
            tmp += s[i];
        } else if (s[i] == '2' || s[i] == '\'') {
            if (!Cube3::is_correct_rotate_character(tmp[(int)tmp.length()-1])) {
                return e;
            }
            else {
                tmp += s[i];
                add_option(v, tmp);
                tmp = "";
            }
        } else if (Cube3::is_correct_rotate_character(s[i])) {
            if (!is_correct_rotate_option(tmp)) {
                return e;
            }
            add_option(v, tmp);
            tmp = "";
            tmp += s[i];
        } else {
            return e;
        }
    }
    if (tmp != "") {
        if (!is_correct_rotate_option(tmp)) {
            return e;
        }
        add_option(v, tmp);
    }
    return v;
}

void Cube3::add_option(std::vector<std::string>& v, std::string new_option) {
    if (!is_correct_rotate_option(new_option)) {
        printf("add_option, new_option不合法！\n");
        return;
    }
    int len = v.size();
    if (len == 0) {
        v.push_back(new_option);
        return;
    }
    std::string pre = v[len-1];
    v.pop_back();
    std::vector<std::string> wait_add = merge_two_rotate_option(pre, new_option);
    int len2 = wait_add.size();
    for (int i = 0; i < len2; ++i) {
        v.push_back(wait_add[i]);
    }
}
bool Cube3::is_opposite_rotate(std::string ra, std::string rb) {
    if (!Cube3::is_correct_rotate_option(ra) || !Cube3::is_correct_rotate_option(rb)) {
        return false;
    }
    if (ra.length() == rb.length()) {
        return false;
    }
    if (ra[0] != rb[0]) {
        return false;
    }
    if (ra.length() > rb.length()) {
        swap(ra, rb);
    }
    return rb[1] == '\'';
}
std::vector<std::string> Cube3::merge_two_rotate_option(std::string pre, std::string post) {
    std::vector<std::string> v;
    if (is_opposite_rotate(pre, post)) {
        return v;
    }
    if (pre[0] != post[0]) {
        v.push_back(pre);
        v.push_back(post);
        return v;
    }
    int len1 = pre.length();
    int len2 = post.length();
    if (len1 == 1 && len2 == 1) {
        std::string tmp = pre;
        tmp += '2';
        v.push_back(tmp);
        return v;
    }
    if (len1 == 2 && len2 == 2) {
        if (pre[1] == '2' && post[1] == '2') { // R2 R2 => 空
            return v;
        } 
        if (pre[1] == '\'' && post[1] == '\'') {
            std::string tmp;
            tmp += pre[0];
            tmp += '2';
            v.push_back(tmp);
            return v;
        }
        if ((pre[1] == '\'' && post[1] =='2') || (pre[1] == '2' && post[1] == '\'') ) {
            std::string tmp;
            tmp += pre[0];
            v.push_back(tmp);
            return v;
        }
    }
    if (len1 > len2) {
        std::string tmp_s = pre;
        pre = post;
        post = tmp_s;
    }
    if (post[1] == '\'') {
        return v;
    } else { //post[1] == '2'  R R2
        std::string tmp;
        tmp += pre[0];
        tmp += '\'';
        v.push_back(tmp);
        return v;
    }
}

bool Cube3::is_correct_rotate_character(char ch) {
    char op_list[] = "LRUDFB";
    for (int i = 0; i < 6; ++i) {
        if (ch == op_list[i]) {
            return true;
        }
    }
    return false;
}

std::vector<std::string>Cube3::get_a_random_disturb() {
    int cnt = 20;
    std::vector<std::string> v;
    //srand(time(NULL));
    char rotate_list[] = "LURFDB";
    while ((int)v.size() < cnt) {
        std::string tmp;
         tmp += rotate_list[rand() % 6];
         int op = rand() % 3;
         if (op == 0) {
            tmp += '2';
         } else if (op == 1) {
            tmp += '\'';
         }
         add_option(v, tmp);
    }
    return v;
}

int main(int argc, const char * argv[]) {
    Cube3 * p = new Cube3();
    std::string f, u;


    srand(time(NULL));

    for (int i = 1; i <= 1; ++i) {
        std::vector<std::string> op_list = Cube3::get_a_random_disturb();
        for (int j = 0; j < (int)op_list.size(); ++j)
             std::cout<<op_list[j]<<" ";
        std::cout<<"\n";
        p->disturb_cube(op_list);
        p->show_all_face_color_graphically();
    }
   



    return 0;
 
    //---------------
    char face_front[] = "ORGRGRWO";
    char face_up[] =    "OGYBRBWO";
    char face_left[] =  "YYBWGOWB";
    char face_right[] = "YWBGOGOY";
    char face_back[] =  "RYBYROGR";
    char face_down[] =  "RWWWYBBG";
//    p->set_face_color(face_up, face_down, face_left, face_right, face_front, face_back);
    std::string disturb_str = "B2 D2 L2 B' D2 B D2 L2 F R2 U' B' U' R' D2 B F2 L2 F";

//    std::string disturb_str = "B2D2L2B'D2BD2L2FR2U'B'U'    R'D2BF2L2F";
    std::cout<<"up "<<face_up<<"\n";
    std::cout<<"front "<<face_front<<"\n";
    std::cout<<"down "<<face_down<<"\n";
    std::cout<<"left "<<face_left<<"\n";
    std::cout<<"right "<<face_right<<"\n";
    std::cout<<"back "<<face_back<<"\n";







    return 0;
    std::cout<<"打乱为："<<disturb_str<<"\n";
    std::cout<<"处理后：";
    std::vector<std::string> v_prase = Cube3::prase_string_to_rotate_op(disturb_str);
    for (int i = 0; i < (int )v_prase.size(); ++i) {
        std::cout<<v_prase[i]<<" ";
    }
    std::cout<<"\n";
//    p->restore_directly(); 
    std::cout<<"打乱之前：\n";
    p->show_all_face_color();
    
    for (int i = 0; i < (int)v_prase.size(); ++i) {
        p->rotate_op(v_prase[i]);
    }
    p->show_all_face_color();
    p->show_all_face_color_graphically();
    return 0;


    p->show_all_face_color();

    p->rotate_b();
    p->rotate_b_plus();
    printf("BB'之后：\n");
    p->show_all_face_color();
    /*
       printf("请输入前面的颜色和上面的颜色：\n");
    while (std::cin>>f>>u) {
        bool tag = p->reset_color(f[0], u[0]); 
        if (tag)
            p->show_face_color_msg();
        else 
            printf("输入有误！\n");
        printf("请输入前面的颜色和上面的颜色：\n");
    }
    */
    delete p;

 return 0;
}
