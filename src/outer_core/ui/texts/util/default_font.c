
const int font_left_side = 2;
const int font_right_side = 13;
const int font_bottom_side = 2;
const int font_top_side = 13;
const int font_upperMiddleSideY = 8;
const int font_lowerMiddleSideY = 5;
const int font_lowerTopSide = 9;
const int elStart = 6;
const int curve = 3;
const int font_lowerCurve = 2;
const int middleSideX = 8;

const unsigned char font_question_mark_length = 9 * 2;
const byte2 font_question_mark[] =
{
    { font_left_side, font_top_side }, { font_right_side, font_top_side },  // top line
    { font_left_side, font_top_side }, { 3, 9 },
    { font_left_side, 9 }, { 5, 9 },
    { font_right_side, font_top_side }, { font_right_side, 7 },
    // right middle to middle
    { font_right_side, 7 }, { 7, 7 },    
    // middle to down line
    { 7, 7 }, { 7, 5 },     
    // dot
    { 6, 3 }, { 8, 3 },
    { 6, 2 }, { 8, 2 }
};

const unsigned char font_space_length = 1 * 2;
const byte2 font_space[] =
{
    { font_left_side, font_bottom_side }, { font_right_side, font_bottom_side }
};

const unsigned char number_0_length = 4 * 2;
const byte2 number_0[] =
{
    { font_left_side, font_top_side }, { font_right_side, font_top_side },
    { font_right_side, font_top_side }, { font_right_side, font_bottom_side },
    { font_left_side, font_top_side }, { font_left_side, font_bottom_side },
    { font_left_side, font_bottom_side }, { font_right_side, font_bottom_side }
};

const int number_1_length = 4 * 2;
const byte2 number_1[] =
{
    { middleSideX, font_bottom_side }, { middleSideX, font_top_side },
    { middleSideX, font_top_side }, { middleSideX - curve, font_top_side - curve },
    { middleSideX, font_bottom_side }, { font_left_side + 1, font_bottom_side },
    { middleSideX, font_bottom_side }, { font_right_side - 1, font_bottom_side },
};

const int number_2_length = 5 * 2;
const byte2 number_2[] =
{
    { font_left_side, font_top_side - 3 }, { font_left_side, font_top_side },
    { font_left_side, font_top_side }, { font_right_side - 3, font_top_side },
    { font_right_side - 3, font_top_side }, { font_right_side, font_top_side - 4 },
    { font_right_side, font_top_side - 4 }, { font_left_side, font_bottom_side },
    { font_left_side, font_bottom_side }, { font_right_side, font_bottom_side }
};

const int number_3_length = 9 * 2;
const byte2 number_3[] =
{
    { font_left_side, font_top_side }, { font_right_side - curve, font_top_side },
    { font_right_side - curve, font_top_side }, { font_right_side, font_top_side - curve },
    { font_right_side, font_top_side - curve }, { font_right_side, font_upperMiddleSideY + curve },
    { font_right_side, font_upperMiddleSideY + curve }, { font_right_side - curve, font_upperMiddleSideY },
    { font_right_side - curve, font_upperMiddleSideY }, { font_left_side + curve, font_upperMiddleSideY },
    { font_right_side - curve, font_upperMiddleSideY }, { font_right_side, font_upperMiddleSideY - curve },
    { font_right_side, font_upperMiddleSideY - curve }, { font_right_side, font_bottom_side + curve },
    { font_right_side, font_bottom_side + curve }, { font_right_side - curve, font_bottom_side },
    { font_right_side - curve, font_bottom_side }, { font_left_side, font_bottom_side }
};

const int number_4_length = 3 * 2;
const byte2 number_4[] =
{
    { middleSideX, font_top_side }, { font_left_side, font_upperMiddleSideY },
    { middleSideX, font_top_side }, { font_upperMiddleSideY, font_bottom_side },
    { font_left_side, font_upperMiddleSideY }, { font_right_side, font_upperMiddleSideY }
};

const int number_5_length = 7 * 2;
const byte2 number_5[] =
{
    { font_left_side, font_top_side }, { font_right_side, font_top_side },
    { font_left_side, font_top_side }, { font_left_side, font_upperMiddleSideY },
    { font_left_side, font_upperMiddleSideY }, { font_right_side - 3, font_upperMiddleSideY },
    { font_right_side - 3, font_upperMiddleSideY }, { font_right_side, font_upperMiddleSideY - 3 },
    { font_right_side, font_upperMiddleSideY - 3 }, { font_right_side, font_bottom_side + 3 },
    { font_right_side, font_bottom_side + 3 }, { font_right_side - 3, font_bottom_side },
    { font_right_side - 3, font_bottom_side }, { font_left_side, font_bottom_side }
};

