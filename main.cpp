#include "main.h"
#include "FileManager.h"

using namespace std;

FileManager file = FileManager();

void clearInputBuffer(){
    cin.sync();  
}

void inputManager(){
    cout << "\nВыберите какой пункт задания вы хотите испытать?\n";
    cout << "1: Дан текстовый файл b, вводится целое число К (проверка числа, что оно > 0 и не вещественное," 
    " ввод будет продолжаться до тех пор, пока не будет введено верное значение). Удалить из него последние К строк." 
    " Если файл содержит меньше К строк, сообщить об этом пользователю, завершить программу.\n";
    cout << "2: Подсчитать количество вхождений заданного пользователем слова в текстовый файл и вывести результат"
    " подсчета. В случае отсутствия в файле заданного пользователем слова вывести об этом сообщение.\n";

    int n;
    clearInputBuffer();
    cin >> n;
    switch (n)
    {
        case 1:
            firstMethod();
            break;
        case 2:
            secondMethod();
            break;
        default:
            errorMessage();
            break;
    }
    return;
}

void errorMessage(){
    cout << "Во вводе допущена ошибка\n";
    if(repeatRequest())
        inputManager();
    return;
}

bool repeatRequest(){
    cout << "Желаете попробовать еще раз? ";
    return acceptRequest();
}

bool acceptRequest() {
    cout << "[Y/N]?\n";
    char c;
    clearInputBuffer();
    cin >> c;
    return c == 'Y' || c == 'y';
}

void firstMethod(){
    fileSelection();
    int n;
    while(true){
        cout << "Введите число строк для удаления: ";
        cin >> n;
        while(cin.fail()){
            cout << "Пожалуйста, введите корректное число: ";
            cin.clear();
            cin >> n;
        }
            
        int k = file.countLines();
        if(n > k){
            cout << "Число удаляемых строк (" << n << ") превышает число строк в файле (" << k << "). Желаете попробовать ввести другое значение? ";
            if (!acceptRequest())
                return; 
        } else break;
            
    }

    file.deleteLastLines(n);
    file.stream.close();
    cout << "Готово!\n";

}

void secondMethod() {
    fileSelection();
    clearInputBuffer();
    cout << "Введите слово для поиска: ";
    string word;
    cin >> word;
    int result = 0;
    for(int i = 0; i < file.countLines(); ++i){ // Строка файла
        string line = file.read();
        for(int j = 0; j < line.length() - word.length() + 1; ++j){ // Перебор точки старта
            bool flag = true;
            for(int k = 0; k < word.length() && flag; ++k){ // Проверка на совпадение
                if(j + k >= line.length())
                    break;
                if(line[j + k] != word[k])
                    flag = false;
            }
            if (flag) result++;
        }
    }
    if(!result)
        cout << "Совпадений не найдено\n";
    else
        cout << "Найдено " << result << " совпадений\n";
}

void fileSelection() {
    cout << "Обращение к файлу " << file.getFileName() << ". Желаете изменить файл? ";
    if (acceptRequest()){
        string fileName;
        while(true){
            clearInputBuffer();
            cout << "Введите имя файла: ";
            cin >> fileName;
            try {
                file.reopenStream(fileName);
                break;
            } catch (const exception& e) {
                cout << e.what() << endl << "Желаете изменить имя на другое? ";
                if (!acceptRequest())
                    return;
            }
        }
    } else 
        file.openFile();
}

int main(){
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    inputManager();
    while(true){
        if(repeatRequest())
            inputManager();
        else
            break;
    }

    return 0;
}