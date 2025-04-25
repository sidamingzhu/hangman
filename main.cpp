#include<iostream>
#include<string>
#include<fstream> //用于文件操作
#include<vector>
#include<cstdlib> //system函数
#include<random> //使用随机数
#include<conio.h> //使用_getch()函数实现无回显的输入
#include<cctype> //tolower, isalpha等函数

using namespace std;

inline istream& Flush(istream&); //清除输入流，源码自带函数，不用改

void ShowMainMenu(int&);

class DrawHangman {
protected:
    void DrawStep1();
    void DrawStep2();
    void DrawStep3();
    void DrawStep4();
    void DrawStep5();
    void DrawStep6();
    void DrawStep7();
    void DrawStep8();
    void DrawStep9();
    void DrawStep10();
public:
    void DrawJudge(int, int);//根据总的机会数和失败次数来画上吊的人
};

DrawHangman man;//全局变量，用来画上吊的人

class BaseGame {
protected:
    int max_attempts;
    double hint_probability;
    DrawHangman* p;
    void SetParameter(int&, double&);
    string InitRandomDisplayedWord(string);//按照概率显示字母或者星号
    void TestAnswer(int&, string&, string&, vector<char>&);
    BaseGame() {
        max_attempts = 4;
        hint_probability = 20;
        p = &man;
    }
};

class HumanVsComputer : public BaseGame {
protected:
    vector<string> word_vector;
    void ShowHumanVsComputerMenu(int&);//展示人机对战菜单并获取选项
    void StartGuessWithComputer();//开始游戏
    void InitWordVector();//从单词库中读取单词并初始化单词向量
    string InitRandomWord();//从单词向量中随机挑选一个单词作为待猜单词
    void AddWord(vector<string>&);
public:
    void InitHumanVsComputer();//初始化人机对战模块
    //构造函数
    HumanVsComputer() : BaseGame() {
        InitWordVector();//创建对象的同时，从单词库中获取单词并初始化单词向量
    }
};

class HumanVsHuman : public BaseGame {
protected:
    void ShowHumanVsHumanMenu(int&);//展示人机对战菜单，并获取用户选择
    void StartGuessWithHuman();//开始游戏
    string InputWord();//无回显输入
public:
    void InitHumanVsHuman();//初始化人机对战模块
    //构造函数
    HumanVsHuman() : BaseGame() {}
};

int main() {
    int main_loop_signal = 1;//主循环判断标志
    int main_choice = 0;//用户的选择
    do {
        ShowMainMenu(main_choice);
        switch (main_choice) {
        case 1: {
            HumanVsHuman obj;
            obj.InitHumanVsHuman();
            break;
        }
        case 2: {
            HumanVsComputer obj;
            obj.InitHumanVsComputer();
            break;
        }
        case 3: {
            cout << " ByeBye!" << endl;
            main_loop_signal = 0;
            break;
        }
        default: {
            cerr << "Invalid Choice! Enter again!" << endl;
            system("pause");
        }
        }
    } while (main_loop_signal == 1);
    system("pause");
    return 0;
}
//清空输入流，防止缓存区影响下一次输入
inline istream& Flush(istream& stream) {
    stream.clear();//清除流的状态标志
    int chars_to_skip = stream.rdbuf()->in_avail();//获取底层缓冲区中可立即读取的字符数量
    return stream.ignore(chars_to_skip);//跳过这些字符实现缓冲区清空
}

//inline istream& Flush(istream& stream) {
//    stream.clear();
//    streamsize chars_to_skip = stream.rdbuf()->in_avail();
//    return stream.ignore(chars_to_skip);
//}