const int number_6_length = 10 * 2;
const byte2 number_6[] =
{
    { font_left_side, font_top_side }, { font_right_side, font_top_side },
    { font_right_side, font_top_side }, { font_right_side, font_top_side - 2 },
    { font_left_side, font_top_side }, { font_left_side, font_upperMiddleSideY },
    { font_left_side, font_upperMiddleSideY }, { font_right_side - 3, font_upperMiddleSideY },
    { font_right_side - 3, font_upperMiddleSideY }, { font_right_side, font_upperMiddleSideY - 3 },
    { font_right_side, font_upperMiddleSideY - 3 }, { font_right_side, font_bottom_side + 3 },
    { font_right_side, font_bottom_side + 3 }, { font_right_side - 3, font_bottom_side },
    { font_right_side - 3, font_bottom_side }, { font_left_side, font_bottom_side },
    { font_right_side - 3, font_bottom_side }, { font_left_side, font_bottom_side },
    { font_left_side, font_bottom_side }, { font_left_side, font_upperMiddleSideY }
};

const int number_7_length = 2 * 2;
const byte2 number_7[] =
{
    { font_left_side, font_top_side }, { font_right_side, font_top_side },
    { font_right_side, font_top_side }, { font_left_side, font_bottom_side }
};

const int number_8_length = 5 * 2;
const byte2 number_8[] =
{
    { font_left_side, font_top_side }, { font_right_side, font_top_side },
    { font_left_side, font_upperMiddleSideY }, { font_right_side, font_upperMiddleSideY },
    { font_left_side, font_bottom_side }, { font_right_side, font_bottom_side },
    { font_left_side, font_top_side }, { font_left_side, font_bottom_side },
    { font_right_side, font_top_side }, { font_right_side, font_bottom_side }
};

const int number_9_length = 5 * 2;
const byte2 number_9[] =
{
    { font_left_side, font_top_side }, { font_right_side, font_top_side },
    { font_left_side, font_upperMiddleSideY }, { font_right_side, font_upperMiddleSideY },
    { font_left_side, font_bottom_side }, { font_right_side, font_bottom_side },
    { font_left_side, font_top_side }, { font_left_side, font_upperMiddleSideY },
    { font_right_side, font_top_side }, { font_right_side, font_bottom_side }
};

const byte2 specialSlash[] =
{
    { 3, 3 }, { 12, 12 }
};

const byte2 specialHyphen[] =
{
    { font_left_side, font_upperMiddleSideY }, { font_right_side, font_upperMiddleSideY }
};

const byte2 specialArrowLeft[] =
{
    { font_left_side, font_upperMiddleSideY }, { font_right_side, font_top_side }, 
    { font_left_side, font_upperMiddleSideY }, { font_right_side, font_bottom_side }
};

const byte2 specialArrowRight[] =
{
    { font_right_side, font_upperMiddleSideY }, { font_left_side, font_top_side }, 
    { font_right_side, font_upperMiddleSideY }, { font_left_side, font_bottom_side }
};

const byte2 specialCross[] =
{
    { middleSideX, font_upperMiddleSideY }, { font_left_side, font_top_side }, 
    { middleSideX, font_upperMiddleSideY }, { font_right_side, font_top_side },
    { middleSideX, font_upperMiddleSideY }, { font_left_side, font_bottom_side },
    { middleSideX, font_upperMiddleSideY }, { font_right_side, font_bottom_side }
};



const byte2 specialPlus[] =
{
    { font_left_side, font_upperMiddleSideY }, { middleSideX, font_upperMiddleSideY },
    { middleSideX, font_upperMiddleSideY }, { font_right_side, font_upperMiddleSideY },
    { middleSideX, font_upperMiddleSideY }, { middleSideX, font_top_side },
    { middleSideX, font_upperMiddleSideY }, { middleSideX, font_bottom_side }
};

const byte2 specialPercentage[] =
{
    { 3, 3 }, { 12, 12 },
    { 3, 9 }, { 4, 10 },
    { 9, 3 }, { 10, 4 }
};
const byte2 specialExclemation[] =
{
    { 7, 6 }, { 7, 13 },
    { 8, 6 }, { 8, 13 },
    { 9, 6 }, { 9, 13 },
    { 7, 1 }, { 9, 1 },
    { 7, 3 }, { 9, 3 }
};

const byte2 leftSquareBrackets[] =
{
    { middleSideX, font_bottom_side }, { middleSideX, font_top_side },
    { middleSideX, font_bottom_side }, { font_right_side, font_bottom_side },
    { middleSideX, font_top_side }, { font_right_side, font_top_side }
};

const byte2 rightSquareBrackets[] =
{
    { middleSideX, font_bottom_side }, { middleSideX, font_top_side },
    { middleSideX, font_bottom_side }, { font_left_side, font_bottom_side },
    { middleSideX, font_top_side }, { font_left_side, font_top_side }
};

