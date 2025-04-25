#include<iostream>
#include<string>
#include<fstream> //�����ļ�����
#include<vector>
#include<cstdlib> //system����
#include<random> //ʹ�������
#include<conio.h> //ʹ��_getch()����ʵ���޻��Ե�����
#include<cctype> //tolower, isalpha�Ⱥ���

using namespace std;

inline istream& Flush(istream&); //�����������Դ���Դ����������ø�

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
    void DrawJudge(int, int);//�����ܵĻ�������ʧ�ܴ��������ϵ�����
};

DrawHangman man;//ȫ�ֱ������������ϵ�����

class BaseGame {
protected:
    int max_attempts;
    double hint_probability;
    DrawHangman* p;
    void SetParameter(int&, double&);
    string InitRandomDisplayedWord(string);//���ո�����ʾ��ĸ�����Ǻ�
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
    void ShowHumanVsComputerMenu(int&);//չʾ�˻���ս�˵�����ȡѡ��
    void StartGuessWithComputer();//��ʼ��Ϸ
    void InitWordVector();//�ӵ��ʿ��ж�ȡ���ʲ���ʼ����������
    string InitRandomWord();//�ӵ��������������ѡһ��������Ϊ���µ���
    void AddWord(vector<string>&);
public:
    void InitHumanVsComputer();//��ʼ���˻���սģ��
    //���캯��
    HumanVsComputer() : BaseGame() {
        InitWordVector();//���������ͬʱ���ӵ��ʿ��л�ȡ���ʲ���ʼ����������
    }
};

class HumanVsHuman : public BaseGame {
protected:
    void ShowHumanVsHumanMenu(int&);//չʾ�˻���ս�˵�������ȡ�û�ѡ��
    void StartGuessWithHuman();//��ʼ��Ϸ
    string InputWord();//�޻�������
public:
    void InitHumanVsHuman();//��ʼ���˻���սģ��
    //���캯��
    HumanVsHuman() : BaseGame() {}
};