void ShowMainMenu(int& choice) {
    system("cls");
    cout << "HH    HH   AAAAAA   NNN   NN   G G G G  MMM        MMM   AAAAAA   NNN   NN" << endl;
    cout << "HH    HH  AA    AA  NNNN  NN  GG        MMMM      MMMM  AA    AA  NNNN  NN" << endl;
    cout << "HHHHHHHH  AAAAAAAA  NN NN NN  GG        MM MM    MM MM  AAAAAAAA  NN NN NN" << endl;
    cout << "HH    HH  AA    AA  NN  NNNN  GG   GGG  MM  MM  MM  MM  AA    AA  NN  NNNN" << endl;
    cout << "HH    HH  AA    AA  NN   NNN   GG   GG  MM   MMMM   MM  AA    AA  NN   NNN" << endl;
    cout << "HH    HH  AA    AA  NN    NN     GGG    MM    MM    MM  AA    AA  NN    NN" << endl;
    cout << "**************************************************************************" << endl;
    cout << " Enter 1 to play against user" << endl;
    cout << " Enter 2 to play against computer" << endl;
    cout << " Enter 3 to quit" << endl;
    cout << "*****************************************" << endl << endl;
    cout << " Enter Your Choice: ";
    cin >> choice;
    Flush(cin);//清空输入流，防止缓存区影响下一次输入
}

//**************************基类**************************
void BaseGame::SetParameter(int& max_attempts_parameter, double& hint_probability_parameter) {
    int max_i;
    double hint_i;
    system("cls");
    cout << "Max Attempts: " << max_attempts_parameter << endl;
    cout << "Hint Probability: " << hint_probability_parameter << endl;
    cout << "Enter Max Attempts (4-10): ";
    cin >> max_i;//这里max_i只接受整型，如果是浮点型，会直接转换成整型，如果是字符型，会变成0
    Flush(cin);
    while ((max_i < 4) || (max_i > 10)) {
        cerr << "Invalid Enter!" << endl;
        cout << "Enter Max Attempts (4-10): ";
        cin >> max_i;
        Flush(cin);
    }
    max_attempts_parameter = max_i;//这里是引用传递，实际上改变了max_attempts的值
    cout << "You set the max attempts: " << max_attempts_parameter << endl;
    cout << "Enter Hint Probability (20-70): " << endl;
    cin >> hint_i;
    Flush(cin);
    while ((hint_i < 20) || (hint_i > 70)) {
        cerr << "Invalid Enter!" << endl;
        cout << "Enter Hint Probability (20-70): ";
        cin >> hint_i;
        Flush(cin);
    }
    hint_probability_parameter = hint_i;//这里是引用传递，实际上改变了hint_probability的值
    cout << "You set the hint probability: " << hint_probability_parameter << endl;
    system("pause");
}

string BaseGame::InitRandomDisplayedWord(string unknown_word_parameter) {
    // 初始化真随机数设备（硬件熵源）用于生成种子
    random_device rd;
    // 使用梅森旋转算法引擎（mt19937）初始化伪随机数生成器
    // 用真随机数种子确保每次运行生成不同的随机序列
    mt19937 generator(rd());
    // 创建1-100的均匀实数分布，用于概率判断
    uniform_real_distribution<double> distribution(1, 100);
    string display_word_inter = unknown_word_parameter;
    // 遍历单词每个字符进行随机隐藏处理
    for (int i = 0; i < unknown_word_parameter.size(); i++) {
        // 生成随机数并与提示概率比较（当随机数>提示概率时隐藏字符）
        // 例如：hint_probability=20时，有20%概率显示原字符，80%概率显示*
        if (distribution(generator) > hint_probability) {
            display_word_inter[i] = '*';
        }
    }
    return display_word_inter;
}