const byte2 specialDot[] = 
{
    { 7, 3 }, { 9, 3 },
    { 7, 5 }, { 9, 5 }
};

const byte2 specialComma[] = 
{
    { 7, 3 }, { 9, 3 },
    { 7, 5 }, { 9, 5 },
    { 7, 3 }, { 3, 1 },
    { 9, 3 }, { 3, 1 }
};

// todo: this
const byte2 specialQuestionMark[] = 
{
    { 3, 12 }, { 10, 12 },  // top line
    // side lines
    { 3, 12 }, { 3, 7 },
    { 10, 12 }, { 10, 7 },

    { 10, 7 }, { 5, 7 }, // right middle to middle
    { 5, 7 }, { 5, 4 }, // middle to down
    { 4, 2 }, { 6, 2 }, // dot
};

const byte2 specialApostrophe[] = 
{
    { 7, 10 }, { 9, 10 },
    { 7, 11 }, { 9, 11 },
    { 7, 12 }, { 9, 12 },
    { 7, 13 }, { 9, 13 }
};

const byte2 specialDoubleDots[] = 
{
    { middleSideX, 4 }, { middleSideX + 2, 4 },
    { middleSideX + 2, 4 }, { middleSideX + 2, 6 },
    { middleSideX, 6 }, { middleSideX + 2, 6 },
    { middleSideX, 4 }, { middleSideX, 7 },
    { middleSideX, 10 }, { middleSideX + 2, 10 },
    { middleSideX + 2, 10 }, { middleSideX + 2, 10 },
    { middleSideX, 12 }, { middleSideX + 2, 12 },
    { middleSideX, 12 }, { middleSideX, 12 },
};

const int font_lower_a_length = 9 * 2;
const byte2 font_lower_a[] =
{
    // right line
    { font_right_side, font_lowerTopSide }, { font_right_side, font_lowerTopSide - curve },
    { font_right_side, font_lowerTopSide - curve }, { font_right_side, font_bottom_side + curve },
    { font_right_side, font_bottom_side + curve }, { font_right_side, font_bottom_side },
    // bottom
    { font_right_side, font_bottom_side + curve }, { font_right_side - curve, font_bottom_side },
    { font_right_side - curve, font_bottom_side }, { font_left_side + curve, font_bottom_side },
    { font_left_side + curve, font_bottom_side }, { font_left_side, font_lowerTopSide - curve },
    // top part
    { font_left_side, font_lowerTopSide - curve }, { font_left_side + curve, font_lowerTopSide },
    { font_left_side + curve, font_lowerTopSide }, { font_right_side - curve, font_lowerTopSide },
    { font_right_side - curve, font_lowerTopSide }, { font_right_side, font_lowerTopSide - curve },
};

const int font_upper_a_length = 3 * 2;
const byte2 font_upper_a[] =
{
    { font_left_side, font_bottom_side }, { middleSideX, font_top_side },
    { middleSideX, font_top_side }, { font_right_side, font_bottom_side },
    { font_left_side + 3, font_upperMiddleSideY }, { font_right_side - 3, font_upperMiddleSideY },
};

const int font_lower_b_length = 5 * 2;
const byte2 font_lower_b[] =
{
    { font_left_side, font_upperMiddleSideY }, { font_right_side, font_upperMiddleSideY },
    { font_left_side, font_bottom_side }, { font_right_side, font_bottom_side },
    { font_left_side, font_upperMiddleSideY }, { font_left_side, font_bottom_side },
    { font_right_side, font_upperMiddleSideY }, { font_right_side, font_bottom_side },
    { font_left_side, font_top_side }, { font_left_side, font_upperMiddleSideY }
};

const int font_upper_b_length = 11 * 2;
const byte2 font_upper_b[] =
{
    { font_left_side, font_top_side }, { font_left_side, font_upperMiddleSideY },
    { font_left_side, font_upperMiddleSideY }, { font_left_side, font_bottom_side },
    { font_left_side, font_upperMiddleSideY }, { font_right_side - curve, font_upperMiddleSideY },
    // bottom loop
    { font_left_side, font_bottom_side }, { font_right_side - curve, font_bottom_side },
    { font_right_side - curve, font_bottom_side }, { font_right_side, font_bottom_side + curve },
    { font_right_side, font_bottom_side + curve }, { font_right_side, font_upperMiddleSideY - curve },
    { font_right_side, font_upperMiddleSideY - curve }, { font_right_side - curve, font_upperMiddleSideY },
    // top loop
    { font_left_side, font_top_side }, { font_right_side - curve, font_top_side },
    { font_right_side - curve, font_top_side }, { font_right_side, font_top_side - curve },
    { font_right_side, font_top_side - curve }, { font_right_side, font_upperMiddleSideY + curve },
    { font_right_side, font_upperMiddleSideY + curve }, { font_right_side - curve, font_upperMiddleSideY },
};