int main() {
    int main_loop_signal = 1;//��ѭ���жϱ�־
    int main_choice = 0;//�û���ѡ��
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
//�������������ֹ������Ӱ����һ������
inline istream& Flush(istream& stream) {
    stream.clear();//�������״̬��־
    int chars_to_skip = stream.rdbuf()->in_avail();//��ȡ�ײ㻺�����п�������ȡ���ַ�����
    return stream.ignore(chars_to_skip);//������Щ�ַ�ʵ�ֻ��������
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
    Flush(cin);//�������������ֹ������Ӱ����һ������
}

//**************************����**************************
void BaseGame::SetParameter(int& max_attempts_parameter, double& hint_probability_parameter) {
    int max_i;
    double hint_i;
    system("cls");
    cout << "Max Attempts: " << max_attempts_parameter << endl;
    cout << "Hint Probability: " << hint_probability_parameter << endl;
    cout << "Enter Max Attempts (4-10): ";
    cin >> max_i;//����max_iֻ�������ͣ�����Ǹ����ͣ���ֱ��ת�������ͣ�������ַ��ͣ�����0
    Flush(cin);
    while ((max_i < 4) || (max_i > 10)) {
        cerr << "Invalid Enter!" << endl;
        cout << "Enter Max Attempts (4-10): ";
        cin >> max_i;
        Flush(cin);
    }
    max_attempts_parameter = max_i;//���������ô��ݣ�ʵ���ϸı���max_attempts��ֵ
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
    hint_probability_parameter = hint_i;//���������ô��ݣ�ʵ���ϸı���hint_probability��ֵ
    cout << "You set the hint probability: " << hint_probability_parameter << endl;
    system("pause");
}

string BaseGame::InitRandomDisplayedWord(string unknown_word_parameter) {
    // ��ʼ����������豸��Ӳ����Դ��������������
    random_device rd;
    // ʹ��÷ɭ��ת�㷨���棨mt19937����ʼ��α�����������
    // �������������ȷ��ÿ���������ɲ�ͬ���������
    mt19937 generator(rd());
    // ����1-100�ľ���ʵ���ֲ������ڸ����ж�
    uniform_real_distribution<double> distribution(1, 100);
    string display_word_inter = unknown_word_parameter;
    // ��������ÿ���ַ�����������ش���
    for (int i = 0; i < unknown_word_parameter.size(); i++) {
        // ���������������ʾ���ʱȽϣ��������>��ʾ����ʱ�����ַ���
        // ���磺hint_probability=20ʱ����20%������ʾԭ�ַ���80%������ʾ*
        if (distribution(generator) > hint_probability) {
            display_word_inter[i] = '*';
        }
    }
    return display_word_inter;
}

void BaseGame::TestAnswer(int& max_attempts_p, string& display_word_p, string& unknown_word_p, vector<char>& letter_vector_p) {
    int wrong_attempts = 0;//�������
    //�������С�ڻ�����
    while (wrong_attempts < max_attempts_p) {
        //��������Ѿ����³�������ֹѭ��
        if (display_word_p == unknown_word_p) {
            break;
        }
        system("cls");
        char a_letter;
        cout << "The unknown word is: " << display_word_p << endl;
        cout << "Letters have been guessed: ";//չʾ�Ѿ��¹�����ĸ
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
        //�жϷ���ĸ
        while (!isalpha(a_letter)) {
            cout << "Invalid Enter! You Should Guess A Letter! " << endl;
            cout << "Guess a letter: ";
            cin >> a_letter;
            Flush(cin);
        }
        //ת��ΪСд
        if (isupper(a_letter)) {
            a_letter = tolower(a_letter);
        }
        //���letter_vector�ǿյľ���ӽ�������������ǿյľ��ж��Ƿ��Ѿ��¹�
        if (letter_vector_p.empty()) {
            letter_vector_p.push_back(a_letter);
        }
        //�ж���ĸ�Ƿ񱻲¹�
        else {
            while (true) {
                int letter_loop_signal = 0;
                for (char letter : letter_vector_p) {
                    if (letter == a_letter) {
                        letter_loop_signal++;
                        break;
                    }
                }
                //�ظ�����������һ����ĸ��ͬʱ�ж��Ƿ����ĸ��ת��ΪСд
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
                //ֻ��ִ�е�else��������ܴ����while���˳���
                else {
                    letter_vector_p.push_back(a_letter);
                    break;
                }
            }
        }
        int right_signal = 0;
        for (int i = 0; i < unknown_word_p.size(); i++) {
            if (a_letter == unknown_word_p[i]) {
                display_word_p[i] = unknown_word_p[i];//���Ǻ��滻Ϊ��ȷ����ĸ
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
    }//whileѭ��������Ҫô�Ǵ������꣬Ҫô�ǵ��ʲ³����ˣ�display_word���滻Ϊ��ȷ�ĵ���
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

//**************************�˻���ս��**************************
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
    vector<char> letter_vector;//�Ѳ���ĸ�б�
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
    while (getline(word_file, word)) {  //ֱ��ʹ��getline����ֵ�жϣ������ظ���ȡ���һ��
        // ��������
        if (word.empty()) continue;
        //ת��ΪСд
        for (char& c : word) {
            if (isupper(c)) {
                c = tolower(c);
            }
        }
        word_vector.push_back(word);//��ӽ���������
    }
    word_file.close();
}

string HumanVsComputer::InitRandomWord() {
    random_device rd;
    mt19937 generator(rd());
    uniform_int_distribution<int> distribution(0, static_cast<int>(word_vector.size()) - 1); //ʹ��static_cast������ʽת�������߱�������������Ϊ֮���Ӷ���������
    return word_vector[distribution(generator)];
}

void HumanVsComputer::AddWord(vector<string>& word_vector_parameter) {
    int loop_signal = 1;
    while (loop_signal == 1) {
        system("cls");
        //������ʸ���
        cout << "There are " << word_vector_parameter.size() << " words in the list" << endl;
        cout << "Enter another word: ";
        string word_i;
        cin >> word_i;
        Flush(cin);
        int loop_counter_i = 0;
        //�жϷ���ĸ
        for (char letter : word_i) {
            if (!isalpha(letter)) {
                cerr << "Invalid Word! Enter again!" << endl;
                loop_counter_i = 1;
                system("pause");
                break;
            }
        }
        if (loop_counter_i == 1) { continue; }
        //תΪСд
        for (char& letter : word_i) {
            if (isupper(letter)) {
                letter = tolower(letter);
            }
        }
        //�ж��ظ�
        for (string word : word_vector_parameter) {
            if (word == word_i) {
                cerr << "The word \" " << word_i << " \" has been in the list! Enter another word!" << endl;
                loop_counter_i = 1;
                system("pause");
                break;
            }
        }
        if (loop_counter_i == 1) { continue; }
        //��ӵ���������
        word_vector_parameter.push_back(word_i);
        //��ӵ��ʿ�
        fstream output_file;
        output_file.open("word.txt", ios::out | ios::app);//��׷�ӵķ�ʽ��
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

//**************************���˶�ս��**************************
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
        //ʹ��_getch()����������س�����ѭ��
        while ((c = _getch()) != '\r') {
            //�����˸��
            if (c == '\b') {
                if (!temp_word.empty()) {
                    temp_word.pop_back();//ɾ�����һ��
                    cout << "\b \b";//�ڿ���̨��ɾ��*
                }
            }
            else {
                temp_word.push_back(c);
                cout << '*';
            }
        }
        int loop_signal_m = 0;
        //�жϷ���ĸ
        for (char letter : temp_word) {
            if (!isalpha(letter)) {
                cout << endl << "Invalid Word! Enter again!" << endl;
                system("pause");
                loop_signal_m = 1;
                break;
            }
        }
        if (loop_signal_m == 1) { continue; }
        //ת��ΪСд
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

//**************************�滭��**************************
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