void BaseGame::TestAnswer(int& max_attempts_p, string& display_word_p, string& unknown_word_p, vector<char>& letter_vector_p) {
    int wrong_attempts = 0;//错误次数
    //错误次数小于机会数
    while (wrong_attempts < max_attempts_p) {
        //如果单词已经被猜出来，终止循环
        if (display_word_p == unknown_word_p) {
            break;
        }
        system("cls");
        char a_letter;
        cout << "The unknown word is: " << display_word_p << endl;
        cout << "Letters have been guessed: ";//展示已经猜过的字母
        if (letter_vector_p.empty()) {
            cout << "None" << endl;
        }
        else {
            for (char letter : letter_vector_p) {
                cout << letter << ' ';
            }
        }
        cout << endl;
        cout << "You have " << max_attempts_p - wrong_attempts << " chances left!" << endl;
        cout << "Guess a letter: ";
        cin >> a_letter;
        Flush(cin);
        //判断非字母
        while (!isalpha(a_letter)) {
            cout << "Invalid Enter! You Should Guess A Letter! " << endl;
            cout << "Guess a letter: ";
            cin >> a_letter;
            Flush(cin);
        }
        //转换为小写
        if (isupper(a_letter)) {
            a_letter = tolower(a_letter);
        }
        //如果letter_vector是空的就添加进向量，如果不是空的就判断是否已经猜过
        if (letter_vector_p.empty()) {
            letter_vector_p.push_back(a_letter);
        }
        //判断字母是否被猜过
        else {
            while (true) {
                int letter_loop_signal = 0;
                for (char letter : letter_vector_p) {
                    if (letter == a_letter) {
                        letter_loop_signal++;
                        break;
                    }
                }
                //重复就重新输入一个字母，同时判断是否非字母，转换为小写
                if (letter_loop_signal >= 1) {
                    cout << "The letter has been guessed! You still have " << max_attempts_p - wrong_attempts << " chances left!" << endl;
                    cout << "Guess another letter: ";
                    cin >> a_letter;
                    Flush(cin);
                    while (!isalpha(a_letter)) {
                        cout << "Invalid Enter! You Should Guess A Letter! " << endl;
                        cout << "Guess a letter: ";
                        cin >> a_letter;
                        Flush(cin);
                    }
                    if (isupper(a_letter)) {
                        a_letter = tolower(a_letter);
                    }
                }
                //只有执行到else，程序才能从这个while中退出来
                else {
                    letter_vector_p.push_back(a_letter);
                    break;
                }
            }
        }
        int right_signal = 0;
        for (int i = 0; i < unknown_word_p.size(); i++) {
            if (a_letter == unknown_word_p[i]) {
                display_word_p[i] = unknown_word_p[i];//将星号替换为正确的字母
                right_signal++;
            }
        }
        if (right_signal >= 1) {
            cout << "Right! The letter \" " << a_letter << " \" is in the word! " << "You have " << max_attempts_p - wrong_attempts << " chances left!" << endl;
            system("pause");
        }
        else {
            wrong_attempts++;
            cout << "Wrong! The letter \" " << a_letter << " \" is not in the word! " << "You have " << max_attempts_p - wrong_attempts << " chances left!" << endl;
            p->DrawJudge(max_attempts_p, wrong_attempts);
            system("pause");
        }
    }//while循环结束，要么是次数用完，要么是单词猜出来了，display_word被替换为正确的单词
    system("cls");
    if (wrong_attempts >= max_attempts_p) {
        cout << "You lost!" << endl;
        p->DrawJudge(max_attempts_p, wrong_attempts);
        cout << "The answer is : " << unknown_word_p << endl;
        system("pause");
    }
    else {
        cout << "You win!" << endl;
        cout << "The answer is : " << unknown_word_p << endl;
        system("pause");
    }
}

//**************************人机对战类**************************
void HumanVsComputer::ShowHumanVsComputerMenu(int& human_vs_computer_choice_p) {
    system("cls");
    cout << "            -Human vs Computer-          " << endl;
    cout << "*****************************************" << endl;
    cout << " Enter 1 to play Right Now" << endl;
    cout << " Enter 2 to set the parameter" << endl;
    cout << " Enter 3 to add words" << endl;
    cout << " Enter 4 to quit" << endl;
    cout << "*****************************************" << endl << endl;
    cout << " Enter Your Choice: ";
    cin >> human_vs_computer_choice_p;
    Flush(cin);
}
void HumanVsComputer::InitHumanVsComputer() {
    int human_vs_computer_loop_signal = 1;
    do {
        int human_vs_computer_choice = 0;
        ShowHumanVsComputerMenu(human_vs_computer_choice);
        switch (human_vs_computer_choice) {
        case 1: {
            StartGuessWithComputer();
            break;
        }
        case 2: {
            SetParameter(max_attempts, hint_probability);
            break;
        }
        case 3: {
            AddWord(word_vector);
            break;
        }
        case 4: {
            human_vs_computer_loop_signal = 0;
            break;
        }
        default: {
            cerr << "Invalid Choice! Enter again!" << endl;
            system("pause");
        }
        }
    } while (human_vs_computer_loop_signal == 1);
}