const int font_lower_c_length = 8 * 2;
const byte2 font_lower_c[] =
{
    { font_left_side + font_lowerCurve, font_lowerTopSide }, { font_right_side - font_lowerCurve, font_lowerTopSide },
    { font_right_side - font_lowerCurve, font_lowerTopSide }, { font_right_side, font_lowerTopSide - font_lowerCurve / 2 },
    { font_left_side + font_lowerCurve, font_lowerTopSide }, { font_left_side, font_lowerTopSide - font_lowerCurve },
    { font_left_side, font_lowerTopSide - font_lowerCurve }, { font_left_side, font_bottom_side + font_lowerCurve },
    { font_left_side, font_bottom_side + font_lowerCurve }, { font_left_side + font_lowerCurve, font_bottom_side },
    { font_left_side + font_lowerCurve, font_bottom_side }, { font_right_side - font_lowerCurve, font_bottom_side },
    { font_right_side - font_lowerCurve, font_bottom_side }, { font_right_side, font_bottom_side + font_lowerCurve / 2 },
};

const int font_upper_c_length = 7 * 2;
const byte2 font_upper_c[] =
{
    { font_right_side, font_top_side - curve }, { font_right_side - curve, font_top_side },
    { font_right_side - curve, font_top_side }, { font_left_side + curve, font_top_side },
    { font_left_side + curve, font_top_side }, { font_left_side, font_top_side - curve },
    { font_left_side, font_top_side - curve }, { font_left_side, font_bottom_side + curve },
    { font_left_side, font_bottom_side + curve }, { font_left_side + curve, font_bottom_side },
    { font_left_side + curve, font_bottom_side }, { font_right_side - curve, font_bottom_side },
    { font_right_side - curve, font_bottom_side }, { font_right_side, font_bottom_side + curve },
};

const int font_lower_d_length = 5 * 2;
const byte2 font_lower_d[] =
{
    { font_left_side, middleSideX }, { font_right_side, middleSideX },
    { font_left_side, font_bottom_side }, { font_right_side, font_bottom_side },
    { font_left_side, middleSideX }, { font_left_side, font_bottom_side },
    { font_right_side, middleSideX }, { font_right_side, font_bottom_side },
    { font_right_side, font_top_side }, { font_right_side, middleSideX }
};

const int font_upper_d_length = 6 * 2;
const byte2 font_upper_d[] =
{
    { font_left_side, font_top_side }, { font_left_side, font_bottom_side },
    { font_left_side, font_top_side }, { middleSideX, font_top_side },
    { middleSideX, font_top_side }, { font_right_side, font_top_side - curve },
    { font_right_side, font_top_side - curve }, { font_right_side, font_bottom_side + curve },
    { font_right_side, font_bottom_side + curve }, { middleSideX, font_bottom_side },
    { middleSideX, font_bottom_side }, { font_left_side, font_bottom_side }
};

const int font_lower_e_length = 7 * 2;
const byte2 font_lower_e[] =
{
    { font_left_side, font_lowerTopSide }, { font_right_side, font_lowerTopSide },
    { font_right_side, font_lowerTopSide }, { font_right_side, font_lowerMiddleSideY },
    { font_right_side, font_lowerMiddleSideY }, { font_left_side, font_lowerMiddleSideY },
    { font_left_side, font_lowerMiddleSideY }, { font_left_side, font_lowerTopSide },
    { font_left_side, font_lowerMiddleSideY }, { font_left_side, font_bottom_side },
    { font_left_side, font_bottom_side }, { font_right_side, font_bottom_side },
    { font_right_side, font_bottom_side }, { font_right_side, font_bottom_side + 1 }
};

const int font_upper_e_length = 4 * 2;
const byte2 font_upper_e[] =
{
    { font_left_side, font_bottom_side }, { font_left_side, font_top_side },
    { font_left_side, font_bottom_side }, { font_right_side, font_bottom_side },
    { font_left_side, font_top_side }, { font_right_side, font_top_side },
    { font_left_side, font_upperMiddleSideY }, { font_right_side - curve, font_upperMiddleSideY }
};

const int font_lower_f_length = 4 * 2;
const byte2 font_lower_f[] =
{
    { middleSideX, font_top_side }, { middleSideX, middleSideX },
    { middleSideX, font_top_side }, { font_right_side, font_top_side },
    { middleSideX, middleSideX }, { middleSideX, font_bottom_side },
    { font_left_side, middleSideX }, { font_right_side, middleSideX }
};

