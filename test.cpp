#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

struct Sinhvien{
    std::string name;
    int age; 
    double math;
    double english;
};

bool initFiles(std::fstream &fileIn);
void printSV(std::fstream &fileIn);
void addSV(std::fstream &fileIn);

int main(){
    std::fstream fileIn;
    if(!initFiles(fileIn)){
        std::cerr << "Error: Could not open file" << std::endl;
        return 1;
    }
    while(true){
        std::cout << "-------------------SINH VIEN ADMINISTRATION--------------------------\n";
        std::cout << "---------------------------------------------------------------------\n";
        std::cout << "|     MENU    |\n";
        std::cout << "---------------\n";
        std::cout << "1.IN DANH SACH SINH VIEN\n";
        std::cout << "2.THEM SINH VIEN\n";
        std::cout << "10. Thoat chuong trinh\n";

        int choice; 
        std::cout << "Nhap lua chon cua ban: ";
        std::cin >> choice;
        std::cin.ignore();
        switch(choice){
            case 1:
                printSV(fileIn);
                break;
            case 2:
                addSV(fileIn);
                break;
            case 10:
                fileIn.close();
                return 0;
        }
    }    
    return 0;
}

bool initFiles(std::fstream &fileIn){
    fileIn.open("input.txt", std::ios_base::in | std::ios_base::out | std::ios_base::app);
    if(fileIn.fail()){
        return false;
    }
    return true;
}

void printSV(std::fstream &fileIn){
    Sinhvien sv;
    fileIn.clear();
    fileIn.seekg(0);
    std::cout << "------------------------------------------------------------------" << std::endl;
    while(getline(fileIn, sv.name, '\t')){
        if(!(fileIn >> sv.age >> sv.math >> sv.english)){
            std::cerr << "Error reading from file" << std::endl;
            continue;
        }
        fileIn.ignore();
        std::cout << sv.name << " " << sv.age << " " << sv.math << " " << sv.english << std::endl;
    }
    std::cout <<"------------------------------------------------------------------" << std::endl;
}

void addSV(std::fstream &fileIn){
    Sinhvien sv;
    while(true){
        std::cout << "----------THEM SINH VIEN---------\n";

        std::cout << "Nhap ten Sinh vien: "; 
        getline(std::cin, sv.name); 

        std::cout << "Nhap tuoi: "; 
        std::cin >> sv.age; 
        std::cin.ignore();

        std::cout << "Nhap diem Toan: "; 
        std::cin >> sv.math; 
        std::cin.ignore();

        std::cout << "Nhap diem Tieng Anh: "; 
        std::cin >> sv.english; 
        std::cin.ignore();
        fileIn << sv.name << '\t' << sv.age << '\t' << sv.math << '\t' << sv.english << std::endl;
        if (fileIn.good()) {
            std::cout << "The file is open and ready for input/output operations." << std::endl;
        } else {
            std::cerr << "An error occurred when opening the file." << std::endl;
        }

        std::cout << "----Y: Tiep tuc / N: Thoat chuong trinh----\n";
        char programEnd;
        std::cin >> programEnd;
        if(programEnd=='N' || programEnd == 'n'){
            std::cout << "Ket thuc chuong trinh\n";
            std::cout << "----------------------------------" << std::endl;
            break;
        }
    }
}