void HumanVsComputer::StartGuessWithComputer() {
    system("cls");
    string unknown_word = InitRandomWord();
    string display_word = InitRandomDisplayedWord(unknown_word);
    vector<char> letter_vector;//已猜字母列表
    TestAnswer(max_attempts, display_word, unknown_word, letter_vector);
}

void HumanVsComputer::InitWordVector() {
    fstream word_file;
    word_file.open("word.txt", ios::in);
    if (!word_file.is_open()) {
        cerr << "open file error" << endl;
        exit(1);
    }
    string word;
    while (getline(word_file, word)) {  //直接使用getline返回值判断，避免重复读取最后一行
        // 跳过空行
        if (word.empty()) continue;
        //转换为小写
        for (char& c : word) {
            if (isupper(c)) {
                c = tolower(c);
            }
        }
        word_vector.push_back(word);//添加进单词向量
    }
    word_file.close();
}

string HumanVsComputer::InitRandomWord() {
    random_device rd;
    mt19937 generator(rd());
    uniform_int_distribution<int> distribution(0, static_cast<int>(word_vector.size()) - 1); //使用static_cast进行显式转换，告诉编译器这是有意为之，从而消除警告
    return word_vector[distribution(generator)];
}

void HumanVsComputer::AddWord(vector<string>& word_vector_parameter) {
    int loop_signal = 1;
    while (loop_signal == 1) {
        system("cls");
        //输出单词个数
        cout << "There are " << word_vector_parameter.size() << " words in the list" << endl;
        cout << "Enter another word: ";
        string word_i;
        cin >> word_i;
        Flush(cin);
        int loop_counter_i = 0;
        //判断非字母
        for (char letter : word_i) {
            if (!isalpha(letter)) {
                cerr << "Invalid Word! Enter again!" << endl;
                loop_counter_i = 1;
                system("pause");
                break;
            }
        }
        if (loop_counter_i == 1) { continue; }
        //转为小写
        for (char& letter : word_i) {
            if (isupper(letter)) {
                letter = tolower(letter);
            }
        }
        //判断重复
        for (string word : word_vector_parameter) {
            if (word == word_i) {
                cerr << "The word \" " << word_i << " \" has been in the list! Enter another word!" << endl;
                loop_counter_i = 1;
                system("pause");
                break;
            }
        }
        if (loop_counter_i == 1) { continue; }
        //添加到单词向量
        word_vector_parameter.push_back(word_i);
        //添加到词库
        fstream output_file;
        output_file.open("word.txt", ios::out | ios::app);//以追加的方式打开
        if (!output_file.is_open()) {
            cerr << "open file error" << endl;
            exit(1);
        }
        output_file << endl << word_i;
        output_file.close();
        cout << "Successful Addition!" << endl;
        loop_signal = 0;
        system("pause");
    }
}

//**************************人人对战类**************************
void HumanVsHuman::ShowHumanVsHumanMenu(int& choice) {
    system("cls");
    cout << "		  -Human vs Human-" << endl;
    cout << "*****************************************" << endl;
    cout << " Enter 1 to play Right Now" << endl;
    cout << " Enter 2 to set the parameter" << endl;
    cout << " Enter 3 to quit" << endl;
    cout << "*****************************************" << endl << endl;
    cout << " Enter Your Choice: ";
    cin >> choice;
    Flush(cin);
}