const int font_upper_f_length = 4 * 2;
const byte2 font_upper_f[] =
{
    { font_left_side, font_top_side }, { font_left_side, middleSideX },
    { font_left_side, font_top_side }, { font_right_side, font_top_side },
    { font_left_side, middleSideX }, { font_left_side, font_bottom_side },
    { font_left_side, middleSideX }, { font_right_side, middleSideX }
};

const int font_lower_g_length = 6 * 2;
const byte2 font_lower_g[] =
{
    { font_left_side, font_lowerTopSide }, { font_right_side, font_lowerTopSide },
    { font_right_side, font_lowerTopSide }, { font_right_side, font_lowerMiddleSideY },
    { font_right_side, font_lowerMiddleSideY }, { font_left_side, font_lowerMiddleSideY },
    { font_left_side, font_lowerTopSide }, { font_left_side, font_lowerMiddleSideY },
    { font_right_side, font_lowerMiddleSideY }, { font_right_side, font_bottom_side },
    { font_right_side, font_bottom_side }, { font_left_side, font_bottom_side }
};

const int font_upper_g_length = 8 * 2;
const byte2 font_upper_g[] =
{
    { font_right_side, font_top_side - curve }, { font_right_side - curve, font_top_side },
    { font_right_side - curve, font_top_side }, { font_left_side + curve, font_top_side },
    { font_left_side + curve, font_top_side }, { font_left_side, font_top_side - curve },
    { font_left_side, font_top_side - curve }, { font_left_side, font_bottom_side + curve },
    { font_left_side, font_bottom_side + curve }, { font_left_side + curve, font_bottom_side },
    { font_left_side + curve, font_bottom_side }, { font_right_side - curve, font_bottom_side },
    { font_right_side - curve, font_bottom_side }, { font_right_side, font_bottom_side + curve + 2 },
    { font_right_side, font_bottom_side + curve + 2 }, { font_right_side - curve - 1, font_bottom_side + curve },
};

const int font_lower_h_length = 4 * 2;
const byte2 font_lower_h[] =
{
    { font_left_side, font_top_side }, { font_left_side, middleSideX },
    { font_left_side, middleSideX }, { font_left_side, font_bottom_side },
    { font_left_side, middleSideX }, { font_right_side, middleSideX },
    { font_right_side, middleSideX }, { font_right_side, font_bottom_side }
};

const int font_upper_h_length = 5 * 2;
const byte2 font_upper_h[] =
{
    { font_left_side, font_top_side }, { font_left_side, middleSideX },
    { font_left_side, middleSideX }, { font_left_side, font_bottom_side },
    { font_left_side, middleSideX }, { font_right_side, middleSideX },
    { font_right_side, middleSideX }, { font_right_side, font_bottom_side },
    { font_right_side, middleSideX }, { font_right_side, font_top_side }
};

const int font_lower_i_length = 2 * 2;
const byte2 font_lower_i[] =
{
    { middleSideX, font_bottom_side }, { middleSideX, middleSideX + 1 },
    { middleSideX, middleSideX + 4 }, { middleSideX, middleSideX + 6 }
};

const int font_upper_i_length = 5 * 2;
const byte2 font_upper_i[] =
{
    { middleSideX, font_top_side }, { middleSideX, font_bottom_side },
    { font_left_side, font_top_side }, { middleSideX, font_top_side },
    { font_right_side, font_top_side }, { middleSideX, font_top_side },
    { font_left_side, font_bottom_side }, { middleSideX, font_bottom_side },
    { font_right_side, font_bottom_side }, { middleSideX, font_bottom_side }
};

const int font_lower_j_length = 3 * 2;
const byte2 font_lower_j[] =
{
    { middleSideX, font_lowerTopSide }, { middleSideX, font_bottom_side + 2 },
    { middleSideX - 2, font_bottom_side }, { middleSideX, font_bottom_side + 2 },
    { middleSideX - 2, font_bottom_side }, { middleSideX - 3, font_bottom_side },
};

const int font_upper_j_length = 3 * 2;
const byte2 font_upper_j[] =
{
    { middleSideX, font_top_side }, { middleSideX, font_bottom_side + 2 },
    { middleSideX - 2, font_bottom_side }, { middleSideX, font_bottom_side + 2 },
    { middleSideX - 2, font_bottom_side }, { middleSideX - 3, font_bottom_side },
};

const int font_lower_k_length = 4 * 2;
const byte2 font_lower_k[] =
{
    { font_left_side, font_lowerTopSide }, { font_left_side, font_lowerMiddleSideY },
    { font_left_side, font_lowerMiddleSideY }, { font_left_side, font_bottom_side },
    { font_left_side, font_lowerMiddleSideY }, { font_right_side, font_lowerTopSide },
    { font_left_side, font_lowerMiddleSideY }, { font_right_side, font_bottom_side },
};

