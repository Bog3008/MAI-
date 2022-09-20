/*Класс Image - создает или перезаписывает в уже существующий файл изображение в формате PGM - изображение с градацией от черного к белому
 Тут можно прочитатьь про этот формат https://en.wikipedia.org/wiki/Netpbm#File_formats
 Запись или создание нового файла происходит в методе show_n_savePnm
 Экземпляр класса служит временным хранилищем для данных об изображенн пока не будет вызван метод show_n_savePnm и данные не будут сохранены
 в данной папке лежат примеры изображений полученные в ходе исполнения данного кода
    Image_test.pgm - картинка созданная методом paint_Y_Zebra - это чередующиеся вертикальные и горизонтальные линии
    Image_with_my_name - картинка с моим именем и первой буквой фамилии, котороя создается из массива my_name в main
*/
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct Image{
    Image(): mx(0), my(0), buf(nullptr),file_name("Image_test.pgm") {}
    ~Image(){
        for(int i = 0; i < my; ++i){
            delete[] buf[i];
        }
        delete[] buf;
        buf = nullptr;
        mx = 0;
        my = 0;
    }
    Image(int x, int y, string name = "Image_test.pgm" ): mx(x), my(y), file_name(name){
        buf = new int * [my];
        for(int i = 0; i < my; ++i){
            buf[i] = new int[mx];
            for(int j = 0; j < mx; ++j){
                buf[i][j] = 0;
            }
        }
    }
    
    void set(int x, int y, int val){
        if(x > mx || y > my){
            cout << "Wrong index in set"<<endl;
            throw 1;
        }
        buf[y][x] = val % 16; // я поставил всего 15 оттенков от белого до черного тк мне так удобнее
    }
    int get(int x, int y){
        return buf[y][x];
    }
    void show_n_savePnm(){
        ofstream mf;
        try{
            mf.open(file_name);
            cout << "File \""<< file_name<< "\" is open"<<endl;
        }
        catch (...){
            cout << "File \""<< file_name<< "\" openning error"<<endl;
            return;
        }
        mf << "P2"<<endl;
        mf << mx << " " << my<<endl;
        mf << "15"<<endl;
        for(int oy  = 0; oy < my; oy++){
            for(int ox  = 0; ox < mx; ox++){
                mf << buf[oy][ox] << " ";
            }
            mf << endl;
        }

        mf.close();
        cout <<"The changes in file \""<< file_name<< "\" were saved"<<endl;
    }
    void paint_Y_Zebra(){
        for(int i = 0; i < my; i+= 2){
            for(int j = 0; j < mx; j++){
                buf[i][j] = 15;
            }
        }
        this->show_n_savePnm();
    }
private:
    int mx, my;
    int ** buf;
    string file_name;
};

int main() {
    Image a(100, 100);
    a.paint_Y_Zebra();
    //a.show_n_savePnm();
    // создаю массив который потом будет основой для картики 
    int my_name [5][30] = {
            { 2 , 2 , 2 , 0 , 0 , 4 , 0 , 0 , 6 , 6 , 6 , 0 , 0 , 8 , 0 , 0 , 0 , 0 ,10 , 0 , 0 ,12 , 0 ,12 , 0 , 0 ,15 ,15 ,15 },
            { 2 , 0 , 0 , 0 , 4 , 0 , 4 , 0 , 6 , 0 , 0 , 0 , 8 , 0 , 8 , 0 , 0 ,10 , 0 ,10 , 0 ,12 , 0 ,12 , 0 , 0 , 0 ,15 , 0 },
            { 2 , 2 , 2 , 0 , 4 , 0 , 4 , 0 , 6 , 0 , 0 , 0 , 8 , 0 , 8 , 0 , 0 ,10 ,10 ,10 , 0 ,12 ,12 ,12 , 0 , 0 , 0 ,15 , 0 },
            { 2 , 0 , 2 , 0 , 4 , 0 , 4 , 0 , 6 , 0 , 0 , 8 , 8 , 8 , 8 , 8 , 0 ,10 , 0 ,10 , 0 ,12 , 0 ,12 , 0 , 0 , 0 ,15 , 0 },
            { 2 , 2 , 2 , 0 , 0 , 4 , 0 , 0 , 6 , 0 , 0 , 8 , 0 , 0 , 0 , 8 , 0 ,10 , 0 ,10 , 0 ,12 , 0 ,12 , 0 ,15 , 0 ,15 , 0 }
    };
    Image b(30, 5, "Image_with_my_name.pgm");
    for(int i = 0; i < 5; i++){
        for(int j = 0; j < 30; j++){
            b.set(j, i, my_name[i][j]);
        }
        cout <<endl;
    }
    b.show_n_savePnm();


}