void HumanVsHuman::InitHumanVsHuman() {
    int human_vs_human_loop_signal = 1;
    do {
        int human_vs_human_choice = 0;
        ShowHumanVsHumanMenu(human_vs_human_choice);
        switch (human_vs_human_choice) {
        case 1: {
            StartGuessWithHuman();
            break;
        }
        case 2: {
            SetParameter(max_attempts, hint_probability);
            break;
        }
        case 3: {
            human_vs_human_loop_signal = 0;
            break;
        }
        default: {
            cerr << "Invalid Choice! Enter again!" << endl;
            system("pause");
        }
        }
    } while (human_vs_human_loop_signal == 1);
}

void HumanVsHuman::StartGuessWithHuman() {
    system("cls");
    string unknown_word = InputWord();
    string display_word = InitRandomDisplayedWord(unknown_word);
    vector<char> letter_vector;
    TestAnswer(max_attempts, display_word, unknown_word, letter_vector);
}

string HumanVsHuman::InputWord() {
    string word;
    while (true) {
        string temp_word;
        system("cls");
        cout << "Input A Word (press \"enter\" to end): ";
        char c;
        //使用_getch()函数，输入回车结束循环
        while ((c = _getch()) != '\r') {
            //处理退格键
            if (c == '\b') {
                if (!temp_word.empty()) {
                    temp_word.pop_back();//删除最后一个
                    cout << "\b \b";//在控制台上删除*
                }
            }
            else {
                temp_word.push_back(c);
                cout << '*';
            }
        }
        int loop_signal_m = 0;
        //判断非字母
        for (char letter : temp_word) {
            if (!isalpha(letter)) {
                cout << endl << "Invalid Word! Enter again!" << endl;
                system("pause");
                loop_signal_m = 1;
                break;
            }
        }
        if (loop_signal_m == 1) { continue; }
        //转换为小写
        for (char& letter : temp_word) {
            if (isupper(letter)) {
                letter = tolower(letter);
            }
        }
        word = temp_word;
        break;
    }
    system("cls");
    return word;
}

//**************************绘画类**************************
void DrawHangman::DrawStep1() {
    cout << "               " << endl;
    cout << "               " << endl;
    cout << "               " << endl;
    cout << "               " << endl;
    cout << "               " << endl;
    cout << "               " << endl;
    cout << " ===============\n";
}

void DrawHangman::DrawStep2() {
    cout << "            +\n";
    cout << "            |\n";
    cout << "            |\n";
    cout << "            |\n";
    cout << "            |\n";
    cout << "            |\n";
    cout << " ===============\n";
}

void DrawHangman::DrawStep3() {
    cout << "        +---+\n";
    cout << "            |\n";
    cout << "            |\n";
    cout << "            |\n";
    cout << "            |\n";
    cout << "            |\n";
    cout << " ===============\n";
}

void DrawHangman::DrawStep4() {
    cout << "        +---+\n";
    cout << "        |   |\n";
    cout << "            |\n";
    cout << "            |\n";
    cout << "            |\n";
    cout << "            |\n";
    cout << " ===============\n";
}

void DrawHangman::DrawStep5() {
    cout << "        +---+\n";
    cout << "        |   |\n";
    cout << "        O   |\n";
    cout << "            |\n";
    cout << "            |\n";
    cout << "            |\n";
    cout << " ===============\n";
}

void DrawHangman::DrawStep6() {
    cout << "        +---+\n";
    cout << "        |   |\n";
    cout << "        O   |\n";
    cout << "        |   |\n";
    cout << "            |\n";
    cout << "            |\n";
    cout << " ===============\n";
}

void DrawHangman::DrawStep7() {
    cout << "        +---+\n";
    cout << "        |   |\n";
    cout << "        O   |\n";
    cout << "       /|   |\n";
    cout << "            |\n";
    cout << "            |\n";
    cout << " ===============\n";
}

void DrawHangman::DrawStep8() {
    cout << "        +---+\n";
    cout << "        |   |\n";
    cout << "        O   |\n";
    cout << "       /|\\  |\n";
    cout << "            |\n";
    cout << "            |\n";
    cout << " ===============\n";
}

void DrawHangman::DrawStep9() {
    cout << "        +---+\n";
    cout << "        |   |\n";
    cout << "        O   |\n";
    cout << "       /|\\  |\n";
    cout << "       / \\  |\n";
    cout << "            |\n";
    cout << " ===============\n";
}