const int font_upper_k_length = 4 * 2;
const byte2 font_upper_k[] =
{
    { font_left_side, font_top_side }, { font_left_side, middleSideX },
    { font_left_side, middleSideX }, { font_left_side, font_bottom_side },
    { font_left_side, middleSideX }, { font_right_side, font_top_side },
    { font_left_side, middleSideX }, { font_right_side, font_bottom_side },
};

const int font_lower_l_length = 3 * 2;
const byte2 font_lower_l[] =
{
    { elStart, font_bottom_side }, { elStart, font_top_side },
    { elStart, font_bottom_side }, { elStart + curve, font_bottom_side },
    { elStart + curve, font_bottom_side }, { elStart + curve, font_bottom_side + curve }
};

const int font_upper_l_length = 3 * 2;
const byte2 font_upper_l[] =
{
    { font_left_side, font_bottom_side }, { font_left_side, font_top_side },
    { font_left_side, font_bottom_side }, { font_right_side, font_bottom_side },
    { font_right_side, font_bottom_side }, { font_right_side, font_bottom_side + 2 }
};

const int font_lower_m_length = 4 * 2;
const byte2 font_lower_m[] =
{
    { font_left_side, font_bottom_side }, { font_left_side, font_lowerTopSide },
    { font_right_side, font_bottom_side }, { font_right_side, font_lowerTopSide },
    { middleSideX, font_bottom_side }, { font_right_side, font_lowerTopSide },
    { middleSideX, font_bottom_side }, { font_left_side, font_lowerTopSide },
};

// copy of font_lowerM
const int font_upper_m_length = 4 * 2;
const byte2 font_upper_m[] =
{
    { font_left_side, font_bottom_side }, { font_left_side, font_top_side },
    { font_right_side, font_bottom_side }, { font_right_side, font_top_side },
    { middleSideX, font_bottom_side }, { font_right_side, font_top_side },
    { middleSideX, font_bottom_side }, { font_left_side, font_top_side },
};

const int font_lower_n_length = 3 * 2;
const byte2 font_lower_n[] =
{
    { font_left_side, font_bottom_side }, { font_left_side, font_lowerTopSide },
    { font_left_side, font_bottom_side }, { font_right_side, font_lowerTopSide },
    { font_right_side, font_bottom_side }, { font_right_side, font_lowerTopSide },
};

// copy of font_lowerN
const int font_upper_n_length = 3 * 2;
const byte2 font_upper_n[] =
{
    { font_left_side, font_bottom_side }, { font_left_side, font_top_side },
    { font_left_side, font_bottom_side }, { font_right_side, font_top_side },
    { font_right_side, font_bottom_side }, { font_right_side, font_top_side },
};

const int font_lower_o_length = 4 * 2;
const byte2 font_lower_o[] =
{
    { font_left_side, font_lowerTopSide }, { font_right_side, font_lowerTopSide },
    { font_right_side, font_lowerTopSide }, { font_right_side, font_bottom_side },
    { font_left_side, font_lowerTopSide }, { font_left_side, font_bottom_side },
    { font_left_side, font_bottom_side }, { font_right_side, font_bottom_side }
};

// copy of font_lowerO
const int font_upper_o_length = 4 * 2;
const byte2 font_upper_o[] =
{
    { font_left_side, font_top_side }, { font_right_side, font_top_side },
    { font_right_side, font_top_side }, { font_right_side, font_bottom_side },
    { font_left_side, font_top_side }, { font_left_side, font_bottom_side },
    { font_left_side, font_bottom_side }, { font_right_side, font_bottom_side }
};

const int font_lower_p_length = 5 * 2;
const byte2 font_lower_p[] =
{
    { font_left_side, font_lowerTopSide }, { font_right_side, font_lowerTopSide },
    { font_right_side, font_lowerTopSide }, { font_right_side, font_lowerMiddleSideY },
    { font_right_side, font_lowerMiddleSideY }, { font_left_side, font_lowerMiddleSideY },
    { font_left_side, font_lowerMiddleSideY }, { font_left_side, font_lowerTopSide },
    { font_left_side, font_lowerMiddleSideY }, { font_left_side, font_bottom_side }
};

// copy of font_lowerP
const int font_upper_p_length = 5 * 2;
const byte2 font_upper_p[] =
{
    { font_left_side, font_top_side }, { font_right_side, font_top_side },
    { font_right_side, font_top_side }, { font_right_side, middleSideX },
    { font_right_side, middleSideX }, { font_left_side, middleSideX },
    { font_left_side, middleSideX }, { font_left_side, font_top_side },
    { font_left_side, middleSideX }, { font_left_side, font_bottom_side }
};

const int font_lower_q_length = 5 * 2;
const byte2 font_lower_q[] =
{
    { font_left_side, font_lowerTopSide }, { font_right_side, font_lowerTopSide },
    { font_right_side, font_lowerTopSide }, { font_right_side, font_lowerMiddleSideY },
    { font_right_side, font_lowerMiddleSideY }, { font_left_side, font_lowerMiddleSideY },
    { font_left_side, font_lowerMiddleSideY }, { font_left_side, font_lowerTopSide },
    { font_right_side, font_lowerMiddleSideY }, { font_right_side, font_bottom_side }
};

const int font_upper_q_length = 5 * 2;
const byte2 font_upper_q[] =
{
    { font_left_side, font_top_side }, { font_right_side, font_top_side },
    { font_right_side, font_top_side }, { font_right_side, middleSideX },
    { font_right_side, middleSideX }, { font_left_side, middleSideX },
    { font_left_side, middleSideX }, { font_left_side, font_top_side },
    { font_right_side, middleSideX }, { font_right_side, font_bottom_side }
};

const int font_lower_r_length = 3 * 2;
const byte2 font_lower_r[] =
{
    { font_left_side, middleSideX + 2 }, { font_left_side, font_bottom_side },
    { font_left_side, middleSideX - 3 }, { font_left_side + 3, middleSideX },
    { font_left_side + 3, middleSideX }, { font_right_side, middleSideX },
};

const int font_upper_r_length = 6 * 2;
const byte2 font_upper_r[] =
{
    { font_left_side, font_top_side }, { font_right_side, font_top_side },
    { font_right_side, font_top_side }, { font_right_side, middleSideX },
    { font_right_side, middleSideX }, { font_left_side, middleSideX },
    { font_left_side, middleSideX }, { font_left_side, font_top_side },
    { font_left_side, middleSideX }, { font_left_side, font_bottom_side },
    { font_left_side, middleSideX }, { font_right_side, font_bottom_side }
};

const int font_lower_s_length = 5 * 2;
const byte2 font_lower_s[] =
{
    { font_left_side, font_lowerTopSide }, { font_right_side, font_lowerTopSide },
    { font_left_side, font_lowerTopSide }, { font_left_side, font_lowerMiddleSideY },
    { font_left_side, font_lowerMiddleSideY }, { font_right_side, font_lowerMiddleSideY },
    { font_right_side, font_lowerMiddleSideY }, { font_right_side, font_bottom_side },
    { font_right_side, font_bottom_side }, { font_left_side, font_bottom_side },
};

const int font_upper_s_length = 5 * 2;
const byte2 font_upper_s[] =
{
    { font_left_side, font_top_side }, { font_right_side, font_top_side },
    { font_left_side, font_top_side }, { font_left_side, middleSideX },
    { font_left_side, middleSideX }, { font_right_side, middleSideX },
    { font_right_side, middleSideX }, { font_right_side, font_bottom_side },
    { font_right_side, font_bottom_side }, { font_left_side, font_bottom_side },
};

const int font_lower_t_length = 6 * 2;
const byte2 font_lower_t[] =
{
    { middleSideX, font_bottom_side }, { middleSideX, middleSideX },
    { middleSideX, middleSideX }, { middleSideX, font_top_side },
    { middleSideX, middleSideX }, { font_left_side, middleSideX },
    { middleSideX, middleSideX }, { font_right_side, middleSideX },
    { middleSideX, font_bottom_side }, { middleSideX + 3, font_bottom_side },
    { middleSideX + 3, font_bottom_side }, { middleSideX + 3, font_bottom_side + 2 }
};

const int font_upper_t_length = 3 * 2;
const byte2 font_upper_t[] =
{
    { middleSideX, font_top_side }, { middleSideX, font_bottom_side },
    { font_left_side, font_top_side }, { middleSideX, font_top_side },
    { font_right_side, font_top_side }, { middleSideX, font_top_side }
};

// Needs more curve
const int font_lower_u_length = 3 * 2;
const byte2 font_lower_u[] =
{
    { font_left_side, font_lowerTopSide }, { font_left_side, font_bottom_side },
    { font_left_side, font_bottom_side }, { font_right_side, font_bottom_side },
    { font_right_side, font_bottom_side }, { font_right_side, font_lowerTopSide }
};

// copied font_lowerU
const int font_upper_u_length = 3 * 2;
const byte2 font_upper_u[] =
{
    { font_left_side, font_top_side }, { font_left_side, font_bottom_side },
    { font_left_side, font_bottom_side }, { font_right_side, font_bottom_side },
    { font_right_side, font_bottom_side }, { font_right_side, font_top_side }
};

const int font_lower_v_length = 2 * 2;
const byte2 font_lower_v[] =
{
    { font_left_side, font_lowerTopSide }, { middleSideX, font_bottom_side },
    { middleSideX, font_bottom_side }, { font_right_side, font_lowerTopSide }
};