void DrawHangman::DrawStep10() {
    cout << "        +---+\n";
    cout << "        |   |\n";
    cout << "        |   |\n";
    cout << "       /|\\  |\n";
    cout << "       / \\  |\n";
    cout << "    O       |\n";
    cout << " ===============\n";
}

void DrawHangman::DrawJudge(int max_attempts_i, int wrong_attempts_i) {
    if (max_attempts_i == 4) {
        switch (wrong_attempts_i) {
        case 1: {
            DrawStep5();
            break;
        }
        case 2: {
            DrawStep6();
            break;
        }
        case 3: {
            DrawStep9();
            break;
        }
        case 4: {
            DrawStep10();
            break;
        }
        default:;
        }
    }
    else if (max_attempts_i == 5) {
        switch (wrong_attempts_i) {
        case 1: {
            DrawStep5();
            break;
        }
        case 2: {
            DrawStep7();
            break;
        }
        case 3: {
            DrawStep8();
            break;
        }
        case 4: {
            DrawStep9();
            break;
        }
        case 5: {
            DrawStep10();
            break;
        }
        default:;
        }
    }
    else if (max_attempts_i == 6) {
        switch (wrong_attempts_i) {
        case 1: {
            DrawStep5();
            break;
        }
        case 2: {
            DrawStep6();
            break;
        }
        case 3: {
            DrawStep7();
            break;
        }
        case 4: {
            DrawStep8();
            break;
        }
        case 5: {
            DrawStep9();
            break;
        }
        case 6: {
            DrawStep10();
            break;
        }
        default:;
        }
    }
    else if (max_attempts_i == 7) {
        switch (wrong_attempts_i) {
        case 1: {
            DrawStep4();
            break;
        }
        case 2: {
            DrawStep5();
            break;
        }
        case 3: {
            DrawStep6();
            break;
        }
        case 4: {
            DrawStep7();
            break;
        }
        case 5: {
            DrawStep8();
            break;
        }
        case 6: {
            DrawStep9();
            break;
        }
        case 7: {
            DrawStep10();
            break;
        }
        default:;
        }
    }
    else if (max_attempts_i == 8) {
        switch (wrong_attempts_i) {
        case 1: {
            DrawStep3();
            break;
        }
        case 2: {
            DrawStep4();
            break;
        }
        case 3: {
            DrawStep5();
            break;
        }
        case 4: {
            DrawStep6();
            break;
        }
        case 5: {
            DrawStep7();
            break;
        }
        case 6: {
            DrawStep8();
            break;
        }
        case 7: {
            DrawStep9();
            break;
        }
        case 8: {
            DrawStep10();
            break;
        }
        default:;
        }
    }
    else if (max_attempts_i == 9) {
        switch (wrong_attempts_i) {
        case 1: {
            DrawStep2();
            break;
        }
        case 2: {
            DrawStep3();
            break;
        }
        case 3: {
            DrawStep4();
            break;
        }
        case 4: {
            DrawStep5();
            break;
        }
        case 5: {
            DrawStep6();
            break;
        }
        case 6: {
            DrawStep7();
            break;
        }
        case 7: {
            DrawStep8();
            break;
        }
        case 8: {
            DrawStep9();
            break;
        }
        case 9: {
            DrawStep10();
            break;
        }
        default:;
        }
    }
    else {
        switch (wrong_attempts_i) {
        case 1: {
            DrawStep1();
            break;
        }
        case 2: {
            DrawStep2();
            break;
        }
        case 3: {
            DrawStep3();
            break;
        }
        case 4: {
            DrawStep4();
            break;
        }
        case 5: {
            DrawStep5();
            break;
        }
        case 6: {
            DrawStep6();
            break;
        }
        case 7: {
            DrawStep7();
            break;
        }
        case 8: {
            DrawStep8();
            break;
        }
        case 9: {
            DrawStep9();
            break;
        }
        case 10: {
            DrawStep10();
            break;
        }
        default:;
        }
    }
}