// copied font_lowerV
const int font_upper_v_length = 2 * 2;
const byte2 font_upper_v[] =
{
    { font_left_side, font_top_side }, { middleSideX, font_bottom_side },
    { middleSideX, font_bottom_side }, { font_right_side, font_top_side }
};

const int font_lower_w_length = 4 * 2;
const byte2 font_lower_w[] =
{
    { font_left_side, font_bottom_side }, { font_left_side, font_lowerTopSide },
    { font_right_side, font_bottom_side }, { font_right_side, font_lowerTopSide },
    { middleSideX, font_lowerTopSide }, { font_right_side, font_bottom_side },
    { middleSideX, font_lowerTopSide }, { font_left_side, font_bottom_side },
};

// copied font_lowerW
const int font_upper_w_length = 4 * 2;
const byte2 font_upper_w[] =
{
    { font_left_side, font_bottom_side }, { font_left_side, font_top_side },
    { font_right_side, font_bottom_side }, { font_right_side, font_top_side },
    { middleSideX, font_top_side }, { font_right_side, font_bottom_side },
    { middleSideX, font_top_side }, { font_left_side, font_bottom_side },
};

const int font_lower_x_length = 4 * 2;
const byte2 font_lower_x[] =
{
    { font_left_side, font_bottom_side }, { middleSideX, font_lowerMiddleSideY },
    { middleSideX, font_lowerMiddleSideY }, { font_right_side, font_lowerTopSide },
    { font_left_side, font_lowerTopSide }, { middleSideX, font_lowerMiddleSideY },
    { middleSideX, font_lowerMiddleSideY }, { font_right_side, font_bottom_side }
};

// copied font_lowerX
const int font_upper_x_length = 4 * 2;
const byte2 font_upper_x[] =
{
    { font_left_side, font_bottom_side }, { middleSideX, font_upperMiddleSideY },
    { middleSideX, font_upperMiddleSideY }, { font_right_side, font_top_side },
    { font_left_side, font_top_side }, { middleSideX, font_upperMiddleSideY },
    { middleSideX, font_upperMiddleSideY }, { font_right_side, font_bottom_side }
};

const int font_lower_y_length = 6 * 2;
const byte2 font_lower_y[] =
{
    { font_left_side, font_lowerTopSide }, { font_left_side, font_lowerMiddleSideY },
    { font_left_side, font_lowerMiddleSideY }, { font_right_side, font_lowerMiddleSideY },
    { font_right_side, font_lowerMiddleSideY }, { font_right_side, font_lowerTopSide },
    { font_right_side, font_lowerMiddleSideY }, { font_right_side, font_bottom_side },
    { font_right_side, font_bottom_side }, { font_left_side + 2, font_bottom_side },
    { font_left_side + 2, font_bottom_side }, { font_left_side + 2, font_bottom_side + 1 },
};

// copied font_lowerY
const int font_upper_y_length = 6 * 2;
const byte2 font_upper_y[] =
{
    { font_left_side, font_top_side }, { font_left_side, font_upperMiddleSideY },
    { font_left_side, font_upperMiddleSideY }, { font_right_side, font_upperMiddleSideY },
    { font_right_side, font_upperMiddleSideY }, { font_right_side, font_top_side },
    { font_right_side, font_upperMiddleSideY }, { font_right_side, font_bottom_side },
    { font_right_side, font_bottom_side }, { font_left_side + 2, font_bottom_side },
    { font_left_side + 2, font_bottom_side }, { font_left_side + 2, font_bottom_side + 1 },
};

const int font_lower_z_length = 3 * 2;
const byte2 font_lower_z[] =
{
    { font_left_side, font_lowerTopSide }, { font_right_side, font_lowerTopSide },
    { font_right_side, font_lowerTopSide }, { font_left_side, font_bottom_side },
    { font_left_side, font_bottom_side }, { font_right_side, font_bottom_side }
};

// copied font_lowerZ
const unsigned char font_upper_z_length = 3 * 2;
const byte2 font_upper_z[] =
{
    { font_left_side, font_top_side }, { font_right_side, font_top_side - 1 },  // top line
    { font_right_side, font_top_side - 1 }, { font_left_side, font_bottom_side + 1 },
    { font_left_side, font_bottom_side + 1 }, { font_right_side, font_bottom_side }
};

const byte2 down_arrow[] =
{
    { font_left_side, font_upperMiddleSideY }, { middleSideX, font_bottom_side },
    { middleSideX, font_top_side }, { middleSideX, font_bottom_side },
    { font_right_side, font_upperMiddleSideY }, { middleSideX, font_bottom_side }
};

const byte2 up_arrow[] =
{
    { font_left_side, font_upperMiddleSideY }, { middleSideX, font_top_side },
    { middleSideX, font_top_side }, { middleSideX, font_bottom_side },
    { font_right_side, font_upperMiddleSideY }, { middleSideX, font_top_side }
};